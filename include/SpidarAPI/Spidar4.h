/** @file
	@JP
		@brief Spidar API
		@author ê‘âH çéêm
	@END_JP
	@EN
		@brief Spidar API
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "spidarenhance.h"
#include "AHSVector3.h"
#include "AHSQPProg.h"
#include "AHSVC6DOF.h"


/**
@JP
	CSpidar4 ÉNÉâÉX
@END_JP
@EN
	CSpidar4 class
@END_EN
 */
template<class T>
class SPIDARAPI_API CSpidar4 :
	public CSpidarEnhance<T>
{
protected:
	CAHSVector3<T>		pos_imp[AHS_SPIDAR4_NUM];
	CAHSVector3<T>		posVel_imp[AHS_SPIDAR4_NUM];
	CAHSVector3<T>		force_imp[AHS_SPIDAR4_NUM];
	CAHSVector3<T>		force_imp_comb[AHS_SPIDAR4_NUM];

protected:
	CAHSVector3<T>		pos_adm[AHS_SPIDAR4_NUM];
	CAHSVector3<T>		force_adm[AHS_SPIDAR4_NUM];

protected:
	CAHSVC6DOF<T>		m_vc[AHS_SPIDAR4_NUM];

protected:
	int m_controlType[AHS_SPIDAR4_NUM];

protected:
	CAHSQPProg<T,4> m_solver[AHS_SPIDAR4_NUM];
protected:
	int Prepeat;
	T Psigma;
	T PposxN;

	int Qrepeat;
	T Qsigma;
	T Qlambda_f;

protected:
	T scalePosX;
	T scalePosY;
	T scalePosZ;

	T scaleForceX;
	T scaleForceY;
	T scaleForceZ;

public:
	CSpidar4(void);
	virtual ~CSpidar4(void);
	virtual int GetSpidarNum();

public:
	virtual void SetPrepeat(int n, int spidar_id = -1);
	virtual void SetPsigma(T sigma, int spidar_id = -1);
	virtual void SetPposxN(T val, int spidar_id = -1);

	virtual void SetQrepeat(int n, int spidar_id = -1);
	virtual void SetQsigma(T sigma, int spidar_id = -1);
	virtual void SetQlambdaF(T lambda, int spidar_id = -1);

	virtual void SetScalePosX(T scale, int spdiar_id = -1);
	virtual void SetScalePosY(T scale, int spdiar_id = -1);
	virtual void SetScalePosZ(T scale, int spdiar_id = -1);

	virtual void SetScaleForceX(T scale, int spdiar_id = -1);
	virtual void SetScaleForceY(T scale, int spdiar_id = -1);
	virtual void SetScaleForceZ(T scale, int spdiar_id = -1);

public:
	virtual int Init			(std::string xmlFileName, int usb_id = -1);
	virtual void Active			(int isActive, int spidar_id = -1 );
	virtual void Calib			(int spidar_id = -1);

protected:// Initì‡Ç≈é¿çsÇ≥ÇÍÇÈ
	virtual int MotorInfoSet	(std::string xmlFileName);

protected:// TimeFuncì‡Ç≈é¿çsÇ≥ÇÍÇÈ
	virtual void SpidarCalc		();


public: // for Impedance
	virtual CAHSVector3<T>		GetPos		(int spidar_id = 0);
	virtual void				SetForce	(CAHSVector3<T>& f,	int spidar_id = 0);
	virtual CAHSVector3<T>		GetPosVel	(int spidar_id = 0);
public: // for Virtual Coupling in impedance control
	virtual CAHSVirtualCoupling<T>& GetVirtualCoupling(int spidar_id = 0);


public:	// for Admittance
	virtual CAHSVector3<T>	GetForce	(int spidar_id = 0);
	virtual void			SetPos		(CAHSVector3<T>&     pos,	int spidar_id = 0);


public:
	virtual void SetControlType(int type,	int spidar_id = 0);

public:
	virtual void Disp		();
};

