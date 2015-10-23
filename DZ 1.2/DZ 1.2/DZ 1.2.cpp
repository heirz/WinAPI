#include <windows.h>
#include<tchar.h>

INT WINAPI WinMain(HINSTANCE hlnst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{
	TCHAR szTitle[] = TEXT("Угадай число");
	TCHAR szChooseNumber[] = TEXT("Загадайте число от 1 до 100.");
	TCHAR szRealyChoose[] = TEXT("Загадали?");
	UINT count = 0;
	UINT number = 50;
	UINT max_number = 100;
	UINT min_number = 1;
	TCHAR buffer[50];
	UINT uAgain;
	UINT yesNo;
	BOOL win = false;
	do
	{
		MessageBox(0, szChooseNumber, szTitle, MB_OK);
		yesNo = MessageBox(0, szRealyChoose, szTitle, MB_YESNO | MB_ICONQUESTION);
		if (yesNo == IDNO)
		{
			wsprintf(buffer, L"Число попыток: %i", count);
			MessageBox(0, buffer, szTitle, MB_OK | MB_ICONSTOP);
			uAgain = MessageBox(0, L"Еще раз?", L"", MB_OKCANCEL | MB_ICONQUESTION);
			continue;
		}
		while (!win)
		{
			wsprintf(buffer, L"Вы задумали это число - %i.\nДа или Нет ?", number);
			yesNo = MessageBox(0, buffer, szTitle, MB_YESNO | MB_ICONQUESTION);
			if (yesNo == IDNO)
			{
				wsprintf(buffer, L"Загаданное число больше %i.\nДа или Нет ?", number);
				yesNo = MessageBox(0, buffer, szTitle, MB_YESNO | MB_ICONQUESTION);
				if (yesNo == IDYES)
				{
					min_number = number + 1;
				}
				else
				{
					max_number = number;
				}
				number = (min_number + max_number) / 2;
				count++;
			}
			else
			{
				count++;
				wsprintf(buffer, L"Число попыток: %i", count);
				MessageBox(0, buffer, szTitle, MB_OK | MB_ICONEXCLAMATION);
				win = true;
			}
		}
		uAgain = MessageBox(0, L"Еще раз?", L"", MB_OKCANCEL | MB_ICONQUESTION);
		win = false;
		number = 50;
		max_number = 100;
		min_number = 1;
		count = 0;
	} while (uAgain == IDOK);

	return 0;
}