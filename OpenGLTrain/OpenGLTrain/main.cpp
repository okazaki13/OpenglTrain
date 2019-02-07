#include"Declaration.h"
#include <GL/glut.h>
#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")

#include <stdio.h>


//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]) {
	extern int WindowPositionX;  //生成するウィンドウ位置のX座標
	extern int WindowPositionY;  //生成するウィンドウ位置のY座標
	extern int WindowWidth;   //生成するウィンドウの幅
	extern int WindowHeight ;    //生成するウィンドウの高さ
	extern char WindowTitle[]; //ウィンドウのタイトル

	


	check_spidar_being();



	openGL_setup(argc, argv);
	glutMainLoop();

	return 0;
}





								
