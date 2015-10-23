#include <Windows.h>
#include <tchar.h>
#define IDI_ICON1 MAKEINTRESOURCE(101)

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Домашнее задание 2.2");

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE PrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASSEX wcl;

	wcl.cbSize = sizeof(wcl);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.lpfnWndProc = WindowProc;
	wcl.cbClsExtra = 0;
	wcl.cbWndExtra = 0;
	wcl.hInstance = hInst;
	wcl.hIcon = LoadIcon(hInst, IDI_ICON1);
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
		TEXT("Где был клик и какой кнопкой"),
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
	TCHAR str[100];
	RECT rect;

	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		GetClientRect(hWnd, &rect);
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		if ((x > rect.left + 10) && (x < rect.right - 10) &&
			(y > rect.top + 10) && (y < rect.bottom - 10))
		{

			SetWindowText(hWnd, TEXT("Щелчок произведен внутри прямоугольника"));
		}
		else if ((x < rect.left + 10) || (x > rect.right - 10) ||
			(y < rect.top + 10) || (y > rect.bottom - 10))
		{
			SetWindowText(hWnd, TEXT("Щелчок произведен снаруже прямоугольника"));
		}
		else
		{
			SetWindowText(hWnd, TEXT("Щелчок произведен на границе прямоугольника"));
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		GetWindowRect(hWnd, &rect);
		wsprintf(str, L"Размеры клиенского окна: %d x %d", rect.right - rect.left, rect.bottom - rect.top);
		SetWindowText(hWnd, str);
	}
	break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}