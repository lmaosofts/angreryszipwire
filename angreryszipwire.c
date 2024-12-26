#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <htmlhelp.h>
#include <math.h>
#include "src.h"

// for win cbs:
// 128 << idx
// (assuming idx is 0-based)

// (?<=^#define )(?P<id>[^ ]+) (?P<val>.*)$

HWND hwnd;
WNDCLASS wc = {};
int fps;
DWORD lastT;

HBRUSH hBrshFromHex(LPCWSTR hex) {
	int len = WideCharToMultiByte(CP_UTF8, 0, hex, -1, 0, 0, 0, 0);
	if(len==0)return NULL;
	char* shHex = (char*)malloc(len);
	WideCharToMultiByte(CP_UTF8, 0, hex, -1, shHex, len, 0, 0);
	unsigned int r, g, b;
	if (sscanf(shHex+1,"%02x%02x%02x",&r,&g,&b)!=3)return(free(shHex),NULL);
	free(shHex);
	return CreateSolidBrush(RGB(r, g, b));
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &ps.rcPaint, wc.hbrBackground);
			SetBkMode(hdc, TRANSPARENT);
			wchar_t fpsCount[256];
			swprintf(fpsCount, 256, L"FPS:\xa0%d", fps);
			TextOutW(hdc, 0, 0, fpsCount, wcslen(fpsCount));
			EndPaint(hwnd, &ps);
			return 0;
		case WM_TIMER:
			DWORD now = GetTickCount();
			fps = (int)floor(1000.0 / (now - lastT));
			lastT = now;
			InvalidateRect(hwnd, NULL, 1);
			return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
	time_t t;
	time(&t);
	srand((unsigned int)(GetCurrentProcessId() + (t >> 16) + t));
	const wchar_t CLASS_NAME[] = L"AngrerysZipWrieGaem";
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = hBrshFromHex(L"#006100");
	wc.lpszClassName = CLASS_NAME;
	if (!RegisterClass(&wc)) {
		return 0;
	}
	hwnd = CreateWindowEx(
		0, // window styles
		CLASS_NAME, // class
		L"angrery's zip wire -  rhe game", // title
		WS_OVERLAPPEDWINDOW, // moar window styles ig
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
	lastT = GetTickCount();
	SetTimer(hwnd, 1, 1000 / 120, 0);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}