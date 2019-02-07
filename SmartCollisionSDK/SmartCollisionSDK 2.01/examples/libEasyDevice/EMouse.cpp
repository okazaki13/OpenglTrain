/** @file
 *  @brief This file is implimentaion of class EMouse.
 */
#include "EMouse.h"
#include <windows.h>

#define HDM_LEFT_BUTTON   1
#define HDM_RIGHT_BUTTON  2
#define HDM_MIDDLE_BUTTON 3
#define HDM_DOWN 11
#define HDM_UP   12

static const BReal frequency=1000;

static MMRESULT TimerId;

static void CALLBACK mm_timer_func(UINT uiID, UINT uiNo, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	EMouse* me = reinterpret_cast<EMouse*>(dwUser);
	if(me)
		me->CallBackHpFunction();

	return;
}

EMouse::EMouse()
{
	center_=0;

	initFlag_=0;

	objectManipulator.Initialize();
    objectManipulator.SetOrientation(orientation_);
}

EMouse::~EMouse()
{
}

void 
EMouse::_GetOrientation(BQuaternion&q)
{
	objectManipulator.GetOrientation(q);
}

void 
EMouse::GetDevicePosition(BVector3&p)
{
	BVector3 p0;
	objectManipulator.GetPosition(p0);

	p.x=p0.x-center_.x;
	p.y=p0.y-center_.y;
	p.z=p0.z-center_.z;

	Convert(p);

	//position=p;
	position_=p;

	return;
}

void 
EMouse::GetDeviceOrientation(BQuaternion& q)
{
	BQuaternion t;
	q.Identity();
    _GetOrientation(t);
	q=t;
	{
		CoordinateMatrix t;
		BVector3 ex,ey,ez;
		ex.Set(1,0,0);
		ey.Set(0,1,0);
		ez.Set(0,0,1);
		BVector3 fx,fy,fz;
		t.Set(q);
		t.Convert(fx,ex);
		t.Convert(fy,ey);
		t.Convert(fz,ez);

		ex=fx;ey=fy;ez=fz;
		BReal m[9];
		m[0]=ex.x;m[3]=ex.y;m[6]=ex.z;
		m[1]=ey.x;m[4]=ey.y;m[7]=ey.z;
		m[2]=ez.x;m[5]=ez.y;m[8]=ez.z;
		q.SetMatrix0(m);
	}
	q.Normalize();
	//orientation=q;
	orientation_=q;

	return;
}

bool 
EMouse::Initialize(void)
{
	initFlag_=1;
	BReal t=1000.0f/frequency;
	if(t<1)
		t=1;
	TimerId=timeSetEvent(static_cast<UINT>(t),
				1,mm_timer_func,
				(DWORD)this,
				TIME_PERIODIC|TIME_CALLBACK_FUNCTION);

	return true;
}

bool 
EMouse::Stop(void)
{
	initFlag_=0;
	timeKillEvent(TimerId);
	return true;
}

void
EMouse::CallBackHpFunction(void)
{
	if(!initFlag_)return;

	EnterHapticThread();
	if(callBackHpFunction)callBackHpFunction(hapticUserData);
	LeaveHapticThread();

	return;
}

void
EMouse::CallBackStFunction(void)
{
	if(callBackStFunction)
		callBackStFunction(hsfUserData);

	return;
}

void
EMouse::CallBackKbFunction(void)
{
	if(callBackKbFunction){
		callBackKbFunction(key_,status,keyboardUserData);
	}
	return;
}

void 
EMouse::SetCallBackHpFunction(void(*hp)(void*),void*userData,BReal frequency)
{
	callBackHpFunction=hp;
    hapticUserData=userData;
	return;
}

void 
EMouse::SetCallBackStFunction(void(*st)(void*),void*userData)
{
	EnterHapticThread();
	st(userData);
	LeaveHapticThread();

	return;
}

void 
EMouse::SetKeyboardFunction(void(*kb)(unsigned char,int,void*), unsigned char key,int status,void*userData)
{
    EnterCollisionThread();
	EnterHapticThread();
	kb(key,status,userData);
	LeaveHapticThread();
    LeaveCollisionThread();

	return;
}

void 
EMouse::MouseFunction(int button,int state, int x, int y)
{
	ObjectManipulator* o = &objectManipulator;

	if(o==0)
		return;
	if(button==HDM_LEFT_BUTTON)
	{
		if(state==HDM_DOWN)
			o->OnLeftButtonDown(x,y);
		else if(state==HDM_UP)
			o->OnLeftButtonUp(x,y);
	}
	else if(button==HDM_RIGHT_BUTTON)
	{
		if(state==HDM_DOWN)
			o->OnRightButtonDown(x,y);
		else if(state==HDM_UP)
			o->OnRightButtonUp(x,y);
	}
	else if(button==HDM_MIDDLE_BUTTON)
	{
		if(state==HDM_DOWN)
			o->OnMiddleButtonDown(x,y);
		else if(state==HDM_UP)
			o->OnMiddleButtonUp(x,y);
	}

	return;
}

void 
EMouse::MotionFunction(int x, int y)
{
	ObjectManipulator* o = &objectManipulator;

	if(o==0)
		return;
	o->OnMouseMove(x,y);

	return;
}

void 
EMouse::ReshapeFunction(int w, int h)
{
	ObjectManipulator*o = &objectManipulator;

	if(o==0)
		return;
	o->OnSize(w,h);

	return;
}

