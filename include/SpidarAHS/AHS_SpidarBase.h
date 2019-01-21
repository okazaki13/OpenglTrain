/** @file
	@JP
		@brief CAHSFunction ÉNÉâÉXíËã`
		@author ê‘âH çéêm
	@END_JP
	@EN
		@brief CAHSFunction Class interface
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/1/15
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/

#pragma once
#include "spidarahs.h"
#include "../include/SpidarAPI/AHSVector.h"
#include "../include/SpidarAPI/AHSQuaternion.h"

#include <stdio.h>
#include <string>

template<class T>
class SPIDARAHS_API AHS_SpidarBase //:public CSpidarAHS
{
protected:
	void* pSpidar;

public:
	AHS_SpidarBase(void);
	virtual ~AHS_SpidarBase(void);

public:	// for state
	virtual int Init			(std::string xmlFileName, int usb_id = -1) = 0;
	virtual void StartHapticLoop();
	virtual void Active			(int isActive, int spidar_id = -1 );
	virtual void Calib			(int spidar_id = -1 );
	virtual void StopHapticLoop	();
	virtual void Quit			();

public: // for Impedance
	virtual CAHSVector3<T>		GetImpPos	(int spidar_id = 0);
	virtual CAHSQuaternion<T>	GetImpOri	(int spidar_id = 0);
	virtual void				SetImpForce	(CAHSVector3<T>& f,	int spidar_id = -1);
	virtual void				SetImpTorque(CAHSVector3<T>& t,	int spidar_id = -1);

public:	// for Admittance
	virtual CAHSVector3<T>		GetAdmForce	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetAdmTorque(int spidar_id = 0);
	virtual void				SetAdmPos	(CAHSVector3<T>&     pos,	int spidar_id = -1);
	virtual void				SetAdmOri	(CAHSQuaternion<T>&  ori,	int spidar_id = -1);

public: // switch
	virtual int		GetDigitalSw(int ch,	int spidar_id = 0);
	virtual T		GetAnalogSw	(int ch,	int spidar_id = 0);

public:
//	void SetHapticLoopCallBackFunction( void (CALLBACK *pf)(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2) );
	void SetHapticLoopCallBackFunction( void (CALLBACK *pf)(DWORD dwUser) );
};
