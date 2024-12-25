#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <htmlhelp.h>
#include "src.h"

// for win cbs:
// 128 << idx
// (assuming idx is 0-based)

HWND hwnd;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
			// do wtf u want here
			EndPaint(hwnd, &ps);
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	time_t t;
	time(&t);
	srand((unsigned int)(GetCurrentProcessId() + (t >> 16) + t));
	const wchar_t CLASS_NAME[] = L"AngrerysZipWrieGaem";
	WNDCLASS wc = {0};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = CLASS_NAME;
	if (!RegisterClass(&wc)) {
		return 0;
	}
	hwnd = CreateWindowEx(
		0, // window styles
		CLASS_NAME, // class
		L"angrery's zip wire -  rhe game", // title
		WS_OVERLAPPEDWINDOW, // WS_TILED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, moar window styles ig
		CW_USEDEFAULT, CW_USEDEFAULT, // xy
		900, // width
		570, // height
		NULL, // parent
		NULL, // menu (later)
		hInstance, // an instance of h (100% NOT CLICKBAIT!!!!)
		NULL // useless app data
	);
	if (hwnd == NULL) {
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	SendMessage(hwnd, WM_SETICON, 0, (LPARAM)LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(APP_ICON)));
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}