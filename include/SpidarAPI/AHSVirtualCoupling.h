#pragma once

#include "spidarapi.h"
#include "AHSQuaternion.h"
#include "AHSVector3.h"

template <class T> class CSpidarEnhance;

template <class T>
class SPIDARAPI_API CAHSVirtualCoupling :
	public CSpidarAPI
{
//protected:
//	int sem;
protected:
	T m_posK;
	T m_posB;
	T m_oriK;
	T m_oriB;
private:
	T m_posGripScale;
	T m_oriGripScale;
	T m_forceObjScale;
	T m_torqueObjScale;
protected:
	CAHSVector3<T> m_pos;
	CAHSVector3<T> m_ori;

public:
	CAHSVirtualCoupling(void);
	virtual ~CAHSVirtualCoupling(void);

public:
	T GetGripPosScale();
	T GetGripOriScale();
	T GetObjForceScale();
	T GetObjTorqueScale();
public:
	T GetPosNorm();
	T GetOriNorm();

public:
	void SetGripPOscale(T pos_grip_scale,T ori_grip_scale);
public:
	void SetObjFTscale(T force_obj_scale,T torque_obj_scale);
public:
	void SetKB(T posK,T posB,T oriK,T oriB);

public:
	virtual void SetSpidar(CSpidarEnhance<T>* pSpidar) = 0;
	virtual CSpidarEnhance<T>* GetSpidar() = 0;

public:
	virtual void Update(
		int isCoupling,float simHz,
		CAHSVector3<T>		posObj,	CAHSVector3<T>		posVelObj,	CAHSVector3<T>&		forceObj,
		CAHSQuaternion<T>	oriObj,	CAHSVector3<T>		oriVelObj,	CAHSVector3<T>&		torqueObj,
		int spidar_id
		);

protected:
	virtual void UpdateVelBase(
		int isCoupling,
		CAHSVector3<T>		posObj,	CAHSVector3<T>		posVelObj,	CAHSVector3<T>&		forceObj,
		CAHSQuaternion<T>	oriObj,	CAHSVector3<T>		oriVelObj,	CAHSVector3<T>&		torqueObj,
		int spidar_id
		) = 0;

};
