#include "Mylib.h"
#include "Snake.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
		case WM_TIMER: {
			switch (wParam) {
			case ID_TIMER1:
				timer1(hwnd);
				break;
			case ID_TIMER2:
				timer2(hwnd);
				break;
			default:
				break;
			}
			break;
		}
		case WM_KEYDOWN :
			switch (wParam) {
			case VK_UP:
				break;
			case VK_DOWN:
				break;
			case VK_LEFT:
				break;
			case VK_RIGHT:
				break;
			}
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			KillTimer(hwnd, ID_TIMER1);
			KillTimer(hwnd, ID_TIMER2);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow){
	WNDCLASSEX wc;
	HWND hwnd;
	MSG	Msg;
	//Step 1: Registering the Windows Class
	setupWindow(&wc, WndProc, background, g_szClassName, hInstance, hPrevInstance,
		lpCmdLine, nCmdShow);
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL,"Windows Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	//Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		program_title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, screen_length, screen_width,
		NULL, NULL, hInstance, NULL);
	if (hwnd == NULL) {
		MessageBox(NULL, "Windows Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	SetTimer(hwnd, ID_TIMER1, ElapseTimer1, NULL);
	SetTimer(hwnd, ID_TIMER2, ElapseTimer2, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	//Step 3: The Massage Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}