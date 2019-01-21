/** @file
	@JP
		@brief CAHSMatrix template class
		@author �ԉH ���m
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
// (M,N)�s��
/**
@JP
	CAHSMatrix �N���X
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
	// �]�u�s��
	CAHSMatrix<T,N,M> tr();

public:
	// �a
	CAHSMatrix<T,M,N> operator+ (CAHSMatrix<T,M,N>& obj);
	// ��
	CAHSMatrix<T,M,N> operator- (CAHSMatrix<T,M,N>& obj);

	// �a�{��
	CAHSMatrix<T,M,N>& operator+= (CAHSMatrix<T,M,N>& obj);

	// ���[��
	CAHSMatrix<T,M,N>& operator-= (CAHSMatrix<T,M,N>& obj);


	// �}�C�i�X
	CAHSMatrix<T,M,N> operator- ();

	// �萔�{
	CAHSMatrix<T,M,N> operator* (T obj);
	// �萔�{*=
	CAHSMatrix<T,M,N>& operator*= (T obj);

	// �萔��
	CAHSMatrix<T,M,N> operator/ (T obj);
	// �萔��/=
	CAHSMatrix<T,M,N>& operator/= (T obj);

	//�s��̐� (M,N)x(N,M)=(M,M)
	CAHSMatrix<T,M,M> operator* (CAHSMatrix<T,N,M>& obj);

	// �s��ƃx�N�g���̐�
	CAHSVector<T,M> operator* (CAHSVector<T,N>& obj);

public:

	// dL = J dr������
	// �璷�Ȃ̂ŁA�����ł̓V�O�}�t���g���Đ���l�Ώۍs��ɂ���
	// �R���X�L�[�@�ɂ��Ax = b ������
	// dL in
	// dr out
	// sigma in
	void chosol_sigma(CAHSVector<T,M>& dL, CAHSVector<T,N>& dr, T sigma);

public:



	// �A��1��������Ax=b��
	// �W���s��A������l�Ώۍs��̂Ƃ�
	// �R���X�L�[�@�ɂ�荂���ɉ���
	static void chosol2(T a[N*N],T x[N],T b[N]);

public:
	// �A���ꎟ������Ax=b��
	// Gauss-Jordan�@�ɂ�����(����b�Ɋi�[�����)
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
