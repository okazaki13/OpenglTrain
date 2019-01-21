/** @file
	@JP
		@brief AHS PID制御 クラス定義
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief AHS PID Control Class interface
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/1/15
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/

#pragma once
#include "FFx2Basefunc.h"

#define FX2_PID_PID_NUM				(16)

/**
@JP
	AHS PID制御 クラス
@END_JP
@EN
	AHS PID Control Class
@END_EN
 */
class AHSAPI_API CFx2PID :
	public CFx2BaseFunc
{
protected:
	int maxPos0[FX2_PID_PID_NUM];///< @JP 目標値(位置)の最大値 @END_JP @EN Maximum value of target position @END_EN
	int minPos0[FX2_PID_PID_NUM];///< @JP 目標値(位置)の最小値 @END_JP @EN Minimum value of target position @END_EN
	int isActiveMaxMinLimiter[FX2_PID_PID_NUM];///< @JP 目標値(位置)の最大最小値制限有効（無効）フラグ @END_JP @EN Activate flag of PID target position limiter @END_EN

//protected:
//	int m_Kp_pos[FX2_PID_PID_NUM];
//	int m_Ki_pos[FX2_PID_PID_NUM];
//	int m_Kd_pos[FX2_PID_PID_NUM];
//protected:
//	int m_Kp_adc[FX2_PID_PID_NUM];
//	int m_Ki_adc[FX2_PID_PID_NUM];
//	int m_Kd_adc[FX2_PID_PID_NUM];

public:
	CFx2PID(void);		///< @JP コンストラクタ @END_JP @EN Constructor @END_EN
	virtual ~CFx2PID(void);	///< @JP デストラクタ	@END_JP @EN Destructor @END_EN

	/**
	@JP
		PID制御のパラメータの設定

	@param[in] ch パラメータを設定するチャンネル番号
	@param[in] kp 比例要素の係数
	@param[in] ki 積分要素の係数
	@param[in] kd 微分要素の係数
	@END_JP
	@EN
		Set values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@param[in] kp Proportional factor of PID
	@param[in] ki Integral factor of PID
	@param[in] kd Derivative factor of PID
	@END_EN
	*/
public:
	void SetPIDHexVal(unsigned int ch,int kp,int ki,int kd);
	void SetPIDVal(unsigned int ch,float kp,float ki,float kd);


public:
	//void SetWaveHex(unsigned int ch,int sin_freq,int e_freq,int mag);
	//int GetWaveHex_sin_freq(unsigned int ch);
	//int GetWaveHex_e_freq(unsigned int ch);
	//int GetWaveHex_mag(unsigned int ch);
public:
	void SetBcompensationKb(unsigned int ch,int kb);
	int  GetBcompensationKb(unsigned int ch);
public:
	void SetMcompensationKm(unsigned int ch,int km);
	int  GetMcompensationKm(unsigned int ch);
	/**
	@JP
		PID制御のパラメータの設定

	@param[in] ch パラメータを設定するチャンネル番号
	@param[in] kp 比例要素の係数
	@END_JP
	@EN
		Set values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@param[in] kp Proportional factor of PID
	@END_EN
	*/
public:
	void SetPIDHex_Kp(unsigned int ch,int kp);
	void SetPID_Kp(unsigned int ch,float kp);
	/**
	@JP
		PID制御のパラメータの設定

	@param[in] ch パラメータを設定するチャンネル番号
	@param[in] ki 積分要素の係数
	@END_JP
	@EN
		Set values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@param[in] ki Integral factor of PID
	@END_EN
	*/
public:
	void SetPIDHex_Ki(unsigned int ch,int ki);
	void SetPID_Ki(unsigned int ch,float ki);
	/**
	@JP
		PID制御のパラメータの設定

	@param[in] ch パラメータを設定するチャンネル番号
	@param[in] kd 微分要素の係数
	@END_JP
	@EN
		Set values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@param[in] kd Derivative factor of PID
	@END_EN
	*/
public:
	void SetPIDHex_Kd(unsigned int ch,int kd);
	void SetPID_Kd(unsigned int ch,float kd);

	/**
	@JP
		PID制御のパラメータの取得

	@param[in] ch 設定パラメータを取得するチャンネル番号
	@param[out] kp 比例要素の係数
	@param[out] ki 積分要素の係数
	@param[out] kd 微分要素の係数
	@END_JP
	@EN
		Get values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@param[out] kp Proportional factor of PID
	@param[out] ki Integral factor of PID
	@param[out] kd Derivative factor of PID
	@END_EN
	*/
public:
	void GetPIDHexVal(unsigned int ch,int& kp,int& ki,int& kd);
	void GetPIDVal(unsigned int ch,float& kp,float& ki,float& kd);
	/**
	@JP
		PID制御のパラメータの取得

	@param[in] ch 設定パラメータを取得するチャンネル番号
	@return kp 比例要素の係数
	@END_JP
	@EN
		Get values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@return kp Proportional factor of PID
	@END_EN
	*/
public:
	int GetPIDHex_Kp(unsigned int ch);
	float GetPID_Kp(unsigned int ch);
	/**
	@JP
		PID制御のパラメータの取得

	@param[in] ch 設定パラメータを取得するチャンネル番号
	@return ki 積分要素の係数
	@END_JP
	@EN
		Get values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@return ki Integral factor of PID
	@END_EN
	*/
public:
	int GetPIDHex_Ki(unsigned int ch);
	float GetPID_Ki(unsigned int ch);
	/**
	@JP
		PID制御のパラメータの取得

	@param[in] ch 設定パラメータを取得するチャンネル番号
	@return kd 微分要素の係数
	@END_JP
	@EN
		Get values of PID control parameters.

	@param[in] ch Chanel number of PID controller
	@return kd Derivative factor of PID
	@END_EN
	*/
public:
	int GetPIDHex_Kd(unsigned int ch);
	float GetPID_Kd(unsigned int ch);

	/**
	@JP
		PID制御の目標値（位置）の設定

	@param[in] ch 目標値（位置）を設定するチャンネル番号
	@param[in] val 目標値（位置）
	@END_JP
	@EN
		Set values of PID control target position.

	@param[in] ch Chanel number of PID controller
	@param[in] val Target position
	@END_EN
	*/
public:
	void SetPos0(unsigned int ch,int val,int isImp = 0);

	/**
	@JP
		PID制御の目標値（位置）の取得

	@param[in] ch 目標値（位置）を取得するチャンネル番号
	@return PID制御の目標値（位置）
	@END_JP
	@EN
		Get value of PID target position.

	@param[in] ch Chanel number of PID controller
	@return value of the target position
	@END_EN
	*/
public:
	int  GetPos0(unsigned int ch);

	/**
	@JP
		PID制御の目標値（位置）の最大値，最小値の設定

	@param[in] ch 設定するチャンネル番号
	@param[in] minVal 目標値（位置）の最小値
	@param[in] maxVal 目標値（位置）の最大値
	@END_JP
	@EN
		Set Maximum and Minimum value of PID control target position.

	@param[in] ch Chanel number of PID controller
	@param[in] minVal Minimum value of Target position
	@param[in] maxVal Maximum value of Target position
	@END_EN
	*/
public:
	void SetMaxMinPos0(unsigned int ch,int minVal,int maxVal);

	/**
	@JP
		PID制御の目標値（位置）の最大値，最小値の初期化

	@param[in] ch 初期化するチャンネル番号
	@END_JP
	@EN
		Initialize Maximum and Minimum value of PID control target position.

	@param[in] ch Chanel number of PID
	@END_EN
	*/
public:
	void ResetMaxMinPos0(int ch = -1);

	/**
	@JP
		PID制御の目標値（位置）の最大値の取得

	@param[in] ch 取得するチャンネル番号
	@return 目標値（位置）の最大値
	@END_JP
	@EN
		Get Maximum value of PID control target position.

	@param[in] ch Chanel number of PID
	@return Maximum value of target position
	@END_EN
	*/
public:
	int  GetMaxPos0(int ch);

	/**
	@JP
		PID制御の目標値（位置）の最小値の取得

	@param[in] ch 取得するチャンネル番号
	@return 目標値（位置）の最小値
	@END_JP
	@EN
		Get Minimum value of PID control target position.

	@param[in] ch Chanel number of PID
	@return Minimum value of target position
	@END_EN
	*/
public:
	int  GetMinPos0(int ch);

	/**
	@JP
		PIDを有効(無効)にする
	@param[in] ch 有効にするPIDのチャンネル番号(負の値はすべてのチャンネル)
	@param[in] isActive 有効にするとき：1(default)，無効にするとき：0
	@END_JP
	@EN
		Activate(or nonactive) of PID
	@param[in] ch Chanel number of the PID(Minus value means all chanel selection)
	@param[in] isActive When PID is active:1(default), otherwise:0
	@END_EN
	*/
public:
	void SetActivePID(int ch, int isActive = 1);//負の値はすべてのチャンネルのPIDをアクティブ

	/**
	@JP
		PIDの有効（無効）値を取得する
	@END_JP
	@EN
		Get state of activate flag of PID
	@END_EN
	*/
public:
	int GetActivePID();

	/**
	@JP
		PIDの有効（無効）値を取得する
	@END_JP
	@EN
		Get state of activate flag of PID
	@END_EN
	*/
public:
	int GetActivePID(unsigned int ch);

	/**
	@JP
		PIDの目標値の最大最小リミッタ制限を有効（無効）にする
	@END_JP
	@EN
		Activate(or nonactive) of PID target position limiter.
	@END_EN
	*/
public:
	void SetActiveMaxMinPos0Limiter(int ch = -1,int isActive = 1);

	/**
	@JP
		PIDの目標値の最大最小リミッタ制限を有効（無効）の取得
	@END_JP
	@EN
		Get state of activate flag of PID target position limiter.
	@END_EN
	*/
public:
	int GetActiveMaxMinPos0Limiter(unsigned int ch);

public:
	void SetSelImpAdm(int ch, int isImp = 1);//負の値はすべてのチャンネルのPWMをアクティブ
public:
	int GetSelImpAdm();
public:
	int GetSelImpAdm(int ch);


public:
	void SetSelSH(int ch, int isSH = 1);//負の値はすべてのチャンネルの制御信号をSH優先にする
public:
	char GetSelSH();
public:
	int GetSelSH(int ch);


// すべての外部設定フラグの設定
public:
	void SetExSetup(int ch, int out = 1);//負の値はすべてのチャンネルの制御信号をSH優先にする
public:
	char GetExSetup();
public:
	int GetExSetup(int ch);

// 外部設定フラグ用でSCIFのスタート信号を設定
public:
	void SetStartSCIF1(int isStart = 1);
public:
	int GetStartSCIF1();

// 外部設定フラグ用でSCIFのリセット信号を設定
public:
	void SetResetSCIF1(int isReset);

	// 外部設定フラグ用でSHのリセット信号を設定
public:
	void SetResetSHx(int isReset);

// 外部設定フラグ用でSH0への通信をPC優先かSH1優先かを設定
public:
	void SetSH0TransSelPCorSH1(int sel = 1);//負の値はすべてのチャンネルの制御信号をSH優先にする
public:
	int GetSH0TransSelPCorSH1();


public:
	virtual unsigned int GetPIDNum();

public:
	virtual int GetMaxPidKpVal();
	virtual int GetMinPidKpVal();
	virtual int GetDPPidKpVal();

	virtual int GetMaxPidKiVal();
	virtual int GetMinPidKiVal();
	virtual int GetDPPidKiVal();

	virtual int GetMaxPidKdVal();
	virtual int GetMinPidKdVal();
	virtual int GetDPPidKdVal();

	virtual int GetMotorRPS();
	virtual int GetMaxPos0Val();
	virtual int GetMinPos0Val();

protected:
	virtual void LogDisp();

public:
	virtual void Disp(HANDLE hOut);

};

#undef FX2_PID_PID_NUM

