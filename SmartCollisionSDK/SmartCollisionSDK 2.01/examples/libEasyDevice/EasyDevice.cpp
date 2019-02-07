/** @file
 *  @brief This file is implimentaion of class EasyDevice.
 */
#include "EasyDevice.h"
#include <windows.h>
#include <stdio.h>

#ifdef USE_PHANTOM
#include "EPhantom.h"
#else
#include "EMouse.h"
#endif

static const BReal defaultscale=1.0;
static MMRESULT				TimerId;
static CRITICAL_SECTION		hapticCriticalSection;
static CRITICAL_SECTION		collisionCriticalSection;

/************************************* class EasyDevice::Impl *******************************/

/** @brief Default Constructor
 */
EasyDevice::Impl::Impl()
{
	origin_=0;
	scale_.x=defaultscale;
	scale_.y=defaultscale;
	scale_.z=defaultscale;
    
    fixQuaternion.Identity();
    centerOrientation.Identity();
    averageFlag=1;
    averageCount=10;
    averageType=0;
    positions.Create(averageCount);
    orientations.Create(averageCount);
    orientation_.Identity();
    position_=0;
    hapticFrequency=1000;
    forceMax=10;
}

/** @brief Destructor
 */
EasyDevice::Impl::~Impl()
{}

bool EasyDevice::Impl::Start(void)
{
    positions.Reset();
    orientations.Reset();
    positions.Resize(averageCount);
    orientations.Resize(averageCount);
    return Initialize();
}

void
EasyDevice::Impl::GetFixedOrientation(BQuaternion&q)
{
    BQuaternion t;
    GetDeviceOrientation(q);
    t=centerOrientation;
    t.Invert();
    q*=t;
    q.Normalize();
}
static int Average(BVector3&t,BVector3*v,int n,
                   int type,
                   BReal width)
{
    BReal a;
    t=0;
    int i;
    if(type==0) {
        for(i=0;i<n;i++)
          t+=v[i];
        a=(BReal)n;
        t*=(BReal)1.0/a;
    } else if(type==1) {
        a=0.0;
        for(i=0;i<n;i++) {
            BReal w=(BReal)(i+1);
            t+=w*v[i];
            a+=w;
        }
        t*=(BReal)1.0/a;
    } else if(type==2) {
        for(i=0;i<n;i++)
          t+=v[i];
        a=(BReal)n;
        t*=(BReal)1.0/a;
        BVector3 t0;
        t0=t;
        t=(BReal)0;
        a=(BReal)0;
        for(i=0;i<n;i++) {
            BVector3 u;
            u=v[i]-t0;
            if(u.Norm()>width)
              continue;
            t+=v[i];
            a+=1.0;
        }
        if(a==0) {
            t=t0;
        } else {
            t*=(BReal)1.0/a;
        }
    } else {
        return -1;
    }
    return 0;
}

void
EasyDevice::Impl::GetPosition(BVector3&position)
{
    BVector3 p;
    GetDevicePosition(p);
    if(averageFlag) {
        positions.Append(p);
        Average(p,positions.Front(),positions.Size(),
                averageType,2.0);
    }
    position=p;
}

void
EasyDevice::Impl::GetOrientation(BQuaternion&q)
{
    GetFixedOrientation(q);
    q*=fixQuaternion;
    q.Normalize();
    if(averageFlag) {
        orientations.Append(orientation);
        int i;
        BVector3 a,t;
        a=0;
        for(i=0;i<orientations.Size();i++) {
            orientations[i].GetRotation(t);
            a+=t;
        }
        a*=(BReal)1.0/orientations.Size();
        orientation.SetRotation(a);
    }
    orientation=q;
}

void
EasyDevice::Impl::SetOrientation(const BQuaternion&q)
{
    BQuaternion t;
    fixQuaternion.Invert();
    t=orientation;
    t*=fixQuaternion;
    fixQuaternion=t;

    fixQuaternion.Invert();
    fixQuaternion*=q;
    fixQuaternion.Normalize();

    orientations.Reset();
    t=q;
    orientations.Append(t);
}

void
EasyDevice::Impl::SetForce(BVector3&t)
{
    return;
}

void
EasyDevice::Impl::SetTorque(BVector3&t)
{
    return;
}

int
EasyDevice::Impl::GetButton(int n)
{
    return 0;
}

void
EasyDevice::Impl::WaitForUserAdmit()
{
    return;
}

void
EasyDevice::Impl::MouseFunction(int button,int state, int x, int y)
{
    return;
}

void
EasyDevice::Impl::MotionFunction(int x, int y)
{
    return;
}

void
EasyDevice::Impl::ReshapeFunction(int w, int h)
{
    return;
}

void 
EasyDevice::Impl::SetScale(BReal s)
{
	scale_.x=s;
	scale_.y=s;
	scale_.z=s;

	return;
}

void 
EasyDevice::Impl::EnterHapticThread(void)
{
	EnterCriticalSection(&hapticCriticalSection);
}

void
EasyDevice::Impl::LeaveHapticThread(void)
{
	LeaveCriticalSection(&hapticCriticalSection);
}

void 
EasyDevice::Impl::EnterCollisionThread(void)
{
	EnterCriticalSection(&collisionCriticalSection);
}

void
EasyDevice::Impl::LeaveCollisionThread(void)
{
	LeaveCriticalSection(&collisionCriticalSection);
}

/************************************* class EasyDevice *************************************/
EasyDevice::EasyDevice(void)
{
#ifdef USE_PHANTOM
    impl_ = new EPhantom();
#else

    impl_ = new EMouse();
#endif

    matrix = new CoordinateMatrix();
    matrix->SetIdentity();
    collisionFrequency=1000;
    runFlag=0;
    callBackClFunction=0;
}

EasyDevice::~EasyDevice(void)
{
    delete matrix;
    delete impl_;
}

bool
EasyDevice::Start(void)
{
	InitializeCriticalSection(&hapticCriticalSection);
    InitializeCriticalSection(&collisionCriticalSection);
    runFlag=1;
    bool status=impl_->Start();
    if(status==false)
      return false;
    Initialize();
    return status;
}

bool
EasyDevice::Stop(void)
{
    if(!runFlag)
      return false;
    timeKillEvent(TimerId);
    bool result;
    result=impl_->Stop();
    runFlag=0;
	Sleep(10);
    DeleteCriticalSection(&collisionCriticalSection);
	DeleteCriticalSection(&hapticCriticalSection);
    return result;
}

void
EasyDevice::SetForce(const float force[3])
{
    BVector3 t,u;
    t=force;
    matrix->Rotate(u,t);
    impl_->SetForce(u);
    return;
}

void
EasyDevice::SetForce(const double force[3])
{
    BVector3 t,u;
    t=force;
    matrix->Rotate(u,t);
    impl_->SetForce(u);
    return;
}

void
EasyDevice::SetTorque(const float torque[3])
{
    BVector3 t,u;
    t=torque;
    matrix->Rotate(u,t);
    impl_->SetTorque(u);
    return;
}

void
EasyDevice::SetTorque(const double torque[3])
{
    BVector3 t,u;
    t=torque;
    matrix->Rotate(u,t);
    impl_->SetTorque(u);
    return;
}

void
EasyDevice::SetScale(float scale)
{
    impl_->SetScale(scale);
    return;
}

void
EasyDevice::SetScale(double scale)
{
    impl_->SetScale(static_cast<BReal>(scale));
    return;
}

void
EasyDevice::SetOrientation(const float orientation[4])
{
    BQuaternion t,u;
    t=orientation;
    t.Normalize();
    matrix->Rotate(u,t);
    impl_->SetOrientation(u);
    return;
}

void
EasyDevice::SetOrientation(const double orientation[4])
{
    BQuaternion t,u,v;
    t=orientation;
    t.Normalize();
    matrix->Rotate(u,t);
    impl_->SetOrientation(u);
    return;
}

void
EasyDevice::ResetOrientation(void)
{
    impl_->fixQuaternion.Identity();
}

void
EasyDevice::GetPosition(float position[3])
{
    BVector3 t,u;
    impl_->GetPosition(t);
    matrix->InverseConvert(u,t);
    u.GetValue(position);

    return;
}

void
EasyDevice::GetPosition(double position[3])
{
    BVector3 t,u;
    impl_->GetPosition(t);
    matrix->InverseConvert(u,t);
    u.GetValue(position);
    return;
}

void
EasyDevice::GetOrientation(float orientation[4])
{
    BQuaternion t,u;
    impl_->GetOrientation(t);
    matrix->InverseRotate(u,t);
    u.GetValue(orientation);
    return;
}

void
EasyDevice::GetOrientation(double orientation[4])
{
    BQuaternion t,u;
    impl_->GetOrientation(t);
    matrix->InverseRotate(u,t);
    u.GetValue(orientation);
    return;
}

void
EasyDevice::GetLastMatrix(float m[16])
{
    BVector3 p,p0;
    BQuaternion q,q0;
    impl_->GetLastPosition(p0);
    impl_->GetLastOrientation(q0);
    matrix->InverseConvert(p,p0);
    matrix->InverseRotate(q,q0);
    CoordinateMatrix c;
    c.Set(p,q);
    c.GetGLMatrix(m);
    return;
}

void
EasyDevice::GetLastMatrix(double m[16])
{
    BVector3 p,p0;
    BQuaternion q,q0;
    impl_->GetLastPosition(p0);
    impl_->GetLastOrientation(q0);
    matrix->InverseConvert(p,p0);
    matrix->InverseRotate(q,q0);
    CoordinateMatrix c;
    c.Set(p,q);
    c.GetGLMatrix(m);
    return;
}

void
EasyDevice::GetLastRawMatrix(float m[16])
{
    BVector3 p;
    BQuaternion q;
    impl_->GetLastPosition(p);
    impl_->GetLastOrientation(q);
    BQuaternion t;
    t=impl_->fixQuaternion;
    t.Invert();
    q*=t;
    q.Normalize();
    CoordinateMatrix c;
    c.Set(p,q);
    c.GetGLMatrix(m);
    return;
}

void
EasyDevice::GetLastRawMatrix(double m[16])
{
    BVector3 p;
    BQuaternion q;
    impl_->GetLastDevicePosition(p);
    impl_->GetLastDeviceOrientation(q);
    CoordinateMatrix c;
    c.Set(p,q);
    c.GetGLMatrix(m);
    return;
}

void
EasyDevice::SetHapticFunction(void(*hpfunction)(void*),void*userData,double frequency)
{
    hapticsUserData=userData;
    hapticFrequency=frequency;
    impl_->SetCallBackHpFunction(hpfunction,userData,(BReal)frequency);
    return;
}

void
EasyDevice::SetCollisionFunction(void(*clFunction)(void*),void*userData,double frequency)
{
    EnterCollisionThread();
    collisionUserData=userData;
    callBackClFunction=clFunction;
    collisionFrequency=frequency;
    LeaveCollisionThread();
    return;
}

void
EasyDevice::SetHapticStatusFunction(void(*function)(void*),void*userData)
{

    if(runFlag){
      impl_->SetCallBackStFunction(function,userData);
    }
    return;
}

void
EasyDevice::SetCollisionStatusFunction(void(*function)(void*),void*userData)
{
    if(runFlag){
        EnterCollisionThread();
        function(userData);
        LeaveCollisionThread();
    }
    return;
}

void
EasyDevice::SetKeyboardFunction(void(*kbfunction)(unsigned char,int,void*),
                                unsigned char key,int status,void*userData)
{
    impl_->SetKeyboardFunction(kbfunction, key, status,userData);
    return;
}


void
EasyDevice::MouseFunction(int button,int state, int x, int y)
{
    impl_->MouseFunction(button,state,x,y);
    return;
}

void
EasyDevice::MotionFunction(int x, int y)
{
    impl_->MotionFunction(x,y);
    return;
}

void
EasyDevice::ReshapeFunction(int w, int h)
{
    impl_->ReshapeFunction(w,h);
    return;
}

int
EasyDevice::GetButton(int n)
{
    if(!runFlag)
      return 0;
    return impl_->GetButton(n);
}

void
EasyDevice::EnterCollisionThread(void)
{
    if(!runFlag)return;
    if(callBackClFunction)impl_->EnterCollisionThread();
}

void
EasyDevice::LeaveCollisionThread(void)
{
    if(!runFlag)return;
    if(callBackClFunction)impl_->LeaveCollisionThread();
}

void
EasyDevice::EnterHapticThread(void)
{
    if(!runFlag)
      return;
    impl_->EnterHapticThread();
}

void
EasyDevice::LeaveHapticThread(void)
{
    if(!runFlag)
      return;
    impl_->LeaveHapticThread();
}

void
EasyDevice::CallBackClFunction(void)
{
    EnterCollisionThread();
    if(callBackClFunction)
      callBackClFunction(collisionUserData);
    LeaveCollisionThread();
    return;
}

void
EasyDevice::WaitForUserAdmit()
{
    impl_->WaitForUserAdmit();
    return;
}

void CALLBACK mm_collision_func(UINT uiID, UINT uiNo, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    EasyDevice* t = reinterpret_cast<EasyDevice*>(dwUser);
    if(t){
        t->CallBackClFunction();
        TimerId=timeSetEvent(1.0,
                             1,mm_collision_func,
                             (DWORD)t,
                             //TIME_PERIODIC|
                             TIME_ONESHOT|
                             TIME_CALLBACK_FUNCTION);
    }
    return;
}

void
EasyDevice::Initialize(void)
{
    InitializeCriticalSection(&collisionCriticalSection);
    BReal t=(BReal)1000.0f/(BReal)collisionFrequency;
    if(t<1)t=1;
    if(callBackClFunction){
        TimerId=timeSetEvent(static_cast<UINT>(t),
                             1,mm_collision_func,
                             (DWORD)this,
                             //TIME_PERIODIC|
                             TIME_ONESHOT|
                             TIME_CALLBACK_FUNCTION);
    }

}

void
EasyDevice::SetMatrix(const double m[16])
{
    matrix->SetGLMatrix(m);
}

void
EasyDevice::SetMatrix(const float m[16])
{
    matrix->SetGLMatrix(m);
}

void
EasyDevice::GetMatrix(double m[16])const
{
    matrix->GetGLMatrix(m);
}

void
EasyDevice::GetMatrix(float m[16])const
{
    matrix->GetGLMatrix(m);
}
