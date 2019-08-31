#include<windows.h>
#include<iostream>
#include<ConsoleApi3.h>
#include"resources.h"

#define IDC_TEXT1 11
#define IDC_TEXT 2
#define IDC_BUTTON 3
#define IDC_BUTTON2 4
#define IDR_MAINFRAME 1
using namespace std;

const char g_szClassName[] = "myWindowClass";

void ShowConsoleWindow()
{
	HWND handle = GetConsoleWindow();

	if (handle == NULL)
	{
		AllocConsole();
	}
	else
	{
		ShowWindow(handle, SW_SHOW);
	}
}

void HideConsoleWindow()
{
	HWND handle = GetConsoleWindow();
	ShowWindow(handle, SW_HIDE);
}

char EditClassName[] = "edit";
char EditClassName2[] = "button";
HINSTANCE hInstance = GetModuleHandle(NULL);

const int icon_size = 25;

int xxx() {
	return 9;
}

//HBITMAP hMyIcon = (HBITMAP)LoadImageW(GetModuleHandle(NULL), L"favicon.bmp", IMAGE_ICON, icon_size, icon_size, LR_LOADFROMFILE);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
	{
		char TextArray[] = "FILE :";
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc,
			// Location of the text
			10,
			40,
			// Text to print
			TextArray,
			// Size of the text, my function gets this for us
			6);
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CREATE:
		HWND hedit,hedit1;

		//hedit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "static", "H!", WS_CHILD | WS_VISIBLE , 10, 35, 20, 25, hwnd, (HMENU)IDC_TEXT1, GetModuleHandle(NULL), NULL);
		hedit = CreateWindowEx(WS_EX_CLIENTEDGE, EditClassName, "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 50, 35, 200, 25, hwnd, (HMENU)IDC_TEXT, GetModuleHandle(NULL), NULL);
		SetFocus(hedit);
		HWND hebutton,hebutton2;
		hebutton = CreateWindowEx(NULL, "Button", "OK", WS_VISIBLE | WS_CHILD | BS_BITMAP | BS_CENTER , 120, 180, 50, 50, hwnd, (HMENU)IDC_BUTTON, GetModuleHandle(NULL), NULL);
		//if(!SendMessage(hwnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1), IMAGE_BITMAP, 320, 300, LR_SHARED))){ SetDlgItemText(hwnd, IDC_TEXT, "fuckk!!"); }
		hebutton2 = CreateWindowEx(NULL, "Button", "..", WS_VISIBLE | WS_CHILD | BS_CENTER, 252, 35, 25, 25, hwnd, (HMENU)IDC_BUTTON2, GetModuleHandle(NULL), NULL);

		SendMessage(hebutton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadImage(GetModuleHandle(NULL),MAKEINTRESOURCE(IDB_BITMAP1),IMAGE_BITMAP,50, 50,LR_SHARED));
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			SetDlgItemText(hwnd, IDC_TEXT, "You pressed the button !");
			break;
		case IDC_BUTTON2:
			OPENFILENAME filedialog;
			char filename[100];
			memset(&filedialog, 0, sizeof(OPENFILENAME));
			filedialog.lStructSize = sizeof(OPENFILENAME);
			filedialog.hwndOwner = hwnd;
			filedialog.lpstrFile = filename;
			filedialog.lpstrFile[0] = '\0';
			filedialog.nMaxFile = 1000;
			filedialog.lpstrFilter = "Executable\0*.exe\0Dll executable\0*.dll\0";
			filedialog.nFilterIndex = 1;
			GetOpenFileName(&filedialog);
			SetDlgItemText(hwnd, IDC_TEXT, filename);
			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_LBUTTONDOWN:
		SetDlgItemText(hwnd, IDC_TEXT, "This is a string");

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//wc.hbrBackground = CreatePatternBrush((HBITMAP)LoadImage(GetModuleHandle(NULL), (LPCSTR)202, IMAGE_BITMAP, 300, 250, LR_SHARED));


	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"#Z3R0",
		WS_OVERLAPPEDWINDOW | BS_BITMAP,
		CW_USEDEFAULT, CW_USEDEFAULT, 320, 300,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Step 3: The Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}