#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include<math.h>

#ifndef M_PI
#define	M_PI		3.14159265358979323846
#endif

typedef int BEnum;

#ifdef USE_REAL8
typedef double BReal;
#else
typedef float BReal;
#endif

class BString {

public:
	char*ptr;
	BString(void) {
		ptr=0;
	}

	~BString(void);

	char**GetReference(void) {
		return&ptr;
	}

	char operator[](int i) {
		return ptr[i];
	}

	char operator*(int i) {
		return ptr[0];
	}

	operator const char*(void) {
		return (const char*)ptr;
	}

	void Destroy(void);
	int Length(void);
	BString&operator=(const char*t);
	BString&operator=(const BString&t);
	bool operator==(const BString&t);
	bool operator==(const char*t);
	bool operator!=(const BString&t) {
		return !(*this==t);
	}

	bool operator!=(const char*t) {
		return !(*this==t);
	}

	void Set(char*s);
};

#include"TemplateVector3.h"
#include"TemplateQuaternion.h"

typedef BTVector3<BReal> BVector3;
typedef BTQuaternion<BReal> BQuaternion;

class CoordinateMatrix {

public:
	BReal mxx,mxy,mxz;
	BReal myx,myy,myz;
	BReal mzx,mzy,mzz;
	BReal tx,ty,tz;
	void SetIdentity(void) {
		mxx=(BReal)1;
		mxy=(BReal)0;
		mxz=(BReal)0;
		tx=(BReal)0;
		myx=(BReal)0;
		myy=(BReal)1;
		myz=(BReal)0;
		ty=(BReal)0;
		mzx=(BReal)0;
		mzy=(BReal)0;
		mzz=(BReal)1;
		tz=(BReal)0;
	}

	void Set(const BQuaternion&q) {
		q.GetMatrix(&mxx);
		tx=(BReal)0;
		ty=(BReal)0;
		tz=(BReal)0;
	}

	void GetQuaternion(BQuaternion&q)const {
		q.SetMatrix(&mxx);
	}

	void Set(const BVector3&t,const BQuaternion&q) {
		BReal rot[3*3];
		q.GetMatrix(rot);
		mxx=rot[0];
		mxy=rot[1];
		mxz=rot[2];
		myx=rot[3];
		myy=rot[4];
		myz=rot[5];
		mzx=rot[6];
		mzy=rot[7];
		mzz=rot[8];
		tx=t.x;
		ty=t.y;
		tz=t.z;
	}

	void GetAxis(BVector3&ex,BVector3&ey,BVector3&ez)const {
#if 0
		ex.Set(mxx,mxy,mxz);
		ey.Set(myx,myy,myz);
		ez.Set(mzx,mzy,mzz);
#else

		ex.Set(mxx,myx,mzx);
		ey.Set(mxy,myy,mzy);
		ez.Set(mxz,myz,mzz);
#endif

	}

	void GetTranslation(BVector3&t)const {
		t.x=tx;
		t.y=ty;
		t.z=tz;
	}

	void GetRotation(BReal m[9])const {
		m[0]=mxx;
		m[1]=mxy;
		m[2]=mxz;
		m[3]=myx;
		m[4]=myy;
		m[5]=myz;
		m[6]=mzx;
		m[7]=mzy;
		m[8]=mzz;
	}

	void GetRotation(BQuaternion&q)const {
		BReal m[9];
		GetRotation(m);//q.SetRotation(m);
		q.SetMatrix(m);
	}

	void Set(const BVector3&t,const BVector3&c,
	         const BQuaternion&q) {
		BReal rot[3*3];
		q.GetMatrix(rot);
		mxx=rot[0];
		mxy=rot[1];
		mxz=rot[2];
		myx=rot[3];
		myy=rot[4];
		myz=rot[5];
		mzx=rot[6];
		mzy=rot[7];
		mzz=rot[8];
		BVector3 u;
		Rotate(u,c);
#if 0
		//InverseRotate(u,c);
		tx=t.x-u.x+c.x;
		ty=t.y-u.y+c.y;
		tz=t.z-u.z+c.z;
#else

		tx=t.x-u.x;
		ty=t.y-u.y;
		tz=t.z-u.z;
#endif

	}
	/*
	void m(BVector3&v,BReal x,BReal y,BReal z) {
		v.x=mxx*x+mxy*y+mxz*z;
		v.y=myx*x+myy*y+myz*z;
		v.z=mzx*x+mzy*y+mzz*z;
	};

	void im(BVector3&v,BReal x,BReal y,BReal z) {
		v.x=mxx*x+myx*y+mzx*z;
		v.y=mxy*x+myy*y+mzy*z;
		v.z=mxz*x+myz*y+mzz*z;
	};

	void rot(BVector3&v,BReal x,BReal y,BReal z)const {
		v.x=mxx*x+mxy*y+mxz*z;
		v.y=myx*x+myy*y+myz*z;
		v.z=mzx*x+mzy*y+mzz*z;
	};
	*/
	void Rotate(BVector3&d,const BVector3&s)const {
		d.x=mxx*s.x+mxy*s.y+mxz*s.z;
		d.y=myx*s.x+myy*s.y+myz*s.z;
		d.z=mzx*s.x+mzy*s.y+mzz*s.z;
	};

	void Rotate(BQuaternion&d,const BQuaternion&s)const {
		BQuaternion dq;
		GetQuaternion(dq);
		d=s;
		d.MultiplyFromLeft(dq);
	};

	void InverseRotate(BQuaternion&d,const BQuaternion&s)const {
		BQuaternion dq;
		GetQuaternion(dq);
		dq.Invert();
		d=s;
		d.MultiplyFromLeft(dq);
	};

	void InverseRotate(BVector3&d,const BVector3&s)const {
		d.x=mxx*s.x+myx*s.y+mzx*s.z;
		d.y=mxy*s.x+myy*s.y+mzy*s.z;
		d.z=mxz*s.x+myz*s.y+mzz*s.z;
	};

	/*void irot(BVector3&v,BReal x,BReal y,BReal z)const{
	v.x=mxx*x+myx*y+mzx*z;
	v.y=mxy*x+myy*y+mzy*z;
	v.z=mxz*x+myz*y+mzz*z;
	};*/
	void Convert(BVector3&a,const BVector3&b)const {
		a.x=mxx*b.x+mxy*b.y+mxz*b.z+tx;
		a.y=myx*b.x+myy*b.y+myz*b.z+ty;
		a.z=mzx*b.x+mzy*b.y+mzz*b.z+tz;
	};

	void InverseConvert(BVector3&a,const BVector3&b)const {
		BVector3 c;
		c.x=b.x-tx;
		c.y=b.y-ty;
		c.z=b.z-tz;
		a.x=mxx*c.x+myx*c.y+mzx*c.z;
		a.y=mxy*c.x+myy*c.y+mzy*c.z;
		a.z=mxz*c.x+myz*c.y+mzz*c.z;
	};

	void cnv(BVector3&a,const BVector3&b)const {
		Convert(a,b);
	}

	void cnv(BReal a[3],const BVector3&b)const {
		a[0]=mxx*b.x+mxy*b.y+mxz*b.z+tx;
		a[1]=myx*b.x+myy*b.y+myz*b.z+ty;
		a[2]=mzx*b.x+mzy*b.y+mzz*b.z+tz;
	};

	void cnv(BVector3&v,BReal x,BReal y,BReal z) {
		v.x=mxx*x+mxy*y+mxz*z+tx;
		v.y=myx*x+myy*y+myz*z+ty;
		v.z=mzx*x+mzy*y+mzz*z+tz;
	};

	void cnv(BReal v[3],BReal x,BReal y,BReal z) {
		v[0]=mxx*x+mxy*y+mxz*z+tx;
		v[1]=myx*x+myy*y+myz*z+ty;
		v[2]=mzx*x+mzy*y+mzz*z+tz;
	};

	void cnv(BReal&t1,BReal&t2,BReal&t3,BReal x,BReal y,BReal z) {
		t1=mxx*x+mxy*y+mxz*z+tx;
		t2=myx*x+myy*y+myz*z+ty;
		t3=mzx*x+mzy*y+mzz*z+tz;
	};

	void cnv(BReal*t1,BReal*t2,BReal*t3,BReal x,BReal y,BReal z) {
		*t1=mxx*x+mxy*y+mxz*z+tx;
		*t2=myx*x+myy*y+myz*z+ty;
		*t3=mzx*x+mzy*y+mzz*z+tz;
	};

	/*void icnv(BVector3&v,BReal x,BReal y,BReal z){
	BReal t1,t2,t3;
	t1=x-tx;t2=y-ty;t3=z-tz;
	v.x=mxx*t1+myx*t2+mzx*t3;
	v.y=mxy*t1+myy*t2+mzy*t3;
	v.z=mxz*t1+myz*t2+mzz*t3;
	};*/
	void icnv(BReal&u1,BReal&u2,BReal&u3,BReal x,BReal y,BReal z) {
		BReal t1,t2,t3;
		t1=x-tx;
		t2=y-ty;
		t3=z-tz;
		u1=mxx*t1+myx*t2+mzx*t3;
		u2=mxy*t1+myy*t2+mzy*t3;
		u3=mxz*t1+myz*t2+mzz*t3;
	};

	void icnv(BReal v[3],BReal x,BReal y,BReal z) {
		BReal t1,t2,t3;
		t1=x-tx;
		t2=y-ty;
		t3=z-tz;
		v[0]=mxx*t1+myx*t2+mzx*t3;
		v[1]=mxy*t1+myy*t2+mzy*t3;
		v[2]=mxz*t1+myz*t2+mzz*t3;
	};

	void SetInverse(const CoordinateMatrix&t) {
		tx=-(t.mxx*t.tx+t.myx*t.ty+t.mzx*t.tz);
		ty=-(t.mxy*t.tx+t.myy*t.ty+t.mzy*t.tz);
		tz=-(t.mxz*t.tx+t.myz*t.ty+t.mzz*t.tz);
		mxx=t.mxx;
		mxy=t.myx;
		mxz=t.mzx;
		myx=t.mxy;
		myy=t.myy;
		myz=t.mzy;
		mzx=t.mxz;
		mzy=t.myz;
		mzz=t.mzz;
	};

	void GetGLMatrix(double m[16])const {
		m[0]=(double)mxx;
		m[4]=(double)mxy;
		m[ 8]=(double)mxz;
		m[12]=(double)tx;
		m[1]=(double)myx;
		m[5]=(double)myy;
		m[ 9]=(double)myz;
		m[13]=(double)ty;
		m[2]=(double)mzx;
		m[6]=(double)mzy;
		m[10]=(double)mzz;
		m[14]=(double)tz;
		m[3]=0.0;
		m[7]=0.0;
		m[11]=0.0;
		m[15]=1.0;
	}

	void GetGLMatrix(float m[16])const {
		m[0]=(float)mxx;
		m[4]=(float)mxy;
		m[ 8]=(float)mxz;
		m[12]=(float)tx;
		m[1]=(float)myx;
		m[5]=(float)myy;
		m[ 9]=(float)myz;
		m[13]=(float)ty;
		m[2]=(float)mzx;
		m[6]=(float)mzy;
		m[10]=(float)mzz;
		m[14]=(float)tz;
		m[3]=0.0f;
		m[7]=0.0f;
		m[11]=0.0f;
		m[15]=1.0f;
	}

	void SetGLMatrix(const double m[16]) {
		mxx=(BReal)m[0];
		mxy=(BReal)m[4];
		mxz=(BReal)m[ 8];
		tx=(BReal)m[12];
		myx=(BReal)m[1];
		myy=(BReal)m[5];
		myz=(BReal)m[ 9];
		ty=(BReal)m[13];
		mzx=(BReal)m[2];
		mzy=(BReal)m[6];
		mzz=(BReal)m[10];
		tz=(BReal)m[14];
	}

	void SetGLMatrix(const float m[16]) {
		mxx=(BReal)m[0];
		mxy=(BReal)m[4];
		mxz=(BReal)m[ 8];
		tx=(BReal)m[12];
		myx=(BReal)m[1];
		myy=(BReal)m[5];
		myz=(BReal)m[ 9];
		ty=(BReal)m[13];
		mzx=(BReal)m[2];
		mzy=(BReal)m[6];
		mzz=(BReal)m[10];
		tz=(BReal)m[14];
	}

	void GetTGLMatrix(double m[16])const {
		m[0]=(double)mxx;
		m[4]=(double)myx;
		m[ 8]=(double)mzx;
		m[12]=(double)tx;
		m[1]=(double)mxy;
		m[5]=(double)myy;
		m[ 9]=(double)mzy;
		m[13]=(double)ty;
		m[2]=(double)mxz;
		m[6]=(double)myz;
		m[10]=(double)mzz;
		m[14]=(double)tz;
		m[3]=(double)0.0;
		m[7]=(double)0.0;
		m[11]=(double)0.0;
		m[15]=(double)1.0;
	}

	void GetTGLMatrix(float m[16])const {
		m[0]=(float)mxx;
		m[4]=(float)myx;
		m[ 8]=(float)mzx;
		m[12]=(float)tx;
		m[1]=(float)mxy;
		m[5]=(float)myy;
		m[ 9]=(float)mzy;
		m[13]=(float)ty;
		m[2]=(float)mxz;
		m[6]=(float)myz;
		m[10]=(float)mzz;
		m[14]=(float)tz;
		m[3]=(float)0.0f;
		m[7]=(float)0.0f;
		m[11]=(float)0.0f;
		m[15]=(float)1.0f;
	}

	void operator=(const CoordinateMatrix&c) {
		mxx=c.mxx;
		mxy=c.mxy;
		mxz=c.mxz;
		mxx=c.myx;
		myy=c.myy;
		myz=c.myz;
		mxx=c.mzx;
		mzy=c.mzy;
		mzz=c.mzz;
		tx=c.tx;
		ty=c.ty;
		tz=c.tz;
	}

	void operator*=(const CoordinateMatrix&c) {
		CoordinateMatrix t;
		t.mxx=mxx*c.mxx+mxy*c.myx+mxz*c.mzx;
		t.myx=myx*c.mxx+myy*c.myx+myz*c.mzx;
		t.mzx=mzx*c.mxx+mzy*c.myx+mzz*c.mzx;

		t.mxy=mxx*c.mxy+mxy*c.myy+mxz*c.mzy;
		t.myy=myx*c.mxy+myy*c.myy+myz*c.mzy;
		t.mzy=mzx*c.mxy+mzy*c.myy+mzz*c.mzy;

		t.mxz=mxx*c.mxz+mxy*c.myz+mxz*c.mzz;
		t.myz=myx*c.mxz+myy*c.myz+myz*c.mzz;
		t.mzz=mzx*c.mxz+mzy*c.myz+mzz*c.mzz;

		t.tx =mxx*c.tx +mxy*c.ty +mxz*c.tz +tx;
		t.ty =myx*c.tx +myy*c.ty +myz*c.tz +ty;
		t.tz =mzx*c.tx +mzy*c.ty +mzz*c.tz +tz;
		*this=t;
	}
};

char*MakeString(const char*s);
void CopyString(char*&d,const char*s);
void CopyString2(char*&d,const char*s);
void DeleteString(char*&s);

//char*str_copy(const char*s);
//void str_copy(char*&d,const char*s);
inline char*str_copy(const char*s) {
	return MakeString(s);
}

inline void str_copy(char*&d,const char*s) {
	CopyString(d,s);
}

#ifdef GetObject
#undef GetObject
#endif

#endif
