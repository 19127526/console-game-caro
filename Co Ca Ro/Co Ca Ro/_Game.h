#pragma once
#include <iostream>
#include <Random>
#include <conio.h>
#include <fstream>
#include "_Menu.h"
#include "_Board.h"
#include "_Point.h"

#define SIZE 14
#define LEFT 25
#define TOP 1
using namespace std;
class _Game
{
private:
	_Board* _b;// a board game
	string _p1Name;
	string _p2Name;
	int _countP1Win;
	int _countP2Win;
	bool _continue;
	bool _turn;// turn: true for the 1
	int _x, _y; // current position of cursor
	bool _changeTurn;
	bool _showCursor;
	int _mode; //0 for PvP, 1 for PvC(easy), 2 for PvC(hard)
public:
	_Game(int);
	~_Game();
	void startGame(); // Function to start the game
	int processFinish();
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void printTurnChar();
	void drawProfile();
	void setUpGame(string = "");
	void moveToDirection(int, int);
	void printWinPos();
	void P1(); // Print WIN P1
	void P2(); // Print WIN P2
	void DRAW(); // Print WIN DRAW
	void COMPUTER(); // Print WIN COMPUTER
	void P1WIN();
	void P2WIN();
	void DRAWWIN();
	void COMPUTERWIN();
};