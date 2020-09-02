#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include "_Point.h"
#include "_Common.h"

const long atkPoint[6] = { 0, 64, 4096, 262144, 16777216, 1073741824 };
const long defPoint[6] = { 0, 8, 512, 32768, 2097152, 134217728 };

using namespace std;
class _Board
{
private:
	int _size;
	int _left, _top;
	int _countX, _countO;
	_Point* _winPos;
	_Point** _pArr;
public:
	_Board(int, int, int);
	~_Board();
	int getSize();
	int getLeft();
	int getTop();
	int getCountX();
	int getCountO();
	int getXAt(int, int);
	int getYAt(int, int);
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	int testBoard(int, int);
	int getCheckAtXY(int, int);
	bool checkRow(int, int, int);
	bool checkCol(int, int, int);
	bool checkDiag1(int, int, int);
	bool checkDiag2(int, int, int);
	long scoreAtkRow(int, int);
	long scoreAtkCol(int, int);
	long scoreAtkDiag1(int, int);
	long scoreAtkDiag2(int, int);
	long scoreDefRow(int, int);
	long scoreDefCol(int, int);
	long scoreDefDiag1(int, int);
	long scoreDefDiag2(int, int);
	_Point PVC_hard();
	_Point PVC_easy();
	void loadBoard(ifstream&);
	void saveBoard(ofstream&);
	_Point* getWinPos();
};