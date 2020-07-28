#include <iostream>
#include "_Common.h"
#include <io.h>
#include <fcntl.h>
using namespace std;

#define ROW 5
#define WIDTH 10
#define TOP_ 1
#define X_CENTER 54

inline void VeMenu()
{
	_Common::setConsoleColor(WHITE, BLACK);
	_Common::clearConsole();
	_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	int left = X_CENTER - WIDTH / 2;
	for (int i = 0; i < ROW * 2 + 1; i++)
	{
		_Common::gotoXY(left , TOP_ + i);
		for (int j = 0; j < WIDTH + 1; j++)
		{
			putchar(32);
		}
	}

	_Common::gotoXY(left + 1, TOP_);
	//putchar(201);
	putchar(218);
	for (int i = 1; i < WIDTH - 2; i++)
	{
		//putchar(205);
		putchar(196);
	}
	putchar(191);
	//putchar(187);


	for (int i = 1; i < ROW * 2; i++)
	{
		_Common::gotoXY(left + WIDTH - 1, TOP_ + i);
		if (i % 2 != 0)
			putchar(179);
		//putchar(186);
		else
			putchar(180);
			//putchar(182);
	}
	_Common::gotoXY(left + WIDTH - 1, TOP_ + ROW * 2);
	putchar(217);
	//putchar(188);

	for (int i = 1; i < WIDTH - 2; i++)
	{
		_Common::gotoXY(left + WIDTH - i - 1, TOP_ + ROW * 2);
		putchar(196);
		//putchar(205);
	}
	_Common::gotoXY(left + 1, TOP_ + ROW * 2);
	putchar(192);
	//putchar(200);

	for (int i = 1; i < ROW * 2; i++)
	{
		_Common::gotoXY(left + 1, TOP_ + ROW * 2 - i);
		if (i % 2 != 0)
			putchar(179);
			//putchar(186);
		else
			putchar(195);
			//putchar(199);
	}

	for (int i = 1; i < WIDTH - 2; i++)
	{
		for (int j = 2; j < ROW * 2; j += 2)
		{
			_Common::gotoXY(i + left + 1, j + TOP_);
			putchar(196);
		}
	}
	_setmode(_fileno(stdin), 0x00020000);
	_setmode(_fileno(stdout), 0x00020000);
	_Common::gotoXY(left + 3, TOP_ + 1);
	wcout << L"Chơi";
	_Common::gotoXY(left + 3, TOP_ + 3);
	wcout << L"Thoát";
}