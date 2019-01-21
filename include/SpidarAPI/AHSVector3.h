/** @file
	@JP
		@brief CAHSVector template class
		@author ê‘âH çéêm
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
	CAHSVector ÉNÉâÉX
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
	//// íËêîî{
	//CAHSVector3<T> operator* (T obj);

	// äOêœ
	CAHSVector3<T> operator^ (CAHSVector3<T>& obj);
	//
	CAHSVector3<T>& operator= (CAHSVector<T,3>& obj);
};


typedef CAHSVector3<float>		CVec3f;
typedef CAHSVector3<double>		CVec3d;
