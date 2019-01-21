/** @file
	@JP
		@brief Spidar API
		@author �ԉH ���m
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
	CAHSWire �N���X
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
	CAHSController* m_pAHS;	// AHS�R���g���[���̃|�C���^
public:
	CAHSController* GetAHS();


protected:
	int m_controlType;		// ���[�^����^�C�v

protected:
	int m_ch_id;			// ���[�^���ڑ�����Ă���R���g���[����CH�ԍ�

protected:
	CAHSVector3<T> m_mPos;	// ���[�^���̎��̏o��[mm]

protected:
	CAHSVector3<T> m_gPos;	// �O���b�v��̎��̈ʒu[mm]

protected:
	T m_minForce;			// �ŏ�����[N]
	T m_maxForce;			// �ő咣��[N]

protected:
	T m_pwmCalibDuty;		// �L�����u���[�V��������PWM�f���[�e�B��[%]
	T m_pwmAfterCalibDuty;	// �L�����u���[�V�������PWM�f���[�e�B��[%]
	T m_pwmDutyMax;		// PWM�̍ő�f���[�e�B��[%]
public:
	T GetPwmCalibDuty();
	T GetPwmAftCalibDuty();
	T GetPwmDutyMax();
	void SetPwmCalibDuty(T duty);
	void SetPwmAftCalibDuty(T duty);
	void SetPwmDutyMax(T duty);

protected://PID����p�����[�^(�C���s�[�_���X��)
	T Kp_i;
	T Ki_i;
	T Kd_i;
	int Kb_i;
	int Km_i;

protected://PID����p�����[�^(�A�h�~�b�^���X��)
	T Kp_a;
	T Ki_a;
	T Kd_a;
	int m_pidAdmAddCount;
public:
	void SetPidAdmAddCount(int count);
	int GetPidAdmAddCount();

protected:
	T pullyRadius;			// �v�[�����a[mm]
protected:
	T encderResolution;		// �G���R�[�_����\[pulse/turn]
protected:
	T torqueConstant;		// ���[�^�̃g���N�萔[mNm/A]
protected:
	T terminal_r;			// ���[�^�̒[�q�Ԓ�R[ohm]
	T terminal_v;			// ���[�^�̒[�q�ԂɎ��ۂɂ����Ă���d��[v]
	T m_volt_duty;

	//
protected:
	// �␳
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
	// �␳
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
	T  m_homeLength;// �z�[���|�W�V�����ł̃��C����
protected:
	T m_lengthPerPulse;// �G���R�[�_1�J�E���g������̎��̒���[mm]
protected:
	T m_forcePerAdcHex;// A/D�R���o�[�^1�J�E���g������̗�[N]
	T m_voltPerAdcHex;// A/D�R���o�[�^1�J�E���g������̓d��[V]
public:
	T GetForcePerAdcHex();
public:
	T GetLengthPerPulse();

protected://�v���l
	T m_forceFromADC;
	T m_voltFromADC;
	T m_lengthFromEnc;

protected://�ڕW�l
	T m_force0;
	T m_length0;
public:
	void SetMinForce(T f);
	void SetMaxForce(T f);
	T	 GetMinForce();
	T	 GetMaxForce();

protected:
	int	m_enc_count;	// �G���R�[�_�J�E���g�l�iUpdateDataFromAHS�ɂ��X�V�j
	T	m_enc_vel;
	T	m_enc_acc;
	T	m_adc_count;	// ADC�l�iUpdateDataFromAHS�ɂ��X�V�j
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
	// �������i�K�����s����I�j
	void InitWire(CAHSController* pAHS,unsigned int ch_id);
	// ���C���ƃR���g���[���̊e���[�^�ڑ��`�����l���̑Ή��t��
	int SetChID(int id);
	// ���C���ƃR���g���[���̊e���[�^�ڑ��`�����l���̑Ή��t���̎擾
	unsigned int GetChID();

public:
	void SetMotorPos(T pos[3]);
	void SetGripPos(T pos[3]);
	// ���[�^����̃��C���̏o���̈ʒu��ݒ肷��
	void SetMotorGripPos(T mPos[3],T gPos[3]);
//public:
//	// �O���b�v��̃��C���ڑ��ʒu��ݒ肷��
//	void SetGripPos(float pos[3]);
public:
	// �G���R�[�_�̑����ݒ�
	void SetEncPhs(int phs);
	// �G���R�[�_�̑����̎擾
	int GetEncPhs();
	char GetEncPhsChar();

public:
	// �G���R�[�_�P�J�E���g������̃��C���̒�����ݒ肷��
	void SetLengthPerPulse();

	// ADC�P�J�E���g������̒��͂̐ݒ�
	void SetForcePerAdcHex();

public:
	// �f�[�^�̍X�V(�擾)
	void UpdateDataFromAHS();
	// �f�[�^�̍X�V(�ݒ�)
	void UpdateDataToAHS();


public:
	// �G���R�[�_�J�E���g�l�̎擾
	int GetEncCount();
	T GetEncVel();
	T GetEncAcc();

	// ADC�l�̎擾
	T GetAdcCount();
public:
	// ADC�l����񎦗͂��擾
	T GetForceFromADC();
	T GetVoltFromADC();
	T GetAmpFromADC();
	int GetADCRaw();
	int GetADCfirRaw();
	// �G���R�[�_�l���烏�C�������擾
	T GetLengthFromEnc();

public:
	// �C���s�[�_���X���䎞�̖ڕW�񎦗͂̐ݒ�iOpen loop�j
	T SetTargetForceOpen(T f0);

public:
	// �C���s�[�_���X���䎞�̖ڕW�񎦗͂̐ݒ�
	T SetTargetForce(T f0);
	// �C���s�[�_���X���䎞�̖ڕW�񎦗͂̎擾
	T GetTargetForce();
protected:
	// �C���s�[�_���X���䎞�̖ڕW�񎦗͂̐ݒ�l�ϊ���̒l�̎擾
	int   GetTargetForceToPID();

public:
	// �A�h�~�b�^���X���䎞�̖ڕW���C�����̐ݒ�
	T SetTargetLength(T len0);
	// �A�h�~�b�^���X���䎞�̖ڕW���C�����̎擾
	T GetTargetLength();
protected:
	// �A�h�~�b�^���X���䎞�̖ڕW���C�����̐ݒ�l�ϊ���̒l�̎擾
	int   GetTargetLengthToPID();

public:
	int GetPID_PV();// PID�̐���ʁi�v���l�j
	int GetPID_SV();// PID�̖ڕW�l
	void SetPID_SV(int val);// PID�̖ڕW�l
	void SetPID_MODE(int val);// PID�̃��[�h�i�d�����䂩�ʒu���䂩�j
	void SetPID_KP(float val);// PID��P
	void SetPID_KI(float val);// PID��I
	void SetPID_KD(float val);// PID��D

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


