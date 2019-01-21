/** @file
@JP
@brief AHS Base Func �N���X��`
@author �ԉH ���m
@END_JP
@EN
@brief AHS Base Func Class interface
@author Katsuhito AKAHANE
@END_EN

@date	2008/11/11
*/
/*
* Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/


#pragma once
#include "FFx2API.h"

class CFx2USBBase;

/**
@JP
\class	AHS Func �N���X
@END_JP
@EN
\class	AHS Func Class
@END_EN
*/
class AHSAPI_API CFx2BaseFunc :
	public CFx2API
{
public:
	CFx2USBBase* m_p_usbIF;			///< @JP USB�֌W�̏���	@END_JP @EN ������ @END_EN
public:
	CFx2BaseFunc(void);				///< @JP �R���X�g���N�^ @END_JP @EN Constructor @END_EN
	virtual ~CFx2BaseFunc(void);	///< @JP �f�X�g���N�^	@END_JP @EN Destructor @END_EN

public:
	virtual int Init(const int ezusb_N = -1);	///< @JP USB�ʐM�̏������Ȃǂ̑O�������s��		@END_JP @EN Initialization of USB	@END_EN
	int InitData();					///< @JP �f�[�^�̏�����		@END_JP @EN Initialization of data	@END_EN

	/**
	@JP
	USB�o���N�]���F�o�����iPC->Device & Device->PC�j
	@END_JP
	@EN
	USB bulk write & read�iPC->Device & Device->PC�j
	@END_EN
	*/
public:
	virtual int UsbBulkUpdate(void);

	/**
	@JP
	���[�^���G���R�[�_�l�̎擾
	@param[in] ch �擾����`�����l���ԍ�
	@END_JP
	@EN
	Get a rotary encoder counter
	@param[in] ch Chanel number of the counter
	@END_EN
	*/
public:
	int		GetEncCount(int ch);
//	float	GetEncCountF(int ch);
	float	GetEncVel(int ch);
	float	GetEncAcc(int ch);
	//float	GetEncVel1(int ch);
	//float	GetEncAcc1(int ch);

public:
	void  SetEncPhs(int ch,int phs);
public:
	int  GetEncPhs(int ch);
	char  GetEncPhsChar(int ch);

	/**
	@JP
	���[�^���G���R�[�_�l�̃N���A
	@param[in] ch �N���A����`�����l���ԍ�
	@END_JP
	@EN
	Clear a rotary encoder counter
	@param[in] ch Chanel number of the counter
	@END_EN
	*/
public:
	void ClrEnc(int ch = -1,int flag = 0);//���̒l�͂��ׂẴ`�����l�����N���A

	/**
	@JP
	A/D �R���o�[�^�l�̎擾
	@param[in] ch �擾����`�����l���ԍ�
	@END_JP
	@EN
	Get a A/D converter value
	@param[in] ch Chanel number of the A/D converter
	@END_EN
	*/
public:
	int   GetADCHexRaw (int ch);
	int   GetADCHexVal (int ch);
	float GetADCVal    (int ch);
	float GetADCMaxVolt();
	float GetADCVolt   (int ch);
public:
	int   GetADC1HexRaw (int ch);// ADC1�p
	int   GetADC1HexVal (int ch);// ADC1�p
	float GetADC1Val    (int ch);// ADC1�p
	float GetADC1MaxVolt();// ADC1�p
	float GetADC1Volt   (int ch);// ADC1�p

	/**
	@JP
	PWM�l�̐ݒ�
	@param[in] ch �ݒ肷��`�����l���ԍ�
	@param[in] val �ݒ肷��l
	@END_JP
	@EN
	Set a PWM value
	@param[in] ch Chanel number of the PWM
	@param[in] val setting value of the PWM
	@END_EN
	*/
public:
	void SetPWMVal(int ch,int val);
	void SetPWMLimitVal(int ch,int val);
	void SetPWMLimitDutyVal(int ch,float duty);

	/**
	@JP
	PWM�l�̎擾
	@param[in] ch �擾����`�����l���ԍ�
	@return PWM�̒l
	@END_JP
	@EN
	Set a PWM value
	@param[in] ch Chanel number of the PWM
	@return PWM value
	@END_EN
	*/
public:
	int  GetPWMVal(int ch);
	int  GetPWMLimitVal(int ch);

	/**
	@JP
	PWM��L��(����)�ɂ���
	@param[in] ch �L���ɂ���PWM�̃`�����l���ԍ�(���̒l�͂��ׂẴ`�����l��)
	@param[in] isActive �L���ɂ���Ƃ��F1(default)�C�����ɂ���Ƃ��F0
	@END_JP
	@EN
	Activate(or nonactive) of PWM
	@param[in] ch Chanel number of the PWM(Minus value means all chanel selection)
	@param[in] isActive When PWM is active�F1(default), otherwise �F0
	@END_EN
	*/
public:
	void SetActivePWM(int ch, int isActive = 1);//���̒l�͂��ׂẴ`�����l����PWM���A�N�e�B�u

	/**
	@JP
	PWM�̗L���i�����j�l���擾����
	@END_JP
	@EN
	Get state of activate flag of PWM
	@END_EN
	*/
public:
	int GetActivePWM();

	/**
	@JP
	PWM�̗L���i�����j�l���擾����
	@END_JP
	@EN
	Get state of activate flag of PWM
	@END_EN
	*/
public:
	int GetActivePWM(int ch);


	/**
	@JP
	Line Sensor�̒l���擾����
	@END_JP
	@EN
	Get value of line sensors
	@END_EN
	*/
public:
	int GetLineSensor();

	/**
	@JP
	Line Sensor�̒l���擾����(�`�����l������)
	@END_JP
	@EN
	Get a value of line sensor
	@END_EN
	*/
public:
	int GetLineSensorL(int ch);

	/**
	@JP
	Line Sensor�̒l���擾����(�`�����l������)
	@END_JP
	@EN
	Get a value of line sensor
	@END_EN
	*/
public:
	int GetLineSensorR(int ch);


	/**
	@JP
	�O�����͒l���擾����
	@END_JP
	@EN
	Get a value of external input
	@END_EN
	*/
public:
	unsigned short GetExInput0();
	unsigned short GetExInput1();
	unsigned short GetExInput2();
	unsigned short GetExInput3();

	/**
	@JP
	�O�����͒l���擾����(�`�����l������)
	@END_JP
	@EN
	Get a value of external input
	@END_EN
	*/
public:
	int GetExInput0(int ch);
	int GetExInput1(int ch);
	int GetExInput2(int ch);
	int GetExInput3(int ch);
	int GetTouchSense(int ch);


	/**
	@JP
	USB LoopBack �e�X�g
	@END_JP
	@EN
	USB LoopBack test
	@END_EN
	*/
public:
	unsigned int LoopBackTest(const unsigned int loop_num = 10,const int isDebug = false);

	/**
	@JP
	USB AHS Init �e�X�g
	@END_JP
	@EN
	USB AHS Init test
	@END_EN
	*/
public:
	unsigned int SystemInitTest(const int isDebug = false);

	/**
	@JP
	USB AHS Crc �e�X�g
	@END_JP
	@EN
	USB AHS Init test
	@END_EN
	*/
public:
	unsigned int SystemCrcTest(const int isDebug = false);

public:
	virtual unsigned int GetModuleNum();
	virtual unsigned int GetEncNum();
	virtual unsigned int GetPwmNum();
	virtual unsigned int GetAdcNum();
public:
	virtual int GetMaxEncVal();
	virtual int GetMinEncVal();
	virtual int GetDPEncVal();

	virtual int GetMaxAdcVal();
	virtual int GetMinAdcVal();
	virtual int GetDPAdcVal();

	virtual int GetMaxPwmVal();
	virtual int GetMinPwmVal();
	virtual int GetDPPwmVal();

public:
	virtual float GetAdcRefV();

protected:
	virtual void LogDisp();
public:
	virtual void Disp(HANDLE hOut);

};
