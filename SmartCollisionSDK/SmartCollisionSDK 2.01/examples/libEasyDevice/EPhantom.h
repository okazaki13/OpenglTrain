#ifndef _EPHANTOM_H_
#define _EPHANTOM_H_

/** @file
 *  @brief This file is Definition of Class EPhantom.
 */
#include "EasyDeviceImpl.h"

class EPhantom : public EasyDevice::Impl
{
  private:
    BVector3 center_;
    int last_state_;

  public:
    EPhantom();
    ~EPhantom();

    void SetForce(BVector3&t);
    void SetTorque(BVector3&t);
    int  GetButton(int n);
    void WaitForUserAdmit();

    void CallBackHpFunction(void);
    void CallBackStFunction(void);
    void CallBackKbFunction(void);

    void GetDevicePosition(BVector3&position);
    void GetDeviceOrientation(BQuaternion&orientation);

    bool Initialize(void);
    bool Stop(void);

    void SetCallBackHpFunction(void(*hp)(void*),void*userData,BReal frequency);
    void SetCallBackStFunction(void(*st)(void*),void*userData);
    void SetKeyboardFunction(void(*kb)(unsigned char,int,void*),
                             unsigned char key,int status,void*);
};

#endif
