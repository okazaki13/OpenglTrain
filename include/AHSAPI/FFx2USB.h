#pragma once
/** @file
	@JP
		@brief USB �Ɋւ���@�\�N���X
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
#include "FFx2USBBase.h"
#include <string>

// ���̃N���X�� AHSAPI.dll ����G�N�X�|�[�g����܂���

/**
@JP
\class	AHS USB �@�\�N���X
@END_JP
@EN
\class	AHS USB function class
@END_EN
 */
class AHSAPI_API CFx2USB : public CFx2USBBase{
private:
	static unsigned int m_instNum;

private:
	HANDLE dev_handle;	///< @JP �f�o�C�X�n���h�� @END_JP @EN device handle				@END_EN
	int fifo_len;		///< @JP SlaveFIFO�̒���  @END_JP @EN Length of SlaveFIFO		@END_EN
	//int sleep_time;		///< @JP �x�~����         @END_JP @EN Sleep time				@END_EN


private:
	volatile int sem_send_pkt;
	volatile int sem_receive_pkt;

private:
public:
	unsigned char send_pkt_buf[512];	///< @JP ���M�p�P�b�g @END_JP @EN Send packet    @END_EN
	unsigned char receive_pkt_buf[512];///< @JP ��M�p�P�b�g @END_JP @EN Receive packet @END_EN



public:
	CFx2USB(void);	///< @JP �R���X�g���N�^ @END_JP @EN Constructor @END_EN
	virtual ~CFx2USB(void);///< @JP �f�X�g���N�^	@END_JP @EN Destructor @END_EN


public:
	virtual unsigned char* GetSendPkt();
	virtual unsigned char* GetReceivePkt();

public:
	virtual int Init(const int ezusb_N = -1);		///< @JP USB�ʐM�̏������Ȃǂ̑O�������s��		@END_JP @EN Initialization of USB	@END_EN
	virtual int UsbBulkWrite(void);	///< @JP USB�o���N�]���iPC->Device�j	@END_JP @EN USB bulk write (PC->Device)	@END_EN
	virtual int UsbBulkRead(void);	///< @JP USB�o���N�]���iDevice->PC�j	@END_JP @EN USB bulk read (Device->PC)	@END_EN
	//virtual int UsbBulkUpdate(void) = 0;///< @JP USB�o���N�]���F�o�����iPC->Device & Device->PC�j	@END_JP @EN USB bulk write & read�iPC->Device & Device->PC�j	@END_EN
	virtual void LogDisp();
	virtual void Disp(HANDLE hOut);


public:
	virtual std::string GetHandleStr();			///< @JP �n���h��������擾�֐�		@END_JP @EN Get handle information str		@END_EN
	virtual int GetFifoLen();	///< @JP SlaveFIFO�̒������擾					@END_JP @EN Get SlaveFIFO length	@END_EN
	virtual void InitPktData(unsigned char pkt[512]);///< @JP USB�]���p�P�b�g�̏�����	@END_JP @EN Initialization of USB backet	@END_EN

public:
	virtual void* GetDevice();

public:
	void SetFifoLen(int len);
};
