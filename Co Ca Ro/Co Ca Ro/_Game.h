#pragma once
#include <iostream>
#include <Random>
#include <conio.h>
#include <fstream>
#include "_Menu.h"
#include "_Board.h"
#include "_Point.h"

#define SIZE 14
#define LEFT 4
#define TOP 1

using namespace std;
class _Game
{
private:
	_Board* _b;       //Bang co caro
	string _p1Name;   //Ten nguoi choi 1
	string _p2Name;   //Ten nguoi choi 2
	int _countP1Wins; //So lan nguoi choi 1 thang
	int _countP2Wins; //So lan nguoi choi 2 thang
	int _countRounds; //So van dau
	bool _finish;     //1: van co chua ket thuc, 0: van co da ket thuc 
	bool _turn;       //1: luot nguoi choi 1, 0: luot nguoi choi 2
	int _x, _y;       //vi tri x, y  tren man hinh
	bool _changeTurn; //gan co de thay doi mau sac khi thay doi luot
	bool _loop;       //1: nguoi choi choi tiep, 0: dung lai
	bool _showCursor; //gan co de phan biet vi tri da co x,o
	int _mode;        //0: che do nguoi-nguoi, 1:nguoi-may(de), 2: nguoi-may(kho)
	bool _loadSymbols;//1: load lai cac ki hieu x,o neu van game chua ket thuc
public:
	_Game();
	~_Game();
	void startGame();    //bat dau tro choi
	int processFinish(); //xu li
	void processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void printTurnSymbol();
	void printInterface();
	void setUpGame(int, string = "");
	void saveData();
	void moveToDirection(int, int);
	void printWinPos();
	void printLoadedSymbols();
	void askContinue();
	void printP1Win()  {}
	void printP2Win() {}
	void printBotWin() {}
	void printDraw() {}
};