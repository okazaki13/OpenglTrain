#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib") 

//(中略)コード上の音を鳴らしたい処理のところに挿入

int OpenSpidarVoice(void) {
	PlaySound("OpenSpidar.wav", NULL, SND_FILENAME | SND_ASYNC);
}