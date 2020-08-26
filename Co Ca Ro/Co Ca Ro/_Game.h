#pragma once
#include <iostream>
#include <Random>
#include <conio.h>
#include "_Board.h"

#define SIZE 14
#define LEFT 25
#define TOP 1

class _Game
{
private:
	_Board* _b;// a board game
	bool _turn;// turn: true for the 1
	int _x, _y; // current position of cursor
	int _command; // input-key from the players
	bool _changeTurn;
	bool _loop;
	bool _showCursor;
	int _mode; //0 for PvP, 1 for PvC(easy), 2 for PvC(hard)
public:
	_Game(int);
	~_Game();
	bool isContinue();
	char askContinue();
	void startGame(); // Function to start the game
	void exitGame(); // Function to exit the game
	int processFinish();
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void printTurnChar();
	void drawProfile();
	void P1(); // Print WIN P1
	void P2(); // Print WIN P2
	void DRAW(); // Print WIN DRAW
	void COMPUTER(); // Print WIN COMPUTER
	void P1WIN();
	void P2WIN();
	void DRAWWIN();
	void COMPUTERWIN();
	COORD getRandomMove();
	COORD getBestMove();
};