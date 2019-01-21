/** @file
	@JP
		@brief CAHSFunction クラス定義
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
#include "FFx2PID.h"

/**
@JP
	AHS 制御機能 クラス
@END_JP
@EN
	AHS Control function Class
@END_EN
 */
class AHSAPI_API CFx2Function :
	public CFx2PID
{
public:
	CFx2Function(void);
	virtual ~CFx2Function(void);
public:
	int GetMotorNum();

};
