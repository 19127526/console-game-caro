#include <iostream>
#include "_Common.h"
#include "_Game.h"

#define SIZE 14
#define LEFT 2
#define TOP 1

int main()
{
	_Common console;
	console.setConsoleWindow();
	_Game g(SIZE, LEFT, TOP, console);
	g.startGame();

	Sleep(100000);
}