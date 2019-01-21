/** @file
	@JP
		@brief Spidar API
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief Spidar API
		@author Katsuhito AKAHANE
	@END_EN

	@date	2011/09/02
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/
#pragma once
#include "spidarg.h"
#include "AHSVC6DOF_SH.h"

#include "../ShareSH/Share_SpidarData.h"
#include "../ShareSH1/Share_SH1Data.h"
#include "../ShareSH1/Share_SimData.h"
#include "../AHSAPI/pkt_id_define_sh0.h"

/**
@JP
	CSHSpidarG クラス
@END_JP
@EN
	CSHSpidarG class
@END_EN
 */
template<class T>
class CSHSpidarG :
	public CSpidarG<T>
{
protected:
	//FILE* m_fp_data;
	int m_rec_bank_id;
	int m_rec_data_index;
	int m_rec_data_last_index;
	int m_rec_lastIndex;

protected:
	REC_DATA rec_data;
	REC_DATA rec_data_chk[2];

protected:
	unsigned char m_demo_wsize;
	unsigned long m_demo_wadd;
	unsigned char m_demo_wdata[64];

protected:
	unsigned int m_motors_address;
	unsigned int m_spi_address;
	unsigned int m_rec_address[2];
	unsigned int m_vw_bank_address;
	int m_vw_bank;
	unsigned int m_vw_address[2];
	unsigned int m_hp_address;

	unsigned char m_vc_send_id;
	//unsigned int m_vcset_wsize ;
	unsigned int m_vcset_wadd  ;
	//unsigned int m_vcupd_wsize ;
	unsigned int m_vcupd_wadd  ;

	int m_motors_size;
	int m_spi_size;
	int m_rec_size;

	int m_isHaptics;
	int m_isRec;

	int m_isCallAfterCalib;
	int m_isCalib;

	T m_trig;

protected:
	CAHSVector3<float>		m_gripForce;
	CAHSVector3<float>		m_gripTorque;

protected:
	// SH1用の通信データ
	int m_sh1sDataSize;
	unsigned int  m_sh1sDataAddress;//初期化時にSH1からアドレスをもらう
	unsigned int  m_sh1rDataAddress;//初期化時にSH1からアドレスをもらう
	unsigned char m_sh1sData[SH_MODEx_SEND_VDATA_LEN];
	unsigned char m_sh1rData[SH_MODEx_RECEIVE_VDATA_LEN];
	int m_isValidSh1rData;

	//
	ST_INIT_SH0_DATA_QUERY	m_query_sh0;
	int m_query_sh0_valid_size;
	ST_INIT_SH1_DATA_QUERY	m_query_sh1;
	int m_query_sh1_valid_size;
	//
	ST_SH0_SYSTEM_DATA m_sh0_system_data;
	ST_SH1_SYSTEM_DATA m_sh1_system_data;

public:
	unsigned long GetSH0QueryAddress(int id);
	unsigned long GetSH1QueryAddress(int id);

protected:
	void (CALLBACK *m_pf_update_sh0)(DWORD dwUser);
	void (CALLBACK *m_pf_update_sh1)(DWORD dwUser);

public:
	void SetUpdateFunc(char mode);

public:
	virtual int isSHsystem();

public:
	CSHSpidarG(void);
	virtual ~CSHSpidarG(void);

protected:
	//
	int init_sh_x(int isChk = 0);
	//
	int init_sh_x_version_chk(int isChk = 0);
	int init_sh_x_query(int isSHxActive,int isChk = 0);
	//
	void init_sh_spidar_data(SH_SPIDAR_G& spig,SH_MOTORS& motors);
	int init_sh_spidar(int isChk = 0);
	//int init_sh_spidar001(int isChk = 0);
	int init_sh_sim(int isChk = 0);
	//
	void fp_out(FILE* fp,const int lastIndex,void* pData);
	int quit_sh_spidar(int isChk = 0);
	void rec_datas();

public:
	virtual int Init			(std::string xmlFileName, int usb_id = -1);
	virtual void Active			(int isActive, int spidar_id = -1 );
	virtual void Calib			(int spidar_id = -1);
	virtual void Quit			();

protected:
	virtual void SpidarCalc();

public:
	void SetRec(int isRec = 1);

public:
	void Flush_W3P4_VirtualWall();
	void Set_W3P4_VirtualWall(int index, float k,float b,float vw[4]);	// indexが負のときwsizeとwaddをリセット
	void Set_W3P4_HapticPoints(int HpNum, float hp[4][3]);

public:
	//void Set_VcSetParameter(
	//	float posK,float posKmax,float posB,float posBmax,float posGripScale,
	//	float oriK,float oriKmax,float oriB,float oriBmax,float oriGripScale);
	void Set_VcUpdateVelBase(int isCoupling,
		float posVelObj[3],float posK,float posB,float posScale,
		float oriVelObj[3],float oriK,float oriB,float oriScale
	);
	void Get_VcForceTorqueObj(T forceObj[3],T torqueObj[3]);

protected:
	static void CALLBACK update_sh0(DWORD dwUser);
	static void CALLBACK update_sh0_vc(DWORD dwUser);
	static void CALLBACK update_sh0_w3h4(DWORD dwUser);
	static void CALLBACK update_sh0_demo(DWORD dwUser);
protected:
	static void CALLBACK update_sh1(DWORD dwUser);
protected:
	static void CALLBACK update_void(DWORD dwUser);	
};
