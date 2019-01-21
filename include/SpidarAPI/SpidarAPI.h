/** @file
	@JP
		@brief CSpidarAPI class
		@author �ԉH ���m
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
// SpidarAPI�̂��ׂẴN���X�̐e�N���X
// ���̃N���X�� SpidarAPI.dll ����G�N�X�|�[�g����܂����B
/**
@JP
	CSpidarAPI �N���X
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
