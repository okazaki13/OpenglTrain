/** @file
	@JP
		@brief CHbmsController クラス定義
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CHbmsController Class interface
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
	Hbms 制御機能 クラス
@END_JP
@EN
	Hbms Control function Class
@END_EN
 */
class AHSAPI_API CHbmsController :
	public CFx2Function
{
public:
	CHbmsController(void);
	virtual ~CHbmsController(void);

public:
	virtual std::string GetAPIStr();			///< @JP API文字列取得関数			@END_JP @EN Get API information str			@END_EN

};
