/** @file
	@JP
		@brief CSpidarAPI class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CSpidarAPI class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once


#ifdef SPIDARAPI_EXPORTS
#define SPIDARAPI_API __declspec(dllexport)
#else
#define SPIDARAPI_API __declspec(dllimport)
#endif

///////////////////////////////////////////////////////////
//
// SpidarAPIのすべてのクラスの親クラス
// このクラスは SpidarAPI.dll からエクスポートされました。
/**
@JP
	CSpidarAPI クラス
@END_JP
@EN
	CSpidarAPI class
@END_EN
 */
class SPIDARAPI_API CSpidarAPI {
public:
	CSpidarAPI(void);
	virtual ~CSpidarAPI(void);
};
