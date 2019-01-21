/* @file
	@JP
		@brief CAHSQPProg template class
		@author �ԉH ���m
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
	CAHSQuaternion �N���X
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
	// �x�N�g���̃m����
	T norm();
	T norm2();

	//�x�N�g���̐��K��
	CAHSQuaternion<T> normal();


	//�����l����
	CAHSQuaternion<T> conj();

	//�t��
	//CAHSQuaternion<T> inv();

public:
	// ��]�̒萔�{���s��
	CAHSQuaternion<T> operator* (T scale);

	// �N�I�[�^�j�I���̐�
	CAHSQuaternion<T> operator* (CAHSQuaternion<T>& obj);

	// �x�N�g���̉�]
	// �N�I�[�^�j�I���ƃx�N�g���̐�(QT^ * V * QT)
	CAHSVector3<T> operator* (CAHSVector3<T>& obj);

public:
	// v������theta��]����l����
	void makeQT(CAHSVector3<T> v, T theta);

public:
	void disp();

};

typedef CAHSQuaternion<float>	CQt4f;
typedef CAHSQuaternion<double>	CQt4d;
