#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib") 
#include <iostream>

//�R�[�h��̉���炵���������̂Ƃ���ɑ}��

//�u�X�p�C�_�[�V�X�e���A�N���v
int OpenSpidarVoice(void) {
	PlaySound("OpenSpidar.wav", NULL, SND_FILENAME | SND_ASYNC);
	return 0;
}