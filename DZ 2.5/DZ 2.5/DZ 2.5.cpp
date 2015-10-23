#include<Windows.h>
#include<tchar.h>
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassWindow[] = TEXT("Домашнее задание 2.5");
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
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
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcl.lpszMenuName = NULL;
	wcl.lpszClassName = szClassWindow;
	wcl.hIconSm = NULL;
	if (!RegisterClassEx(&wcl))
	{
		return 0;
	}
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Домашнее задание 2.5"),
		WS_OVERLAPPEDWINDOW, 0, 0, 100,
		100, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MessageBox(hWnd, TEXT("Откройте, пожалуйста, \"Калькулятор\""), TEXT("Работа с калькулятором"), MB_OK | MB_ICONINFORMATION);
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}
BOOL CALLBACK EnumChildProcDialogHide(HWND hWnd, LPARAM lParam)
{
	TCHAR caption[MAX_PATH] = { 0 }, className[100] = { 0 }, text[500] = { 0 };
	GetWindowText(hWnd, caption, 100);
	GetClassName(hWnd, className, 100);
	ShowWindow(hWnd, SW_HIDE);
	return TRUE;
}
BOOL CALLBACK EnumChildProcHide(HWND hWnd, LPARAM lParam)
{
	TCHAR caption[MAX_PATH] = { 0 }, className[100] = { 0 }, text[500] = { 0 };
	GetWindowText(hWnd, caption, 100);
	GetClassName(hWnd, className, 100);
	if (!lstrcmp(className, TEXT("#32770")))
	{
		{
			EnumChildProcDialogHide(hWnd, lParam);
		}
	}
	return TRUE;
}
BOOL CALLBACK EnumChildProcShow(HWND hWnd, LPARAM lParam)
{
	ShowWindow(hWnd, SW_SHOW);
	return TRUE;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (!h)
			{
				MessageBox(hWnd, TEXT("Необходимо открыть \"Калькулятор\"!"), NULL, MB_OK | MB_ICONERROR);
			}
			else
			{
				EnumChildWindows(h, EnumChildProcHide, (LPARAM)hWnd);
			}
		}
		else if (wParam == VK_ESCAPE)
		{
			HWND h = FindWindow(TEXT("CalcFrame"), TEXT("Калькулятор"));
			if (!h)
			{
				MessageBox(hWnd, TEXT("Необходимо открыть \"Калькулятор\"!"), NULL, MB_OK | MB_ICONERROR);
			}
			else
			{
				EnumChildWindows(h, EnumChildProcShow, (LPARAM)hWnd);
			}
		}
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}