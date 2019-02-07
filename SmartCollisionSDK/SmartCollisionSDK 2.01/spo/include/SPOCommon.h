/*************************************************************************\

  Copyright 2006 3D Inc.
  All Rights Reserved.
  
*************************************************************************/
#ifndef _SPO_COMMON_H_
#define _SPO_COMMON_H_

typedef int SPOint;
typedef unsigned int SPOuint;
typedef int SPOenum;
typedef float SPOfloat;
typedef double SPOdouble;
typedef char SPOchar;
typedef char* SPOstring;
typedef bool SPObool;

#ifdef SPO_REAL4
#  define SPO_REAL_SIZE                  4
#else
#  define SPO_REAL_SIZE                  8
#endif

#if SPO_REAL_SIZE == 8
typedef double SPOreal;
#else
typedef float SPOreal;
#endif

#define SPO_NO_ERROR                   0
#define SPO_ERROR_FAILED               100001
#define SPO_ERROR_INVALID_TYPE         100002
#define SPO_ERROR_INVALID_DATA         100003
#define SPO_ERROR_INVALID_LICENSE      1000000

#define SPO_PIECE_TYPE_UNKNOWN         0
#define SPO_PIECE_TYPE_CONVEX          1
#define SPO_PIECE_TYPE_CLOSED          2
#define SPO_PIECE_TYPE_SINGLE_BOUNDARY 4

#define SPO_EDGE_TYPE_BRANCHED         1
#define SPO_EDGE_TYPE_DUPLICATE        2
#define SPO_EDGE_TYPE_UNLINKED         4
#define SPO_EDGE_TYPE_FOLDING          8
#define SPO_EDGE_TYPE_FOLDED           8
#define SPO_EDGE_TYPE_LINKED          16

#define SPO_EDGE_TYPE_CONVEX          32
#define SPO_EDGE_TYPE_CONCAVE         64
#define SPO_EDGE_TYPE_FLAT           128

#define SPO_TRIANGULATION_TYPE_REDUCE_EDGE_LENGTH      1
#define SPO_TRIANGULATION_TYPE_REDUCE_AREA_DIFFERENCE  2
#define SPO_TRIANGULATION_TYPE_REDUCE_WIDTH_DIFFERENCE 3

#define SPO_VERSION                 1000

#endif
