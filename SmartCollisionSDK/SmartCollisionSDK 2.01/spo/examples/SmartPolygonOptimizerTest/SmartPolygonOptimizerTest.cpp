/*************************************************************************\

  Copyright 2006 3D Inc.
  All Rights Reserved.

 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "spo.h"

// loads object
bool LoadObject(SPOObject&object,const char*file)
{
    FILE*fp;
    fp=fopen(file,"r");
    if(fp==NULL){
        printf("Error: Failed to load file '%s'\n",file);
        return false;
    }
    int vertexSize=0;
    int faceSize=0;
    // count vertices and faces
    for(;;){
        char s[2000];
        int c;
        c=getc(fp);if(c==EOF)break;ungetc(c,fp);
        fgets(s,2000,fp);
        double v[3];
        int f[3];
        if(sscanf(s,"v %lg %lg %lg",v+0,v+1,v+2)==3)vertexSize++;
        if(sscanf(s,"f %d %d %d",f+0,f+1,f+2)==3)faceSize++;
    }
    rewind(fp);
    double*vertices=new double[vertexSize*3];
    int*faces=new int[faceSize*3];
    int i=0,j=0;
    // store vertices and faces
    for(;;){
        char s[2000];
        int c;
        c=getc(fp);if(c==EOF)break;ungetc(c,fp);
        fgets(s,2000,fp);
        if(sscanf(s,"v %lg %lg %lg",
                  vertices+3*i+0,
                  vertices+3*i+1,
                  vertices+3*i+2)==3){
            i++;
        }
        int f[3];
        if(sscanf(s,"f %d %d %d",f+0,f+1,f+2)==3){
            faces[3*j+0]=f[0]-1;
            faces[3*j+1]=f[1]-1;
            faces[3*j+2]=f[2]-1;
            j++;
        }
    }
    fclose(fp);
    int result;
    // addTriangles
    result=object.AddTriangles(vertices,vertexSize,
                               faces,faceSize);
    if(result==SPO_ERROR_INVALID_LICENSE){
        printf("Error: Invalid license.\n");
        return false;
    }
    if(result!=SPO_NO_ERROR){
        printf("Error: Failed to add triangles.\n");
        return false;
    }
    delete vertices;
    delete faces;
    return true;
}

// print the result of diagnosis about SPOObject
void Print(SPOObject&object)
{
    int i;
    printf("Closed:%s\n",object.IsClosed()?"true":"false");
    printf("Convex:%s\n",object.IsConvex(1e-3)?"true":"false");
    printf("Single piece:%s\n",object.IsSingleBoundary()?"true":"false");
    printf("PicesSize=%d\n",object.GetPieceCount());
    for(i=0;i<object.GetPieceCount();i++){
        const SPOPiece*p=object.GetPiece(i);
        printf(" #%d\n",i);
        printf("  vertex size: %d\n",p->vertexSize);
        printf("  triangle size: %d\n",p->triangleSize);
        printf("  Closed:%s\n",object.IsClosed(i)?"true":"false");
        printf("  Convex:%s\n",object.IsConvex(i,1e-3)?"true":"false");
        printf("  Single piece:%s\n",object.IsSingleBoundary(i)?"true":"false");
        printf("  Branched  edge:%d\n",object.GetEdgeCount(SPO_EDGE_TYPE_BRANCHED,i));
        printf("  Duplicate edge:%d\n",object.GetEdgeCount(SPO_EDGE_TYPE_DUPLICATE,i));
        printf("  Unlinked  edge:%d\n",object.GetEdgeCount(SPO_EDGE_TYPE_UNLINKED,i));
        printf("  Folding   edge:%d\n",object.GetEdgeCount(SPO_EDGE_TYPE_FOLDING,i,1e-3));
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int i;
    for(i=1;i<argc;i++){
        SPOObject object;
        if(LoadObject(object,argv[i])==false){
            printf("Error:Falied to load  object '%s'\n",argv[i]);
            return -1;
        }
        printf("***Imformation of raw model data***\n");
        Print(object);
        // Insert methods of modification
        object.ConnectVertices(1e-4);
        object.SplitEdges(2,20);
        object.CloseHoles();
        object.RemoveRedundantVertices(0.01,20);
        object.RemoveThinTriangles(0.05,20);
        object.ChangeTriangulationPattern(SPO_TRIANGULATION_TYPE_REDUCE_WIDTH_DIFFERENCE,0.01,20);
        object.RemoveRedundantVertices(0.01,20);
        object.DecomposeIntoSingleBoundaryPieces();
        printf("***Imformation of modified model data***\n");
        Print(object);
    }
    system("pause");
    return 0;
}

