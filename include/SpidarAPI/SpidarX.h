/** @file
	@JP
		@brief SpidarX API
		@author ê‘âH çéêm
	@END_JP
	@EN
		@brief SpidarX API
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "spidarenhance.h"
#include "AHSVector3.h"
#include "AHSQPProg.h"

#include "AHSVC6DOF.h"

/**
@JP
	CSpidarX ÉNÉâÉX
@END_JP
@EN
	CSpidarX class
@END_EN
 */
template<class T>
class CSpidarX :
	public CSpidarEnhance<T>
{
protected:
	CAHSVC6DOF<T>		m_vc[AHS_SPIDARX_NUM];

public:
	CSpidarX(void);
	virtual ~CSpidarX(void);
	virtual int Init			(std::string xmlFileName, int usb_id = -1);

public: // for Virtual Coupling in impedance control
	virtual CAHSVirtualCoupling<T>& GetVirtualCoupling(int spidar_id = 0);

};
