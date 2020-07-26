#pragma once
#include <Windows.h>

#define	BLACK 0
#define	BLUE 1
#define	RED 4
#define WHITE 7
#define LIGHT_BLUE 9
#define	LIGHT_RED 12
#define	BRIGHT_WHITE 15

class _Common
{
private:
	HWND hWnd; //,default_hWnd;
	HANDLE hConsoleOutput; //,default_hConsoleOutput;
public:
	_Common();
	//~_Common();
	void setConsoleWindow();
	void gotoXY(short, short);
	void movCenterAndRes();
	void setConsoleColor(int, int);
	void hideScrollBar();
	void setConsoleTitle();
	void disableMaximize();
	void showCursor(bool);
	void setFontInfo();
	void clearConsole();
};