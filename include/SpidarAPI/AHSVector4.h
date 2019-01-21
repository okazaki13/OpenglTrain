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
	CAHSVector4 ÉNÉâÉX
@END_JP
@EN
	CAHSVector4 class
@END_EN
 */
template <class T>
class SPIDARAPI_API CAHSVector4 :
	public CAHSVector<T,4>
{
public:
	CAHSVector4(void);
	virtual ~CAHSVector4(void);
public:
	T& X();
	T& Y();
	T& Z();
	T& W();

	//
	CAHSVector4<T>& operator= (CAHSVector<T,4>& obj);
};


typedef CAHSVector4<float>		CVec4f;
typedef CAHSVector4<double>		CVec4d;
