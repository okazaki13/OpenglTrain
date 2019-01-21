/** @file
@JP
@brief AHS Base Func クラス定義
@author 赤羽 克仁
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
\class	AHS Func クラス
@END_JP
@EN
\class	AHS Func Class
@END_EN
*/
class AHSAPI_API CFx2BaseFunc :
	public CFx2API
{
public:
	CFx2USBBase* m_p_usbIF;			///< @JP USB関係の処理	@END_JP @EN ＊＊＊ @END_EN
public:
	CFx2BaseFunc(void);				///< @JP コンストラクタ @END_JP @EN Constructor @END_EN
	virtual ~CFx2BaseFunc(void);	///< @JP デストラクタ	@END_JP @EN Destructor @END_EN

public:
	virtual int Init(const int ezusb_N = -1);	///< @JP USB通信の初期化などの前処理を行う		@END_JP @EN Initialization of USB	@END_EN
	int InitData();					///< @JP データの初期化		@END_JP @EN Initialization of data	@END_EN

	/**
	@JP
	USBバルク転送：双方向（PC->Device & Device->PC）
	@END_JP
	@EN
	USB bulk write & read（PC->Device & Device->PC）
	@END_EN
	*/
public:
	virtual int UsbBulkUpdate(void);

	/**
	@JP
	ロータリエンコーダ値の取得
	@param[in] ch 取得するチャンネル番号
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
	ロータリエンコーダ値のクリア
	@param[in] ch クリアするチャンネル番号
	@END_JP
	@EN
	Clear a rotary encoder counter
	@param[in] ch Chanel number of the counter
	@END_EN
	*/
public:
	void ClrEnc(int ch = -1,int flag = 0);//負の値はすべてのチャンネルをクリア

	/**
	@JP
	A/D コンバータ値の取得
	@param[in] ch 取得するチャンネル番号
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
	int   GetADC1HexRaw (int ch);// ADC1用
	int   GetADC1HexVal (int ch);// ADC1用
	float GetADC1Val    (int ch);// ADC1用
	float GetADC1MaxVolt();// ADC1用
	float GetADC1Volt   (int ch);// ADC1用

	/**
	@JP
	PWM値の設定
	@param[in] ch 設定するチャンネル番号
	@param[in] val 設定する値
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
	PWM値の取得
	@param[in] ch 取得するチャンネル番号
	@return PWMの値
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
	PWMを有効(無効)にする
	@param[in] ch 有効にするPWMのチャンネル番号(負の値はすべてのチャンネル)
	@param[in] isActive 有効にするとき：1(default)，無効にするとき：0
	@END_JP
	@EN
	Activate(or nonactive) of PWM
	@param[in] ch Chanel number of the PWM(Minus value means all chanel selection)
	@param[in] isActive When PWM is active：1(default), otherwise ：0
	@END_EN
	*/
public:
	void SetActivePWM(int ch, int isActive = 1);//負の値はすべてのチャンネルのPWMをアクティブ

	/**
	@JP
	PWMの有効（無効）値を取得する
	@END_JP
	@EN
	Get state of activate flag of PWM
	@END_EN
	*/
public:
	int GetActivePWM();

	/**
	@JP
	PWMの有効（無効）値を取得する
	@END_JP
	@EN
	Get state of activate flag of PWM
	@END_EN
	*/
public:
	int GetActivePWM(int ch);


	/**
	@JP
	Line Sensorの値を取得する
	@END_JP
	@EN
	Get value of line sensors
	@END_EN
	*/
public:
	int GetLineSensor();

	/**
	@JP
	Line Sensorの値を取得する(チャンネルごと)
	@END_JP
	@EN
	Get a value of line sensor
	@END_EN
	*/
public:
	int GetLineSensorL(int ch);

	/**
	@JP
	Line Sensorの値を取得する(チャンネルごと)
	@END_JP
	@EN
	Get a value of line sensor
	@END_EN
	*/
public:
	int GetLineSensorR(int ch);


	/**
	@JP
	外部入力値を取得する
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
	外部入力値を取得する(チャンネルごと)
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
	USB LoopBack テスト
	@END_JP
	@EN
	USB LoopBack test
	@END_EN
	*/
public:
	unsigned int LoopBackTest(const unsigned int loop_num = 10,const int isDebug = false);

	/**
	@JP
	USB AHS Init テスト
	@END_JP
	@EN
	USB AHS Init test
	@END_EN
	*/
public:
	unsigned int SystemInitTest(const int isDebug = false);

	/**
	@JP
	USB AHS Crc テスト
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
