#pragma once
#include <stdio.h>
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
public:
	_Game();
	~_Game();
	bool isContinue();
	char askContinue();
	void startGame(); // Function to start the game
	void exitGame(); // Function to exit the game
	int processFinish();
	bool processCheckBoard();
	int getCommand();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void printTurnChar();
	void drawProfile();
};