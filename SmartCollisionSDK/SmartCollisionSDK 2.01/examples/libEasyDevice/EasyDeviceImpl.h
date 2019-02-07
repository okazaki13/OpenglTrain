#ifndef _EASYDEVICEIMPL_H_
#define _EASYDEVICEIMPL_H_

/** @file
 *  @brief This file is Definition of Class EasyDevice::Impl.
 *
 *  This is used for internal implimentation .
 */
#include "EasyDevice.h"
#include "BasicTypes.h"
#include "TemplateArray.h"

#define HAPTICS_BUTTON_DOWN 1
#define HAPTICS_BUTTON_UP   2
#define HAPTICS_BUTTON_ON   3
#define HAPTICS_BUTTON_OFF  0

class EasyDevice::Impl{
    friend EasyDevice;
protected:
    BVector3 origin_;
	BVector3 scale_;
    BVector3 position_;      // raw position of device
    BQuaternion orientation_;// raw orientation of device
	BVector3 position;
	BQuaternion orientation;
	BQuaternion centerOrientation;
	BQuaternion fixQuaternion;
    //
    int averageFlag;
    int averageCount;
    int averageType;
    BQueue<BVector3>positions;
    BQueue<BQuaternion>orientations;
    //
    BReal hapticFrequency;
    BReal forceMax;
    //
	void(*callBackHpFunction)(void*);
	void(*callBackStFunction)(void*);
	void(*callBackKbFunction)(unsigned char,int status,void*);
	void*keyboardUserData;
	void*hsfUserData;
	void*hapticUserData;
	unsigned char key_;
    int status;
    //
    void Convert(BVector3&t)
      {
          t.x=origin_.x+t.x*scale_.x;
          t.y=origin_.y+t.y*scale_.y;
          t.z=origin_.z+t.z*scale_.z;
      }
	void EnterHapticThread(void);
	void LeaveHapticThread(void);
	void EnterCollisionThread(void);
	void LeaveCollisionThread(void);
public:
	Impl(void);
	~Impl(void);

	bool Start(void);
	void GetPosition(BVector3&position);
	void GetFixedOrientation(BQuaternion&q);
	void GetOrientation(BQuaternion&q);
	void SetOrientation(const BQuaternion&q);
	void SetScale(BReal s);
    void GetLastPosition(BVector3&p)const{p=position;}
    void GetLastOrientation(BQuaternion&q)const{q=orientation;}
    void GetLastDevicePosition(BVector3&p)const{p=position_;}
    void GetLastDeviceOrientation(BQuaternion&q)const{q=orientation_;}

	virtual	void SetForce(BVector3&t);
	virtual	void SetTorque(BVector3&t);
	virtual	int  GetButton(int n);
	virtual	void WaitForUserAdmit();

	//mouse function
	virtual	void MouseFunction(int button,int state, int x, int y);
	virtual	void MotionFunction(int x, int y);
	virtual	void ReshapeFunction(int w, int h);

	virtual	void GetDevicePosition(BVector3&position)=0;
	virtual	void GetDeviceOrientation(BQuaternion&orientation)=0;

	virtual	bool Initialize(void)=0;
	virtual	bool Stop(void)=0;

	virtual	void SetCallBackHpFunction(void(*hp)(void*),void*userData,BReal frequency)=0;
	virtual	void SetCallBackStFunction(void(*st)(void*),void*userData)=0;
	virtual	void SetKeyboardFunction(void(*kb)(unsigned char,int,void*),
                                     unsigned char key, int status,void*userData)=0; 
};
#endif
