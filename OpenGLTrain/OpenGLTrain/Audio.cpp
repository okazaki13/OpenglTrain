#include <windows.h>
#include <mmsystem.h>
#include <tchar.h>
#pragma comment(lib, "winmm.lib") 

//(’†—ª)ƒR[ƒhã‚Ì‰¹‚ğ–Â‚ç‚µ‚½‚¢ˆ—‚Ì‚Æ‚±‚ë‚É‘}“ü

int OpenSpidarVoice(void) {
	PlaySound("OpenSpidar.wav", NULL, SND_FILENAME | SND_ASYNC);

	return 0;
}