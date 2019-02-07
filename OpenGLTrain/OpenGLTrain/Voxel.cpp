#include "Voxel.h"
#include <GL/glut.h>



Voxel::Voxel()
{
	color[0] = 124;
	color[1] = 177;
	color[2] = 255;
	color[3] = 50;
	size = 1;
}


Voxel::~Voxel()
{
}


void Voxel::create_voxel(int offset[3]) {
	//立方体
	glPushMatrix();
	glClearColor(color[0], color[1], color[2],color[3]);//色の設定.引数は４つでRGBA（Aは透明度）
	glTranslated(offset[0], offset[1],offset[2]);//平行移動値の設定
	glutSolidCube(size);//引数：(一辺の長さ)
	glPopMatrix();

}

//cube一つだけ生成するとき
void Voxel::create_voxel(int offset_x, int offset_y, int offset_z) {
	//立方体
	glPushMatrix();
	glClearColor(color[0], color[1], color[2],color[3]);//色の設定。引数は４つでRGBA（Aは透明度）
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

//ボクセルで立方体か長方形のオブジェクトを作るとき
void Voxel::CreateVoxelObject(int a, int b, int c) {
	for (int i; i < a; i++) {
		for (int j; j < b; j++) {
			for (int k; k < c; k++) {
				glPushMatrix();
				glClearColor(color[0], color[1], color[2], color[3]);//色の設定
				glTranslated(i, j, k);//平行移動値の設定
				glutSolidCube(size);//引数：(一辺の長さ)
				voxelID[i][j][k] = true;
				glPopMatrix();
			}
		}
	}
}
