/*************************************************************************\

  Copyright(C) 2006 3D Inc.
  All Rights Reserved.
  
*************************************************************************/

#ifndef SC_COMMOM_H
#define SC_COMMOM_H

typedef int SCint;
typedef unsigned int SCuint;
typedef int SCenum;
typedef float SCfloat;
typedef double SCdouble;
typedef char SCchar;
typedef char* SCstring;
typedef bool SCbool;

#define SC_NO_ERROR                        0
#define SC_ERROR_FAILED                    1
#define SC_ERROR_INVALID_ATTRIBUTE         2
#define SC_ERROR_INVALID_VALUE             3
#define SC_ERROR_INVALID_ID                4
#define SC_ERROR_DUPLICATE_ID              5
#define SC_ERROR_INVALID_TYPE             11
#define SC_ERROR_INVALID_TYPE_COMBINATION 12
#define SC_ERROR_INVALID_DATA             13
#define SC_ERROR_NO_RESULT                14
#define SC_ERROR_NO_CONTROLLED_OBJECT     15
#define SC_ERROR_INVALID_GROUP_ID         16
#define SC_ERROR_NO_OBJECT                17
#define SC_ERROR_INVALID_INDEX            18

#define SC_ERROR_DUPLICATE_GROUP_PAIR     19
#define SC_ERROR_INVALID_GROUP_PAIR       20

#define SC_ERROR_INVALID_BVH_FILE                    200
#define SC_ERROR_INVALID_INITIAL_TRANSFORMATION      201
#define SC_ERROR_UNKNOWN_DISTANCE                    202

#define SC_ERROR_INVALID_LICENSE                     300
//

#define SC_OBJECT_TYPE_TRIANGLE_SOUP     91
#define	SC_OBJECT_TYPE_CLOSED_POLYHEDRA  92
#define	SC_OBJECT_TYPE_CLOSED_POLYHEDRON 93
#define SC_OBJECT_TYPE_CONVEX_POLYHEDRON 94

// types of position
#define SC_POSITION_ORIGIN                300
#define SC_POSITION_WORLD_CENTER          301
#define SC_POSITION_LOCAL_CENTER          302
#define SC_POSITION_NEW_LOCAL_CENTER      303
#define SC_POSITION_NEW_WORLD_CENTER      304
// types of orientation
#define SC_ORIENTATION_QUATERNION         310
#define SC_ORIENTATION_MATRIX             311
// types of position
#define SC_TRANSFORMATION_MATRIX          320
#define SC_TRANSFORMATION_MULTIPLY_MATRIX 321
#define SC_TRANSFORMATION_INVERSE_MATRIX  322
// IDs of group
#define SC_DEFAULT_GROUP_ID            0
#define SC_STATIC_GROUP_ID            -1
// types of status
#define SC_DISTANCE                    401
#define SC_MD_VECTOR                   402
#define SC_TPD_VECTOR                  403
#define SC_CONVEX_TPD_VECTOR           404
#define SC_RPD_VECTOR                  405
#define SC_RPD_QUATERNION              406
#define SC_PD_MATRIX                   407
#define SC_PD_INVERSE_MATRIX           408

#define SC_POINT_ON_CONTROLLED_OBJECT        411
#define SC_POINT_ON_STATIC_OBJECT            412
#define SC_POINT_ON_CONTACT_OBJECT           413
#if 0
#define SC_POINT_ON_PENETRATION_OBJECT       414
#define SC_POINT_ON_LOCAL_CONTROLLED_OBJECT  415
#define SC_POINT_ON_LOCAL_STATIC_OBJECT      416
#endif
// 
#define SC_STATIC_OBJECT_ID                  417
#define SC_CONTROLLED_OBJECT_ID              418

//
#define SC_GROUP_ID                          439
#define SC_OBJECT_ID                         430
#define SC_PIECE_ID                          431
#define SC_CONTROLLED_OBJECT_ID2             418

#define SC_STATUS_RESULT                     440
#define SC_STATUS_COUNT                      441
#define SC_PAIR_COUNT                        441
#define SC_CONTACT_NORMAL                    445

#define SC_CONTROLLED_OBJECT_SIZE            501
#define SC_CONTROLLED_OBJECT_IDS             502

#define SC_ACTIVITY_ACTIVE                    0
#define SC_ACTIVITY_INACTIVE                  1
#define SC_ACTIVITY_PASSIVE                   2
#define SC_ACTIVITY_SLEEPING                  3
#define SC_ACTIVITY_ONE_WAY_ACTIVE            4
#define SC_ACTIVITY_ONE_WAY_INACTIVE          5

// after Ver 1.02
#define SC_CONTACT_POSITION                  601
#define SC_CONTACT_ORIENTATION               602
#define SC_CONTACT_TRANSFORMATION_MATRIX     603

// after Ver 1.5
#define SC_CTPD_VECTOR                       604
#define SC_CDISTANCE                         605
#define SC_POINT_ON_TARGET                   411
#define SC_POINT_ON_OPPONENT                 412
#define SC_POINT_ON_TARGET_IN_CONTACT        413
#define SC_OPPONENT_OBJECT_ID                417
#define SC_TARGET_OBJECT_ID                  418


#define SC_FALSE                             0
#define SC_TRUE                              1

#endif
