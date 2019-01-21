/** @file
	@JP
		@brief CSpidarN class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CSpidarN class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2011/02/17
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/

#pragma once
//#include "spidarhybrid.h"
#include "spidarenhance.h"
#include "AHSWire.h"

class CAHSController;
template<class T> class CSpidarEnhance;

#define MAX_CTR_NUM 4
#define MAX_WIRE_NUM ((AHS_SPIDARX_NUM) * (MAX_CTR_NUM))

/**
@JP
	CSpidarN クラス
@END_JP
@EN
	CSpidarN class
@END_EN
 */
template <class T>
class SPIDARAPI_API CSpidarN :
	public CSpidarEnhance<T>
{
protected:
	int m_numAHS;
	CSpidarEnhance<T>** m_ppAHS;
	int m_numWire;
	CAHSWire<T>** m_ppWire;

private:
	CSpidarN(void);// デフォルトは1台分
public:
	CSpidarN(int n);
	virtual ~CSpidarN(void);

public:
	//virtual CAHSController* GetController(int id);
	virtual CAHSControllerSH4_01* GetController(int id);
	

public:
	virtual CAHSWire<T>* GetWire(int id);
public:
	virtual CAHSWire<T>* GetMoter(int id);
public:
	virtual int WireNum();
public:
	virtual int GetSpidarNum();

public:
	virtual int Init			(std::string xmlFileName, int usb_id = -1);	// xmlFileNameには複数のファイル名が;を区切り文字にして格納されている.
	virtual void Active			(int isActive, int spidar_id = -1);///< @JP PID制御を有効にする @END_JP @EN @END_EN
	virtual void Calib			(int spidar_id = -1);
	virtual void StartHapticLoop(int msec = -1);
	//virtual void StopHapticLoop	();
	virtual void Quit			();
protected:// Init内で実行される
//	virtual int MotorInfoSet	(std::string xmlFileName);
//	virtual int MotorInfoSetXML(std::string xmlFileName);
	virtual void BeforeCalib	(int spidar_id = -1);
	virtual void AfterCalib		(int spidar_id = -1);
//public://protected:// TimeFunc内で実行される
//	virtual void SetDataToAHS	();
//	virtual void GetDataFromAHS	();
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

public:	// for Admittance
	virtual CAHSVector3<T>		GetForce	(int spidar_id = 0);
	virtual CAHSVector3<T>		GetTorque	(int spidar_id = 0);
	virtual void				SetPos		(CAHSVector3<T>&     pos,	int spidar_id = -1);
	virtual void				SetOri		(CAHSQuaternion<T>&  ori,	int spidar_id = -1);


protected:
	static void CALLBACK TimeFuncN(UINT uID,UINT uMsg,DWORD dwUser,DWORD dw1,DWORD dw2);

public:
	virtual void SetControlType(int type,	int spidar_id = -1);
protected:
	virtual void LogInit();
public:
	virtual void Disp();

};

typedef CSpidarN<float>			CSpidarNF;
typedef CSpidarN<double>		CSpidarND;
