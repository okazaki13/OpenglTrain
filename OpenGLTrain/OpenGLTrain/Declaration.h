#pragma once
#include <windows.h>


//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------

//glut_setup
void Initialize(void);
void openGL_setup(int argc, char *argv[]);



void object();

int OpenSpidarVoice(void);


//SpidarInit.cpp
void init_spidar();
void CALLBACK hapticLoop_w3p4(DWORD dwUser);
void endHaptic();
void check_spidar_being();

//display.cpp
void Display(void);
void Ground();  //大地の描画

//using_stl
void create_cutting_edge();
void matrix_cutting_edge();