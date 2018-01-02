#include <windows.h>

#define WIN32_LEAN_AND_MEAN
#define program_title "Snakes"
#define screen_length 1080
#define screen_width 705
const char g_szClassName[] = "myWindowsClass";
#define ID_TIMER1 1
#define ID_TIMER2 2
#define background "images\\white.bmp"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setupWindow(WNDCLASSEX *wc, WNDPROC WndProc, const char *File,const char *ClassName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	const char *icon_name = "images\\ICON.ico";
	wc->cbSize = sizeof(WNDCLASSEX);
	wc->style = CS_VREDRAW | CS_HREDRAW;;
	wc->lpfnWndProc = WndProc;
	wc->cbClsExtra = 0;
	wc->cbWndExtra = 0;
	wc->hInstance = hInstance;
	wc->hIcon = LoadImage(NULL, icon_name, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	wc->hCursor = LoadCursor(NULL, IDC_ARROW);
	wc->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc->lpszMenuName = NULL;
	wc->lpszClassName = ClassName;
	wc->hIconSm = LoadImage(NULL, icon_name, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
	
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, File, IMAGE_BITMAP, screen_length, screen_width, LR_LOADFROMFILE);
	if (NULL == hbmp)  
	{
		MessageBox(NULL, "BitMap Loading Failed.", "Error", MB_ICONEXCLAMATION | MB_OK);
	}
	else
	{
		HBRUSH hbr = CreatePatternBrush(hbmp);
		if (NULL == hbr)
		{
			MessageBox(NULL, "Brush Creation Failed.", "Error", MB_ICONEXCLAMATION | MB_OK);
		}
		else
		{
			wc->hbrBackground = hbr;
		}
	}
}
int setup_checkError(WNDCLASSEX *wc) {
	if (!RegisterClassEx(wc)) {
		MessageBox(NULL, "Windows Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}
	else
	{
		return 0;
	}
}
int create_checkError(HWND hwnd) {
	if (hwnd == NULL) {
		MessageBox(NULL, "Windows Registration Failed!(create)", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}
	else
	{
		return 0;
	}
}

void drawPixel(HWND hwnd, unsigned int x, unsigned int y, char R, char G,char B) {
	HDC hdc = GetWindowDC(hwnd);
	HBRUSH NewBrush;
	HPEN NewPen;
	NewBrush = CreateSolidBrush(RGB(R, G, B));
	NewPen = CreatePen(PS_SOLID, 1, RGB(R, G, B));
	const int size = 10;
	const int refx = 10;
	const int refy = 35;
	SelectObject(hdc, NewBrush);
	SelectObject(hdc, NewPen);
	Rectangle(hdc, size*x + refx, size*y + refy , size*x + refx + size, size*y + refy + size);
	DeleteObject(NewBrush);
	DeleteObject(NewPen);
	ReleaseDC(hwnd,hdc);
}

/*
void drawBitmap(HDC hdc,char *File,int cursorX, int cursorY, int Width, int Length) {
	BITMAP          bitmap;
	HDC             hdcMem;
	HGDIOBJ         oldBitmap;
	HBITMAP hBitmap01 = (HBITMAP)LoadImage(NULL, File, IMAGE_BITMAP, Length, Width, LR_LOADFROMFILE);
	if (hBitmap01 == NULL)
		MessageBox(0, "Couldn't load the image", "Error", MB_OK);
	else {
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap01);

		GetObject(hBitmap01, sizeof(bitmap), &bitmap);
		BitBlt(hdc, cursorX, cursorY, Length, Width, hdcMem, 0, 0, SRCAND);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

	}
}
*/
/*
void moveCat(HDC hdc, char *File, int old_cursorX, int old_cursorY, int cursorX, int cursorY, int Width, int Length) {
	BITMAP          bitmap;
	HDC             hdcMem;
	HGDIOBJ         oldBitmap;
	HBITMAP hBitmap01 = (HBITMAP)LoadImage(NULL, File, IMAGE_BITMAP, Length, Width, LR_LOADFROMFILE);
	if (hBitmap01 == NULL)
		MessageBox(0, "Couldn't load the image", "Error", MB_OK);
	else {
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap01);

		
		GetObject(hBitmap01, sizeof(bitmap), &bitmap);
		BitBlt(hdc, old_cursorX, old_cursorY, Length, Width, hdcMem, 0, 0, WHITENESS);

		GetObject(hBitmap01, sizeof(bitmap), &bitmap);
		BitBlt(hdc, cursorX, cursorY, Length, Width, hdcMem, 0, 0, SRCAND);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

	}
}
*/