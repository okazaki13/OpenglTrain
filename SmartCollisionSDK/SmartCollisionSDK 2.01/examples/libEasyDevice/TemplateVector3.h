#ifndef _TEMPLATE_VECTOR3_H_
#define  _TEMPLATE_VECTOR3_H_

template<class T>
class BTVector3 {

public:
	T x,y,z;
	BTVector3(void) {}

	BTVector3(T x0,T y0,T z0) {
		x=x0;
		y=y0;
		z=z0;
	}

	//BTVector3(T p[3]){x=p[0];y=p[1];z=p[2];}
	BTVector3(const float*p) {
		x=(T)(p[0]);
		y=(T)(p[1]);
		z=(T)(p[2]);
	}

	BTVector3(const double*p) {
		x=(T)(p[0]);
		y=(T)(p[1]);
		z=(T)(p[2]);
	}

	//void ld0(void){x=y=z=0;}
	void Set(T x0,T y0,T z0) {
		x=x0;
		y=y0;
		z=z0;
	}

	void GetValue(float*t)const {
		t[0]=(float)x;
		t[1]=(float)y;
		t[2]=(float)z;
	}

	void GetValue(double*t)const {
		t[0]=(double)x;
		t[1]=(double)y;
		t[2]=(double)z;
	}

	T Norm(void)const {
		return (T)sqrt(x*x+y*y+z*z);
	}

	T SquareNorm(void)const {
		return (x*x+y*y+z*z);
	}

	void Normalize(void) {
		T t=x*x+y*y+z*z;

		if(t>0) {
			t=((T)1.0)/(T)sqrt(t);
			x*=t;
			y*=t;
			z*=t;
		}
	}

	T Normalize2(void) {
		T t,u;
		u=(T)sqrt(x*x+y*y+z*z);

		if(u>0) {
			t=((T)1.0)/u;
			x*=t;
			y*=t;
			z*=t;
		}

		return u;
	}

	T NegativeNormalize2(void) {
		T t,u;
		u=-(T)sqrt(x*x+y*y+z*z);

		if(u<0) {
			t=((T)1.0)/u;
			x*=t;
			y*=t;
			z*=t;
		}

		return u;
	}

	T&operator[](int i) {
		return (&x)[i];
	}

	BTVector3<T> operator+(const BTVector3<T>&a) const {
		return BTVector3(x+a.x,y+a.y,z+a.z);
	}

	BTVector3<T> operator-(const BTVector3<T>&a) const {
		return BTVector3(x-a.x,y-a.y,z-a.z);
	}

	void operator+=(const BTVector3<T>&a) {
		x+=a.x;
		y+=a.y;
		z+=a.z;
	}

	void operator-=(const BTVector3<T>&a) {
		x-=a.x;
		y-=a.y;
		z-=a.z;
	}

	bool operator==(const BTVector3<T>&a) {
		return x==a.x&&y==a.y&&z==a.z;
	}

	bool operator!=(const BTVector3<T>&a) {
		return x!=a.x||y!=a.y||z!=a.z;
	}

	void operator/=(T a) {
		a=((T)1.0)/a;
		x*=a;
		y*=a;
		z*=a;
	}

	void operator*=(T a) {
		x*=a;
		y*=a;
		z*=a;
	}

	//void operator-(void){x=-x;y=-y;z=-z;}
	void Negative(void) {
		x=-x;
		y=-y;
		z=-z;
	}

	void Invert(void) {
		x=-x;
		y=-y;
		z=-z;
	}

	operator T*(void)const {
		return(T*)&x;
	}

	BTVector3<T>&operator=(const BTVector3<T>&a) {
		x=a.x;
		y=a.y;
		z=a.z;
		return*this;
	}

	//BTVector3 operator=(const BTVector3&a){x=a.x;y=a.y;z=a.z;return*this;}
	BTVector3<T>&operator=(int a) {
		x=y=z=(T)a;
		return*this;
	}

	BTVector3<T>&operator=(float a) {
		x=y=z=(T)a;
		return*this;
	}

	BTVector3<T>&operator=(double a) {
		x=y=z=(T)a;
		return*this;
	}

	BTVector3<T>&operator=(const float a[3]) {
		x=a[0];
		y=a[1];
		z=a[2];
		return*this;
	}

	BTVector3<T>&operator=(const double a[3]) {
		x=(T)(a[0]);
		y=(T)(a[1]);
		z=(T)(a[2]);
		return*this;
	}

};

template<class T>
inline T ScalerProduct(const BTVector3<T>&a,const BTVector3<T>&b) {
	return a.x*b.x+a.y*b.y+a.z*b.z;
}

template<class T>
inline void VectorProduct(BTVector3<T>&u,const BTVector3<T>&a,const BTVector3<T>&b) {
	u.x=a.y*b.z-a.z*b.y;
	u.y=a.z*b.x-a.x*b.z;
	u.z=a.x*b.y-a.y*b.x;
}

template<class T>
inline T VectorProductNorm(const BTVector3<T>&a,const BTVector3<T>&b) {
	T u;
	u.x=a.y*b.z-a.z*b.y;
	u.y=a.z*b.x-a.x*b.z;
	u.z=a.x*b.y-a.y*b.x;
	return u.Norm();
}

template<class T>
inline BTVector3<T> operator*(const BTVector3<T>&t,int a) {
	//BVector3 u;u.x=t.x*a;u.y=t.y*a;u.z=t.z*a;return u;
	return BTVector3<T>((T)a*t.x,(T)a*t.y,(T)a*t.z);
}

template<class T>
inline BTVector3<T> operator*(int a,const BTVector3<T>&t) {
	//BVector3 u;u.x=t.x*a;u.y=t.y*a;u.z=t.z*a;return u;
	return BTVector3<T>((T)a*t.x,(T)a*t.y,(T)a*t.z);
}

template<class T>
inline BTVector3<T> operator*(const BTVector3<T>&t,float a) {
	//BVector3 u;u.x=t.x*a;u.y=t.y*a;u.z=t.z*a;return u;
	return BTVector3<T>((T)a*t.x,(T)a*t.y,(T)a*t.z);
}

template<class T>
inline BTVector3<T> operator*(float a,const BTVector3<T>&t) {
	//BVector3 u;u.x=t.x*a;u.y=t.y*a;u.z=t.z*a;return u;
	return BTVector3<T>((T)a*t.x,(T)a*t.y,(T)a*t.z);
}

template<class T>
inline BTVector3<T> operator*(const BTVector3<T>&t,double a) {
	//BVector3 u;u.x=t.x*a;u.y=t.y*a;u.z=t.z*a;return u;
	return BTVector3<T>((T)a*t.x,(T)a*t.y,(T)a*t.z);
}

template<class T>
inline BTVector3<T> operator*(double a,const BTVector3<T>&t) {
	//BVector3 u;u.x=t.x*a;u.y=t.y*a;u.z=t.z*a;return u;
	return BTVector3<T>((T)a*t.x,(T)a*t.y,(T)a*t.z);
}

#endif

