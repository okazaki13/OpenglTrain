#include"Declaration.h"
#include <GL/glut.h>
#include "Voxel.h"
#include"Tool.h"

void object() {
	Voxel voxel;
	Tool tool;

	voxel.set_voxelcolor(1.0, 0, 0);
	voxel.set_voxelsize(10);
	voxel.create_voxel(20, 10, 20);

	tool.create_ballendmill(0,0,0);
	tool.drawCylinder(tool.get_endmill_D() / (2.2f * 10), tool.get_endmill_D(), 20);

}