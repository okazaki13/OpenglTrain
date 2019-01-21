/** @file
	@JP
		@brief CSpidarAdmittance class
		@author 赤羽 克仁
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
// インタフェースのみの定義
// このクラスは SpidarAPI.dll からエクスポートされました。
/**
@JP
	CSpidarAdmittance クラス
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


