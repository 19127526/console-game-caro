#pragma once
#include "_Point.h"
#include <iostream>
#include "_Common.h"
class _Board{
private:
	int _size;
	int _left, _top;
	_Point** _pArr;
public:
	_Board(int, int, int);
	~_Board();
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	void resetData();
	void drawBoard();
	int checkboard(int, int, bool);
	int testBoard();
};
