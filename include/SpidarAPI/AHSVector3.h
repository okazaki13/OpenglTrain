/** @file
	@JP
		@brief CAHSVector template class
		@author �ԉH ���m
	@END_JP
	@EN
		@brief CAHSVector template class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "AHSVector.h"

/**
@JP
	CAHSVector �N���X
@END_JP
@EN
	CAHSVector class
@END_EN
 */
template <class T>
class SPIDARAPI_API CAHSVector3 :
	public CAHSVector<T,3>
{
public:
	CAHSVector3(void);
	CAHSVector3(T x,T y,T z){this->X() = x;this->Y() = y;this->Z() = z;};
	virtual ~CAHSVector3(void);

public:
	T& X();
	T& Y();
	T& Z();
	//// �萔�{
	//CAHSVector3<T> operator* (T obj);

	// �O��
	CAHSVector3<T> operator^ (CAHSVector3<T>& obj);
	//
	CAHSVector3<T>& operator= (CAHSVector<T,3>& obj);
};


typedef CAHSVector3<float>		CVec3f;
typedef CAHSVector3<double>		CVec3d;
