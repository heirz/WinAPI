#include <Windows.h>
#include <tchar.h>
#include "resource.h"
#include <ctime>
#include <vector>

using std::vector;

HWND hStart, hListNums, hResult, hSumm, hMulti, hArithmetics;
vector<int> myNums;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstans, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	srand(time(NULL));
	return DialogBox(hInstans, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT nDigits;
	TCHAR str[15];

	switch (message)
	{
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return TRUE;
	case WM_INITDIALOG:
		hStart = GetDlgItem(hWnd, IDC_START);
		hListNums = GetDlgItem(hWnd, IDC_NUMS);
		hResult = GetDlgItem(hWnd, IDC_RESULT);
		hSumm = GetDlgItem(hWnd, IDC_SUMM);
		hMulti = GetDlgItem(hWnd, IDC_MULTI);
		hArithmetics = GetDlgItem(hWnd, IDC_ARITH);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_START)
		{

			myNums.clear();
			SendMessage(hListNums, LB_RESETCONTENT, 0, 0);

			unsigned int i = 0;
			UINT nCountNums = rand() % 11 + 10;

			while (i < nCountNums)
			{
				nDigits = rand() % 21 - 10;
				if (!nDigits)
				{
					continue;
				}
				myNums.push_back(nDigits);
				swprintf(str, TEXT("%d"), nDigits);
				SendMessage(hListNums, LB_ADDSTRING, 0, LPARAM(str));
				++i;
			}
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_SUMM)
		{
			INT nResult = 0;
			for (auto a : myNums)
			{
				nResult += a;
			}
			swprintf(str, L"%d", nResult);
			SetWindowText(hResult, str);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_MULTI)
		{
			INT nResult = 1;
			for (auto a : myNums)
			{
				nResult *= a;
			}
			swprintf(str, L"%d", nResult);
			SetWindowText(hResult, str);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_ARITH)
		{
			FLOAT nResult = 0;
			for (auto a : myNums)
			{
				nResult += a;
			}
			nResult /= myNums.size();
			swprintf(str, L"%.3f", nResult);
			SetWindowText(hResult, str);
			return TRUE;
		}
	}
	return FALSE;
}