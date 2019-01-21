/** @file
	@JP
		@brief Spidar API
		@author 赤羽 克仁
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
#include "spidarapi.h"
#include "AHSVector3.h"

class CAHSController;

/**
@JP
	CAHSWire クラス
@END_JP
@EN
	CAHSWire class
@END_EN
 */
template <class T>
class SPIDARAPI_API CAHSWire :
	public CSpidarAPI
{
protected:
	CAHSController* m_pAHS;	// AHSコントローラのポインタ
public:
	CAHSController* GetAHS();


protected:
	int m_controlType;		// モータ制御タイプ

protected:
	int m_ch_id;			// モータが接続されているコントローラのCH番号

protected:
	CAHSVector3<T> m_mPos;	// モータ側の糸の出口[mm]

protected:
	CAHSVector3<T> m_gPos;	// グリップ上の糸の位置[mm]

protected:
	T m_minForce;			// 最小張力[N]
	T m_maxForce;			// 最大張力[N]

protected:
	T m_pwmCalibDuty;		// キャリブレーション時のPWMデューティ比[%]
	T m_pwmAfterCalibDuty;	// キャリブレーション後のPWMデューティ比[%]
	T m_pwmDutyMax;		// PWMの最大デューティ比[%]
public:
	T GetPwmCalibDuty();
	T GetPwmAftCalibDuty();
	T GetPwmDutyMax();
	void SetPwmCalibDuty(T duty);
	void SetPwmAftCalibDuty(T duty);
	void SetPwmDutyMax(T duty);

protected://PID制御パラメータ(インピーダンス時)
	T Kp_i;
	T Ki_i;
	T Kd_i;
	int Kb_i;
	int Km_i;

protected://PID制御パラメータ(アドミッタンス時)
	T Kp_a;
	T Ki_a;
	T Kd_a;
	int m_pidAdmAddCount;
public:
	void SetPidAdmAddCount(int count);
	int GetPidAdmAddCount();

protected:
	T pullyRadius;			// プーリ半径[mm]
protected:
	T encderResolution;		// エンコーダ分解能[pulse/turn]
protected:
	T torqueConstant;		// モータのトルク定数[mNm/A]
protected:
	T terminal_r;			// モータの端子間抵抗[ohm]
	T terminal_v;			// モータの端子間に実際にかけている電圧[v]
	T m_volt_duty;

	//
protected:
	// 補正
	int correction_targetForceOpen_isActive;
	T   correction_targetForceOpen_a0;
	T   correction_targetForceOpen_a1;
	T   correction_targetForceOpen_a2;
	T   correction_targetForceOpen_a3;
public:
	void Set_correction_targetForceOpen(int isActive, T a0, T a1, T a2, T a3);
public:
	T GetCorrection_targetForceOpen_a0(){ return correction_targetForceOpen_a0;}
public:
	T GetCorrection_targetForceOpen_a1(){ return correction_targetForceOpen_a1;}
public:
	T GetCorrection_targetForceOpen_a2(){ return correction_targetForceOpen_a2;}
public:
	T GetCorrection_targetForceOpen_a3(){ return correction_targetForceOpen_a3;}
protected:
	// 補正
	int correction_adc_to_force_isActive;
	T   correction_adc_to_force_a0;
	T   correction_adc_to_force_a1;
	T   correction_adc_to_force_a2;
	T   correction_adc_to_force_a3;
public:
	void Set_correction_adc_to_force(int isActive, T a0, T a1, T a2, T a3);
public:
	T GetCorrection_adc_to_force_a0(){ return correction_adc_to_force_a0;}
public:
	T GetCorrection_adc_to_force_a1(){ return correction_adc_to_force_a1;}
public:
	T GetCorrection_adc_to_force_a2(){ return correction_adc_to_force_a2;}
public:
	T GetCorrection_adc_to_force_a3(){ return correction_adc_to_force_a3;}
/////////////////////////////////////////////

protected:
	T  m_homeLength;// ホームポジションでのワイヤ長
protected:
	T m_lengthPerPulse;// エンコーダ1カウント当たりの糸の長さ[mm]
protected:
	T m_forcePerAdcHex;// A/Dコンバータ1カウント当たりの力[N]
	T m_voltPerAdcHex;// A/Dコンバータ1カウント当たりの電圧[V]
public:
	T GetForcePerAdcHex();
public:
	T GetLengthPerPulse();

protected://計測値
	T m_forceFromADC;
	T m_voltFromADC;
	T m_lengthFromEnc;

protected://目標値
	T m_force0;
	T m_length0;
public:
	void SetMinForce(T f);
	void SetMaxForce(T f);
	T	 GetMinForce();
	T	 GetMaxForce();

protected:
	int	m_enc_count;	// エンコーダカウント値（UpdateDataFromAHSにより更新）
	T	m_enc_vel;
	T	m_enc_acc;
	T	m_adc_count;	// ADC値（UpdateDataFromAHSにより更新）
	int m_isEncInterpolation;
public:
	void SetIsEncInterpolation(int flag){
		this->m_isEncInterpolation = flag;
	}

	char GetIsEncInterpolationChar(){
		if(this->m_isEncInterpolation) return 't';
		else return 'f';
	}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

public:
	CAHSWire(void);
	virtual ~CAHSWire(void);

public:
	CAHSVector3<T>& gPos();
	CAHSVector3<T>& mPos();

public:
	T GetPullyRadius();
	T GetEncResolution();
	T GetTorqueConstant();
public:
	void SetPullyRadius(T radius);
	void SetEncResolution(T res);
	void SetTorqueConstant(T cons);
	void SetTerminal_r(T cons);
	void SetTerminal_v(T cons);
	T GetTerminal_r();
	T GetTerminal_v();

public:
	void SetActivePWM(int val);
	int GetActivePWM();
	void SetActivePID(int val);
	int GetActivePID();
public:
	// 初期化（必ず実行せよ！）
	void InitWire(CAHSController* pAHS,unsigned int ch_id);
	// ワイヤとコントローラの各モータ接続チャンネルの対応付け
	int SetChID(int id);
	// ワイヤとコントローラの各モータ接続チャンネルの対応付けの取得
	unsigned int GetChID();

public:
	void SetMotorPos(T pos[3]);
	void SetGripPos(T pos[3]);
	// モータからのワイヤの出口の位置を設定する
	void SetMotorGripPos(T mPos[3],T gPos[3]);
//public:
//	// グリップ上のワイヤ接続位置を設定する
//	void SetGripPos(float pos[3]);
public:
	// エンコーダの相順設定
	void SetEncPhs(int phs);
	// エンコーダの相順の取得
	int GetEncPhs();
	char GetEncPhsChar();

public:
	// エンコーダ１カウント当たりのワイヤの長さを設定する
	void SetLengthPerPulse();

	// ADC１カウント当たりの張力の設定
	void SetForcePerAdcHex();

public:
	// データの更新(取得)
	void UpdateDataFromAHS();
	// データの更新(設定)
	void UpdateDataToAHS();


public:
	// エンコーダカウント値の取得
	int GetEncCount();
	T GetEncVel();
	T GetEncAcc();

	// ADC値の取得
	T GetAdcCount();
public:
	// ADC値から提示力を取得
	T GetForceFromADC();
	T GetVoltFromADC();
	T GetAmpFromADC();
	int GetADCRaw();
	int GetADCfirRaw();
	// エンコーダ値からワイヤ長を取得
	T GetLengthFromEnc();

public:
	// インピーダンス制御時の目標提示力の設定（Open loop）
	T SetTargetForceOpen(T f0);

public:
	// インピーダンス制御時の目標提示力の設定
	T SetTargetForce(T f0);
	// インピーダンス制御時の目標提示力の取得
	T GetTargetForce();
protected:
	// インピーダンス制御時の目標提示力の設定値変換後の値の取得
	int   GetTargetForceToPID();

public:
	// アドミッタンス制御時の目標ワイヤ長の設定
	T SetTargetLength(T len0);
	// アドミッタンス制御時の目標ワイヤ長の取得
	T GetTargetLength();
protected:
	// アドミッタンス制御時の目標ワイヤ長の設定値変換後の値の取得
	int   GetTargetLengthToPID();

public:
	int GetPID_PV();// PIDの制御量（計測値）
	int GetPID_SV();// PIDの目標値
	void SetPID_SV(int val);// PIDの目標値
	void SetPID_MODE(int val);// PIDのモード（電流制御か位置制御か）
	void SetPID_KP(float val);// PIDのP
	void SetPID_KI(float val);// PIDのI
	void SetPID_KD(float val);// PIDのD

	float GetPID_Kp();
	float GetPID_Ki();
	float GetPID_Kd();

	int GetPIDHex_Kp();
	int GetPIDHex_Ki();
	int GetPIDHex_Kd();

public:
	void SetControlType(int type);

public:
	int GetControlType();
	char GetControlTypeChar();

public:
	void  SetKp_i(T val);
	void  SetKi_i(T val);
	void  SetKd_i(T val);
	void  SetKb_i(int val);
	void  SetKm_i(int val);
	T GetKp_i();
	T GetKi_i();
	T GetKd_i();
	int GetKb_i();
	int GetKm_i();

	void  SetKp_a(T val);
	void  SetKi_a(T val);
	void  SetKd_a(T val);
	T GetKp_a();
	T GetKi_a();
	T GetKd_a();

public:
	void SetPWM_duty_percent(T percent);
	T GetPWM_duty_percent();

public:
	void SetPWM_duty(T duty);
	T GetPWM_duty();

public:
	void Disp(FILE* fp ,int isTitle = 0);

};


typedef CAHSWire<float>			CWireF;
typedef CAHSWire<double>		CWireD;


