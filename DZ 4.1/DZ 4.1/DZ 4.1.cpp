#include <Windows.h>
#include <tchar.h>
#include <cstdlib>
#include "resource.h"

HINSTANCE hInst;
HWND hBottonResult, hLeftOperand, hRightOperand, hOperation, hStaticResult;
const int size = 10;
TCHAR data[size];
FLOAT nFirstValue, nSecondValue, nResult;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	case WM_INITDIALOG:
		hStaticResult = GetDlgItem(hWnd, IDC_STATIC1);
		hBottonResult = GetDlgItem(hWnd, IDC_BUTTON1);
		hLeftOperand = GetDlgItem(hWnd, IDC_EDIT1);
		hRightOperand = GetDlgItem(hWnd, IDC_EDIT3);
		hOperation = GetDlgItem(hWnd, IDC_EDIT2);
		return TRUE;
	case WM_COMMAND:
		if (wParam == IDC_BUTTON1)
		{
			if (!GetWindowText(hLeftOperand, data, size))
			{
				SetWindowText(hStaticResult, TEXT("Ошибка! Отсутствует первый операнд"));
				return TRUE;
			}
			nFirstValue = _tstof(data);
			if (!GetWindowText(hRightOperand, data, size))
			{
				SetWindowText(hStaticResult, TEXT("Ошибка! Отсутствует второй операнд"));
				return TRUE;
			}
			nSecondValue = _tstof(data);

			GetWindowText(hOperation, data, size);
			if (lstrcmp(data, TEXT("+")) &&
				lstrcmp(data, TEXT("-")) &&
				lstrcmp(data, TEXT("*")) &&
				lstrcmp(data, TEXT("/")))
			{
				SetWindowText(hStaticResult, TEXT("Ошибка! Неверный оператор"));
				return TRUE;
			}
			if (!lstrcmp(data, TEXT("+")))
			{
				nResult = nFirstValue + nSecondValue;
			}
			if (!lstrcmp(data, TEXT("-")))
			{
				nResult = nFirstValue - nSecondValue;
			}
			if (!lstrcmp(data, TEXT("*")))
			{
				nResult = nFirstValue * nSecondValue;
			}
			if (!lstrcmp(data, TEXT("/")) && !nSecondValue)
			{
				SetWindowText(hStaticResult, TEXT("Ошибка! Нельзя делить на ноль!"));
				return TRUE;
			}
			else if (!lstrcmp(data, TEXT("/")))
			{
				nResult = nFirstValue / nSecondValue;
			}
			swprintf(data, L"%.3f", nResult);
			SetWindowText(hStaticResult, data);
		}
		return TRUE;
	}
	return FALSE;
}