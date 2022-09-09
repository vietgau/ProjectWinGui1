#include "windows.h"

HWND hwndBnt1;
HWND hwndBnt2;
HWND hwndCheckbox;
HWND hwndEdit1;
HWND hwndEdit2;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	MSG msg ;
	WNDCLASS wc = {0};
	wc.lpszClassName = TEXT( "Revert" );
	wc.hInstance = hInstance ;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc ;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClass(&wc);
	CreateWindow( wc.lpszClassName, TEXT("Revert"),WS_OVERLAPPEDWINDOW | WS_VISIBLE,50, 50, 800, 800, 0, 0, hInstance, 0);
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
			hwndEdit1 = CreateWindow(TEXT("edit"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 250, 350, 30, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			SetFocus(hwndEdit1);
			hwndEdit2 = CreateWindow(TEXT("edit"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 350, 350, 30, hwnd, (HMENU)2, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			SendMessage(hwndEdit2, EM_SETREADONLY, TRUE, NULL);
			hwndBnt1 = CreateWindow(TEXT("button"), TEXT("Revert"), WS_VISIBLE | WS_CHILD, 550, 650, 80, 25, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			hwndBnt2 = CreateWindow(TEXT("button"), TEXT("Quit"), WS_VISIBLE | WS_CHILD, 650, 650, 80, 25, hwnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			hwndCheckbox = CreateWindow(TEXT("button"), TEXT("UP/DOWN Case"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 270, 450, 185, 35, hwnd, (HMENU)3, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			CheckDlgButton(hwnd, 1, BST_CHECKED);
		break; 
		}
		case WM_COMMAND: 
		{
			if (lParam == (LPARAM)hwndBnt1)
			{ 
				Beep(40, 50); 
				MessageBox(NULL, (LPCWSTR)L"alo",(LPCWSTR)L"A",
				MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2);
			}
			if (lParam == (LPARAM)hwndBnt2)
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