#include "_Common.h"
#include "_Menu.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void setConsoleWindow()
{
	_Common::setFontInfo();
	_Common::movCenterAndRes();
	_Common::disableMaximize();
	_Common::setConsoleTitle();
	_Common::hideScrollBars();
	_Common::showCursor(false);
	//disableMouseInput();
}

int main()
{
	setConsoleWindow();
	_Menu::mainScreen();
}