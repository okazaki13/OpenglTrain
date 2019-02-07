/** @file
 *  @brief This file is implimentaion of class ObjectManipulator.
 */
#include "ObjectManipulator.h"
#include <windows.h>

static void calcDxDy(double&dx,double&dy,
		     BVector3 point1,
		     BVector3 point,int wx,int wy)
{
	dx= (double)(point.x-point1.x)/wx;
	dy= (double)(point.y-point1.y)/wy;

	return;
}

ObjectManipulator::ObjectManipulator(void)
{
	position_=0;
	orientation_.Identity();
}

void ObjectManipulator::Initialize(void)
{
	position_=0;
	orientation_.Identity();
	mouse_mode_=NONE;
	scale_=0.1f;

	return;
}

void ObjectManipulator::SetPosition(const BVector3&p)
{
	if(!(mouse_mode_==TRANSLATE_XY || mouse_mode_==TRANSLATE_XZ))
		position_=p;
	SetTransformation(position_,orientation_);

	return;
}

void ObjectManipulator::SetOrientation(const BQuaternion&q)
{
	orientation_=q;
	SetTransformation(position_,orientation_);

	return;
}

void ObjectManipulator::SetTransformation(const BVector3&p,
					  const BQuaternion&q)
{
	position_=p;
	orientation_=q;

	return;
}

void ObjectManipulator::GetPosition(BVector3&p)
{
	p=position_;

	return;
}

void ObjectManipulator::GetOrientation(BQuaternion&q)
{
	q=orientation_;

	return;
}

bool ObjectManipulator::OnLeftButtonDown(int x,int y)
{
	BVector3 point;
	point.Set(static_cast<BReal>(x), static_cast<BReal>(y), 0.0f);

	if(mouse_mode_==NONE)
	{
		orientation0_=orientation_;
		point1_=point;
		int fx,fy;
		double ex,ey;
		BVector3 point0;point0=0;
		calcDxDy(ex,ey,point0,point1_,wx_,wy_);

		if     (ex<=0.33)fx=0;
		else if(ex< 0.67)fx=1;
		else            fx=2;
		if     (ey<=0.33)fy=0;
		else if(ey< 0.67)fy=1;
		else            fy=2;

		if(fx==1)
		{
			if(fy==1);
			else     
				mouse_mode_=ROTATE_X;
		}
		else
		{
			if(fy==1)
				mouse_mode_=ROTATE_Y;
			else     
				mouse_mode_=ROTATE_Z;
		}
	}
	return false;
}

bool ObjectManipulator::OnLeftButtonUp(int x,int y)
{
	if(mouse_mode_!=NONE)
	{
		mouse_mode_=NONE;
		return true;
	}
	return false;
}

bool ObjectManipulator::OnRightButtonDown(int x,int y)
{
	BVector3 point;
	point.Set(static_cast<BReal>(x), static_cast<BReal>(y), 0.0f);
	if(mouse_mode_==NONE)
	{
		point1_=point;
		position0_=position_;
		mouse_mode_=TRANSLATE_XZ;
		return true;
	}
	return false;
}

bool ObjectManipulator::OnRightButtonUp(int x,int y)
{
	if(mouse_mode_!=NONE)
	{
		mouse_mode_=NONE;
		return true;
	}
	return false;    
}

bool ObjectManipulator::OnMiddleButtonDown(int x,int y)
{
	BVector3 point;
	point.Set(static_cast<BReal>(x), static_cast<BReal>(y), 0.0f);
	if(mouse_mode_==NONE)
	{
		point1_=point;
		position0_=position_;
		mouse_mode_=TRANSLATE_XY;
		return true;
	}
	return false;
}

bool ObjectManipulator::OnMiddleButtonUp(int x,int y)
{
	if(mouse_mode_!=NONE)
	{
		mouse_mode_=NONE;
		return true;
	}
	return false;
}

void ObjectManipulator::OnMouseMove(int x,int y)
{
	BVector3 point;
	point.Set(static_cast<BReal>(x), static_cast<BReal>(y), 0.0f);
	if(mouse_mode_==TRANSLATE_XY)
	{
		position_.x=position0_.x+(point.x-point1_.x)*scale_;
		position_.y=position0_.y-(point.y-point1_.y)*scale_;
	}
	else if(mouse_mode_==TRANSLATE_XZ)
	{
		position_.x=position0_.x+(point.x-point1_.x)*scale_;
		position_.z=position0_.z+(point.y-point1_.y)*scale_;
	}
	else if(mouse_mode_==ROTATE_X)
	{
		double dx,dy;calcDxDy(dx,dy,point1_,point,wx_,wy_);
		orientation_=orientation0_;
		BQuaternion dq;
		dq.SetRotation(static_cast<BReal>(dy*(M_PI*1)), 0.0f, 0.0f);orientation_.MultiplyFromLeft(dq);
	}
	else if(mouse_mode_==ROTATE_Y)
	{
		double dx,dy;calcDxDy(dx,dy,point1_,point,wx_,wy_);
		orientation_=orientation0_;
		BQuaternion dq;
		dq.SetRotation(0.0f, static_cast<BReal>(dx*(M_PI*1)), 0.0f);orientation_.MultiplyFromLeft(dq);
	}
	else if(mouse_mode_==ROTATE_Z)
	{
		BVector3 point0;point0=0;
		double dx,dy;calcDxDy(dx,dy,point0,point1_,	wx_,wy_);
		double ex,ey;calcDxDy(ex,ey,point0,point	,wx_,wy_);
		orientation_=orientation0_;
		BReal t=static_cast<BReal>( atan2(dy-0.5,dx-0.5)-atan2(ey-0.5,ex-0.5) );
		BQuaternion dq;
		dq.SetRotation(0,0,t);orientation_.MultiplyFromLeft(dq);
	}
	else
		return;

	SetTransformation(position_,orientation_);

	return;
}

void ObjectManipulator::OnSize(int wx0,int wy0)
{
	wx_=wx0;wy_=wy0;

	return;
}
