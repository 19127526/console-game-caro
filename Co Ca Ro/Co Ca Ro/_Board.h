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
	int checkBoard(int, int, bool);
	int testBoard(int, int);
	bool isPlacedAtXY(int, int);
	bool checkHang(int, int, int);
	bool checkCot(int, int, int);
	bool checkCheo1(int, int, int);
	bool checkCheo2(int, int, int);
};