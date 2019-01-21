/* @file
	@JP
		@brief CAHSQPProg template class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CAHSQPProg template class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include "SpidarAPI.h"
#include "AHSVector3.h"

/**
@JP
	CAHSQuaternion クラス
@END_JP
@EN
	CAHSQuaternion class
@END_EN
 */
template<class T>
class SPIDARAPI_API CAHSQuaternion :
	public CSpidarAPI
{
protected:
	T w;
	CAHSVector3<T> v;

public:
	CAHSQuaternion(void);
#if 1
	CAHSQuaternion(T w,T x,T y,T z){
		this->w = w;
		this->v.X() = x;
		this->v.Y() = y;
		this->v.Z() = z;
	};
#endif
	virtual ~CAHSQuaternion(void);

#if 0
public:
	void init(T w,T x,T y,T z){
		this->w = w;
		this->v.X() = x;
		this->v.Y() = y;
		this->v.Z() = z;
	}
#endif

public:
	T& X();
	T& Y();
	T& Z();
	T& W();

	CAHSVector3<T>& V();

public:
	void unit();
	// ベクトルのノルム
	T norm();
	T norm2();

	//ベクトルの正規化
	CAHSQuaternion<T> normal();


	//共役四元数
	CAHSQuaternion<T> conj();

	//逆元
	//CAHSQuaternion<T> inv();

public:
	// 回転の定数倍を行う
	CAHSQuaternion<T> operator* (T scale);

	// クオータニオンの積
	CAHSQuaternion<T> operator* (CAHSQuaternion<T>& obj);

	// ベクトルの回転
	// クオータニオンとベクトルの積(QT^ * V * QT)
	CAHSVector3<T> operator* (CAHSVector3<T>& obj);

public:
	// v方向にtheta回転する四元数
	void makeQT(CAHSVector3<T> v, T theta);

public:
	void disp();

};

typedef CAHSQuaternion<float>	CQt4f;
typedef CAHSQuaternion<double>	CQt4d;
