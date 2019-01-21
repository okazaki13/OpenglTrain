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
#include <math.h>
#include "SpidarAPI.h"


//////////////////////////////////////////////////////////////////////////////
// Quadratic Programming (Active Set Method)
// Copy right Katsuhito AKAHANE
//
// f(x) = (1/2)x'Qx - c'x    ->minimize
// minX <= x <= maxX
//
/**
@JP
	CAHSQPProg クラス
@END_JP
@EN
	CAHSQPProg class
@END_EN
 */
template <class T, unsigned int N>
class SPIDARAPI_API CAHSQPProg :
	public CSpidarAPI
{
public:
	T gVecX[N];		//out:最適解
	T gMatQ[N][N];	//in:二次計画の２次の係数
	T gVecC[N];		//in:二次計画の１次の係数
protected:
	T gMatA[N][N];
	T minX;
	T maxX;

	T gMatR[N][N];
	T gVecL[N];

	T gVecXYNext[2*N];
	T gVecD[N];

	int isActiveSet[N];

public:
	CAHSQPProg(void);
	virtual ~CAHSQPProg(void);

	//
	// 二次計画法の初期化処理関数
	// ボックス条件の設定 (minTin <= X <= maxTin)
public:
	void InitQuadpr(T minTin, T maxTin);
	//
	// 二次計画法メイン関数
	// この関数を呼び出す前に
	// InitQuadpr() を呼び出し
	// gMatQ[N][N]
	// gVecC[N]
	// の設定をすること
	// また、gMatQ,gVecC は、計算の前後で変更されることはない。
public:
	int quadpr(const int max = 10);

protected:
	//
	// 各ステップで求める連立１次方程式の係数行列を生成する
	void MakeCalcMat();
	//
	//　N次元連立１次方程式を解く
	void CalcMatRXL(T a[][N], T x[], T b[]);
	void CalcMatRXL_Pivot(T a[][N], T x[], T b[]);

	//
	// gVecX[] == gVecXYNext[] をチェック
	int isVecX_VecXNext();
	//
	// 最適解が見つかったかどうかをチェック
	int CalcLambda();
	//
	// 探索方向のステップ幅を求める
	void CalcAlpha();
};

typedef CAHSQPProg<float,2>		CAHSQPSolver2f;
typedef CAHSQPProg<float,3>		CAHSQPSolver3f;
typedef CAHSQPProg<float,4>		CAHSQPSolver4f;
typedef CAHSQPProg<float,5>		CAHSQPSolver5f;
typedef CAHSQPProg<float,6>		CAHSQPSolver6f;
typedef CAHSQPProg<float,7>		CAHSQPSolver7f;
typedef CAHSQPProg<float,8>		CAHSQPSolver8f;
typedef CAHSQPProg<float,9>		CAHSQPSolver9f;
typedef CAHSQPProg<float,10>	CAHSQPSolver10f;
typedef CAHSQPProg<float,11>	CAHSQPSolver11f;
typedef CAHSQPProg<float,12>	CAHSQPSolver12f;

typedef CAHSQPProg<double,2>	CAHSQPSolver2d;
typedef CAHSQPProg<double,3>	CAHSQPSolver3d;
typedef CAHSQPProg<double,4>	CAHSQPSolver4d;
typedef CAHSQPProg<double,5>	CAHSQPSolver5d;
typedef CAHSQPProg<double,6>	CAHSQPSolver6d;
typedef CAHSQPProg<double,7>	CAHSQPSolver7d;
typedef CAHSQPProg<double,8>	CAHSQPSolver8d;
typedef CAHSQPProg<double,9>	CAHSQPSolver9d;
typedef CAHSQPProg<double,10>	CAHSQPSolver10d;
typedef CAHSQPProg<double,11>	CAHSQPSolver11d;
typedef CAHSQPProg<double,12>	CAHSQPSolver12d;

