#include"Declaration.h"
#include <GL/glut.h>
#include<iostream>

using namespace std;

//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //バッファの消去

	Ground();

	object();//工具や切削物などを表示する関数
	cout << "描画" << endl;
	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)でダブルバッファリングを利用可
}

//----------------------------------------------------
// 大地の描画
//----------------------------------------------------
void Ground() {
	double ground_max_x = 300.0;
	double ground_max_y = 300.0;
	glColor3d(0.8, 0.8, 0.8);  // 大地の色
	glBegin(GL_LINES);
	for (double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0) {
		glVertex3d(-ground_max_x, ly, 0);
		glVertex3d(ground_max_x, ly, 0);
	}
	for (double lx = -ground_max_x; lx <= ground_max_x; lx += 10.0) {
		glVertex3d(lx, ground_max_y, 0);
		glVertex3d(lx, -ground_max_y, 0);
	}
	glEnd();
}


void RedisplayTimer(int value) {

	glutPostRedisplay();
	glutTimerFunc(50, RedisplayTimer, 0); //第１引数でFPS指定（ms）
}