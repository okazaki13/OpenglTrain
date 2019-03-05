#include"Declaration.h"
#include"GlobalVariable.h"
#include <GL/glut.h>
#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")

#pragma comment(lib,"../../SmartCollisionSDK/SmartCollisionSDK 2.01/lib/sc.lib")
#pragma comment(lib,"../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/lib/spo.lib")

#include <stdio.h>




//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]) {

	
	check_spidar_being();

	////////////////////////////////////
	//OpenGLの初期設定
	////////////////////////////////////
	glutInit(&argc, argv);//環境の初期化
	int  WindowPositionX = 100;  //生成するウィンドウ位置のX座標
	int  WindowPositionY = 100;  //生成するウィンドウ位置のY座標
	int  WindowWidth = 512;    //生成するウィンドウの幅
	int  WindowHeight = 512;    //生成するウィンドウの高さ
	char WindowTitle[] = "世界の始まり";  //ウィンドウのタイトル
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//ウィンドウの位置の指定
	glutInitWindowSize(WindowWidth, WindowHeight); //ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  //ウィンドウの作成
	glutDisplayFunc(Display); //描画時に呼び出される関数を指定する（関数名：Display）
	glutTimerFunc(1000, RedisplayTimer, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(sKeybord);
	Initialize(); //初期設定の関数を呼び出す



	///////////////////////////////////////
	//OpenGLのディスプレイリストとSC準備
	//////////////////////////////////////
	ready_tool();
	ready_voxel();



	atexit(endHaptic);
	glutMainLoop();

	return 0;
}





								
