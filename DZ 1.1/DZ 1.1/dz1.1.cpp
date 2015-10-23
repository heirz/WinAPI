#include <windows.h>
#include<tchar.h>

INT WINAPI WinMain(HINSTANCE hlnst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	TCHAR szTitle[] = TEXT("Резюме");
	TCHAR szFullNane[] = TEXT("Меня зовут Никита Ганькович.");
	TCHAR szAge[] = TEXT("Мне 22 года.");
	TCHAR szCity[] = TEXT("Я живу в городе Минск.");
	TCHAR szCount[] = TEXT("В заголовке данного окна указано\nколичество символов на странице.");
	UINT count = (lstrlen(szFullNane) + lstrlen(szAge) + lstrlen(szCity) + lstrlen(szCount)) / 5;
	TCHAR buffer[4];
	UINT uAgain;
	//swprintf(buffer, L"%d", count);
	wsprintf(buffer, L"%i", count);

	do
	{
		MessageBox(0, szFullNane, szTitle, MB_OK);
		MessageBox(0, szAge, szTitle, MB_OK);
		MessageBox(0, szCity, szTitle, MB_OK);
		uAgain = MessageBox(0, L"Еще раз?", L"", MB_OKCANCEL | MB_ICONQUESTION);
	} while (uAgain == IDOK);

	MessageBox(0, szCount, buffer, MB_OK | MB_ICONEXCLAMATION);

	return 0;
}