#include"Declaration.h"
#include <GL/glut.h>
#include "Voxel.h"

void object() {
	Voxel voxel;

	voxel.set_voxelcolor(1.0, 0, 0);
	voxel.set_voxelsize(10);

	voxel.create_voxel(0, 0, 0);

}