#pragma once
#include "_Point.h"
#include "_Common.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <random>

const long atkPoint[7] = { 0, 64, 4096, 262144, 16777216, 1073741824 };
const long defPoint[7] = { 0, 8, 512, 32768, 2097152, 134217728 };

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
	int getXAt(int, int);
	int getYAt(int, int);
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	int testBoard(int, int);
	bool isPlacedAtXY(int, int);
	bool checkRow(int, int, int);
	bool checkCol(int, int, int);
	bool checkDiag1(int, int, int);
	bool checkDiag2(int, int, int);
	long scoreAtkCheckRow(int, int);
	long scoreAtkCheckCol(int, int);
	long scoreAtkCheckDiag1(int, int);
	long scoreAtkCheckDiag2(int, int);
	long scoreDefCheckRow(int, int);
	long scoreDefCheckCol(int, int);
	long scoreDefCheckDiag1(int, int);
	long scoreDefCheckDiag2(int, int);
	_Point PVC_hard();
	_Point PVC_easy();
	void loadData(ifstream&);
	void saveData() {};
	_Point* getWinPos();
};