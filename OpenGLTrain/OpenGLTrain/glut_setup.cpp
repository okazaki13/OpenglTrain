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
	glClearColor(1.0, 1.0, 1.0, 1.0); //背景色
	glEnable(GL_DEPTH_TEST);//デプスバッファを使用：glutInitDisplayMode() で GLUT_DEPTH を指定する

	gluPerspective(30.0, (double)WindowWidth / (double)WindowHeight, 0.1, 1000.0); //透視投影法の視体積gluPerspactive(th, w/h, near, far);
	gluLookAt(
		0.0, -100.0, 50.0, // 視点の位置x,y,z;
		0.0, 100.0, 0.0,   // 視界の中心位置の参照点座標x,y,z
		0.0, 0.0, 1.0);  //視界の上方向のベクトルx,y,z
}




//openGLのセットアップをまとめた関数
void openGL_setup(int argc, char *argv[]) {
	glutInit(&argc, argv);//環境の初期化
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//ウィンドウの位置の指定
	glutInitWindowSize(WindowWidth, WindowHeight); //ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  //ウィンドウの作成
	glutDisplayFunc(Display); //描画時に呼び出される関数を指定する（関数名：Display）
	Initialize(); //初期設定の関数を呼び出す
}