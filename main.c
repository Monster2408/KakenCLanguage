#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <shellapi.h>
#include <shellapi.h>
#include <objbase.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "shell32.lib")

#define _WIN32_WINNT 0x0500
#define WINDOW_WIDTH    1280     // �\�t�g�N����ɕ\�����鏉���E�C���h�E���T�C�Y
#define WINDOW_HEIGHT   720      // �\�t�g�N����ɕ\�����鏉���E�C���h�E�c�T�C�Y

#define BUTTON_ID1 0             // Start Button
#define BUTTON_ID2 1             // End Button
#define BUTTON_IDA 2             // A Button
#define BUTTON_IDB 3             // B Button
#define BUTTON_ID  4

#define TITLE _T("TEST")

HWND MainHwnd;
HWND Button_1, Button_2, Button_A, Button_B, Button, NewButton; // �{�^���p

RECT recDisplay, recWindow, recClient;

BOOLEAN DebugMode = TRUE;

void DoGetActiveWindow(); // DoGetActiveWindow() �̐錾

int main() // �v���O�������s��Ɏ��s�����֐��H
{
	if (!DebugMode) 
	{
		HWND hWnd = GetConsoleWindow(); // �R���\�[���E�C���h�E�擾
		ShowWindow(hWnd, SW_MINIMIZE);  // �R���\�[���E�C���h�E�ŏ����H
		ShowWindow(hWnd, SW_HIDE);      // �R���\�[���E�C���h�E�B��
	}
	DoGetActiveWindow();            // DoGetActiveWindow() �̎��s
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
	HDC hdc;
	RECT rec;
	RECT rect;
	PAINTSTRUCT ps;
	int width = WINDOW_WIDTH;
	int height = WINDOW_HEIGHT;
	static int iCount = 0;
	static TCHAR strCount[8];


	static HWND hPush;

	switch (msg) {  // ������ꂽ���b�Z�[�W�𔭌�(?)

	case WM_CREATE:
		createButtons(hwnd, wp, lp, width);
		return 0;
		/*
			�E�C���h�E������ꂽ�瓮��I��
		*/
	case WM_DESTROY:                                                                      // �E�C���h�E������ꍇ
		PostQuitMessage(0);                                                               // �V�X�e�����I��炷
		return 0;
		/*
			�R�}���h
		*/
	case WM_COMMAND:                                                                      // �R�}���h�ł������ꍇ
		switch (LOWORD(wp)) {
			/*
				��ʃT�C�Y�̕ύX�ɉ����ă{�^���̈ʒu��ύX����
				�������Ȃ�����
			*/
		case BUTTON_ID1:                                                // �{�^���P�ł������ꍇ
			OpenUrl(0);
			DestroyWindow(hwnd);
			break;
		case BUTTON_ID2:                                                                  // �{�^���Q�ł������ꍇ
			DestroyWindow(hwnd);                                                          // �V�X�e�����~
			break;
		case BUTTON_IDA:                                                                  // �{�^��A�ł������ꍇ
			OpenUrl(1);
			DestroyWindow(hwnd);                                                          // �V�X�e�����~
			break;
		case BUTTON_IDB:                                                                  // �{�^���ł������ꍇ
			OpenUrl(2);
			DestroyWindow(hwnd);                                                          // �V�X�e�����~
			break;
		case BUTTON_ID:
			DestroyWindow(Button_1);
			DestroyWindow(Button_2);
			DestroyWindow(Button_A);
			DestroyWindow(Button_B);
			DestroyWindow(Button);
			hdc = GetDC(hwnd);
			TextOut(hdc, 10, 10, _TEXT("aaa"), 3);
			NewButton = CreateWindow(
				TEXT("BUTTON"),
				TEXT("�g�b�v�y�[�W"),
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
				width,
				300, // ��̍���(Y���W�͑O�̍��W��+60)
				400,
				50,
				hwnd,
				(HMENU)BUTTON_ID1,
				((LPCREATESTRUCT)(lp))->hInstance,
				NULL
			);
			UpdateWindow(NewButton);
			ShowWindow(NewButton, SW_SHOW);
			break;
		}
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

int OpenUrl(int i) {
	HINSTANCE hInst;
	if (i == 0) {
		hInst = ShellExecute(NULL, TEXT("open"), TEXT("http://192.168.51.210:8080/"), NULL, NULL, SW_SHOWNORMAL);
	}
	else if (i == 1) {
		hInst = ShellExecute(NULL, TEXT("open"), TEXT("http://192.168.51.210:8080/2syu-denki/"), NULL, NULL, SW_SHOWNORMAL);
	}
	else {
		hInst = ShellExecute(NULL, TEXT("open"), TEXT("https://google.com"), NULL, NULL, SW_SHOWNORMAL);
	}

	if (hInst < (HINSTANCE)32) {    // 32�����͋N���Ɏ��s
		return 0;
	}
	return 0;
}

int createButtons(HWND hwnd, WPARAM wp, LPARAM lp, int width) {
	RECT rect;
	if (GetWindowRect(hwnd, &rect))
	{
		width = rect.right - rect.left;
	}
	width = (width / 2) - 200;
	Button_1 = CreateWindow(
		TEXT("BUTTON"),
		TEXT("�g�b�v�y�[�W"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		width,
		300, // ��̍���(Y���W�͑O�̍��W��+60)
		400,
		50,
		hwnd,
		(HMENU)BUTTON_ID1,
		((LPCREATESTRUCT)(lp))->hInstance,
		NULL
	);

	Button_A = CreateWindow(
		TEXT("BUTTON"),
		TEXT("����d�C�H���m"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		width,
		360, // ��̍���(Y���W�͑O�̍��W��+60)
		195,
		50,
		hwnd,
		(HMENU)BUTTON_IDA,
		((LPCREATESTRUCT)(lp))->hInstance,
		NULL
	);

	Button_B = CreateWindow(
		TEXT("BUTTON"),
		TEXT("GOOGLE"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		width + 205,
		360, // ��̍���(Y���W�͑O�̍��W��+60)
		195,
		50,
		hwnd,
		(HMENU)BUTTON_IDB,
		((LPCREATESTRUCT)(lp))->hInstance,
		NULL
	);

	Button_2 = CreateWindow(
		TEXT("BUTTON"),
		TEXT("CLOSE"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		width,
		420,
		400,
		50,
		hwnd,
		(HMENU)BUTTON_ID2,
		((LPCREATESTRUCT)(lp))->hInstance,
		NULL
	);

	Button = CreateWindow(
		TEXT("BUTTON"),
		TEXT("TEST"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		width,
		480,
		400,
		50,
		hwnd,
		(HMENU)BUTTON_ID,
		((LPCREATESTRUCT)(lp))->hInstance,
		NULL
	);
	return 0;
}

/* �A�N�e�B�u�E�B���h�E��\������ */
void DoGetActiveWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
	HWND hWnd, hDeskWnd;
	WNDCLASS winc;
	MSG msg;

	hDeskWnd = GetDesktopWindow();                              // PC�̉�ʃT�C�Y�擾
	GetWindowRect(hDeskWnd, &recDisplay);                       // ��ʂɊւ���f�[�^�擾

	winc.style = CS_HREDRAW | CS_VREDRAW;                       // ���낢��...
	winc.lpfnWndProc = WindowProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, NULL);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = TEXT("MainWindow");

	DWORD dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);

	if (!RegisterClass(&winc)) return 0;                        // �E�C���h�E���\���ł��Ȃ�������I��

	/* �E�C���h�E�̏ڍאݒ� */
	MainHwnd = CreateWindow(
		TEXT("MainWindow"),
		TEXT("����΍�\�t�g"),
		WS_OVERLAPPED | WS_SYSMENU,
		(recDisplay.right - WINDOW_WIDTH) / 2,                 //����x���W
		(recDisplay.bottom - WINDOW_HEIGHT) / 2,               //����y���W
		WINDOW_WIDTH, //��
		WINDOW_HEIGHT, //����
		NULL, NULL,
		hInstance, NULL
	);

	/* ������ݒ� */
	HDC hdc;
	RECT rect;
	hdc = GetDC(MainHwnd);
	LPTSTR lptStr = _T("����΍��p�\�t�g");
	TextOut(hdc, 10, 10, lptStr, lstrlen(lptStr));
	ReleaseDC(MainHwnd, hdc);

	/* �E�C���h�E���őO�ʂ� */
	SetWindowPos(
		MainHwnd,
		HWND_TOPMOST,
		(recDisplay.right - WINDOW_WIDTH) / 2, //����x���W
		(recDisplay.bottom - WINDOW_HEIGHT) / 2, //����y���W
		WINDOW_WIDTH, //��
		WINDOW_HEIGHT, //����
		NULL
	);

	UpdateWindow(MainHwnd);
	ShowWindow(MainHwnd, SW_SHOW);

	if (MainHwnd == NULL) return 0;

	while (GetMessage(&msg, NULL, 0, 0)) DispatchMessage(&msg);
	return msg.wParam;
}