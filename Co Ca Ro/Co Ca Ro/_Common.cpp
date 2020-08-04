#include "_Common.h"

HWND _Common::consoleWindow;
HANDLE _Common::consoleOutput;

//_Common::_Common()
//{
//}

//_Common::~_Common()
//{
//}

void _Common::setConsoleWindow()
{
	consoleWindow = GetConsoleWindow();
	consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	setFontInfo();
	movCenterAndRes();
	disableMaximize();
	setConsoleTitle();
	hideScrollBars();
	showCursor(false);
}

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
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX));
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