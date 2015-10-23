#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Домашнее задание 2.4");

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
	hWnd = CreateWindowEx(0,szClassWindow,TEXT("Изменение размера окна и его перемещение"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInst,NULL);	
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd); 

	MessageBox(0,
		TEXT("Для изменения размера окна нажмите Enter,\nа для перемещения окна воспользуйтесь\nстрелочками"),
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
	RECT rect;
	GetWindowRect(hWnd, &rect);
	INT wndX = rect.left;
	INT wndY = rect.top;
	INT wndWidth = rect.right - rect.left;
	INT wndHeight = rect.bottom - rect.top;

	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
	{
		if (wParam == VK_RETURN)
		{
			MoveWindow(hWnd, 0, 0, 300, 300, TRUE);
		}
		if (wParam == VK_DOWN || wParam == VK_NUMPAD2)
		{
			MoveWindow(hWnd, wndX, wndY + 10, wndWidth, wndHeight, TRUE);
		}
		if (wParam == VK_UP || wParam == VK_NUMPAD8)
		{
			MoveWindow(hWnd, wndX, wndY - 10, wndWidth, wndHeight, TRUE);
		}
		if (wParam == VK_LEFT || wParam == VK_NUMPAD4)
		{
			MoveWindow(hWnd, wndX - 10, wndY, wndWidth, wndHeight, TRUE);
		}
		if (wParam == VK_RIGHT || wParam == VK_NUMPAD6)
		{
			MoveWindow(hWnd, wndX + 10, wndY, wndWidth, wndHeight, TRUE);
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}