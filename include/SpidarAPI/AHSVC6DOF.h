#pragma once
#include "ahsvirtualcoupling.h"
#include "SpidarEnhance.h"


template <class T>
class SPIDARAPI_API CAHSVC6DOF :
	public CAHSVirtualCoupling<T>
{
protected:
	CSpidarEnhance<T>* m_pSpidar;

protected:
	// グリップの情報
	//CAHSVector3<T>		posGripPrev;
	//CAHSQuaternion<T>	oriGripPrev;

	// オブジェクトの情報
	//CAHSVector3<T>		posObjePrev;
	//CAHSQuaternion<T>	oriObjePrev;

	// 力（出力）の情報
	CAHSVector3<T>		f_delta;
	CAHSVector3<T>		t_delta;

public:
	CAHSVC6DOF(void);
	virtual ~CAHSVC6DOF(void);
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
