#ifndef OBJECT_MANIPULATOR_H
#define OBJECT_MANIPULATOR_H

/** @file
 *  @brief This file is Definition of Class ObjectManipulator.
 */
#include "BasicTypes.h"

class ObjectManipulator
{
private:
	BReal	scale_;
	int		wx_,wy_;

	BVector3 point1_;
	BVector3 position_;
	BVector3 position0_;

	BQuaternion orientation_;
	BQuaternion orientation0_;

	enum MOUSE_MODE{
		NONE,
		ROTATE,
		SCALE,
		ROTATE_X,
		ROTATE_Y,
		ROTATE_Z,
		TRANSLATE_XY,
		TRANSLATE_YZ,
		TRANSLATE_XZ};
	MOUSE_MODE mouse_mode_;

	void SetTransformation(const BVector3&p, const BQuaternion&q);

public:
	ObjectManipulator(void);
	void Initialize(void);

	void SetPosition(const BVector3&p);
	void SetOrientation(const BQuaternion&q);

	void GetPosition(BVector3&p);
	void GetOrientation(BQuaternion&q);

	// MouseInterface
	bool OnLeftButtonDown(int x,int y);
	bool OnLeftButtonUp(int x,int y);
	bool OnRightButtonDown(int x,int y);
	bool OnRightButtonUp(int x,int y);
	bool OnMiddleButtonDown(int x,int y);
	bool OnMiddleButtonUp(int x,int y);

	void OnMouseMove(int x,int y);
	void OnSize(int wx,int wy);
};

#endif
