#include "_Game.h"

_Game::_Game(char pSize, short pLeft, short pTop, _Common& console) : _x(pLeft), _y(pTop), console(console)
{
	_b = new _Board(pSize, pLeft, pTop, console);
	_loop = _turn = true;
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
		case 72:
			return _command = 2;
		case 75:
			return _command = 3;
		case 77:
			return _command = 4;
		case 80:
			return _command = 5;
		default:
			return _command = 0;
		}
	}
	else
	{
		if (c == 27)
			return _command = 1;
		else if (c == 87 || c == 119)
			return _command = 2;
		else if (c == 65 || c == 97)
			return _command = 3;
		else if (c == 68 || c == 100)
			return _command = 4;
		else if (c == 83 || c == 115)
			return _command = 5;
		else if (c == 13)
			return _command = 6;
		else
			return _command = 0;
	}
}

char _Game::askContinue()
{
	console.gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	return getCommand();
}

void _Game::startGame()
{
	console.clearConsole();
	_b->resetData(); // Setting the original data
	_b->drawBoard(); // Draw boad
	_x = _b->getXAt(6, 6);
	_y = _b->getYAt(6, 6);
	console.gotoXY(_x, _y);
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
			processCheckBoard();
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
	switch (_b->checkBoard(_x, _y, _turn))
	{
	case -1:
		putchar('X');
		break;
	case 1:
		putchar('O');
		break;
	case 0:
		return false; // Tick the cell marked
	}
	return true;
}

int _Game::processFinish()
{
	console.gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard();
	switch (pWhoWin)
	{
	case -1:
		printf("The player %d won and the player %d lost\n", true, false);
		break;
	case 1:
		printf("The player %d won and the player %d lost\n", false, true);
		break;
	case 0:
		printf("The player %d draw with the player %d\n", false, true);
		break;
	case 2:
		_turn = !_turn; // change turn if nothing happen
	}
	console.gotoXY(_x, _y);// Return the current position of cursor
	return pWhoWin;
}

void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_x += 4;
		console.gotoXY(_x, _y);
	}
}

void _Game::moveLeft()
{
	if (_x > _b->getXAt(0, 0))
	{
		_x -= 4;
		console.gotoXY(_x, _y);
	}
}

void _Game::moveDown()
{
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_y += 2;
		console.gotoXY(_x, _y);
	}
}

void _Game::moveUp()
{
	if (_y > _b->getYAt(0, 0))
	{
		_y -= 2;
		console.gotoXY(_x, _y);
	}
}

