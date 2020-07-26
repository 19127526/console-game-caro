#include "_Common.h"

_Common::_Common()
{
	hWnd = GetConsoleWindow();
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//default_hWnd = hWnd, default_hConsoleOutput = hConsoleOutput;
}

//_Common::~_Common()
//{
//	hWnd = default_hWnd;
//	hConsoleOutput = default_hConsoleOutput;
//	setConsoleWindow();
//}

void _Common::setConsoleWindow()
{
	setFontInfo();
	movCenterAndRes();
	disableMaximize();
	setConsoleTitle();
	hideScrollBar();
	showCursor(false);
}

void _Common::gotoXY(short pX, short pY)
{
	SetConsoleCursorPosition(hConsoleOutput, COORD{ pX, pY });
}

void _Common::movCenterAndRes()
{
	RECT rectClient, rectWindow;
	GetClientRect(hWnd, &rectClient), GetWindowRect(hWnd, &rectWindow);
	int width = 1200;
	int height = 784;
	int posx = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posy = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(hWnd, posx, posy, width, height, TRUE);
}

void _Common::setConsoleColor(int background, int foreground)
{
	SetConsoleTextAttribute(hConsoleOutput, background * 16 + foreground);
}

void _Common::hideScrollBar()
{
	ShowScrollBar(hWnd, SB_BOTH, 0);
}

void _Common::setConsoleTitle()
{
	SetConsoleTitle(L"\u0043\u1EDC\u0020\u0043\u0041\u0052\u00D4");
}

void _Common::disableMaximize()
{
	SetWindowLong(hWnd, GWL_STYLE,
		GetWindowLong(hWnd, GWL_STYLE) & ~(WS_MAXIMIZEBOX));
}

void _Common::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(hConsoleOutput, &info);
}

void _Common::setFontInfo()
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(hConsoleOutput, FALSE, &info);
	//info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsoleOutput, FALSE, &info);
}

void _Common::clearConsole()
{
	system("cls");
}