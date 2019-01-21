/** @file
	@JP
		@brief CSpidarHybrid class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CSpidarHybrid class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "SpidarImpedance.h"
#include "SpidarAdmittance.h"


///////////////////////////////////////////////////////////
//
// インタフェースのみの定義
// このクラスは SpidarAPI.dll からエクスポートされました。
/**
@JP
	CSpidarHybrid クラス
@END_JP
@EN
	CSpidarHybrid class
@END_EN
 */
template<class T>
class SPIDARAPI_API CSpidarHybrid :
	public CSpidarImpedance<T>, public CSpidarAdmittance<T>
{
public:
	CSpidarHybrid(void);
	virtual ~CSpidarHybrid(void);
};
