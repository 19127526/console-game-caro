#include "_Common.h"

HWND _Common::consoleWindow = GetConsoleWindow();
HANDLE _Common::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void _Common::gotoXY(int pX, int pY)
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)pX, (short)pY });
}

void _Common::movCenterAndRes()
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 1216;
	int height = 784;
	int posx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posx, posy, width, height, TRUE);
}

void _Common::setConsoleColor(int background, int foreground)
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + foreground);
}

void _Common::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void _Common::setConsoleTitle()
{
	SetConsoleTitle(L"\u0043\u1EDC\u0020\u0043\u0041\u0052\u00D4");
}

void _Common::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void _Common::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void _Common::setFontInfo()
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
	info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
}

void _Common::clearConsole()
{
	system("cls");
}

void _Common::disableMouseInput()
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

int _Common::getConsoleInput()
{
	int c = _getch();
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case 72: //up arrow
			return 2;
		case 75: //left arrow
			return 3;
		case 77: //right arrow
			return 4;
		case 80: //down arrow
			return 5;
		default: //none arrow
			return 0;
		}
	}
	else
	{
		if (c == 27)                  //esc
			return 1;
		else if (c == 87 || c == 119) //W, w
			return 2;
		else if (c == 65 || c == 97)  //A, a
			return 3;
		else if (c == 68 || c == 100) //D, d
			return 4;
		else if (c == 83 || c == 115) //S, s
			return 5;
		else if (c == 13)             //Enter
			return 6;
		else if (c == 72 || c == 104) //H, h
			return 7;
		else
			return 0;
	}
}


void _Common::playSound(int i)
{
	static vector<const wchar_t*> soundFile{ L"moveO.wav", L"moveX.wav", L"move.wav", L"enter.wav", L"error.wav", L"placed.wav", };
	PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}