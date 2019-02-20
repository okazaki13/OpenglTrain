#include <GL/glut.h>
#include"Declaration.h"


int  WindowPositionX = 100;  //生成するウィンドウ位置のX座標
int  WindowPositionY = 100;  //生成するウィンドウ位置のY座標
int  WindowWidth = 512;    //生成するウィンドウの幅
int  WindowHeight = 512;    //生成するウィンドウの高さ
char WindowTitle[] = "世界の始まり";  //ウィンドウのタイトル

//----------------------------------------------------
// 初期設定の関数
//----------------------------------------------------
void Initialize(void) {
	glClearColor(1.0, 1.0, 1.0, 0.1); //背景色
	glEnable(GL_BLEND);//デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gluPerspective(30.0, (double)WindowWidth / (double)WindowHeight, 0.1, 1000.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);
	gluLookAt(
		20, -200.0, 50.0, // 視点の位置x,y,z;
		20, 0.0, 0.0,   // 視界の中心位置の参照点座標x,y,z
		0.0,0.0, 1.0);  //視界の上方向のベクトルx,y,z
}




