/** @file
	@JP
		@brief CAHSMatrix template class
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief CAHSMatrix template class
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/06/30
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/
#pragma once
#include <math.h>
#include "SpidarAPI.h"
#include "AHSVector.h"
#include "AHSQPProg.h"

//////////////////////////////////////////////////////////////////////////////
// (M,N)行列
/**
@JP
	CAHSMatrix クラス
@END_JP
@EN
	CAHSMatrix class
@END_EN
 */
template <class T, unsigned int M, unsigned int N>
class SPIDARAPI_API CAHSMatrix :
	public CSpidarAPI
{
protected:
	T data [M*N];

public:
	CAHSMatrix(void);
	virtual ~CAHSMatrix(void);

public:
	T* Data();
	void zero();
	void unit();

	CAHSMatrix<T,M,N>& copy(CAHSMatrix<T,M,N>& obj);

public:
	// 転置行列
	CAHSMatrix<T,N,M> tr();

public:
	// 和
	CAHSMatrix<T,M,N> operator+ (CAHSMatrix<T,M,N>& obj);
	// 差
	CAHSMatrix<T,M,N> operator- (CAHSMatrix<T,M,N>& obj);

	// 和＋＝
	CAHSMatrix<T,M,N>& operator+= (CAHSMatrix<T,M,N>& obj);

	// 差ー＝
	CAHSMatrix<T,M,N>& operator-= (CAHSMatrix<T,M,N>& obj);


	// マイナス
	CAHSMatrix<T,M,N> operator- ();

	// 定数倍
	CAHSMatrix<T,M,N> operator* (T obj);
	// 定数倍*=
	CAHSMatrix<T,M,N>& operator*= (T obj);

	// 定数割
	CAHSMatrix<T,M,N> operator/ (T obj);
	// 定数割/=
	CAHSMatrix<T,M,N>& operator/= (T obj);

	//行列の積 (M,N)x(N,M)=(M,M)
	CAHSMatrix<T,M,M> operator* (CAHSMatrix<T,N,M>& obj);

	// 行列とベクトルの積
	CAHSVector<T,M> operator* (CAHSVector<T,N>& obj);

public:

	// dL = J drを解く
	// 冗長なので、内部ではシグマ逆を使って正定値対象行列にして
	// コレスキー法によりAx = b を解く
	// dL in
	// dr out
	// sigma in
	void chosol_sigma(CAHSVector<T,M>& dL, CAHSVector<T,N>& dr, T sigma);

public:



	// 連立1次方程式Ax=bの
	// 係数行列Aが正定値対象行列のとき
	// コレスキー法により高速に解く
	static void chosol2(T a[N*N],T x[N],T b[N]);

public:
	// 連立一次方程式Ax=bを
	// Gauss-Jordan法により解く(解はbに格納される)
	static int GaussJordan(T a[N*N], T b[N]);

public:
	void disp();
	void disp_t();

};


//////////////////////////////////////////////////////////////////////////////
//
typedef CAHSMatrix<float,2,2>		CMat22f;
typedef CAHSMatrix<float,3,3>		CMat33f;
typedef CAHSMatrix<float,4,4>		CMat44f;
typedef CAHSMatrix<float,6,6>		CMat66f;
typedef CAHSMatrix<float,8,8>		CMat88f;
typedef CAHSMatrix<float,8,6>		CMat86f;

typedef CAHSMatrix<double,2,2>		CMat22d;
typedef CAHSMatrix<double,3,3>		CMat33d;
typedef CAHSMatrix<double,4,4>		CMat44d;
typedef CAHSMatrix<double,6,6>		CMat66d;
typedef CAHSMatrix<double,8,8>		CMat88d;
typedef CAHSMatrix<double,8,6>		CMat86d;
