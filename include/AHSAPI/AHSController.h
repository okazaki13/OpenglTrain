/** @file
	@JP
		@brief CAHSController クラス定義
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CAHSFunction Class interface
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/1/15
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/


#pragma once
#include "ffx2function.h"


/**
@JP
	AHS 制御機能 クラス
@END_JP
@EN
	AHS Control function Class
@END_EN
 */

class AHSAPI_API CAHSController :
	public CFx2Function
{
public:
	CAHSController(void);
	virtual ~CAHSController(void);

public:
	virtual std::string GetAPIStr();			///< @JP API文字列取得関数			@END_JP @EN Get API information str			@END_EN

public:
	virtual unsigned int GetModuleNum();
	virtual unsigned int GetEncNum();
	virtual unsigned int GetPwmNum();
	virtual unsigned int GetAdcNum();
	virtual unsigned int GetPIDNum();

public:
	virtual int GetDipSW(int ch);// コントローラのIDの取得（DIPスイッチの値）
	virtual int GetUserSW(int ch);// コントローラのIDの取得（DIPスイッチの値）

	//virtual int GetDeviceID();// コントローラのIDの取得（DIPスイッチの値）

};
