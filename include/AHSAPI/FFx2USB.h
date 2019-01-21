#pragma once
/** @file
	@JP
		@brief USB に関する機能クラス
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief USB Function Class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2008/11/11
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#include "FFx2USBBase.h"
#include <string>

// このクラスは AHSAPI.dll からエクスポートされました

/**
@JP
\class	AHS USB 機能クラス
@END_JP
@EN
\class	AHS USB function class
@END_EN
 */
class AHSAPI_API CFx2USB : public CFx2USBBase{
private:
	static unsigned int m_instNum;

private:
	HANDLE dev_handle;	///< @JP デバイスハンドル @END_JP @EN device handle				@END_EN
	int fifo_len;		///< @JP SlaveFIFOの長さ  @END_JP @EN Length of SlaveFIFO		@END_EN
	//int sleep_time;		///< @JP 休止時間         @END_JP @EN Sleep time				@END_EN


private:
	volatile int sem_send_pkt;
	volatile int sem_receive_pkt;

private:
public:
	unsigned char send_pkt_buf[512];	///< @JP 送信パケット @END_JP @EN Send packet    @END_EN
	unsigned char receive_pkt_buf[512];///< @JP 受信パケット @END_JP @EN Receive packet @END_EN



public:
	CFx2USB(void);	///< @JP コンストラクタ @END_JP @EN Constructor @END_EN
	virtual ~CFx2USB(void);///< @JP デストラクタ	@END_JP @EN Destructor @END_EN


public:
	virtual unsigned char* GetSendPkt();
	virtual unsigned char* GetReceivePkt();

public:
	virtual int Init(const int ezusb_N = -1);		///< @JP USB通信の初期化などの前処理を行う		@END_JP @EN Initialization of USB	@END_EN
	virtual int UsbBulkWrite(void);	///< @JP USBバルク転送（PC->Device）	@END_JP @EN USB bulk write (PC->Device)	@END_EN
	virtual int UsbBulkRead(void);	///< @JP USBバルク転送（Device->PC）	@END_JP @EN USB bulk read (Device->PC)	@END_EN
	//virtual int UsbBulkUpdate(void) = 0;///< @JP USBバルク転送：双方向（PC->Device & Device->PC）	@END_JP @EN USB bulk write & read（PC->Device & Device->PC）	@END_EN
	virtual void LogDisp();
	virtual void Disp(HANDLE hOut);


public:
	virtual std::string GetHandleStr();			///< @JP ハンドル文字列取得関数		@END_JP @EN Get handle information str		@END_EN
	virtual int GetFifoLen();	///< @JP SlaveFIFOの長さを取得					@END_JP @EN Get SlaveFIFO length	@END_EN
	virtual void InitPktData(unsigned char pkt[512]);///< @JP USB転送パケットの初期化	@END_JP @EN Initialization of USB backet	@END_EN

public:
	virtual void* GetDevice();

public:
	void SetFifoLen(int len);
};
