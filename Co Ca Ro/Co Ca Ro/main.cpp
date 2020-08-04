#include <iostream>
#include "_Common.h"
#include "_Game.h"
//#include "NhapNhay.cpp"
//#include "VeMenu.cpp"

#define SIZE 14
#define LEFT 25
#define TOP 1

using namespace std;

int main()
{
	_Common::setConsoleWindow();
	//VeMenu();
	//NhapNhay();
	_Game g(SIZE, LEFT, TOP);
	g.startGame();
	Sleep(100000000);
}