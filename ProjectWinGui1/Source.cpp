#include "windows.h"
HWND hwnd1;
HWND hwnd2;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	MSG msg ;
	WNDCLASS wc = {0};
	wc.lpszClassName = TEXT( "Buttons" );
	wc.hInstance = hInstance ;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc ;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
	CreateWindow( wc.lpszClassName, TEXT("Buttons"),WS_OVERLAPPEDWINDOW | WS_VISIBLE,50, 50, 800, 800, 0, 0, hInstance, 0);
	while( GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);DispatchMessage(&msg);
	}
	return(int) msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{ 
	switch (msg) 
	{ 
		case WM_CREATE: 
		{
			hwnd1 = CreateWindow(TEXT("button"), TEXT("Beep"), WS_VISIBLE | WS_CHILD, 20, 50, 80, 25, hwnd, (HMENU)1, NULL, NULL);
			hwnd2 = CreateWindow(TEXT("button"), TEXT("Quit"), WS_VISIBLE | WS_CHILD, 120, 50, 80, 25, hwnd, (HMENU)2, NULL, NULL);
		break; 
		}
		case WM_COMMAND: 
		{
			if (lParam == (LPARAM)hwnd1)
			{ 
				Beep(40, 50); 
				MessageBox(NULL, (LPCWSTR)L"alo",(LPCWSTR)L"A",
				MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
			}
			if (LOWORD(wParam) == 2) 
			{ 
				PostQuitMessage(0); 
			}
		break; 
		}
		case WM_DESTROY: 
		{
			PostQuitMessage(0);
		break; } 
	}
	return DefWindowProc(hwnd, msg, wParam, lParam); 
}