/*************************************************************************\

  Copyright 2006 3D Inc.
  All Rights Reserved.
  
*************************************************************************/

#ifndef _SPO_OBJECT_H_
#define _SPO_OBJECT_H_

#include"SmartPolygonOptimizerExport.h"
#include"SPOCommon.h"

struct SPOPiece{
    SPOreal*vertices;
    SPOint vertexSize;
    SPOint*triangles;
    SPOint triangleSize;
};

class SPOObjectBody;

class SPODllExport SPOObject{
    SPOObjectBody*object;
public:
    SPOObject(void);
    ~SPOObject(void);
    SPOint AddTriangles(const SPOfloat*vertices,SPOint vertexSize,
			const SPOint*triangles,SPOint triangleSize);
    SPOint AddTriangles(const SPOdouble*vertices,SPOint vertexSize,
			const SPOint*triangles,SPOint triangleSize);
    SPOint GetPieceCount(void)const;
    const SPOPiece*GetPiece(int index)const;
    SPOObject&operator=(const SPOObject&object);
    SPOint RemoveClosedPieces(void);
    SPOint RemoveUnclosedPieces(void);
    SPOint RemoveConvexPieces(SPOdouble tolerance=0);
    SPOint RemoveNonconvexPieces(SPOdouble tolerance=0);

    SPOint ConnectVertices(SPOdouble tolerance,SPObool removeVerticesFlag=true);
    SPOint DecomposeIntoSingleBoundaryPieces(void);
    SPOint MergePieces(void);
    SPOint RemoveRedundantVertices(SPOdouble tolerance,int iteration,
                                   SPObool removeVerticesFlag=true);
    SPOint RemoveThinTriangles(SPOdouble tolerance,int iteration,
                               SPObool moveVerticesFlag=false);
    SPOint RemoveSmallVolumePieces(SPOdouble tolerance);
    SPOint SplitEdges(SPOdouble tolerance,int iteration=1,SPObool moveVerticesFlag=false);
    SPOint CloseHoles(void);
    SPOint ChangeTriangulationPattern(SPOenum type,SPOdouble tolerance,int iteration=1);

    SPObool IsClosed(void)const;
    SPObool IsClosed(SPOint index)const;
    SPObool IsConvex(SPOdouble tolerance=0)const;
    SPObool IsConvex(SPOint index,SPOdouble tolerance=0)const;
    SPObool IsSingleBoundary(void)const;
    SPObool IsSingleBoundary(SPOint index)const;

    SPOint GetEdgeCount(SPOenum type)const;
    SPOint GetEdgeCount(SPOenum type,SPOdouble tolerance)const;
    SPOint GetEdgeCount(SPOenum type,SPOint index,SPOdouble tolerance)const;
};

#endif
