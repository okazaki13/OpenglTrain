#pragma once
#include "AHS_SpidarBase.h"

class AHS_SpidarX :
	public AHS_SpidarBase<float>
{
public:
	AHS_SpidarX(void);
	virtual ~AHS_SpidarX(void);
public:
	virtual int Init(std::string xmlFileName, int usb_id = -1);
};
