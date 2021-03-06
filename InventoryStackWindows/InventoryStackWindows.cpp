// InventoryStackWindows.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "InventoryStackWindows.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Window controls
WNDPROC oldEditProc;
WNDPROC defButtonProc[2];
HWND hListBox1, hListBox2, hEditBox1;
HWND hLabel1, hLabel2;
HWND hButton1, hButton2;

// Forward declarations of functions included in this code module:
ATOM RegisterWindowClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK ButtonPushProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ButtonPopProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_INVENTORYSTACKWINDOWS, szWindowClass, MAX_LOADSTRING);
	RegisterWindowClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INVENTORYSTACKWINDOWS));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: RegisterWindowClass()
//
ATOM RegisterWindowClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INVENTORYSTACKWINDOWS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, 642, 350, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
      return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	switch (message)
	{
		case WM_CREATE:
		{
			// Listbox 1
			hListBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
				7, 35, 300, 200,
				hWnd, NULL, hInstance, NULL);

			// Listbox 2
			hListBox2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", NULL,
				WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL,
				320, 35, 300, 200,
				hWnd, NULL, hInstance, NULL);

			// Label 1
			hLabel1 = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", NULL,
				WS_CHILD | WS_VISIBLE,
				7, 7, 160, 21,
				hWnd, NULL, hInstance, NULL);
			SetWindowTextW(hLabel1, L"Queue (First-In-First-Out)");
			
			// Label 2
			hLabel2 = CreateWindowExW(WS_EX_TRANSPARENT, L"STATIC", NULL,
				WS_CHILD | WS_VISIBLE,
				327, 7, 160, 21,
				hWnd, NULL, hInstance, NULL);
			SetWindowTextW(hLabel2, L"Stack (Last-In-First-Out)");

			// Editbox
			hEditBox1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("Edit"), NULL,
				WS_CHILD | WS_VISIBLE, 65, 240, 150, 20,
				hWnd, NULL, NULL, NULL);

			// Button 1
			hButton1 = CreateWindowExW(WS_EX_APPWINDOW, L"BUTTON", NULL,
				WS_CHILD | WS_VISIBLE, 60, 265, 70, 21,
				hWnd, NULL, hInstance, NULL);
			SetWindowTextW(hButton1, L"Push Item");
			defButtonProc[0] = (WNDPROC)SetWindowLongPtr(hButton1, GWLP_WNDPROC, (LONG_PTR)ButtonPushProc);

			// Button 2
			hButton2 = CreateWindowExW(WS_EX_APPWINDOW, L"BUTTON", NULL,
				WS_CHILD | WS_VISIBLE, 150, 265, 70, 21,
				hWnd, NULL, hInstance, NULL);
			SetWindowTextW(hButton2, L"Pop Item");
			defButtonProc[1] = (WNDPROC)SetWindowLongPtr(hButton2, GWLP_WNDPROC, (LONG_PTR)ButtonPopProc);
			break;
		}

		case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;

				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
            }

			break;
        }

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK ButtonPushProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_LBUTTONUP:
		{
			WCHAR buffer[MAX_LOADSTRING];
			GetWindowText(hEditBox1, buffer, MAX_LOADSTRING);
			SendMessage(hListBox1, LB_ADDSTRING, 0, (LPARAM)buffer);
			SendMessage(hListBox2, LB_INSERTSTRING, 0, (LPARAM)buffer);
			break;
		}
	}

	return CallWindowProc(defButtonProc[0], hwnd, msg, wp, lp);
}

LRESULT CALLBACK ButtonPopProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_LBUTTONUP:
		{
			SendMessage(hListBox1, LB_DELETESTRING, 0, 0);
			SendMessage(hListBox2, LB_DELETESTRING, 0, 0);
			break;
		}
	}

	return CallWindowProc(defButtonProc[1], hwnd, msg, wp, lp);
}
