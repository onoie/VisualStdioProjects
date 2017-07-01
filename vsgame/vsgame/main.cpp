#include <DxLib.h>
int WINAPI WinMain(HINSTANCE h1, HINSTANCE hP, LPSTR lpC ,int nC){
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1){
		return 1;
	}
	DrawBox(0, 0, 120, 120, 0x00FFF, TRUE);
	WaitKey();
	DxLib_End();
	return 0;
}