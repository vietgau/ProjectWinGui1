#include "windows.h"

#define Bnt 1
#define Edit 2
#define Checkbox 3
#define MAXLENG 2056
HWND hwndBnt1;
HWND hwndBnt2;
HWND hwndCheckbox;
HWND hwndEdit1;
HWND hwndEdit2;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void ReverseText(wchar_t* text);
void LowUpText(wchar_t* text);
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
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(int) msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{ 
	switch (msg) 
	{ 
		case WM_CREATE: 
		{
			hwndEdit1 = CreateWindow(TEXT("edit"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 250, 350, 30, hwnd, (HMENU)Edit, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			SetFocus(hwndEdit1);
			hwndEdit2 = CreateWindow(TEXT("edit"), 0, WS_CHILD | WS_VISIBLE | WS_BORDER, 200, 350, 350, 30, hwnd, (HMENU)Edit, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			SendMessage(hwndEdit2, EM_SETREADONLY, TRUE, NULL);
			hwndBnt1 = CreateWindow(TEXT("button"), TEXT("Revert"), WS_VISIBLE | WS_CHILD, 550, 650, 80, 25, hwnd, (HMENU)Bnt, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			hwndBnt2 = CreateWindow(TEXT("button"), TEXT("Quit"), WS_VISIBLE | WS_CHILD, 650, 650, 80, 25, hwnd, (HMENU)Bnt, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			hwndCheckbox = CreateWindow(TEXT("button"), TEXT("UP/DOWN Case"), WS_VISIBLE | WS_CHILD | BS_CHECKBOX, 270, 450, 185, 35, hwnd, (HMENU)Checkbox, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			CheckDlgButton(hwnd, Checkbox, BST_CHECKED);

		break; 
		}
		case WM_COMMAND: 
		{
			static wchar_t stringText[MAXLENG + 1];
			BOOL check = IsDlgButtonChecked(hwnd, Checkbox);
			if (lParam == (LPARAM)hwndBnt1 && !check)
			{ 
				GetWindowTextW(hwndEdit1, stringText, MAXLENG);
				ReverseText(stringText);
				SetWindowTextW(hwndEdit2, stringText);
				return 0;
			}
			else if(lParam == (LPARAM)hwndBnt1 && check)
			{
				GetWindowTextW(hwndEdit1, stringText, MAXLENG);
				LowUpText(stringText);
				ReverseText(stringText);
				SetWindowTextW(hwndEdit2, stringText);
				return 0;
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
void ReverseText(wchar_t* text)
{
	int leng, i;
	wchar_t tempChar;

	i = 0;
	while (text[i] != 0)
		i++;
	leng = i;
	for (i = 0; i < leng / 2; i++)
	{
		tempChar = text[i];
		text[i] = text[leng - 1 - i];
		text[leng - 1 - i] = tempChar;
	}
}
void LowUpText(wchar_t* text)
{
	int leng, i;
	i = 0;
	while (text[i] != 0)
		i++;
	leng = i;
	for (i = 0; i < leng; i++)
	{
		// lower
		if (text[i]>=65 && text[i] <= 90)
		{
			text[i] = text[i] + 32;
		}
		//uper
		else if (text[i] >= 97 && text[i] <= 122)
		{
			text[i] = text[i] - 32;
		}
	}
}