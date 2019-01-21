#pragma once
#include "SpidarAHS.h"

SPIDARAHS_API SPIDAR_HANDLE ahsCreate_SpidarG_D(char* xmlFileName, int usb_id = -1);
SPIDARAHS_API SPIDAR_HANDLE ahsCreate_Spidar4_D(char* xmlFileName, int usb_id = -1);
SPIDARAHS_API SPIDAR_HANDLE ahsCreate_SpidarX_D(char* xmlFileName, int usb_id = -1);

SPIDARAHS_API void ahsStartHapticLoop_D(SPIDAR_HANDLE pAHS);
SPIDARAHS_API void ahsActive_D         (SPIDAR_HANDLE pAHS,int isActive,   int spidar_id = -1);
SPIDARAHS_API void ahsCalib_D          (SPIDAR_HANDLE pAHS,                int spidar_id = -1);
SPIDARAHS_API void ahsStopHapticLoop_D (SPIDAR_HANDLE pAHS);
SPIDARAHS_API SPIDAR_HANDLE ahsQuit_D  (SPIDAR_HANDLE pAHS);

SPIDARAHS_API void ahsGetImpPos_D      (SPIDAR_HANDLE pAHS,double pos[3],   int spidar_id =  0);
SPIDARAHS_API void ahsGetImpOri_wxyz_D (SPIDAR_HANDLE pAHS,double ori[4],   int spidar_id =  0);
//SPIDARAHS_API void ahsGetImpOri_xyzw_D (SPIDAR_HANDLE pAHS,double ori[4],   int spidar_id =  0);
SPIDARAHS_API void ahsSetImpForce_D    (SPIDAR_HANDLE pAHS,double force[3] ,int spidar_id = -1);
SPIDARAHS_API void ahsSetImpTorque_D   (SPIDAR_HANDLE pAHS,double torque[3],int spidar_id = -1);

SPIDARAHS_API void ahsGetAdmForce_D    (SPIDAR_HANDLE pAHS,double force[3], int spidar_id =  0);
SPIDARAHS_API void ahsGetAdmTorque_D   (SPIDAR_HANDLE pAHS,double torque[3],int spidar_id =  0);
SPIDARAHS_API void ahsSetAdmPos_D      (SPIDAR_HANDLE pAHS,double pos[3],   int spidar_id = -1);
SPIDARAHS_API void ahsSetAdmOri_wxyz_D (SPIDAR_HANDLE pAHS,double ori[4],   int spidar_id = -1);
//SPIDARAHS_API void ahsSetAdmOri_xyzw_D (SPIDAR_HANDLE pAHS,double ori[4],   int spidar_id = -1);

SPIDARAHS_API int   ahsGetDigitalSw_D  (SPIDAR_HANDLE pAHS,int ch,         int spidar_id =  0);
SPIDARAHS_API double ahsGetAnalogSw_D   (SPIDAR_HANDLE pAHS,int ch,         int spidar_id =  0);

//SPIDARAHS_API void ahsSetHapticLoopCallBackFunction_D(SPIDAR_HANDLE pAHS,  void (CALLBACK *pf)(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2) );
SPIDARAHS_API void ahsSetHapticLoopCallBackFunction_D(SPIDAR_HANDLE pAHS,  void (CALLBACK *pf)(DWORD dwUser) );

