/** @file
	@JP
		@brief CAHSController �N���X��`
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
#include "ffx2function.h"


/**
@JP
	AHS ����@�\ �N���X
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
	virtual std::string GetAPIStr();			///< @JP API������擾�֐�			@END_JP @EN Get API information str			@END_EN

public:
	virtual unsigned int GetModuleNum();
	virtual unsigned int GetEncNum();
	virtual unsigned int GetPwmNum();
	virtual unsigned int GetAdcNum();
	virtual unsigned int GetPIDNum();

public:
	virtual int GetDipSW(int ch);// �R���g���[����ID�̎擾�iDIP�X�C�b�`�̒l�j
	virtual int GetUserSW(int ch);// �R���g���[����ID�̎擾�iDIP�X�C�b�`�̒l�j

	//virtual int GetDeviceID();// �R���g���[����ID�̎擾�iDIP�X�C�b�`�̒l�j

};
