#pragma once
/** @file
	@JP
		@brief USB �Ɋւ���@�\�N���X(���)
		@author �ԉH ���m
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
\class	AHS USB �@�\�N���X
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
	virtual int Init(const int ezusb_N = -1) = 0;		///< @JP USB�ʐM�̏������Ȃǂ̑O�������s��		@END_JP @EN Initialization of USB	@END_EN
	virtual int UsbBulkWrite(void) = 0;	///< @JP USB�o���N�]���iPC->Device�j	@END_JP @EN USB bulk write (PC->Device)	@END_EN
	virtual int UsbBulkRead(void) = 0;	///< @JP USB�o���N�]���iDevice->PC�j	@END_JP @EN USB bulk read (Device->PC)	@END_EN
	//virtual int UsbBulkUpdate(void) = 0;///< @JP USB�o���N�]���F�o�����iPC->Device & Device->PC�j	@END_JP @EN USB bulk write & read�iPC->Device & Device->PC�j	@END_EN
	virtual void LogDisp() = 0;
	virtual void Disp(HANDLE hOut) = 0;

public:
	virtual std::string GetHandleStr() = 0;			///< @JP �n���h��������擾�֐�		@END_JP @EN Get handle information str		@END_EN
	virtual int GetFifoLen() = 0;	///< @JP SlaveFIFO�̒������擾					@END_JP @EN Get SlaveFIFO length	@END_EN
	virtual void InitPktData(unsigned char pkt[512]) = 0;///< @JP USB�]���p�P�b�g�̏�����	@END_JP @EN Initialization of USB backet	@END_EN

public:
	virtual void* GetDevice() = 0;

};
