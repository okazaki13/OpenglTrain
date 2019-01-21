/** @file
	@JP
		@brief CSpidarEnhance class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CSpidarEnhance class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "SpidarHybrid.h"
#include "AHSWire.h"
#include <windows.h>
#include <string>
#include <time.h>
#include "AHSVirtualCoupling.h"


//class CAHSController;
class CAHSControllerSH4_01;

///////////////////////////////////////////////////////////
//
// このクラスは SpidarAPI.dll からエクスポートされました。
/**
@JP
	CSpidarEnhance クラス
@END_JP
@EN
	CSpidarEnhance class
@END_EN
 */
template <class T>
class SPIDARAPI_API CSpidarEnhance :
	public CSpidarHybrid<T>
{
protected:
	//CAHSController*		m_pController;
	CAHSControllerSH4_01* m_pController;

	CAHSWire<T>			m_wire[AHS_SPIDARX_NUM];//32本対応を考えないといけないね！
	UINT				m_FTimerID;
	int					m_msec;
	int					m_sh_usec;
	char				m_sh_mode;

	std::string			m_spidarStr;

	int					m_skill_level;

	T					m_tired_hour;
	time_t				m_sTime;
	time_t				m_nTime;
	int					m_isTalk;
	int					m_isCalib_inInit;
	int					m_init_error_id;

	//T					m_posUnit;
	//T					m_oriUnit;
	//T					m_forceUnit;
	//T					m_torqueUnit;

public:
	virtual int isSHsystem();
protected:
	void (CALLBACK *m_pf_userTimeFunc)(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2);
	void (CALLBACK *m_pf_userTimeFuncEasy)(DWORD dwUser);
public:
	void SetMMTCallBackFun    ( void (CALLBACK *pf)(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2) );
	void SetMMTCallBackFunEasy( void (CALLBACK *pf)(DWORD dwUser) );

protected:
	CSpidarEnhance	(int n);
public:
	CSpidarEnhance	(void);
	virtual ~CSpidarEnhance	(void);

public:
	//virtual CAHSController* GetController(int id = 0);
	virtual CAHSControllerSH4_01* GetController(int id = 0);

public:
	void SetSkillLevel(int level);
	void SetIsTalk(int flag);
	void SetIsCalib_in_Init(int flag);

public:
	virtual void SetPrepeat(int n, int spidar_id = -1);
	virtual void SetPsigma(T sigma, int spidar_id = -1);
	virtual void SetPposxN(T val, int spidar_id = -1);
	virtual void SetPorixN(T val, int spidar_id = -1);

	virtual void SetQrepeat(int n, int spidar_id = -1);
	virtual void SetQsigma(T sigma, int spidar_id = -1);
	virtual void SetQlambdaF(T lambda, int spidar_id = -1);
	virtual void SetQlambdaT(T lambda, int spidar_id = -1);

	//virtual void SetScalePosX(T scale, int spdiar_id = -1);
	//virtual void SetScalePosY(T scale, int spdiar_id = -1);
	//virtual void SetScalePosZ(T scale, int spdiar_id = -1);
	//virtual void SetScaleOriPhi(T scale, int spdiar_id = -1);
	//virtual void SetScaleForceX(T scale, int spdiar_id = -1);
	//virtual void SetScaleForceY(T scale, int spdiar_id = -1);
	//virtual void SetScaleForceZ(T scale, int spdiar_id = -1);
	//virtual void SetScaleTorqueX(T scale, int spdiar_id = -1);
	//virtual void SetScaleTorqueY(T scale, int spdiar_id = -1);
	//virtual void SetScaleTorqueZ(T scale, int spdiar_id = -1);

	//virtual void SetTorqueUnit(T scale, int spdiar_id = -1);

public:
	void SetMMTmsec(int msec);
	int GetMMTmsec();

public:
	void SetSH_SPIusec(int usec);
	int GetSH_SPIusec();

	void SetSH_SPImode(char mode);
	char GetSH_SPImode();

public:
	virtual CAHSWire<T>* GetWire(int id);
public:
	virtual CAHSWire<T>* GetMoter(int id);
public:
	virtual int WireNum();


public:
	virtual int GetSpidarNum();
public:
	std::string GetAPIStr();			///< @JP API文字列取得関数			@END_JP @EN Get API information str			@END_EN
	std::string GetVersionStr();		///< @JP バージョン文字列取得関数	@END_JP @EN Get version information str		@END_EN
	std::string GetCopyrightStr();		///< @JP コピーライト文字列取得関数	@END_JP @EN Get copyright information str	@END_EN

public:
	virtual int Init			(std::string xmlFileName, int usb_id = -1);
	virtual void Active			(int isActive, int spidar_id = -1);///< @JP PID制御を有効にする @END_JP @EN @END_EN
	virtual void Calib			(int spidar_id = -1);
	virtual void StartHapticLoop(int msec = -1);
	virtual void StopHapticLoop	();
	virtual void Quit			();
public:
	static int GetSpidarTypeFromXML(std::string xmlFileName, std::string& spidarType);
protected:// Init内で実行される
	virtual int MotorInfoSet	(std::string xmlFileName);
	virtual int MotorInfoSetXML(std::string xmlFileName);
public:
	virtual void BeforeCalib	(int spidar_id = -1);
	virtual void AfterCalib		(int spidar_id = -1);
public://protected:// TimeFunc内で実行される
	virtual void SetDataToAHS	();
	virtual void GetDataFromAHS	();
protected:
	virtual void SpidarCalc		();
	virtual void UserUpdate		();

public: // for Impedance
	virtual CAHSVector3<T>		GetPos		(int spidar_id = 0);
	virtual CAHSQuaternion<T>	GetOri		(int spidar_id = 0);
	virtual void				SetForce	(CAHSVector3<T>& f,	int spidar_id = -1);
	virtual void				SetTorque	(CAHSVector3<T>& t,	int spidar_id = -1);
	virtual CAHSVector3<T>		GetPosVel	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetOriVel	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetPosVelIir	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetOriVelIir	(int spidar_id = 0);

public: // for Virtual Coupling in impedance control
	virtual CAHSVirtualCoupling<T>& GetVirtualCoupling(int spidar_id = 0) = 0;

public:	// for Admittance
	virtual CAHSVector3<T>		GetForce	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetTorque	(int spidar_id = 0);
	virtual void				SetPos		(CAHSVector3<T>&     pos,	int spidar_id = -1);
	virtual void				SetOri		(CAHSQuaternion<T>&  ori,	int spidar_id = -1);


public: // switch
	virtual int		GetDigitalSw(int ch,	int spidar_id = 0);
	virtual T		GetAnalogSw	(int ch,	int spidar_id = 0);
	virtual int		GetTouchSw  (int ch,	int spidar_id = 0);

protected:
	static void CALLBACK TimeFunc(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2);

public:
	virtual void SetControlType(int type,	int spidar_id = -1);
public:
	static int GetControlTypeID(int type);
	static char GetControlTypeChar(int typeID);


protected:
	int Locate(HANDLE hOut, int x, int y);
protected:
	virtual void LogInit();

public:
	virtual void Disp();
	virtual void ErrorOut_init(int error_id);
	virtual void TipsOut();
};

typedef CSpidarEnhance<float>		CSpidarEnhanceF;
typedef CSpidarEnhance<double>		CSpidarEnhanceD;
