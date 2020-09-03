#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include "_Point.h"
#include "_Common.h"

const long atkPoint[6] = { 0, 64, 4096, 262144, 16777216, 1073741824 }; //mảng điểm tấn công
const long defPoint[6] = { 0, 8, 512, 32768, 2097152, 134217728 };      //mảng điểm phòng thủ
using namespace std;

class _Board
{
private:
	int _size;              //Kích cỡ bàn cờ
	int _left, _top;        //Tọa độ bắt đầu bàn cờ
	int _countX, _countO;   //Đếm số quân cờ mỗi người chơi
	_Point* _winPos;        //Vị trí 5 quân cờ thắng
	_Point** _pArr;         //Mảng vị trí ô cờ
public:
	_Board(int, int, int);			//Phương thức dựng
	~_Board();						//Phương thức hủy
	int getSize();					//Lấy kích cỡ
	int getLeft();					//Lấy tọa độ trái bắt đầu bàn cờ
	int getTop();					//Lấy tọa độ trên bắt đầu bàn cờ
	int getCountX();				//Lấy số quân cờ người chơi 1
	int getCountO();				//Lấy số quân cờ người chơi 2
	int getXAt(int, int);			//Lấy tọa độ x tại ô
	int getYAt(int, int);			//Lấy tọa độ y tại ô
	void resetData();				//Cài lại bàn cờ
	void drawBoard();				//Vẽ bảng cờ
	int checkBoard(int, int, bool); //Kiểm tra vị trí trên bàn cờ
	int testBoard(int, int);        //Kiểm tra thắng thua
	int getCheckAtXY(int, int);     //Lấy quân cờ ở ô
	bool checkRow(int, int, int);   //Kiểm tra 
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