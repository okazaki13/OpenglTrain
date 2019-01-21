/** @file
	@JP
		@brief CSpidarBase class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CSpidarBase class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "spidarapi.h"
#include "AHSVector.h"

#include <stdio.h>
#include <string>

#define AHS_SPIDAR8_NUM (8)
#define AHS_SPIDARX_NUM (8)
#define AHS_SPIDAR4_NUM (2)
#define AHS_SPIDARG_NUM (1)

///////////////////////////////////////////////////////////
//
// インタフェースのみの定義
// このクラスは SpidarAPI.dll からエクスポートされました。
/**
@JP
	CSpidarBase クラス
@END_JP
@EN
	CSpidarBase class
@END_EN
 */
template <class T>
class SPIDARAPI_API CSpidarBase :
	public CSpidarAPI
{
private:
	static unsigned int m_instNum;
protected:
	FILE* m_fp_log;

public:
	CSpidarBase	(void);
	virtual ~CSpidarBase(void);

public:	// for state
	virtual int Init			(std::string xmlFileName, int usb_id = -1)	= 0;
	virtual void StartHapticLoop(int msec = -1)	= 0;
	virtual void Active			(int isActive, int spidar_id = -1 )= 0;
	virtual void Calib			(int spidar_id = -1 )= 0;
	virtual void StopHapticLoop	()					= 0;
	virtual void Quit			()					= 0;
public:
	virtual void Disp			()					= 0;
public: // switch
	virtual int		GetDigitalSw(int ch,	int spidar_id = 0)	= 0;
	virtual T		GetAnalogSw	(int ch,	int spidar_id = 0)	= 0;
};
