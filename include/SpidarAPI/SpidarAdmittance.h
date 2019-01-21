/** @file
	@JP
		@brief CSpidarAdmittance class
		@author �ԉH ���m
	@END_JP
	@EN
		@brief CSpidarAdmittance class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "spidarbase.h"
#include "AHSVector.h"
#include "AHSQuaternion.h"

///////////////////////////////////////////////////////////
//
// �C���^�t�F�[�X�݂̂̒�`
// ���̃N���X�� SpidarAPI.dll ����G�N�X�|�[�g����܂����B
/**
@JP
	CSpidarAdmittance �N���X
@END_JP
@EN
	CSpidarAdmittance class
@END_EN
 */
template<class T>
class SPIDARAPI_API CSpidarAdmittance :
	public virtual CSpidarBase<T>
{
public:
	CSpidarAdmittance(void);
	virtual ~CSpidarAdmittance(void);


public:	// for Admittance
	virtual CAHSVector3<T>	GetForce	(int spidar_id = 0)	= 0;
	virtual CAHSVector3<T>	GetTorque	(int spidar_id = 0)	= 0;
	virtual void			SetPos		(CAHSVector3<T>&     pos,	int spidar_id = 0)	= 0;
	virtual void			SetOri		(CAHSQuaternion<T>&  ori,	int spidar_id = 0)	= 0;
};


