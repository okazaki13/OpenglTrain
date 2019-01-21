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
#include "spidarapi.h"
#include <math.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////////
//
/**
@JP
	CAHSVector �N���X
@END_JP
@EN
	CAHSVector class
@END_EN
 */
template <class T, unsigned int N>
class SPIDARAPI_API CAHSVector : 
	public CSpidarAPI
{
protected:
	T data[N];

public:
	CAHSVector(void);
	virtual ~CAHSVector(void);

public:
	T* Data();
public:
	void zero();

	CAHSVector<T,N>& copy(CAHSVector<T,N>& obj);

	// �x�N�g���̃m����
	T norm();
	T norm2();

	//�x�N�g���̐��K��
	CAHSVector<T,N> normal();

public:
	// �a
	CAHSVector<T,N> operator+ (CAHSVector<T,N>& obj);
	// ��
	CAHSVector<T,N> operator- (CAHSVector<T,N>& obj);
	// �a�{��
	CAHSVector<T,N>& operator+= (CAHSVector<T,N>& obj);
	// ���[��
	CAHSVector<T,N>& operator-= (CAHSVector<T,N>& obj);

	// �}�C�i�X
	CAHSVector<T,N> operator- ();

	// �萔�{
	CAHSVector<T,N> operator* (T obj);

	// �萔��
	CAHSVector<T,N> operator/ (T obj);

	// ����
	T operator* (CAHSVector<T,N>& obj);

	void disp(const char format[]=NULL,int isNewLine = false);

};

#if 0

//////////////////////////////////////////////////////////////////////////////
//
template <class T>
class CAHSVector3 :
	public CAHSVector<T,3>
{
public:
	CAHSVector3(void){};
	CAHSVector3(T x,T y,T z){this->X() = x;this->Y() = y;this->Z() = z;};
	virtual ~CAHSVector3(void){};

public:
	T& X(){ return this->data[0];};
	T& Y(){ return this->data[1];};
	T& Z(){ return this->data[2];};

	// �O��
	CAHSVector3<T> operator^ (CAHSVector3<T>& obj){
//	CAHSVector3<T> operator^ (CAHSVector<T,3>& obj){
		CAHSVector3<T> ans;
		ans.X() = this->Y()*obj.Z() - this->Z()*obj.Y();
		ans.Y() = this->Z()*obj.X() - this->X()*obj.Z();
		ans.Z() = this->X()*obj.Y() - this->Y()*obj.X();
		return ans;
	};

	//
	CAHSVector3<T>& operator= (CAHSVector<T,3>& obj){
		//for(int i=0;i<3;i++){
		//	this->Data()[i] = obj.Data()[i];
		//}
		//return *this;
		return (CAHSVector3<T>&)this->copy(obj);
	};
};

//////////////////////////////////////////////////////////////////////////////
//
template <class T>
class CAHSVector4 :
	public CAHSVector<T,4>
{
public:
	CAHSVector4(void){};
	virtual ~CAHSVector4(void){};

public:
	T& X(){ return this->data[0];};
	T& Y(){ return this->data[1];};
	T& Z(){ return this->data[2];};
	T& W(){ return this->data[3];};

	//
	CAHSVector4<T>& operator= (CAHSVector<T,4>& obj){
		return (CAHSVector4<T>&)this->copy(obj);
	};
};

//////////////////////////////////////////////////////////////////////////////
//
template <class T>
class CAHSQuaternion// :
//	public CAHSVector4<T>
{
protected:
	CAHSVector3<T> v;
	T w;

public:
	CAHSQuaternion(void){ this->w = 1;};
	virtual ~CAHSQuaternion(void){};

public:
	T& X(){ return this->v.Data()[0];};
	T& Y(){ return this->v.Data()[1];};
	T& Z(){ return this->v.Data()[2];};
	T& W(){ return this->w;};

	CAHSVector3<T>& V(){
		return this->v;
	};

public:
	void unit(){
		this->W() = 1;
		this->V().zero();
	}
	// �x�N�g���̃m����
	T norm(){
		return sqrt(this->norm2());
	};
	T norm2(){
		T ans = this->W() * this->W() + this->V().norm2();
		return ans;
	};

	//�x�N�g���̐��K��
	CAHSQuaternion<T> normal(){
		CAHSQuaternion<T> ans;
		T norm = this->norm();
		ans.W() = this->W() / norm;
		ans.V() = this->V() / norm;
		return ans;
	};

	//�����l����
	CAHSQuaternion<T> conj(){
		CAHSQuaternion<T> ans;
		ans.W() = this->W();
		ans.V() = -(this->V());
		return ans;
	};

	//�t��
	CAHSQuaternion<T> inv(){
		CAHSQuaternion<T> ans = this->conj();
		T norm2 = this->norm2();
		ans.W() /= norm2;
		ans.V() = ans.V() / norm2;
		return ans;
	};

public:
	// �N�I�[�^�j�I���̐�
	CAHSQuaternion<T> operator* (CAHSQuaternion<T>& obj){
		CAHSQuaternion<T> ans;
		ans.W() = this->W() * obj.W() - this->V()*obj.V();
		ans.V() = this->V()*obj.W() + obj.V()*this->W() + this->v.operator ^(obj.v);
		return ans;
	};

	// �x�N�g���̉�]
	// �N�I�[�^�j�I���ƃx�N�g���̐�(QT^ * V * QT)
	CAHSVector3<T> operator* (CAHSVector3<T>& obj){
		CAHSQuaternion<T> P;
		P.W() = 0;
		P.V() = obj;
		CAHSQuaternion<T> Q = this->normal();
		CAHSQuaternion<T> Qinv = Q.conj();
		CAHSQuaternion<T> ans = ((Q * P) * Qinv);
		return ans.V();
	};

public:
	// v������theta��]����l����
	void makeQT(CAHSVector3<T> v, T theta){
		CAHSVector3<T> vn;
		vn = v.normal();
		this->W() = cos((T)(theta/2.0));
		this->V() = vn * sin((T)(theta/2.0));
	};

public:
	void disp(){
		printf("<%f ",this->W());
		this->V().disp();
		printf(">");
	};
};
#endif;

typedef CAHSVector<float,1>		CVec1f;
typedef CAHSVector<float,2>		CVec2f;
//typedef CAHSVector<float,3>		CVec3f;
//typedef CAHSVector<float,4>		CVec4f;
typedef CAHSVector<float,5>		CVec5f;
typedef CAHSVector<float,6>		CVec6f;
typedef CAHSVector<float,7>		CVec7f;
typedef CAHSVector<float,8>		CVec8f;

typedef CAHSVector<double,1>	CVec1d;
typedef CAHSVector<double,2>	CVec2d;
//typedef CAHSVector<double,3>	CVec3d;
//typedef CAHSVector<double,4>	CVec4d;
typedef CAHSVector<double,5>	CVec5d;
typedef CAHSVector<double,6>	CVec6d;
typedef CAHSVector<double,7>	CVec7d;
typedef CAHSVector<double,8>	CVec8d;
