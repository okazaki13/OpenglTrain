#pragma once
#include <windows.h>


//----------------------------------------------------
// �֐��v���g�^�C�v�i��ɌĂяo���֐����ƈ����̐錾�j
//----------------------------------------------------
void Initialize(void);
void Display(void);
void Ground(void);  //��n�̕`��

void object();

int OpenSpidarVoice(void);


//SpidarInit.cpp
void init_spidar();
void CALLBACK hapticLoop_w3p4(DWORD dwUser);
void endHaptic();