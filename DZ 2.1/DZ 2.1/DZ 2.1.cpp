#include <Windows.h>
#include <tchar.h>
#define IDI_ICON_ICO MAKEINTRESOURCE(101)

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Домашнее задание 1");

//HICON hIcon;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE PrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, IDI_ICON_ICO);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;

	if (!RegisterClassEx(&wcl))
		return 0;

	hWnd = CreateWindowEx(
		0,
		szClassWindow,
		TEXT("Клики мышью"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	TCHAR szStrClicks[100];
	static UINT nCountLeft = 0;
	static UINT nCountRight = 0;
	static UINT nCountMiddle = 0;
	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		++nCountLeft;
		wsprintf(szStrClicks, TEXT("Количество кликов: левой - %d, правой - %d, средней - %d"), nCountLeft, nCountRight, nCountMiddle);
		SetWindowText(hWnd, szStrClicks);
		break;
	case WM_LBUTTONDBLCLK:
		++nCountLeft;
		wsprintf(szStrClicks, TEXT("Количество кликов: левой - %d, правой - %d, средней - %d"), nCountLeft, nCountRight, nCountMiddle);
		SetWindowText(hWnd, szStrClicks);
		break;
	case WM_RBUTTONDOWN:
		++nCountRight;
		wsprintf(szStrClicks, TEXT("Количество кликов: левой - %d, правой - %d, средней - %d"), nCountLeft, nCountRight, nCountMiddle);
		SetWindowText(hWnd, szStrClicks);
		break;
	case WM_RBUTTONDBLCLK:
		++nCountRight;
		wsprintf(szStrClicks, TEXT("Количество кликов: левой - %d, правой - %d, средней - %d"), nCountLeft, nCountRight, nCountMiddle);
		SetWindowText(hWnd, szStrClicks);
		break;
	case WM_MBUTTONDOWN:
		++nCountMiddle;
		wsprintf(szStrClicks, TEXT("Количество кликов: левой - %d, правой - %d, средней - %d"), nCountLeft, nCountRight, nCountMiddle);
		SetWindowText(hWnd, szStrClicks);
		break;
	case WM_MBUTTONDBLCLK:
		++nCountMiddle;
		wsprintf(szStrClicks, TEXT("Количество кликов: левой - %d, правой - %d, средней - %d"), nCountLeft, nCountRight, nCountMiddle);
		SetWindowText(hWnd, szStrClicks);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}