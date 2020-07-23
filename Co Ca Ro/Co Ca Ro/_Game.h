#pragma once
#include <stdio.h>
#include <conio.h>
#include "_Board.h"

class _Game
{
private:
	_Board* _b;// a board game
	bool _turn;// turn: true for the 1
	short _x, _y; // current position of cursor
	int _command; // input-key from the players
	bool _loop;
	_Common& console;
public:
	_Game(char, short, short, _Common&);
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
};