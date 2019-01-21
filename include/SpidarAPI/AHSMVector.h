#pragma once
#include "AHSMatrix.h"


//////////////////////////////////////////////////////////////////////////////
//
template <class T, unsigned int N>
class CAHSMVector : public CAHSMatrix<T,N,1>
{
public:
	CAHSMVector(void){
	//	this->zero();
	};
	~CAHSMVector(void){};
public:

	// ベクトルのノルム
	T norm(){ return sqrt(this->norm2()); };
	T norm2(){
		T ans = 0;
		for(int i=0;i<N;i++){ ans += this->data[i] * this->data[i]; }
		return ans;
	};

	//ベクトルの正規化
	CAHSVector<T,N> normal(){
		CAHSVector<T,N> ans;
		ans = (*this) / this->norm();
		return ans;
	};

	//
	CAHSMVector<T,N>& operator= (CAHSMatrix<T,N,1>& obj){
		return (CAHSMVector<T,N>&)( this->copy(obj) );
	};

	// 内積
	T operator* (CAHSMVector<T,N>& obj){
		//T ans = 0;
		//for(int i=0;i<N;i++){ ans += this->data[i] * obj.data[i];}
		//return ans;
		return (this->tr()*obj).Data()[0];
	};

};



//////////////////////////////////////////////////////////////////////////////
//
template <class T>
class CAHSMVector3 :
	public CAHSMVector<T,3>
{
public:
	CAHSMVector3(void){};
	CAHSMVector3(T x,T y,T z){this->X() = x;this->Y() = y;this->Z() = z;};
	~CAHSMVector3(void){};

public:
	T& X(){ return this->data[0];};
	T& Y(){ return this->data[1];};
	T& Z(){ return this->data[2];};

	// 外積
	CAHSMVector3<T> operator^ (CAHSMVector3<T>& obj){
		CAHSVector3<T> ans;
		ans.X() = this->Y()*obj.Z() - this->Z()*obj.Y();
		ans.Y() = this->Z()*obj.X() - this->X()*obj.Z();
		ans.Z() = this->X()*obj.Y() - this->Y()*obj.X();
		return ans;
	};

	//
	CAHSMVector3<T>& operator= (CAHSMatrix<T,3,1>& obj){
		return (CAHSMVector3<T>&)( this->copy(obj) );
	};

};



//////////////////////////////////////////////////////////////////////////////
//
template <class T>
class CAHSMVector4 :
	public CAHSMVector<T,4>
{
public:
	CAHSMVector4(void){};
	~CAHSMVector4(void){};

public:
	T& X(){ return this->data[0];};
	T& Y(){ return this->data[1];};
	T& Z(){ return this->data[2];};
	T& W(){ return this->data[3];};

	//
	CAHSMVector4<T>& operator= (CAHSMatrix<T,4,1>& obj){
		return (CAHSMVector4<T>&)( this->copy(obj) );
	};
};


//////////////////////////////////////////////////////////////////////////////
//
template <class T>
class CAHSMQuaternion// :
//	public CAHSVector4<T>
{
protected:
	CAHSMVector3<T> v;
	T w;

public:
	CAHSMQuaternion(void){ this->w = 1;};
	~CAHSMQuaternion(void){};

public:
	T& X(){ return this->v.Data()[0];};
	T& Y(){ return this->v.Data()[1];};
	T& Z(){ return this->v.Data()[2];};
	T& W(){ return this->w;};

	CAHSMVector3<T>& V(){
		return this->v;
	};

public:
	void unit(){
		this->W() = 1;
		this->V().zero();
	}
	// ベクトルのノルム
	T norm(){
		return sqrt(this->norm2());
	};
	T norm2(){
		T ans = this->W() * this->W() + this->V().norm2();
		return ans;
	};

	//ベクトルの正規化
	CAHSQuaternion<T> normal(){
		CAHSQuaternion<T> ans;
		T norm = this->norm();
		ans.W() = this->W() / norm;
		ans.V() = this->V() / norm;
		return ans;
	};

	//共役四元数
	CAHSQuaternion<T> conj(){
		CAHSQuaternion<T> ans;
		ans.W() = this->W();
		ans.V() = -(this->V());
		return ans;
	};

	//逆元
	CAHSQuaternion<T> inv(){
		CAHSQuaternion<T> ans = this->conj();
		T norm2 = this->norm2();
		ans.W() /= norm2;
		ans.V() = ans.V() / norm2;
		return ans;
	};

public:
	// クオータニオンの積
	CAHSQuaternion<T> operator* (CAHSQuaternion<T>& obj){
		CAHSQuaternion<T> ans;
		ans.W() = this->W() * obj.W() - this->V()*obj.V();
		ans.V() = this->V()*obj.W() + obj.V()*this->W() + this->v.operator ^(obj.v);
		return ans;
	};

	// ベクトルの回転
	// クオータニオンとベクトルの積(QT^ * V * QT)
	CAHSVector3<T> operator* (CAHSMVector3<T>& obj){
		CAHSQuaternion<T> P;
		P.W() = 0;
		P.V() = obj;
		CAHSQuaternion<T> Q = this->normal();
		CAHSQuaternion<T> Qinv = Q.conj();

		CAHSQuaternion<T> ans = ((Qinv * P) * Q);
		return ans.V();
	};

public:
	// v方向にtheta回転する四元数
	void makeQT(CAHSMVector3<T> v, T theta){
		CAHSMVector3<T> vn;
		vn = v.normal();
		this->W() = cos(theta/2.0);
		this->V() = vn * sin(theta/2.0);
	};

public:
	void disp(){
		printf("<%f ",this->W());
		this->V().disp();
		printf(">");
	};
};

#if 0
#endif