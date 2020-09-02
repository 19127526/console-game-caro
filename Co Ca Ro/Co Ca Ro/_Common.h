#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>
#pragma comment(lib, "Winmm.lib")

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

using namespace std;

class _Common
{
private:
	static HWND consoleWindow;
	static HANDLE consoleOutput;
public:
	_Common() {}
	~_Common() {}
	static void gotoXY(int, int);
	static void movCenterAndRes();
	static void setConsoleColor(int, int);
	static void hideScrollBars();
	static void setConsoleTitle();
	static void disableMaximize();
	static void showCursor(bool);
	static void setFontInfo();
	static void clearConsole();
	static void disableMouseInput();
	static int getConsoleInput();
	static void playSound(int);
};