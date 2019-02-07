#ifndef _TEMPLATE_QUATERNION_H_
#define _TEMPLATE_QUATERNION_H_

#include <math.h>
#include"TemplateVector3.h"

template<class T>
class BTQuaternion {

public:
	T s;
	T vx,vy,vz;
	void Set(T s0,T vx0,T vy0,T vz0) {
		s=s0;
		vx=vx0;
		vy=vy0;
		vz=vz0;
	}

	void GetValue(float*t) {
		t[0]=(float)s;
		t[1]=(float)vx;
		t[2]=(float)vy;
		t[3]=(float)vz;
	}

	void GetValue(double*t) {
		t[0]=(double)s;
		t[1]=(double)vx;
		t[2]=(double)vy;
		t[3]=(double)vz;
	}

	BTQuaternion(void) {
		;
	}

	BTQuaternion(T s0,T vx0,T vy0,T vz0) {
		Set(s0,vx0,vy0,vz0);
	}

	T Norm(void)const {
		return (T)sqrt(s*s+vx*vx+vy*vy+vz*vz);
	}

	void SetRotation(T wx,T wy,T wz) {
		T c,s,w;
		w=(T)sqrt(wx*wx+wy*wy+wz*wz);
		c=(T)cos(w*(T)0.5);
		s=(T)sin(w*(T)0.5);

		if(w>0)
			s/=w;

		Set(c,s*wx,s*wy,s*wz);
	}

	void SetRotation(const BTVector3<T>&a) {
		SetRotation(a.x,a.y,a.z);
	}

	void GetRotation(BTVector3<T>&a)const {
		// |a|<=M_PI
		a.Set(vx,vy,vz);
		T t=a.Norm();

		if(t!=0) {
			T u;
			u=(T)atan2(t,s)*2;

			if     (u>=(T)  M_PI )
				u-=(T)(M_PI*2.0);
			else if(u<=(T)(-M_PI))
				u+=(T)(M_PI*2.0);

			a*=u/t;
		}
	}

	//void set_rot(T wx,T wy,T wz){SetRotation(wx,wy,wz);}
	void Identity(void) {
		s=1;
		vx=vy=vz=0;
	}

	void Normalize(void) {
		T t;

		if(s<0) {
			t=(T)-1.0/Norm();
		} else {
			t=(T)1.0/Norm();
		}

		s*=t;
		vx*=t;
		vy*=t;
		vz*=t;
	}

	void Invert(void) {
		vx=-vx;
		vy=-vy;
		vz=-vz;
	}

	void GetYXZAngle(T a[3])const {
		//{{cos(a1)*cos(a3)+sin(a1)*sin(a2)*sin(a3),cos(a3)*sin(a1)*sin(a2)-cos(a1)*sin(a3),cos(a2)*sin(a1)},
		//{cos(a2)*sin(a3),cos(a2)*cos(a3),-sin(a2)},
		//{-cos(a3)*sin(a1)+cos(a1)*sin(a2)*sin(a3),cos(a1)*cos(a3)*sin(a2)+sin(a1)*sin(a3),cos(a1)*cos(a2)}}
		T f10,f11,f12;
		T f02,f22;

		f10=(vy*vx+s*vz)*2;//a[3]
		f11=(T)1.0-(vz*vz+vx*vx)*2;//a[4]
		f12=(vy*vz-s*vx)*2;//a[5]
		//a[2],a[5],a[8]
		f02=(vx*vz+s*vy)*2;//a[2]
		f22=(T)1.0-(vx*vx+vy*vy)*2;//a[8]
		{
			a[0]=(T)atan2(f02,f22);//ax,cos(a2)>0‚Ì‚Æ‚«
			a[2]=(T)atan2(f10,f11);//az,cos(a2)>0‚Ì‚Æ‚«
			a[1]=(T)asin(-f12);
			//T t=cos(a[2]);
			//if(t!=0)a[1]=atan2(-f12,f11/t);
			//else    a[1]=atan2(-f12,f10/sin(a[2]);
		}
	}

	void GetXYZAngle(T a[3])const {
		//{{cos(ay)*cos(az),-cos(ay)*sin(az),sin(ay)},
		//{cos(az)*sin(ax)*sin(ay)+cos(ax)*sin(az),cos(ax)*cos(az)-sin(ax)*sin(ay)*sin(az),-cos(ay)*sin(ax)},
		//{-cos(ax)*cos(az)*sin(ay)+sin(ax)*sin(az),cos(az)*sin(ax)+cos(ax)*sin(ay)*sin(az),cos(ax)*cos(ay)}}
		T f00,f01,f02;
		T f12,f22;
#if 1

		f00=(T)1.0-(vy*vy+vz*vz)*2;
		f01=(vx*vy-s*vz)*2;
		f02=(vx*vz+s*vy)*2;
		f12=(vy*vz-s*vx)*2;
		f22=(T)1.0-(vx*vx+vy*vy)*2;
#else

		f00=(T)1.0-(vy*vy+vz*vz)*2;
		f01=(vy*vx+s*vz)*2;
		f02=(vz*vx-s*vy)*2;
		f12=(vz*vy+s*vx)*2;
		f22=(T)1.0-(vx*vx+vy*vy)*2;
#endif

		T f10,f11;
		f10=(vy*vx+s*vz)*(T)2;
		f11=(T)1.0-(vz*vz+vx*vx)*(T)2;

		if(f02<-1.0)
			f02=(T)-1.0;
		else if(f02>1.0)
			f02=(T)1.0;

		if(f02==(T)1.0) {
			a[1]=(T)(M_PI*0.5);
			a[0]=(T)atan2(f10,f11);
			a[2]=(T)0;
		} else if(f02==(T)-1) {
			a[1]=(T)(-M_PI*0.5);
			a[0]=(T)atan2(-f10,f11);
			a[2]=(T)0;
		} else {
			a[0]=(T)atan2(-f12,f22);//ax
			a[2]=(T)atan2(-f01,f00);//az
			//a[1]=asin(f02);      //ay
			T t=(T)cos(a[2]);

			if(t>0)
				a[1]=(T)(M_PI*0.5)-(T)atan2(f00,f02*t);      //ay
			else
				a[1]=(T)(M_PI*0.5)-(T)atan2(-f00,-f02*t);      //ay
		}

		//if     (f02==-1.0)a[1]=-M_PI*0.5;
		//else if(f02== 1.0)a[1]= M_PI*0.5;
	}

	void SetXYZAngle(T ax,T ay,T az) {
		BTQuaternion<T> dq;
		SetRotation(ax,0,0);
		dq.SetRotation(0,ay,0);
		(*this)*=dq;
		dq.SetRotation(0,0,az);
		(*this)*=dq;
	}

	void SetYXZAngle(T ay,T ax,T az) {
		BTQuaternion<T> dq;
		SetRotation(0,ay,0);
		dq.SetRotation(ax,0,0);
		(*this)*=dq;
		dq.SetRotation(0,0,az);
		(*this)*=dq;
	}

	void SetEulerAngle(T a1,T a2,T a3) {
		BTQuaternion<T> dq;
		SetRotation(0,0,a1);
		dq.SetRotation(0,a2,0);
		(*this)*=dq;
		dq.SetRotation(0,0,a3);
		(*this)*=dq;
	}

	void GetEulerAngle(T a[3])const {
		T f00,f01,f02;
		T f12;
		T f20,f21,f22;
		f22=(T)1.0-(vx*vx+vy*vy)*2;

		if(f22<=-1) {
			f00=(T)1.0-(vy*vy+vz*vz)*2;
			f01=(vx*vy-s*vz)*2;
			a[0]=(T)-atan2(-f01,f00);
			a[1]=(T)(M_PI*0.5);
			a[2]=0;
		} else if(f22>=1) {
			f00=(T)1.0-(vy*vy+vz*vz)*2;
			f01=(vx*vy-s*vz)*2;
			a[0]=(T)atan2(-f01,f00);
			a[1]=0;
			a[2]=0;
		} else {
			f02=(vx*vz+s*vy)*2;
			f12=(vy*vz-s*vx)*2;
			f20=(vz*vx-s*vy)*2;
			f21=(vz*vy+s*vx)*2;
			a[0]=(T)atan2(f12,f02); //a1(sin(a2)>0)
			a[1]=(T)acos(f22);      //a2
			a[2]=(T)atan2(f21,-f20);//a3(sin(a2)>0)

			if(a[0]<0) {
				a[0]=(T)atan2(-f12,-f02);
				a[1]=-a[1];
				a[2]=(T)atan2(-f21,f20);
			}
		}
	}

#if 1
#if 1
	void SetMatrix(const float m[9]) {
		float trace=m[0]+m[4]+m[8]+1.0f;

		if(trace>1e-8) {
			float t;
			t=0.5f/(float)sqrt(trace);
			s=(T)(0.5f*sqrt(trace));
			//s=(T)(0.25f/t);
			vx=(T)((m[7]-m[5])*t);
			vy=(T)((m[2]-m[6])*t);
			vz=(T)((m[3]-m[1])*t);
		} else {
			if(m[0]>m[4]&&m[0]>m[8]) {
				float t=2.0f*(float)sqrt(1.0f+m[0]-m[4]-m[8]);
				vx=(T)(0.25f*t);
				vy=(T)((m[1]+m[3])/t);
				vz=(T)((m[2]+m[6])/t);
				s =(T)((m[5]-m[7])/t);
			} else if(m[4]>m[8]) {
				float t=2.0f*(float)sqrt(1.0f+m[4]-m[0]-m[8]);
				vx=(T)((m[1]+m[3])/t);
				vy=(T)(0.25f*t);
				vz=(T)((m[5]+m[7])/t);
				s =(T)((m[2]-m[6])/t);
			} else {
				float t=2.0f*(float)sqrt(1.0f+m[8]-m[0]-m[4]);
				vx=(T)((m[2]+m[6])/t);
				vy=(T)((m[5]+m[7])/t);
				vz=(T)(0.25f*t);
				s =(T)((m[1]-m[3])/t);
			}
		}

		Normalize();
	}

	void SetMatrix(const double m[9]) {
		double trace=m[0]+m[4]+m[8]+1.0;

		if(trace>1e-8) {
			double t;
			t=0.5/sqrt(trace);
			s=(T)(0.25/t);
			vx=(T)((m[7]-m[5])*t);
			vy=(T)((m[2]-m[6])*t);
			vz=(T)((m[3]-m[1])*t);
		} else {
			if(m[0]>m[4]&&m[0]>m[8]) {
				double t=2.0*sqrt(1.0+m[0]-m[4]-m[8]);
				vx=(T)(0.25*t);
				vy=(T)((m[1]+m[3])/t);
				vz=(T)((m[2]+m[6])/t);
				s =(T)((m[5]-m[7])/t);
			} else if(m[4]>m[8]) {
				double t=2.0*sqrt(1.0+m[4]-m[0]-m[8]);
				vx=(T)((m[1]+m[3])/t);
				vy=(T)(0.25*t);
				vz=(T)((m[5]+m[7])/t);
				s =(T)((m[2]-m[6])/t);
			} else {
				double t=2.0*sqrt(1.0+m[8]-m[0]-m[4]);
				vx=(T)((m[2]+m[6])/t);
				vy=(T)((m[5]+m[7])/t);
				vz=(T)(0.25*t);
				s =(T)((m[1]-m[3])/t);
			}
		}

		Normalize();
	}

#endif
	void SetTMatrix(const float m[9]) {
		float t[9];
		t[0]=m[0];
		t[1]=m[3];
		t[2]=m[6];
		t[3]=m[1];
		t[4]=m[4];
		t[5]=m[7];
		t[6]=m[2];
		t[7]=m[5];
		t[8]=m[8];
		SetMatrix(t);
	}

	void SetTMatrix(const double m[9]) {
		double t[9];
		t[0]=m[0];
		t[1]=m[3];
		t[2]=m[6];
		t[3]=m[1];
		t[4]=m[4];
		t[5]=m[7];
		t[6]=m[2];
		t[7]=m[5];
		t[8]=m[8];
		SetMatrix(t);
	}

#endif
	void GetMatrix(double a[9])const {
		a[0]=1.0-2.0*(double)(vy*vy+vz*vz);
		a[1]=2.0*(double)(vx*vy-s*vz);
		a[2]=2.0*(double)(vx*vz+s*vy);
		a[3]=2.0*(double)(vy*vx+s*vz);
		a[4]=1.0-2.0*(double)(vz*vz+vx*vx);
		a[5]=2.0*(double)(vy*vz-s*vx);
		a[6]=2.0*(double)(vz*vx-s*vy);
		a[7]=2.0*(double)(vz*vy+s*vx);
		a[8]=1.0-2.0*(double)(vx*vx+vy*vy);
	}

	void GetMatrix(float a[9])const {
		a[0]=1.0f-2.0f*(float)(vy*vy+vz*vz);
		a[1]=2.0f*(float)(vx*vy-s*vz);
		a[2]=2.0f*(float)(vx*vz+s*vy);
		a[3]=2.0f*(float)(vy*vx+s*vz);
		a[4]=1.0f-2.0f*(float)(vz*vz+vx*vx);
		a[5]=2.0f*(float)(vy*vz-s*vx);
		a[6]=2.0f*(float)(vz*vx-s*vy);
		a[7]=2.0f*(float)(vz*vy+s*vx);
		a[8]=1.0f-2.0f*(float)(vx*vx+vy*vy);
	}

	void GetTMatrix(float a[9])const {//transposed matrix
		a[0]=1.0f-2.0f*(float)(vy*vy+vz*vz);
		a[3]=2.0f*(float)(vx*vy-s*vz);
		a[6]=2.0f*(float)(vx*vz+s*vy);
		a[1]=2.0f*(float)(vy*vx+s*vz);
		a[4]=1.0f-2.0f*(float)(vz*vz+vx*vx);
		a[7]=2.0f*(float)(vy*vz-s*vx);
		a[2]=2.0f*(float)(vz*vx-s*vy);
		a[5]=2.0f*(float)(vz*vy+s*vx);
		a[8]=1.0f-2.0f*(float)(vx*vx+vy*vy);
	}

	void GetTMatrix(double a[9])const {//transposed matrix
		a[0]=1.0-2.0*(double)(vy*vy+vz*vz);
		a[3]=2.0*(double)(vx*vy-s*vz);
		a[6]=2.0*(double)(vx*vz+s*vy);
		a[1]=2.0*(double)(vy*vx+s*vz);
		a[4]=1.0-2.0*(double)(vz*vz+vx*vx);
		a[7]=2.0*(double)(vy*vz-s*vx);
		a[2]=2.0*(double)(vz*vx-s*vy);
		a[5]=2.0*(double)(vz*vy+s*vx);
		a[8]=1.0-2.0*(double)(vx*vx+vy*vy);
	}

	void SetMatrix0(T m[9]) {
#if 0
		SetMatrix(m);
#else
		//{{cos(ay)*cos(az),-cos(ay)*sin(az),sin(ay)},
		//{cos(az)*sin(ax)*sin(ay)+cos(ax)*sin(az),cos(ax)*cos(az)-sin(ax)*sin(ay)*sin(az),-cos(ay)*sin(ax)},
		//{-cos(ax)*cos(az)*sin(ay)+sin(ax)*sin(az),cos(az)*sin(ax)+cos(ax)*sin(ay)*sin(az),cos(ax)*cos(ay)}}
		T f00,f01,f02;
		T f12,f22;
		T f10,f11;
		f00=m[0];
		f01=m[1];
		f02=m[2];
		f12=m[5];
		f22=m[8];
		//f10=(vy*vx+s*vz)*2;
		//f11=(T)1.0-(vz*vz+vx*vx)*2;
		f10=m[3];
		f11=m[4];
		T a[3];

		if(f02<-1.0)
			f02=(T)-1.0;
		else if(f02>1.0)
			f02=(T)1.0;

		if(f02==1) {
			a[1]=(T)(M_PI*0.5);
			a[0]=(T)atan2(f10,f11);
			a[2]=0;
		} else if(f02==-1) {
			a[1]=-(T)(M_PI*0.5);
			a[0]=(T)atan2(-f10,f11);
			a[2]= 0;
		} else {
			a[0]=(T)atan2(-f12,f22);//ax
			a[2]=(T)atan2(-f01,f00);//az
			//a[1]=asin(f02);      //ay
			T t=(T)cos(a[2]);

			if(t>0)
				a[1]=(T)(M_PI*0.5)-(T)atan2(f00,f02*t);      //ay
			else
				a[1]=(T)(M_PI*0.5)-(T)atan2(-f00,-f02*t);      //ay
		}

		SetXYZAngle(a[0],a[1],a[2]);
#endif

	}

	static void tm16to9(float m[9],const float t[16]) {
		m[0]=t[0];
		m[3]=t[1];
		m[6]=t[ 2];
		m[1]=t[4];
		m[4]=t[5];
		m[7]=t[ 6];
		m[2]=t[8];
		m[5]=t[9];
		m[8]=t[10];
	}

	static void tm16to9(double m[9],const double t[16]) {
		m[0]=t[0];
		m[3]=t[1];
		m[6]=t[ 2];
		m[1]=t[4];
		m[4]=t[5];
		m[7]=t[ 6];
		m[2]=t[8];
		m[5]=t[9];
		m[8]=t[10];
	}

	static void m16to9(double m[9],const double t[16]) {
		m[0]=t[0];
		m[3]=t[4];
		m[6]=t[ 8];
		m[1]=t[1];
		m[4]=t[5];
		m[7]=t[ 9];
		m[2]=t[2];
		m[5]=t[6];
		m[8]=t[10];
	}

	static void m16to9(float m[9],const float t[16]) {
		m[0]=t[0];
		m[3]=t[4];
		m[6]=t[ 8];
		m[1]=t[1];
		m[4]=t[5];
		m[7]=t[ 9];
		m[2]=t[2];
		m[5]=t[6];
		m[8]=t[10];
	}

	static void m9to16(double t[16],const double m[9]) {
		t[ 0]=m[0];
		t[ 1]=m[1];
		t[ 2]=m[2];
		t[ 3]=0;
		t[ 4]=m[3];
		t[ 5]=m[4];
		t[ 6]=m[5];
		t[ 7]=0;
		t[ 8]=m[6];
		t[ 9]=m[7];
		t[10]=m[8];
		t[11]=0;
		t[12]=0   ;
		t[13]=0   ;
		t[14]=0   ;
		t[15]=1;
	}

	static void m9to16(float t[16],const float m[9]) {
		t[ 0]=m[0];
		t[ 1]=m[1];
		t[ 2]=m[2];
		t[ 3]=0;
		t[ 4]=m[3];
		t[ 5]=m[4];
		t[ 6]=m[5];
		t[ 7]=0;
		t[ 8]=m[6];
		t[ 9]=m[7];
		t[10]=m[8];
		t[11]=0;
		t[12]=0   ;
		t[13]=0   ;
		t[14]=0   ;
		t[15]=1;
	}

	void SetGLMatrix(const double t[16]) {
		double m[9];
		m16to9(m,t);
		SetTMatrix(m);
	}

	void SetGLMatrix(const float t[16]) {
		float m[9];
		m16to9(m,t);
		SetTMatrix(m);
	}

	void SetTGLMatrix(const double t[16]) {
		double m[9];
		m16to9(m,t);
		SetMatrix(m);
	}

	void SetTGLMatrix(const float t[16]) {
		float m[9];
		m16to9(m,t);
		SetMatrix(m);
	}

	void GetGLMatrix(float m[16]) {
		float t[9];
		GetTMatrix(t);
		m9to16(m,t);
	}

	void GetGLMatrix(double m[16]) {
		double t[9];
		GetTMatrix(t);
		m9to16(m,t);
	}

	void GetTGLMatrix(float m[16]) {
		float t[9];
		GetMatrix(t);
		m9to16(m,t);
	}

	void GetTGLMatrix(double m[16]) {
		double t[9];
		GetMatrix(t);
		m9to16(m,t);
	}

	void operator+=(const BTQuaternion<T>&a) {
		s+=a.s;
		vx+=a.vx;
		vy+=a.vy;
		vz+=a.vz;
	}

	void operator*=(T c) {
		BTVector3<T> t;
		GetRotation(t);
		t*=c;
		SetRotation(t);
	}

	void operator*=(const BTQuaternion<T>&b) {
		BTQuaternion<T> a;
		a=*this;
		s=a.s*b.s-(a.vx*b.vx+a.vy*b.vy+a.vz*b.vz);
		vx=a.s*b.vx+b.s*a.vx+(a.vy*b.vz-a.vz*b.vy);
		vy=a.s*b.vy+b.s*a.vy+(a.vz*b.vx-a.vx*b.vz);
		vz=a.s*b.vz+b.s*a.vz+(a.vx*b.vy-a.vy*b.vx);
	}

	void operator*=(const BTVector3<T>&b) {
		BTQuaternion<T> t;
		t.SetRotation(b);
		(*this)*=t;
	}

	void operator/=(const BTQuaternion<T>&b) {
		BTQuaternion<T> t;
		t=b;
		t.Invert();
		(*this)*=t;
	}

	void MultiplyFromLeft(const BTQuaternion<T>&a) {
		BTQuaternion<T> b;
		b=*this;
		s=a.s*b.s-(a.vx*b.vx+a.vy*b.vy+a.vz*b.vz);
		vx=a.s*b.vx+b.s*a.vx+(a.vy*b.vz-a.vz*b.vy);
		vy=a.s*b.vy+b.s*a.vy+(a.vz*b.vx-a.vx*b.vz);
		vz=a.s*b.vz+b.s*a.vz+(a.vx*b.vy-a.vy*b.vx);
	}

	void DivideFromLeft(const BTQuaternion<T>&a0) {
		BTQuaternion<T> a;
		a=a0;
		a.Invert();
		MultiplyFromLeft(a);
	}

	void MultiplyFromLeft(const BTVector3<T>&a) {
		BTQuaternion<T> t;
		t.SetRotation(a);
		MultiplyFromLeft(t);
	}

	void DivideFromLeft(const BTVector3<T>&a) {
		BTQuaternion<T> t;
		t.SetRotation(a);
		t.Invert();
		MultiplyFromLeft(t);
	}

	T&operator[](int i) {
		return (&s)[i];
	}

	BTQuaternion<T>&operator=(const BTQuaternion<T>&t) {
		s=t.s;
		vx=t.vx;
		vy=t.vy;
		vz=t.vz;
		return*this;
	}

	void operator=(const BTVector3<T>&t) {
		SetRotation(t);
	}

	BTQuaternion<T>&operator=(const float a[4]) {
		s =(T)a[0];
		vx=(T)a[1];
		vy=(T)a[2];
		vz=(T)a[3];
		return*this;
	}

	BTQuaternion<T>&operator=(const double a[4]) {
		s =(T)a[0];
		vx=(T)a[1];
		vy=(T)a[2];
		vz=(T)a[3];
		return*this;
	}

	//operator const T*(void)const{return(const T*)&s;}
	operator T*(void)const {
		return(T*)&s;
	}

	bool operator==(const BTQuaternion<T>&t)const {
		return (s==t.s&&
		        vx==t.vx&&
		        vy==t.vy&&
		        vz==t.vz);
	}

	bool operator!=(const BTQuaternion<T>&t)const {
		return (s!=t.s||vx!=t.vx||vy!=t.vy||vz!=t.vz);
	}

	void operator>=(double a[4])const {
		a[0]=(double)s;
		a[1]=(double)vx;
		a[2]=(double)vy;
		a[3]=(double)vz;
	}

	void operator>=(float a[4])const {
		a[0]=(float)s;
		a[1]=(float)vx;
		a[2]=(float)vy;
		a[3]=(float)vz;
	}
};

template<class T>
inline void GetDifference(BTQuaternion<T>&q,
                          const BTQuaternion<T>&q1,
                          const BTQuaternion<T>&q2) {
	q=q2;
	q/=q1;
}

template<class T>
inline void GetDifference(BTVector3<T>&t,
                          const BTQuaternion<T>&q1,
                          const BTQuaternion<T>&q2) {
	BTQuaternion<T> q;
	q=q2;
	q/=q1;
	q.GetRotation(t);
}

template<class T>
inline T GetDifference(const BTQuaternion<T>&q1,
                       const BTQuaternion<T>&q2) {
	BTVector3<T> t;
	GetDifference(t,q1,q2);
	return t.Norm();
}

#endif

