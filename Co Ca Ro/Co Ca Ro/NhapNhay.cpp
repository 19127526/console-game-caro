#include <stdio.h>
#include "_Common.h"

void callX()
{
	_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
	putchar(88);
}

void callO()
{
	_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_RED);
	putchar(79);
}

void firstLine(bool swap, int i)
{
	for (int j = 0; j < 8; j++)
	{
		_Common::gotoXY(j * 14 + 5, (i % 6) * 6);
		(j % 2 == swap) ? callX() : callO();
	}
}

void secondLine(bool swap, int i)
{
	for (int j = 0; j < 7; j++)
	{
		_Common::gotoXY(j * 14 + 12, (i % 6 + 1) * 6);
		(j % 2 == swap) ? callO() : callX();
	}
}

void NhapNhay()
{
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_Common::clearConsole();
	bool swap = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 6; j += 2)
		{
			firstLine(swap, j);
			secondLine(swap, j);
		}
		Sleep(200);
		swap = !swap;
	}
}