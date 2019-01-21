/** @file
	@JP
		@brief CSpidar8 class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CSpidar8 class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2011/02/17
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/


#pragma once
#include "spidarn.h"

//#include "spidarenhance.h"
//#include "AHSVector3.h"
#include "AHSQPProg.h"

#include "AHSVC6DOF.h"


/**
@JP
	CSpidar8 クラス
@END_JP
@EN
	CSpidar8 class
@END_EN
 */
template <class T>
class SPIDARAPI_API CSpidar8 :
	public CSpidarN<T>
{
protected:
	T border_force_gain[AHS_SPIDAR8_NUM];

protected:
	CAHSVector3<T>		pos_imp[AHS_SPIDAR8_NUM];
	CAHSVector3<T>		posVel_imp[AHS_SPIDAR8_NUM];
	CAHSVector3<T>		force_imp[AHS_SPIDAR8_NUM];
	CAHSVector3<T>		force_imp_comb[AHS_SPIDAR8_NUM];
protected:
	CAHSVector3<T>		pos_adm[AHS_SPIDAR8_NUM];
	CAHSVector3<T>		force_adm[AHS_SPIDAR8_NUM];

protected:
	CAHSVC6DOF<T>		m_vc[AHS_SPIDAR8_NUM];

protected:
	int m_controlType[AHS_SPIDAR8_NUM];

protected:
	CAHSQPProg<T,3> m_solver[AHS_SPIDAR8_NUM];
protected:
	CAHSVector<T,4> m_motor_face_f[AHS_SPIDAR8_NUM];//3つのモータの作る面の方程式の4元ベクトル

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
	CSpidar8(void);//コントローラ3台を使います
	virtual ~CSpidar8(void);
	virtual int Init			(std::string xmlFileName, int usb_id = -1);

	virtual void Calib			(int spidar_id = -1);
protected:// Init内で実行される
	virtual int MotorInfoSet	(std::string xmlFileName);

public:
	virtual CAHSVector3<T>		GetEnc		(int spidar_id = 0);

public: // for Impedance
	virtual CAHSVector3<T>		GetPos		(int spidar_id = 0);
	virtual void				SetForce	(CAHSVector3<T>& f,	int spidar_id = 0);
//	virtual CAHSVector3<T>		GetPosVel	(int spidar_id = 0);

public: // for Virtual Coupling in impedance control
	virtual CAHSVirtualCoupling<T>& GetVirtualCoupling(int spidar_id = 0);

public:	// for Admittance
	virtual CAHSVector3<T>		GetForce	(int spidar_id = 0);
//	virtual CAHSVector3<T>		GetTorque	(int spidar_id = 0);
//	virtual void				SetPos		(CAHSVector3<T>&     pos,	int spidar_id = -1);
//	virtual void				SetOri		(CAHSQuaternion<T>&  ori,	int spidar_id = -1);


protected:
	virtual void SpidarCalc		();
protected:
	void SpidarCalc_impedance_VIS();//virtual inverse sigma（疑似逆行列）
	void SpidarCalc_impedance_IS(); //inverse sigma（逆行列）
};


typedef CSpidar8<float>			CSpidar8F;
typedef CSpidar8<double>		CSpidar8D;
