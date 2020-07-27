#include "_Board.h"

_Board::_Board(const char& p_size, const short& pX, const short& pY, _Common& _console) :
	_size(p_size), _left(pX), _top(pY), console(_console)
{
	_pArr = new _Point * [p_size];
	for (int i = 0; i < p_size; i++)
		_pArr[i] = new _Point[p_size];
	_countX = _countO = 0;
}

_Board::~_Board()
{
	for (int i = 0; i < _size; i++)
		delete[] _pArr[i];
	delete[] _pArr;
	_pArr = nullptr;
}


int _Board::getSize()
{
	return _size;
}

int _Board::getLeft()
{
	return _left;
}

int _Board::getTop()
{
	return _top;
}

int _Board::getXAt(int i, int j)
{
	return _pArr[i][j].getX();
}

int _Board::getYAt(int i, int j)
{
	return _pArr[i][j].getY();
}

void _Board::resetData()
{
	if (_size == 0)
		return; // Firstly calling constructor before calling resetData
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			_pArr[i][j].setX(4 * j + _left + 3); // x-value of boardgame
			_pArr[i][j].setY(2 * i + _top + 1); // y-value of boardgame
			_pArr[i][j].setCheck(0);
		}
	}
}

void _Board::drawBoard()
{
	if (_pArr == NULL)
		return;

	console.setConsoleColor(WHITE, BLACK);
	console.clearConsole();
	console.setConsoleColor(BRIGHT_WHITE, BLACK);

	for (short i = 0; i < _size * 2 + 1; i++)
	{
		console.gotoXY(_left, _top + i);
		for (short k = 0; k < _size * 4 + 3; k++)
		{
			putchar(32);
		}
	}

	console.gotoXY(_left + 1, _top);
	putchar(201); //Ve duong tren
	for (short i = 1; i < _size * 4; i++)
	{
		//Sleep(10);
		if (i % 4 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);

	for (short i = 1; i < _size * 2; i++)
	{
		//Sleep(20);
		console.gotoXY(_size * 4 + _left + 1, i + _top);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(182);
	}
	console.gotoXY(_size * 4 + _left + 1, _size * 2 + _top);
	putchar(188);


	for (short i = 1; i < _size * 4; i++)
	{
		console.gotoXY(_size * 4 + _left - i + 1, _size * 2 + _top);
		//Sleep(10);
		if (i % 4 == 0)
			putchar(207);
		else
			putchar(205);
	}
	console.gotoXY(_left + 1, _size * 2 + _top);
	putchar(200);

	for (short i = 1; i < _size * 2; i++)
	{
		//Sleep(20);
		console.gotoXY(_left + 1, _size * 2 + _top - i);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(199);
	}

	for (short i = 1; i < _size * 2; i++)
	{
		for (short j = 4; j < _size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				console.gotoXY(j + _left + 1, i + _top);
				putchar(179);
			}
		}
		//Sleep(20);
	}

	for (short i = 1; i < _size * 4; i++)
	{
		for (short j = 2; j < _size * 2; j += 2)
		{
			console.gotoXY(i + _left + 1, j + _top);
			if (i % 4 == 0)
				putchar(197);
			else
				putchar(196);
		}
		//Sleep(10);
	}
}


int _Board::checkBoard(int pX, int pY, bool setPos, bool pTurn, int *getI, int *getJ)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
			{
				if (setPos == 1 && _pArr[i][j].getCheck() == 0)
				{
					*getI = i;
					*getJ = j;
					if (pTurn)
						_pArr[i][j].setCheck(-1); // If current turn is true: c = -1
					else
						_pArr[i][j].setCheck(1);// If current turn is false: c = 1
				}
				(pTurn == 1) ? _countX++ : _countO++;
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}

int _Board::testBoard(int i, int j)
{
	if (_countX + _countO == _size * _size)
		return 0; // draw
	else if (i == 0 && j == 0)
		return -1; // win 0
	else if (i == _size - 1 && j == _size - 1)
		return 1; // win  1
	return 2; // continue
}