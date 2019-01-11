#include "Voxel.h"
#include <GL/glut.h>



Voxel::Voxel()
{
}


Voxel::~Voxel()
{
}


void Voxel::create_voxel(int offset[2]) {
	//立方体
	glPushMatrix();
	glColor3d(color[0], color[1], color[2]);//色の設定
	glTranslated(offset[0], offset[1],offset[2]);//平行移動値の設定
	glutSolidCube(size);//引数：(一辺の長さ)
	glPopMatrix();

}

void Voxel::create_voxel(int offset_x, int offset_y, int offset_z) {
	//立方体
	glPushMatrix();
	glColor3d(color[0], color[1], color[2]);//色の設定
	glTranslated(offset_x, offset_y,offset_z);//平行移動値の設定
	glutSolidCube(size);//引数：(一辺の長さ)
	glPopMatrix();
}

void Voxel::set_voxelcolor(double R, double G, double B) {
	color[0] = R;
	color[1] = G;
	color[2] = B;

}

void Voxel::set_voxelsize(double s) {
	size = s;
}