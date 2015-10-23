#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("Домашнее задание 2.3");

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
	hWnd = CreateWindowEx(0, szClassWindow, TEXT("Изменение названия и перемещение Калькулятора"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MessageBox(hWnd, TEXT("Откройте, пожалуйста, \"Калькулятор\""), TEXT("Переименование калькультора"), MB_OK | MB_ICONINFORMATION);

	while (GetMessage(&lpMsg, NULL, 0, 0))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return lpMsg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	INT calcX, calcY, calcWidth, calcHeight;
	HWND hCalc;
	static TCHAR caption[MAX_PATH] = { 0 };

	switch (uMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0); 
		break;
	case WM_LBUTTONDOWN:
	{
		if (lstrcmp(caption, L"\0") == 0)
		{
			lstrcpy(caption, L"Калькулятор");
		}
		hCalc = FindWindow(TEXT("CalcFrame"), caption); 		
		if (!hCalc)
		{
			MessageBox(hWnd, TEXT("Необходимо открыть \"Калькулятор\""), TEXT("Ошибка!!!"), MB_OK | MB_ICONSTOP);
		}
		else
		{
			SetWindowText(hCalc, TEXT("Это Рэпчик Детка"));
			MessageBox(hWnd, TEXT("Нажмите среднюю кнопку мыши, чтобы вернуть старое название."), TEXT("Сообщение"), MB_OK | MB_ICONINFORMATION);
			BringWindowToTop(hCalc);
			GetWindowText(hCalc, caption, 100);
		}
	}
	break;
	case WM_MBUTTONDOWN:
	{
		if (lstrcmp(caption, L"\0") == 0)
		{
			lstrcpy(caption, L"Калькулятор");
		}
		hCalc = FindWindow(TEXT("CalcFrame"), caption);
		if (!hCalc)
		{
			MessageBox(hWnd, TEXT("Необходимо открыть \"Калькулятор\""), TEXT("Ошибка!!!"), MB_OK | MB_ICONSTOP);
		}
		else
		{
			SetWindowText(hCalc, TEXT("Калькулятор"));
			BringWindowToTop(hCalc);
			GetWindowText(hCalc, caption, 100);
		}
	}
	break;
	case WM_RBUTTONDOWN:
	{
		if (lstrcmp(caption, L"\0") == 0)
		{
			lstrcpy(caption, L"Калькулятор");
		}
		hCalc = FindWindow(TEXT("CalcFrame"), caption);
		if (!hCalc)
		{
			MessageBox(hWnd, TEXT("Необходимо открыть \"Калькулятор\""), TEXT("Ошибка!!!"), MB_OK | MB_ICONSTOP);
		}
		else
		{
			RECT calcRect;
			GetWindowRect(hCalc, &calcRect);
			calcX = calcRect.left + 30;
			calcY = calcRect.top;
			calcWidth = calcRect.right - calcRect.left;
			calcHeight = calcRect.bottom - calcRect.top;
			MoveWindow(hCalc, calcX, calcY, calcWidth, calcHeight, TRUE);
			BringWindowToTop(hCalc);
			GetWindowText(hCalc, caption, 100);
		}
	}
	break;
	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
