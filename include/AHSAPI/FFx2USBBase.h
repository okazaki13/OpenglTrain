#pragma once
/** @file
	@JP
		@brief USB に関する機能クラス(基底)
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

#include "ffx2api.h"

/**
@JP
\class	AHS USB 機能クラス
@END_JP
@EN
\class	AHS USB function class
@END_EN
 */
class AHSAPI_API CFx2USBBase :
	public CFx2API
{
public:
	CFx2USBBase(void);
	virtual ~CFx2USBBase(void);

public:
	virtual unsigned char* GetSendPkt() = 0;
	virtual unsigned char* GetReceivePkt() = 0;

public:
	virtual int Init(const int ezusb_N = -1) = 0;		///< @JP USB通信の初期化などの前処理を行う		@END_JP @EN Initialization of USB	@END_EN
	virtual int UsbBulkWrite(void) = 0;	///< @JP USBバルク転送（PC->Device）	@END_JP @EN USB bulk write (PC->Device)	@END_EN
	virtual int UsbBulkRead(void) = 0;	///< @JP USBバルク転送（Device->PC）	@END_JP @EN USB bulk read (Device->PC)	@END_EN
	//virtual int UsbBulkUpdate(void) = 0;///< @JP USBバルク転送：双方向（PC->Device & Device->PC）	@END_JP @EN USB bulk write & read（PC->Device & Device->PC）	@END_EN
	virtual void LogDisp() = 0;
	virtual void Disp(HANDLE hOut) = 0;

public:
	virtual std::string GetHandleStr() = 0;			///< @JP ハンドル文字列取得関数		@END_JP @EN Get handle information str		@END_EN
	virtual int GetFifoLen() = 0;	///< @JP SlaveFIFOの長さを取得					@END_JP @EN Get SlaveFIFO length	@END_EN
	virtual void InitPktData(unsigned char pkt[512]) = 0;///< @JP USB転送パケットの初期化	@END_JP @EN Initialization of USB backet	@END_EN

public:
	virtual void* GetDevice() = 0;

};
