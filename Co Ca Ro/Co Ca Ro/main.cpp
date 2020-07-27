#include <iostream>
#include "_Common.h"
#include "_Game.h"
#include "NhapNhay.cpp"
//#include <io.h>
//#include <fcntl.h>
//#include <string>

#define SIZE 14
#define LEFT 2
#define TOP 1

using namespace std;
//int main()
//{
//	_Common::setConsoleWindow();
//	_Game g(SIZE, LEFT, TOP);
//	/*g.startGame();*/
//
//	Sleep(100000);
//}

int main()
{
	_Common::setConsoleWindow();
	NhapNhay();
	_Game g(SIZE, LEFT, TOP);
	g.startGame();
}






















//_setmode(_fileno(stdin), 0x00020000);
//_setmode(_fileno(stdout), 0x00020000);
//wcout << L"Tiếng Việt có dấu" << std::endl;
//wstring test;
//getline(wcin, test);