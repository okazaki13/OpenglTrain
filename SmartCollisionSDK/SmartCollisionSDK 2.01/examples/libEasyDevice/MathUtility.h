#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

#include <math.h>

#ifndef M_PI
#define	M_PI		3.14159265358979323846
#endif

template <class T>
inline void CopyVector(T*d,const T*s,int n)
{
	int i;
	for(i=0;i<n;i++)d[i]=s[i];
}

template <class T>
inline T Norm3(const T a[3])
{
	return (T)sqrt((double)(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]));
}

template <class T>
inline T Norm4(const T a[4])
{
    return (T)sqrt((double)(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]+a[3]*a[3]));
}

template <class T>
inline void Normalize3(T a[3])
{
	T t=Norm3(a);
	if(t==0.0)t=1.0;
	t=(T)1.0/t;
	a[0]*=t;a[1]*=t;a[2]*=t;
}

template <class T>
inline void Normalize4(T a[4])
{
	T t=Norm4(a);
	if(t==0.0)t=1.0;
	t=1.0/t;
	a[0]*=t;a[1]*=t;a[2]*=t;a[3]*=t;
}

template <class T>
inline void GetNormal(T n[3],
		      const T v1[3],
		      const T v2[3],
		      const T v3[3])
{
	double a[3],b[3];
	a[0]=v2[0]-v1[0];
	a[1]=v2[1]-v1[1];
	a[2]=v2[2]-v1[2];
	b[0]=v3[0]-v1[0];
	b[1]=v3[1]-v1[1];
	b[2]=v3[2]-v1[2];
	n[0]=a[1]*b[2]-a[2]*b[1];
	n[1]=a[2]*b[0]-a[0]*b[2];
	n[2]=a[0]*b[1]-a[1]*b[0];
	Normalize3(n);
}

template <class T>
inline void FromVectorToQuaternion(T q[4],const T v[3])
{
    double t=Norm3(v);
    if(t==0)
    {
    	q[0]=1;q[1]=q[2]=q[3]=0;
    }
    else
    {
    	double u=t*0.5;
		t=sin(u)/t;
		q[0]=cos(u);
		q[1]=t*v[0];
		q[2]=t*v[1];
		q[3]=t*v[2];
	}
}

template <class T>
inline void FromQuaternionToVector(T v[3],const T q[4])
{
	v[0]=q[1];
	v[1]=q[2];
	v[2]=q[3];
	T t=Norm3(v);
	if(t!=0.0)
	{
	   	double u=atan2(t,q[0])*2.0;
	    if     (u>= M_PI)u-=(M_PI*2.0);
	    else if(u<=-M_PI)u+=(M_PI*2.0);
	    u/=t;
	    v[0]*=u;
	    v[1]*=u;
	    v[2]*=u;
	}
}

template <class T>
inline void MultiplyQuaternion(T d[4],
			       const T a[4],
			       const T b[4])
{
	d[0]=a[0]*b[0]-(a[1]*b[1]+a[2]*b[2]+a[3]*b[3]);
	d[1]=a[0]*b[1]+b[0]*a[1]+(a[2]*b[3]-a[3]*b[2]);
	d[2]=a[0]*b[2]+b[0]*a[2]+(a[3]*b[1]-a[1]*b[3]);
	d[3]=a[0]*b[3]+b[0]*a[3]+(a[1]*b[2]-a[2]*b[1]);
}

template <class T>
inline void InvertQuaternion(T a[4])
{
    a[1]=-a[1];
    a[2]=-a[2];
    a[3]=-a[3];
}

template <class T>
inline void NormalizeQuaternion(T a[4])
{
    T t;
    t=sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]+a[3]*a[3]);
    if(t==0)t=1;
    t=1.0/t;
    a[0]*=t;
    a[1]*=t;
    a[2]*=t;
    a[3]*=t;
}

template <class T>
inline void ConvertFromQuaternionToMatrix(const T q[4],T m[3*3])
{
    T s,vx,vy,vz;
    s=q[0];vx=q[1];vy=q[2];vz=q[3];
    m[0]=(double)1.0-(vy*vy+vz*vz)*2;m[3]=(vx*vy-s*vz)*2;m[6]=(vx*vz+s*vy)*2;
    m[1]=(vy*vx+s*vz)*2;m[4]=(double)1.0-(vz*vz+vx*vx)*2;m[7]=(vy*vz-s*vx)*2;
    m[2]=(vz*vx-s*vy)*2;m[5]=(vz*vy+s*vx)*2;m[8]=(double)1.0-(vx*vx+vy*vy)*2;
    
}

template <class T>
inline void ConvertFromMatrixToQuaternion(const T m[3*3],T q[4])
{
    T s,s4;
    s=sqrt(m[0]+m[4]+m[8]+1.0)*0.5;s4=s*4;
    q[0]=s;
    q[1]=(m[5]-m[7])/s4;
    q[2]=(m[6]-m[2])/s4;
    q[3]=(m[1]-m[3])/s4;
    NormalizeQuaternion(q);
}

template <class T>
inline void MakeMatrix(T m[16],T t[3],T q[4])
{
    double r[9];
    ConvertFromQuaternionToMatrix(q,r);
    m[0]=r[0];m[4]=r[3];m[ 8]=r[6];m[12]=t[0];
    m[1]=r[1];m[5]=r[4];m[ 9]=r[7];m[13]=t[1];
    m[2]=r[2];m[6]=r[5];m[10]=r[8];m[14]=t[2];
    m[3]=0   ;m[7]=0   ;m[11]=0   ;m[15]=1;
}

inline void MakeMatrix(double m[16],double p[3],double c[3],double q[4])
{
    double r[9];
    ConvertFromQuaternionToMatrix(q,r);
    m[0]=r[0];m[4]=r[3];m[ 8]=r[6];m[12]=p[0]-(r[0]*c[0]+r[3]*c[1]+r[6]*c[2]);
    m[1]=r[1];m[5]=r[4];m[ 9]=r[7];m[13]=p[1]-(r[1]*c[0]+r[4]*c[1]+r[7]*c[2]);
    m[2]=r[2];m[6]=r[5];m[10]=r[8];m[14]=p[2]-(r[2]*c[0]+r[5]*c[1]+r[8]*c[2]);
    m[3]=0   ;m[7]=0   ;m[11]=0   ;m[15]=1;
}

inline void MultiplyMatrixAndVector(double d[3],
				    const double m[16],
				    const double s[3])
{
	d[0]=m[0]*s[0]+m[4]*s[1]+m[ 8]*s[2]+m[12];
	d[1]=m[1]*s[0]+m[5]*s[1]+m[ 9]*s[2]+m[13];
	d[2]=m[2]*s[0]+m[6]*s[1]+m[10]*s[2]+m[14];
}

inline void MultiplyInverseMatrixAndVector(double d[3],
				    const double m[16],
				    const double s[3])
{
    double tx,ty,tz;
    tx=s[0]-m[12];
    ty=s[1]-m[13];
    tz=s[2]-m[14];
    d[0]=m[0]*tx+m[1]*ty+m[ 2]*tz;
    d[1]=m[4]*tx+m[5]*ty+m[ 6]*tz;
    d[2]=m[8]*tx+m[9]*ty+m[10]*tz;
}

template <class T>
inline void VectorProduct(T d[3],
			  const T a[3],
			  const T b[3])
{
    d[0]=a[1]*b[2]-a[2]*b[1];
    d[1]=a[2]*b[0]-a[0]*b[2];
    d[2]=a[0]*b[1]-a[1]*b[0];
}

#endif
