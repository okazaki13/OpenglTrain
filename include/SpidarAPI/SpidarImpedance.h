/** @file
	@JP
		@brief CSpidarImpedance class
		@author �ԉH ���m
	@END_JP
	@EN
		@brief CSpidarImpedance class
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
	CSpidarImpedance �N���X
@END_JP
@EN
	CSpidarImpedance class
@END_EN
 */
template<class T>
class SPIDARAPI_API CSpidarImpedance :
	public virtual CSpidarBase<T>
{
public:
	CSpidarImpedance(void);
	virtual ~CSpidarImpedance(void);

public: // for Impedance
	virtual CAHSVector3<T>		GetPos		(int spidar_id = 0)	= 0;
	virtual CAHSQuaternion<T>	GetOri		(int spidar_id = 0)	= 0;
	virtual void				SetForce	(CAHSVector3<T>& f,	int spidar_id = 0)	= 0;
	virtual void				SetTorque	(CAHSVector3<T>& t,	int spidar_id = 0)	= 0;

	virtual CAHSVector3<T>		GetPosVel	(int spidar_id = 0)	= 0;
	virtual CAHSVector3<T>		GetOriVel	(int spidar_id = 0)	= 0;
	virtual CAHSVector3<T>		GetPosVelIir	(int spidar_id = 0)	= 0;
	virtual CAHSVector3<T>		GetOriVelIir	(int spidar_id = 0)	= 0;

};

