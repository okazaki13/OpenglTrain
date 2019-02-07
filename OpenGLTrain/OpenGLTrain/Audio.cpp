#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib") 
#include <iostream>

//コード上の音を鳴らしたい処理のところに挿入

//「スパイダーシステム、起動」
int OpenSpidarVoice(void) {
	PlaySound("OpenSpidar.wav", NULL, SND_FILENAME | SND_ASYNC);
	return 0;
}