// HelloSmartCollision.cpp

#include <stdio.h>
#include <stdlib.h>

#include "sc.h"

double vertices[12]={0,0,0,
    1,0,0,
    0,1,0,
    0,0,1};
int triangles[12]={0,2,1,
    1,3,0,
    0,3,2,
    1,2,3};

int main(int argc, char* argv[])
{
    SCSceneManager manager(SC_SCENE_MANAGER_CLOSED_POLYHEDRA);
    SCObject object1(SC_OBJECT_TYPE_CLOSED_POLYHEDRON);
	SCObject object2(SC_OBJECT_TYPE_CLOSED_POLYHEDRON);
    double position1[3]={1.0,1.0,1.0};
    double position2[3]={0.0,0.0,0.5};
    double distance;
    // Add geometry to objects
	if(object1.AddTriangles(vertices,4,triangles,4)==SC_ERROR_INVALID_LICENSE){
		// license check error happened
		printf("Error: Invalid lincense.\n");
		system("pause");
        return -1;
    }
    object2.AddTriangles(SC_OBJECT_TYPE_CLOSED_POLYHEDRON,vertices,4,triangles,4);
    // Set attributes of SCSceneManager
    manager.SetAttributeDouble(SC_SCENE_MANAGER_MAX_DISTANCE,10.0);
    manager.SetAttributeDouble(SC_SCENE_MANAGER_TOLERANCE,0.1);
    manager.SetAttributeInteger(SC_SCENE_MANAGER_MAX_ITERATION,10);
    // Add objects SCSceneManager
    manager.AddObject(1000,&object1);
    manager.AddObject(2000,&object2);
    manager.AddObjectToGroup(0,1000);

	printf("Hello SmartCollision!\n");
	// Set transformation 
    manager.SetTransformation(SC_POSITION_ORIGIN,position1);
	// Execution of collision detection
    manager.UpdateStatus();
    // Get status of collision detection
    manager.GetStatus(SC_DISTANCE,&distance);
	// Print results
    printf("In position=%lg,%lg,%lg\n",position1[0],position1[1],position1[2]);
    printf("  Distance=%lg(=sqrt(4/3))\n",distance);
	// Set transformation 
    manager.SetTransformation(SC_POSITION_ORIGIN,position2);
	// Execution of collision detection
    manager.UpdateStatus();
    // Get status of collision detection
    manager.GetStatus(SC_DISTANCE,&distance);
	// Print results
    printf("In position=%lg,%lg,%lg\n",position2[0],position2[1],position2[2]);
    printf("  Pentration depth=%lg(=sqrt(1/12))\n",-distance);
	//
    system("pause");
    return 0;
}


