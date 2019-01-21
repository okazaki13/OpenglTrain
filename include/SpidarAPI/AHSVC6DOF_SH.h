#pragma once
#include "ahsvirtualcoupling.h"
#include "SHSpidarG.h"

template <class T> class CSpidarEnhance;
template <class T> class CSHSpidarG;

template <class T>
class CAHSVC6DOF_SH :
	public CAHSVirtualCoupling<T>
{
protected:
	CSHSpidarG<T>* m_pSpidar;

public:
	CAHSVC6DOF_SH(void);
	virtual ~CAHSVC6DOF_SH(void);
public:
	virtual void SetSpidar(CSpidarEnhance<T>* pSpidar);
	virtual CSpidarEnhance<T>* GetSpidar();

protected:
	virtual void UpdateVelBase(
		int isCoupling,
		CAHSVector3<T>		posObj,	CAHSVector3<T>		posVelObj,	CAHSVector3<T>&		forceObj,
		CAHSQuaternion<T>	oriObj,	CAHSVector3<T>		oriVelObj,	CAHSVector3<T>&		torqueObj,
		int spidar_id
		);

		/*
protected:
		virtual void UpdatePosBase(
		int isCoupling,float simHz,
		CAHSVector3<T>		posObj,	CAHSVector3<T>		posVelObj,	CAHSVector3<T>&		forceObj,
		CAHSQuaternion<T>	oriObj,	CAHSVector3<T>		oriVelObj,	CAHSVector3<T>&		torqueObj,
		int spidar_id
		);
		*/
	
};
