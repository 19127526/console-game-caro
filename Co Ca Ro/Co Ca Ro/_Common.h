#pragma once
#include <Windows.h>

#define	BLACK 0
#define	LIGHTGRAY 7
#define	LIGHTCYAN 11
#define	LIGHTRED 12
#define	WHITE 15

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
	void hideCursor();
	void setFontInfo();
	void clearConsole();
};