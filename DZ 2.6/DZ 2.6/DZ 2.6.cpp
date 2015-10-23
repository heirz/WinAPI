#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassWindow[] = TEXT("Домашнее задание 2.6");
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
		return 0;
	hWnd = CreateWindowEx(0,szClassWindow,TEXT("Изменение размера окна и автоматическое перемещение по периметру"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT, NULL,NULL,hInst,NULL); 		 
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); 
	MessageBox(0,
		TEXT("Для изменения размера окна и его автоматического\nдвижения нажмите Enter, а для остановки - клавишу Esc."),
		TEXT("Подсказка"), MB_OK | MB_ICONINFORMATION);
	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static INT wndX = 0;
	static INT wndY = 0;
	const INT wndWidth = 300;
	const INT wndHeight = 300;
	const INT panel = 40;
	HDC hDCScreen = GetDC(NULL);
	const int screenWidth = GetDeviceCaps(hDCScreen, HORZRES);
	const int screenHight = GetDeviceCaps(hDCScreen, VERTRES);
	
	switch (uMessage)
	{
	case WM_DESTROY: 
		PostQuitMessage(0); 
		break;
	case WM_TIMER:
		if (wndX + wndWidth <= screenWidth && wndY == 0)
		{
			MoveWindow(hWnd, wndX, wndY, wndWidth, wndHeight, TRUE);
			wndX += 10;
		}
		if (wndX + wndWidth == screenWidth && wndY + wndWidth <= screenHight - panel)
		{
			MoveWindow(hWnd, wndX, wndY, wndWidth, wndHeight, TRUE);
			wndY += 10;
		}
		if (wndY + wndWidth == screenHight - panel && wndX >= 0)
		{
			MoveWindow(hWnd, wndX, wndY, wndWidth, wndHeight, TRUE);
			wndX -= 10;
		}
		if (wndX == 0 && wndY >= 0)
		{
			MoveWindow(hWnd, wndX, wndY, wndWidth, wndHeight, TRUE);
			wndY -= 10;
		}
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			SetTimer(hWnd, 1, 10, NULL);
		}
		else if (wParam == VK_ESCAPE)
			KillTimer(hWnd, 1);
		break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}