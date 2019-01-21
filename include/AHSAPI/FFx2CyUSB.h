#pragma once
#include "ffx2usb.h"
#include "cusb2.h"
#include "cyapi.h"

/**
@JP
\class	AHS USB �@�\�N���X (CyUSB��)
@END_JP
@EN
\class	AHS USB function class (for CyUSB)
@END_EN
 */
class AHSAPI_API CFx2CyUSB :
	public CFx2USB
{
public:
	cusb2 *gpUsb;
	UCHAR dev_id;

public:
	CCyUSBEndPoint *inep		;//= usb->get_endpoint(0x86);
	CCyUSBEndPoint *outep		;//= usb->get_endpoint(0x02);
	CCyUSBEndPoint *outep_cmd	;//= usb->get_endpoint(0x08);

public:
	CFx2CyUSB(void);
	virtual ~CFx2CyUSB(void);


public:
	virtual int Init(const int ezusb_N = -1);		///< @JP USB�ʐM�̏������Ȃǂ̑O�������s��		@END_JP @EN Initialization of USB	@END_EN
	virtual int UsbBulkWrite(void);	///< @JP USB�o���N�]���iPC->Device�j	@END_JP @EN USB bulk write (PC->Device)	@END_EN
	virtual int UsbBulkRead(void);	///< @JP USB�o���N�]���iDevice->PC�j	@END_JP @EN USB bulk read (Device->PC)	@END_EN

public:
	virtual void* GetDevice();
};
