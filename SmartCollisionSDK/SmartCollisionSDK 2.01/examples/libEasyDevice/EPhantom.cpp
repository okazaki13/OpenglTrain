/** @file
 *  @brief This file is implimentaion of class EPhantom.
 */
#include "EPhantom.h"
#include <HD/hd.h>
#include <stdio.h>
#include <float.h>
#include <windows.h>

static HHD					ghHD = HD_INVALID_HANDLE;
static HDSchedulerHandle	gSchedulerCallback = HD_INVALID_HANDLE;
int DoCalibration(void);

HDCallbackCode HDCALLBACK CallBackFunctionHaptics(void *data)
{
    EPhantom* me = reinterpret_cast<EPhantom*>(data);

    HHD hHD;
    if( hHD= hdGetCurrentDevice() == HD_INVALID_HANDLE )
      printf("HD_INVALID_HANDLE\n");
    //From here(force frame)
    hdBeginFrame(hHD);
    me->CallBackHpFunction();
    hdEndFrame(hHD);
    //end(force frame)
    HDErrorInfo error;
    if (HD_DEVICE_ERROR(error = hdGetError()))
      return HD_CALLBACK_DONE;

    return HD_CALLBACK_CONTINUE;
}


EPhantom::EPhantom()
{
    center_=0;
    last_state_=0;
}

EPhantom::~EPhantom()
{
}

void
EPhantom::SetForce(BVector3&t)
{
    BVector3 u;
    u.Set(t.x,t.y,t.z);
    BReal a;a=u.Norm();
    if(a>forceMax)u*=forceMax/a;

    HDdouble phantomForce[3];
    phantomForce[0]=u.x;
    phantomForce[1]=u.y;
    phantomForce[2]=u.z;
    hdSetDoublev(HD_CURRENT_FORCE, phantomForce);
    return;
}

void
EPhantom::SetTorque(BVector3&t)
{
    HDdouble phantomForce[3];
    phantomForce[0]=t.x;
    phantomForce[1]=t.y;
    phantomForce[2]=t.z;
    hdSetDoublev(HD_CURRENT_TORQUE, phantomForce);

    return;
}

void
EPhantom::GetDevicePosition(BVector3& p)
{
    int i=0;
    HDdouble phantomPos[3];
    for(;;){
        hdGetDoublev(HD_CURRENT_POSITION, phantomPos);
        p.x=static_cast<BReal>(phantomPos[0])-center_.x;
        p.y=static_cast<BReal>(phantomPos[1])-center_.y;
        p.z=static_cast<BReal>(phantomPos[2])-center_.z;
        if(!(_isnan(p.x)||_isnan(p.y)||_isnan(p.z)))break;
        printf("EPhantom::GetPosition nan\n");
    }
    Convert(p);
    position_=p;
    return;
}

void
EPhantom::GetDeviceOrientation(BQuaternion&q)
{
    double t[16];
    hdGetDoublev(HD_CURRENT_TRANSFORM,t);
    q.SetGLMatrix(t);
    orientation_=q;
    return;
}

int
EPhantom::GetButton(int n)
{
    int current_state, return_val;
    static int button[4]={	HD_DEVICE_BUTTON_1,HD_DEVICE_BUTTON_2,
        HD_DEVICE_BUTTON_3,HD_DEVICE_BUTTON_4};
    hdGetIntegerv(HD_CURRENT_BUTTONS, &current_state);

    if( (last_state_&button[n]) !=(current_state&button[n]) ){
        if(current_state&button[n]){
            return_val = EH_BUTTON_DOWN;

        }else{
            return_val = EH_BUTTON_UP;
        }
    }else{
        if(current_state&button[n]){
            return_val = EH_BUTTON_ON;
        }else{
            return_val = EH_BUTTON_OFF;
        }
    }
    last_state_ = current_state;

    return return_val;
}

bool
EPhantom::Initialize(void)
{
    if(DoCalibration()!=0)
      return false;

    HDErrorInfo error;
    ghHD = hdInitDevice(HD_DEFAULT_DEVICE);
    if (HD_DEVICE_ERROR(error = hdGetError())){
        fprintf(stderr, "Failed to initialize haptic device. \n Press any key to quit.\n");
        getchar();
        return false;
    }

    hdEnable(HD_FORCE_OUTPUT);
    hdEnable(HD_MAX_FORCE_CLAMPING);

    //Start Scheduler
    hdStartScheduler();
    if (HD_DEVICE_ERROR(error = hdGetError())){
        fprintf(stderr, "Failed to start scheduler. \n Press any key to quit.\n");
        getchar();
        return false;
    }
    gSchedulerCallback = hdScheduleAsynchronous(CallBackFunctionHaptics,
                                                this,
                                                HD_MAX_SCHEDULER_PRIORITY);
    return true;
}

bool
EPhantom::Stop(void)
{
    EnterHapticThread();
    hdDisable(HD_FORCE_OUTPUT);
    hdDisable(HD_MAX_FORCE_CLAMPING);
    //Stop Scheduler
    hdStopScheduler();
    hdUnschedule(gSchedulerCallback);
    hdDisableDevice(hdGetCurrentDevice());

    LeaveHapticThread();
    return true;
}

void
EPhantom::CallBackHpFunction(void)
{
    EnterHapticThread();
    if(callBackHpFunction)callBackHpFunction(hapticUserData);
    LeaveHapticThread();

    return;
}

void
EPhantom::CallBackStFunction(void)
{
    if(callBackStFunction)
      callBackStFunction(hsfUserData);

    return;
}

void
EPhantom::CallBackKbFunction(void)
{
    if(callBackKbFunction){
        callBackKbFunction(key_,status,keyboardUserData);
    }
    return;
}

void
EPhantom::SetCallBackHpFunction(void(*hp)(void*),void*userData,BReal frequency)
{
    callBackHpFunction=hp;
    hapticUserData=userData;
    return;
}

HDCallbackCode HDCALLBACK StateCallback(void *pUserData)
{
    EPhantom* me = reinterpret_cast<EPhantom*>(pUserData);
    me->CallBackStFunction();

    /* execute this only once. */
    return HD_CALLBACK_DONE;
}

void
EPhantom::SetCallBackStFunction(void(*st)(void*),void*userData)
{
    callBackStFunction=st;
    hsfUserData=userData;
#if 1
	EnterHapticThread();
    StateCallback(this);
	LeaveHapticThread();
#else
    hdScheduleSynchronous(StateCallback,
                          this, HD_MIN_SCHEDULER_PRIORITY);
#endif
    return;
}

HDCallbackCode HDCALLBACK KeyCallback(void *pUserData)
{
    EPhantom* me = reinterpret_cast<EPhantom*>(pUserData);
    me->CallBackKbFunction();

    /* execute this only once. */
    return HD_CALLBACK_DONE;
}

void
EPhantom::SetKeyboardFunction(void(*kb)(unsigned char,int,void*),
                              unsigned char key,int status,void*pUserData)
{
    EnterCollisionThread();
	EnterHapticThread();
	kb(key,status,pUserData);
	LeaveHapticThread();
    LeaveCollisionThread();
    return;
}

void
EPhantom::WaitForUserAdmit()
{
    printf("Hold the haptic device handle in the neutral position.\n");
    printf("Press enter to continue\n");
    char s[100];
    fgets(s,100,stdin);

    return;
}
