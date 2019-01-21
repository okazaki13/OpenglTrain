#pragma once
#include "AHS_SpidarBase.h"


class SPIDARAHS_API AHS_SpidarG :
	public AHS_SpidarBase<float>
{
public:
	AHS_SpidarG(void);
	virtual ~AHS_SpidarG(void);
public:
	virtual int Init(std::string xmlFileName, int usb_id = -1);
};
