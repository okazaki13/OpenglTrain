/** @file
	@JP
		@brief CHbmsController �N���X��`
		@author �ԉH ���m
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
	Hbms ����@�\ �N���X
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
	virtual std::string GetAPIStr();			///< @JP API������擾�֐�			@END_JP @EN Get API information str			@END_EN

};
