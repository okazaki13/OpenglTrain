#include"Declaration.h"
#include <GL/glut.h>

//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]) {
	extern int WindowPositionX;  //生成するウィンドウ位置のX座標
	extern int WindowPositionY;  //生成するウィンドウ位置のY座標
	extern int WindowWidth;   //生成するウィンドウの幅
	extern int WindowHeight ;    //生成するウィンドウの高さ
	extern char WindowTitle[]; //ウィンドウのタイトル

	OpenSpidarVoice();//茜ちゃんボイスの呼び出し

	glutInit(&argc, argv);//環境の初期化
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//ウィンドウの位置の指定
	glutInitWindowSize(WindowWidth, WindowHeight); //ウィンドウサイズの指定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//ディスプレイモードの指定
	glutCreateWindow(WindowTitle);  //ウィンドウの作成
	glutDisplayFunc(Display); //描画時に呼び出される関数を指定する（関数名：Display）
	Initialize(); //初期設定の関数を呼び出す
	glutMainLoop();
	return 0;
}





								
