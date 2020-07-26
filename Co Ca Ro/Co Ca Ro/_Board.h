#pragma once
#include <stdio.h>
#include "_Point.h"
#include "_Common.h"

class _Board
{
private:
	int _size;
	int _left, _top;
	int _countX, _countO;
	_Point** _pArr;
	_Common& console;
public:
	_Board(const char&, const short&, const short&, _Common&);
	~_Board();
	int getSize();
	int getLeft();
	int getTop();
	int getXAt(int, int);
	int getYAt(int, int);
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool, bool = 0);
	int testBoard();
};