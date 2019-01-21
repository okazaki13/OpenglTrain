/** @file
	@JP
		@brief CAHSFunction �N���X��`
		@author �ԉH ���m
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
	AHS ����@�\ �N���X
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
