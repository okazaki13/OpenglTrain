/** @file
	@JP
		@brief CSpidarHybrid class
		@author �ԉH ���m
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
// �C���^�t�F�[�X�݂̂̒�`
// ���̃N���X�� SpidarAPI.dll ����G�N�X�|�[�g����܂����B
/**
@JP
	CSpidarHybrid �N���X
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
