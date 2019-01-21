/** @file
	@JP
		@brief AHS PID���� �N���X��`
		@author �ԉH ���m
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
	AHS PID���� �N���X
@END_JP
@EN
	AHS PID Control Class
@END_EN
 */
class AHSAPI_API CFx2PID :
	public CFx2BaseFunc
{
protected:
	int maxPos0[FX2_PID_PID_NUM];///< @JP �ڕW�l(�ʒu)�̍ő�l @END_JP @EN Maximum value of target position @END_EN
	int minPos0[FX2_PID_PID_NUM];///< @JP �ڕW�l(�ʒu)�̍ŏ��l @END_JP @EN Minimum value of target position @END_EN
	int isActiveMaxMinLimiter[FX2_PID_PID_NUM];///< @JP �ڕW�l(�ʒu)�̍ő�ŏ��l�����L���i�����j�t���O @END_JP @EN Activate flag of PID target position limiter @END_EN

//protected:
//	int m_Kp_pos[FX2_PID_PID_NUM];
//	int m_Ki_pos[FX2_PID_PID_NUM];
//	int m_Kd_pos[FX2_PID_PID_NUM];
//protected:
//	int m_Kp_adc[FX2_PID_PID_NUM];
//	int m_Ki_adc[FX2_PID_PID_NUM];
//	int m_Kd_adc[FX2_PID_PID_NUM];

public:
	CFx2PID(void);		///< @JP �R���X�g���N�^ @END_JP @EN Constructor @END_EN
	virtual ~CFx2PID(void);	///< @JP �f�X�g���N�^	@END_JP @EN Destructor @END_EN

	/**
	@JP
		PID����̃p�����[�^�̐ݒ�

	@param[in] ch �p�����[�^��ݒ肷��`�����l���ԍ�
	@param[in] kp ���v�f�̌W��
	@param[in] ki �ϕ��v�f�̌W��
	@param[in] kd �����v�f�̌W��
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
		PID����̃p�����[�^�̐ݒ�

	@param[in] ch �p�����[�^��ݒ肷��`�����l���ԍ�
	@param[in] kp ���v�f�̌W��
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
		PID����̃p�����[�^�̐ݒ�

	@param[in] ch �p�����[�^��ݒ肷��`�����l���ԍ�
	@param[in] ki �ϕ��v�f�̌W��
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
		PID����̃p�����[�^�̐ݒ�

	@param[in] ch �p�����[�^��ݒ肷��`�����l���ԍ�
	@param[in] kd �����v�f�̌W��
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
		PID����̃p�����[�^�̎擾

	@param[in] ch �ݒ�p�����[�^���擾����`�����l���ԍ�
	@param[out] kp ���v�f�̌W��
	@param[out] ki �ϕ��v�f�̌W��
	@param[out] kd �����v�f�̌W��
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
		PID����̃p�����[�^�̎擾

	@param[in] ch �ݒ�p�����[�^���擾����`�����l���ԍ�
	@return kp ���v�f�̌W��
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
		PID����̃p�����[�^�̎擾

	@param[in] ch �ݒ�p�����[�^���擾����`�����l���ԍ�
	@return ki �ϕ��v�f�̌W��
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
		PID����̃p�����[�^�̎擾

	@param[in] ch �ݒ�p�����[�^���擾����`�����l���ԍ�
	@return kd �����v�f�̌W��
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
		PID����̖ڕW�l�i�ʒu�j�̐ݒ�

	@param[in] ch �ڕW�l�i�ʒu�j��ݒ肷��`�����l���ԍ�
	@param[in] val �ڕW�l�i�ʒu�j
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
		PID����̖ڕW�l�i�ʒu�j�̎擾

	@param[in] ch �ڕW�l�i�ʒu�j���擾����`�����l���ԍ�
	@return PID����̖ڕW�l�i�ʒu�j
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
		PID����̖ڕW�l�i�ʒu�j�̍ő�l�C�ŏ��l�̐ݒ�

	@param[in] ch �ݒ肷��`�����l���ԍ�
	@param[in] minVal �ڕW�l�i�ʒu�j�̍ŏ��l
	@param[in] maxVal �ڕW�l�i�ʒu�j�̍ő�l
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
		PID����̖ڕW�l�i�ʒu�j�̍ő�l�C�ŏ��l�̏�����

	@param[in] ch ����������`�����l���ԍ�
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
		PID����̖ڕW�l�i�ʒu�j�̍ő�l�̎擾

	@param[in] ch �擾����`�����l���ԍ�
	@return �ڕW�l�i�ʒu�j�̍ő�l
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
		PID����̖ڕW�l�i�ʒu�j�̍ŏ��l�̎擾

	@param[in] ch �擾����`�����l���ԍ�
	@return �ڕW�l�i�ʒu�j�̍ŏ��l
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
		PID��L��(����)�ɂ���
	@param[in] ch �L���ɂ���PID�̃`�����l���ԍ�(���̒l�͂��ׂẴ`�����l��)
	@param[in] isActive �L���ɂ���Ƃ��F1(default)�C�����ɂ���Ƃ��F0
	@END_JP
	@EN
		Activate(or nonactive) of PID
	@param[in] ch Chanel number of the PID(Minus value means all chanel selection)
	@param[in] isActive When PID is active:1(default), otherwise:0
	@END_EN
	*/
public:
	void SetActivePID(int ch, int isActive = 1);//���̒l�͂��ׂẴ`�����l����PID���A�N�e�B�u

	/**
	@JP
		PID�̗L���i�����j�l���擾����
	@END_JP
	@EN
		Get state of activate flag of PID
	@END_EN
	*/
public:
	int GetActivePID();

	/**
	@JP
		PID�̗L���i�����j�l���擾����
	@END_JP
	@EN
		Get state of activate flag of PID
	@END_EN
	*/
public:
	int GetActivePID(unsigned int ch);

	/**
	@JP
		PID�̖ڕW�l�̍ő�ŏ����~�b�^������L���i�����j�ɂ���
	@END_JP
	@EN
		Activate(or nonactive) of PID target position limiter.
	@END_EN
	*/
public:
	void SetActiveMaxMinPos0Limiter(int ch = -1,int isActive = 1);

	/**
	@JP
		PID�̖ڕW�l�̍ő�ŏ����~�b�^������L���i�����j�̎擾
	@END_JP
	@EN
		Get state of activate flag of PID target position limiter.
	@END_EN
	*/
public:
	int GetActiveMaxMinPos0Limiter(unsigned int ch);

public:
	void SetSelImpAdm(int ch, int isImp = 1);//���̒l�͂��ׂẴ`�����l����PWM���A�N�e�B�u
public:
	int GetSelImpAdm();
public:
	int GetSelImpAdm(int ch);


public:
	void SetSelSH(int ch, int isSH = 1);//���̒l�͂��ׂẴ`�����l���̐���M����SH�D��ɂ���
public:
	char GetSelSH();
public:
	int GetSelSH(int ch);


// ���ׂĂ̊O���ݒ�t���O�̐ݒ�
public:
	void SetExSetup(int ch, int out = 1);//���̒l�͂��ׂẴ`�����l���̐���M����SH�D��ɂ���
public:
	char GetExSetup();
public:
	int GetExSetup(int ch);

// �O���ݒ�t���O�p��SCIF�̃X�^�[�g�M����ݒ�
public:
	void SetStartSCIF1(int isStart = 1);
public:
	int GetStartSCIF1();

// �O���ݒ�t���O�p��SCIF�̃��Z�b�g�M����ݒ�
public:
	void SetResetSCIF1(int isReset);

	// �O���ݒ�t���O�p��SH�̃��Z�b�g�M����ݒ�
public:
	void SetResetSHx(int isReset);

// �O���ݒ�t���O�p��SH0�ւ̒ʐM��PC�D�悩SH1�D�悩��ݒ�
public:
	void SetSH0TransSelPCorSH1(int sel = 1);//���̒l�͂��ׂẴ`�����l���̐���M����SH�D��ɂ���
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

