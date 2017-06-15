// GlobalHookDll.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//
// ref: http://chaboneko.daiwa-hotcom.com/wordpress/?p=34
#include "stdafx.h"
#include <cstdio>
#include <tchar.h>
#include "GlobalHookDll.h"

// ���ׂẴX���b�h�ɃZ�b�g�����t�b�N�ɂȂ�̂�
// �O���[�o���ϐ������L����K�v������
//���L�Z�O�����g
#pragma data_seg(".shareddata")
HHOOK hKeyHook = 0;
HWND g_hWnd = 0;        //�L�[�R�[�h�̑����̃E�C���h�E�n���h��
#pragma data_seg()

HINSTANCE hInst;
//bool bSetHook;    //SetHook�֐����Ă񂾃v���Z�X�ł��邩

EXPORT_API_ int SetHook(HWND hWnd)
{
	hKeyHook = SetWindowsHookEx(WH_KEYBOARD, KeyHookProc, hInst, 0);
	if (hKeyHook == NULL){
		//�t�b�N���s
	}
	else {
		//bSetHook = TRUE;
		//�t�b�N����
		g_hWnd = hWnd;
	}
	return 0;
}

EXPORT_API_ int ResetHook()
{
	if (UnhookWindowsHookEx(hKeyHook) != 0){
		//�t�b�N��������
	}
	else{
		//�t�b�N�������s
	}
	return 0;
}

EXPORT_API_ LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wp, LPARAM lp)
{
	TCHAR msg[64] = { 0 };
	if (nCode < 0)    //���܂莖
		return CallNextHookEx(hKeyHook, nCode, wp, lp);
	if (nCode == HC_ACTION){
		//�ړI�̃E�C���h�E�ɃL�[�{�[�h���b�Z�[�W�ƁA�L�[�R�[�h�̓]��

		// �ǂ��ŉ����Ă�HOOK����
		//�{�^���������ꂽ��Ԃ̎�����(�����̓X���[)
		if ((lp & 0x80000000) == 0){
			//�ʏ�L�[
			if ((lp & 0x20000000) == 0)
			{
				// Enter�ȊO
				if (wp != VK_RETURN) {
					_stprintf_s(msg, _T("%c�������ꂽ��(�L�E�ցE`)�I"), int(wp));
					MessageBox(NULL, msg, NULL, MB_OK);
					PostMessage(g_hWnd, WM_KEYDOWN, wp, 0);
				}
			}
			//�V�X�e���L�[(Alt(+����)�A��������F10�̎�)
			else
			{
				MessageBox(NULL, TEXT("�V�X�e���L�[�������ꂽ��I"), NULL, MB_OK);
				PostMessage(g_hWnd, WM_SYSKEYDOWN, wp, 0);
			}
		}
	}

	return CallNextHookEx(hKeyHook, nCode, wp, lp);
}

// �G���g���|�C���g
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// �A�^�b�`
		hInst = hModule;
		//bSetHook = FALSE;
		break;
	case DLL_PROCESS_DETACH:
		// �f�^�b�`
		break;
	}
	return TRUE;
}