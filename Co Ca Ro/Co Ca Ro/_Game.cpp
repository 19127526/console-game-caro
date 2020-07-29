#include "_Game.h"
#include <iostream>
using namespace std;
_Game::_Game(char pSize, short pLeft, short pTop) : _x(pLeft), _y(pTop)
{
	_b = new _Board(pSize, pLeft, pTop);
	_loop = _turn = _changeTurn = true;
	_showCursor = false;
	_command = -1;
}

_Game::~_Game()
{
	delete _b;
}

bool _Game::isContinue()
{
	return _loop;
}

int _Game::getCommand()
{
	int c = _getch();
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case 72: //up arrow
			return _command = 2;
		case 75: //left arrow
			return _command = 3;
		case 77: //right arrow
			return _command = 4;
		case 80: //down arrow
			return _command = 5;
		default: //none arrow
			return _command = 0;
		}
	}
	else
	{
		if (c == 27)                  //esc
			return _command = 1;
		else if (c == 87 || c == 119) //W, w
			return _command = 2;
		else if (c == 65 || c == 97)  //A, a
			return _command = 3;
		else if (c == 68 || c == 100) //D, d
			return _command = 4;
		else if (c == 83 || c == 115) //S, s
			return _command = 5;
		else if (c == 13)             //Enter
			return _command = 6;
		else
			return _command = 0;
	}
}

char _Game::askContinue()
{
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	return getCommand();
}

void _Game::startGame()
{
	_Common::clearConsole();
	_b->resetData(); // Setting the original data
	_b->drawBoard(); // Draw boad
	_x = _b->getXAt(5, 6);
	_y = _b->getYAt(5, 6);
	_Common::gotoXY(_x, _y);
	moveDown();
	while (isContinue())
	{
		switch (getCommand())
		{
		case 1:
			exitGame();
		case 2:
			moveUp();
			break;
		case 3:
			moveLeft();
			break;
		case 4:
			moveRight();
			break;
		case 5:
			moveDown();
			break;
		case 6:
			if (processCheckBoard())
			{

			}
		}
	}
}

void _Game::exitGame()
{
	system("cls");
	_loop = false;
}


bool _Game::processCheckBoard()
{
	int c = _b->checkBoard(_x, _y, _turn);
	if (c == -1 || c == 1)
	{
		_Common::gotoXY(_x, _y);
		if (c == -1)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
			putchar(88);
		}
		else
		{
			_Common::setConsoleColor(BRIGHT_WHITE, RED);
			putchar(79);
		}
		int result = processFinish();
		if (result == 2)
		{
			_showCursor = true;
			_Common::showCursor(_showCursor);
		}
		return true;
	}
	else
		return false; // Tick the cell marked
}

int _Game::processFinish()
{
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard(_x, _y);
	switch (pWhoWin)
	{
	case -1:
		cout << "The player 1 Win";
		break;
	case 1:
		cout<< "The player 2 Win";
		break;
	case 0:
		cout <<"2 players Draw";
		break;
	case 2:
		_turn = !_turn; // change turn if nothing happen
		_changeTurn = 1;
	}
	_Common::gotoXY(_x, _y);// Return the current position of cursor
	return pWhoWin;
}

void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_x += 4;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
}

void _Game::moveLeft()
{
	if (_x > _b->getXAt(0, 0))
	{
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_x -= 4;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
}

void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_y += 2;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
}

void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0))
	{
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_y -= 2;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
}

void _Game::printTurnChar()
{
	if (_b->isPlacedAtXY(_x,_y))
	{
		if (_showCursor == false)
		{
			_showCursor = true;
			_Common::showCursor(_showCursor);
		}
	}
	else
	{
		if (_showCursor == true)
		{
			_showCursor = false;
			_Common::showCursor(_showCursor);
		}
		if (_changeTurn == 1)
		{
			if (_turn == 1)
				_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
			else
				_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_RED);
			_changeTurn = 0;
		}
		if (_turn == 1)
			putchar(120);
		else
			putchar(111);
		_Common::gotoXY(_x, _y);
	}
}
	