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
#include "AHSVC6DOF.h"
#include "AHSVector3.h"
#include "AHSQPProg.h"


// IIRópÇÃèÛë‘ïœêîÅEéûíËêîÇäiî[
template<class T>
struct SPIDARAPI_API ST_IIR{
	T d1;
	T d2;
	T k;	// 0<k<1
};

/**
@JP
	CSpidarG ÉNÉâÉX
@END_JP
@EN
	CSpidarG class
@END_EN
 */
template<class T>
class SPIDARAPI_API CSpidarG :
	public CSpidarEnhance<T>
{
protected:
	CAHSVector3<T>		pos_imp;
	CAHSVector3<T>		posVel_imp;
	CAHSVector3<T>		oriVel_imp;
	CAHSVector3<T>		posVel_imp_iir;
	CAHSVector3<T>		oriVel_imp_iir;
	CAHSVector3<T>		posAcc_imp;
	CAHSVector3<T>		oriAcc_imp;
	CAHSQuaternion<T>	ori_imp;
	CAHSVector3<T>		force_imp;
	CAHSVector3<T>		torque_imp;
	CAHSVector3<T>		force_imp_comb;
	CAHSVector3<T>		torque_imp_comb;
private:
	ST_IIR<T> iirD[6];

protected:
	CAHSVector3<T>		pos_adm;
	CAHSQuaternion<T>	ori_adm;
	CAHSVector3<T>		posVel_adm;
	CAHSVector3<T>		oriVel_adm;
	CAHSVector3<T>		force_adm;
	CAHSVector3<T>		torque_adm;

protected:
	CAHSVirtualCoupling<T>*		m_pvc;

protected:
	int m_controlType;

protected:
	CAHSQPProg<T,8> m_solver;
protected:
	int Prepeat;
	T Psigma;
	T PposxN;
	T PorixN;

	int Qrepeat;
	T Qsigma;
	T Qlambda_f;
	T Qlambda_t;

public:
	CSpidarG(void);
	virtual ~CSpidarG(void);
	virtual int GetSpidarNum();

public:
	virtual void SetPrepeat(int n, int spidar_id = -1);
	virtual void SetPsigma(T sigma, int spidar_id = -1);
	virtual void SetPposxN(T val, int spidar_id = -1);
	virtual void SetPorixN(T val, int spidar_id = -1);

	virtual void SetQrepeat(int n, int spidar_id = -1);
	virtual void SetQsigma(T sigma, int spidar_id = -1);
	virtual void SetQlambdaF(T lambda, int spidar_id = -1);
	virtual void SetQlambdaT(T lambda, int spidar_id = -1);

public:
	virtual int Init			(std::string xmlFileName, int usb_id = -1);
	virtual void Active			(int isActive, int spidar_id = -1 );
	virtual void Calib			(int spidar_id = -1);

protected:
	virtual int MotorInfoSet	(std::string xmlFileName);

protected:
	virtual void SpidarCalc();

public: // for Impedance
	virtual CAHSVector3<T>		GetPos		(int spidar_id = 0);
	virtual CAHSQuaternion<T>	GetOri		(int spidar_id = 0);
	virtual void				SetForce	(CAHSVector3<T>& f,	int spidar_id = 0);
	virtual void				SetTorque	(CAHSVector3<T>& t,	int spidar_id = 0);
	virtual CAHSVector3<T>		GetPosVel	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetOriVel	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetPosVelIir	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetOriVelIir	(int spidar_id = 0);
public: // for Virtual Coupling in impedance control
	virtual CAHSVirtualCoupling<T>& GetVirtualCoupling(int spidar_id = 0);

public:	// for Admittance
	virtual CAHSVector3<T>	GetForce	(int spidar_id = 0);
	virtual CAHSVector3<T>	GetTorque	(int spidar_id = 0);
	virtual void			SetPos		(CAHSVector3<T>&     pos,	int spidar_id = 0);
	virtual void			SetOri		(CAHSQuaternion<T>&  ori,	int spidar_id = 0);

public:
	virtual void SetControlType(int type,	int spidar_id = 0);

public:
	virtual void Disp		();
};
