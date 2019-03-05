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


//Spidar.cpp
void init_spidar();
void CALLBACK hapticLoop_w3p4(DWORD dwUser);
void endHaptic();
void check_spidar_being();
void value_conversion(float position[], float quaternion[]);

//display.cpp
void Display(void);
void Ground();  //大地の描画
void RedisplayTimer(int value);

//using_stl
void ready_tool();
void make_tool();

//using_voxel
void ready_voxel();
void make_voxel();

//keybord
void keyboard(unsigned char key, int x, int y);
void sKeybord(int Key, int x, int y);


//rotation
void QuaternionToAxisVector(float quaternion[4], float axisvector[4]);