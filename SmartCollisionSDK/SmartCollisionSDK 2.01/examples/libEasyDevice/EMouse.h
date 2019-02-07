#ifndef _EHMOUSE_H_
#define _EHMOUSE_H_

/** @file
 *  @brief This file is Definition of Class EMouse.
 */
#include "EasyDeviceImpl.h"
#include "ObjectManipulator.h"

class EMouse : public EasyDevice::Impl
{
  private:
    BVector3 center_;
    BEnum initFlag_;
    ObjectManipulator	objectManipulator;
    void _GetOrientation(BQuaternion&q);
  public:
    EMouse();
    ~EMouse();

    void MouseFunction(int button,int state, int x, int y);
    void MotionFunction(int x, int y);
    void ReshapeFunction(int w, int h);

    void CallBackHpFunction(void);
    void CallBackStFunction(void);
    void CallBackKbFunction(void);

    //void SetOrientation(const BQuaternion&orientation);

    void GetDevicePosition(BVector3&position);
    void GetDeviceOrientation(BQuaternion&orientation);
    
    bool Initialize(void);
    bool Stop(void);

    void SetCallBackHpFunction(void(*hp)(void*),void*userData,BReal frequency);
    void SetCallBackStFunction(void(*st)(void*),void*userData);
    void SetKeyboardFunction(void(*kb)(unsigned char,int,void*), unsigned char key,int status,void*userData);
};

#endif