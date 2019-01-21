#pragma once
#include "AHS_SpidarBase.h"


class SPIDARAHS_API AHS_Spidar4 :
	public AHS_SpidarBase<float>
{
public:
	AHS_Spidar4(void);
	virtual ~AHS_Spidar4(void);
public:
	virtual int Init(std::string xmlFileName, int usb_id = -1);
};
