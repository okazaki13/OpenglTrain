/*************************************************************************\

  Copyright(C) 2006 3D Inc.
  All Rights Reserved.

*************************************************************************/
#ifndef _SC_SCENE_MANAGER_H_
#define _SC_SCENE_MANAGER_H_

#include"sc.h"
#include"SmartCollisionExport.h"

//
#define SC_SCENE_MANAGER_CLOSED_POLYHEDRA SC_OBJECT_TYPE_CLOSED_POLYHEDRA
#define SC_SCENE_MANAGER_TRIANGLE_SOUP    SC_OBJECT_TYPE_TRIANGLE_SOUP

// attributes of SCSceneManager
#define SC_SCENE_MANAGER_TOLERANCE                     100
#define SC_SCENE_MANAGER_MAX_DISTANCE                  101
#define SC_SCENE_MANAGER_MAX_ITERATION                 102
#define SC_SCENE_MANAGER_SAFETY_COEFFICIENT            103
#define SC_SCENE_MANAGER_FORCE_STIFFNESS               104
#define SC_SCENE_MANAGER_TORQUE_STIFFNESS              105
#define SC_SCENE_MANAGER_ROTATION_MODE                 106
#define SC_SCENE_MANAGER_TYPE                          107
#define SC_SCENE_MANAGER_PENETRATION_DEPTH_COMPUTATION 108
#define SC_VERSION                                     1000

#define SC_ROTATION_MODE_NONE  201
#define SC_ROTATION_MODE_INPUT 202
#define SC_ROTATION_MODE_FREE  203
#define SC_ROTATION_MODE_MIX   204

class SingleObjectCollisionManager;
class SCObject;

class SCDllExport SCSceneManager
{
private:
	SingleObjectCollisionManager*manager;
	SCuint license;

	SCint GetStatus0(SCenum type,SCdouble*status);
	SCint GetStatus0(SCenum type,SCfloat*status);
	SCint GetStatus0(SCenum type,SCint*status);
public:
	SCSceneManager(SCenum type);
	~SCSceneManager(void);

	SCint SetAttributeDouble(SCenum attribute,SCdouble value);
	SCint SetAttributeFloat(SCenum attribute,SCfloat value);
	SCint SetAttributeInteger(SCenum attribute,SCint value);
	SCint SetAttributeEnum(SCenum attribute,SCenum value);

	SCint GetAttributeDouble(SCenum attribute,SCdouble&value)const;
	SCint GetAttributeFloat(SCenum attribute,SCfloat&value)const;
	SCint GetAttributeInteger(SCenum attribute,SCint&value)const;
	SCint GetAttributeEnum(SCenum attribute,SCenum&value)const;
	SCint GetAttributeString(SCenum attribute,const SCstring&value)const;

	SCint AddObject(SCint id,SCObject*object);
	SCint DeleteObject(SCint id);
    // Sets grouping
	SCint AddObjectToGroup(SCint gid,SCint id);
	SCint DeleteObjectFromGroup(SCint gid,SCint id);
    SCint DeleteGroup(int gid);
    SCint ResetGroup(void);
	// obsolute forms
	SCint AddControlledObject(SCint id,SCint gid=SC_DEFAULT_GROUP_ID)
	{
		return AddObjectToGroup(gid,id);
	}
	SCint DeleteControlledObject(SCint id,SCint gid=SC_DEFAULT_GROUP_ID)
	{
		return DeleteObjectFromGroup(gid,id);
	}
    // obsolute forms
	SCint DeactivateObject(SCint oid);
	SCint ActivateObject(SCint oid);
    
    // Sets activity
	SCint SetActivityObject(SCint gid,SCenum type);
	SCint SetActivityGroup(SCint gid,SCenum type);
	SCint SetActivityGroupPair(SCint gid1,SCint gid2,SCenum type);
    SCint ResetActivity(void);
    // 
	SCint SetTransformation(int gid,SCenum type,const SCfloat *trans);
	SCint SetTransformation(int gid,SCenum type,const SCdouble*trans);
	SCint GetTransformation(int gid,SCenum type,SCfloat *trans)const;
	SCint GetTransformation(int gid,SCenum type,SCdouble*trans)const;
    // obsolute forms
	SCint SetTransformation(SCenum type,const SCfloat*trans,
                            SCint gid=SC_DEFAULT_GROUP_ID)
	{
		return SetTransformation(gid,type,trans);
	}
	SCint SetTransformation(SCenum type,const SCdouble*trans,
                            SCint gid=SC_DEFAULT_GROUP_ID)
	{
		return SetTransformation(gid,type,trans);
	}
	SCint GetTransformation(SCenum type,SCfloat*trans,
                            SCint gid=SC_DEFAULT_GROUP_ID)const
	{
		return GetTransformation(gid,type,trans);
	}
	SCint GetTransformation(SCenum type,SCdouble*trans,
                            SCint gid=SC_DEFAULT_GROUP_ID)const
	{
		return GetTransformation(gid,type,trans);
	}
	// Updates status
	SCint UpdateStatus(void);
	// Gets status
	SCint GetStatus(SCenum type,SCint*status);
	SCint GetStatus(SCenum type,SCfloat*status);
	SCint GetStatus(SCenum type,SCdouble*status);
	// Gets status for multiple objects
	SCint GetStatus(SCenum type,SCint   *status,SCint index,SCbool reverseFlag=false);
	SCint GetStatus(SCenum type,SCfloat *status,SCint index,SCbool reverseFlag=false);
	SCint GetStatus(SCenum type,SCdouble*status,SCint index,SCbool reverseFlag=false);
    // Resets status
    SCint ResetStatus(void);
};

#endif
