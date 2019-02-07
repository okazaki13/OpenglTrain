/*************************************************************************\

  Copyright(C) 2006 3D Inc.
  All Rights Reserved.
  
*************************************************************************/
#ifndef _SC_OBJECT_H_
#define _SC_OBJECT_H_

#include"SCCommon.h"
#include"SmartCollisionExport.h"

class CollisionObject;
class SCSceneManager;

class SCDllExport SCObject{
private:
    CollisionObject*object;
    SCSceneManager*manager;
    SCuint id;
public:
    SCObject(SCenum type);
    SCObject(void);
    ~SCObject(void);
    //
    SCint SetTransformation(SCenum type,const SCfloat*trans);
    SCint SetTransformation(SCenum type,const SCdouble*trans);
    SCint GetTransformation(SCenum type,SCfloat*trans)const;
    SCint GetTransformation(SCenum type,SCdouble*trans)const;
    
    SCint AddTriangles(const SCdouble*vertex,SCint vertexNum,
                       const SCint*triangle,SCint triangleNum,
                       const SCchar*bvhFile=0);
    SCint AddTriangles(const SCfloat*vertex,SCint vertexNum,
                       const SCint*triangle,SCint triangleNum,
                       const SCchar*bvhFile=0);
    SCint AddTriangles(SCenum type,
                       const SCdouble*vertex,SCint vertexNum,
                       const SCint*triangle,SCint triangleNum,
                       const SCchar*bvhFile=0);
    SCint AddTriangles(SCenum type,
                       const SCfloat*vertex,SCint vertexNum,
                       const SCint*triangle,SCint triangleNum,
                       const SCchar*bvhFile=0);
    //
    friend SCSceneManager;
};

#endif
