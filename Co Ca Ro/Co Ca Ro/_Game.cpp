#include "_Game.h"
using namespace std;
_Game::_Game(int mode)
{
	_mode = mode;
	_x = LEFT, _y = TOP;
	_b = new _Board(SIZE, LEFT, TOP);
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

char _Game::askContinue()
{
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	return 0;//getCommand();
}

void _Game::startGame()
{
	_Common::clearConsole();
	_b->resetData();
	_b->drawBoard();
	//drawProfile();
	_x = _b->getXAt(5, 6);
	_y = _b->getYAt(5, 6);
	_Common::gotoXY(_x, _y);
	moveDown();
	while (isContinue())
	{
		if(_mode == 0 || (_turn == 1))
		{
			switch (_Common::getConsoleInput())
			{
			case 1:
				return;
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
				processCheckBoard();
				break;
			default:
				_Common::playSound(4);
			}
		}
		else
		{
			do
			{
				COORD coord = (_mode == 1) ? getRandomMove() : getBestMove();
				_x = _b->getXAt(0, 0) + coord.X * 4;
				_y = _b->getYAt(0, 0) + coord.Y * 2;
			} while (!processCheckBoard());
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
		_Common::playSound(3);
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
	{
		if (_mode == 0)
			_Common::playSound(5);
		return false;
	}
}

int _Game::processFinish()
{
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard(_x, _y);
	switch (pWhoWin)
	{
	case -1:
		printP1Win();
		break;
	case 1:
		if (_mode == 1 || _mode == 2)
			printBotWin();
		else
			printP2Win();
		break;
	case 0:
		printDraw();
		break;
	case 2:
		_turn = !_turn; // change turn if nothing happen
		_changeTurn = 1;
	}
	_Common::gotoXY(_x, _y);
	return pWhoWin;
}

void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_Common::playSound(_turn);
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_x += 4;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
	else
	{
		_Common::playSound(4);
	}
}

void _Game::moveLeft()
{
	if (_x > _b->getXAt(0, 0))
	{
		_Common::playSound(_turn);
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_x -= 4;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
	else
	{
		_Common::playSound(4);
	}
}

void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_Common::playSound(_turn);
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_y += 2;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
	else
	{
		_Common::playSound(4);
	}
}

void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0))
	{
		_Common::playSound(_turn);
		if (_b->isPlacedAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_y -= 2;
		_Common::gotoXY(_x, _y);
		printTurnChar();
	}
	else
	{
		_Common::playSound(4);
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
	

void _Game::drawProfile()
{
	for (int i = 0; i < 25; i++)
	{
		_Common::gotoXY(3, 3 + i);
		for (int k = 0; k < 19; k++)
		{
			putchar(32);
		}
		_Common::gotoXY(87, 3 + i);
		for (int k = 0; k < 19; k++)
		{
			putchar(32);
		}
	}
}

COORD _Game::getRandomMove()
{
	static random_device rd;
	static mt19937 mt(rd());
	static uniform_int_distribution<short> dist(0, _b->getSize() - 1);
	return COORD{ dist(mt), dist(mt) };
}

COORD _Game::getBestMove()
{
	short i = 13; short j = 13;
	return COORD{ i,j };
}
