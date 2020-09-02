#include "_Game.h"

_Game::_Game()
{
	_mode = -1;
	_x = LEFT, _y = TOP;
	_b = new _Board(SIZE, LEFT, TOP);
	_loop = _turn = _changeTurn = true;
	_finish = false;
	_showCursor = false;
	_p1Name = _p2Name = "";
	_countP1Wins = _countP2Wins = 0;
	_loadSymbols = false;
}

_Game::~_Game()
{
	delete _b;
	_b = nullptr;
}

void _Game::startGame()
{
	_Common::clearConsole();
	while (_loop)
	{
		bool pause = false;
		_finish = false;
		printInterface();
		_x = _b->getXAt(5, 6);
		_y = _b->getYAt(5, 6);
		_Common::gotoXY(_x, _y);
		moveDown();
		while (!_finish && !pause)
		{
			if (_mode == 0 || (_turn == 1 && _countRounds % 2 == 0) || (_turn == 0 && _countRounds%2==1))
			{
				switch (_Common::getConsoleInput())
				{
				case 0:
					_Common::playSound(4);
					break;
				case 1:
					saveData();
					_Menu::exitScreen();
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
				case 7:
					pause = 1;
					_loadSymbols = 1;
					_Menu::helpScreen();
					_showCursor = false;
					break;
				}
			}
			else
			{
				_Point p = (_mode == 1) ? _b->PVC_easy() : _b->PVC_hard();
				moveToDirection(p.getX(), p.getY());
				processCheckBoard();
			}
		}
		if (pause)
			continue;
		_countRounds++;
		askContinue();
		if (_loop)
		{
			swap(_p1Name, _p2Name);
			swap(_countP1Wins, _countP2Wins);
		}
	}
	saveData();
}

void _Game::processCheckBoard()
{
	int c = _b->checkBoard(_x, _y, _turn);
	if (c == -1 || c == 1)
	{
		_Common::playSound(3);
		_Common::gotoXY(_x, _y);
		if (c == 1)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
			putchar(88);
			_Common::gotoXY(86, 8);
			cout << _b->getCountX();
		}
		else
		{
			_Common::setConsoleColor(BRIGHT_WHITE, RED);
			putchar(79);
			_Common::gotoXY(86, 21);
			cout << _b->getCountO();
		}
		int result = processFinish();
		if (result == 2)
		{
			int color[] = { RED, BLUE }, pos[] = { 22,9 };
			_Common::setConsoleColor(BRIGHT_WHITE, color[_turn]);
			_Common::gotoXY(83, pos[_turn]);
			cout << "IN TURN!";
			_Common::gotoXY(83, pos[!_turn]);
			cout << "        ";
			_Common::gotoXY(_x, _y);
			_showCursor = true;
			_Common::showCursor(_showCursor);
		}
	}
	else
	{
		if (_mode == 0)
			_Common::playSound(5);
	}
}

int _Game::processFinish()
{
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard(_x, _y);
	switch (pWhoWin)
	{
	case -1:
		_finish = 1;
		_countP2Wins++;
		printWinPos();
		printP1Win();
		break;
	case 1:
		_finish = 1;
		_countP1Wins++;
		printWinPos();
		if (_mode == 1 || _mode == 2)
			printBotWin();
		else
			printP2Win();
		break;
	case 0:
		_finish = 1;
		printDraw();
		break;
	case 2:
		_turn = !_turn; // change turn if nothing happen
		_changeTurn = 1;
	}
	return pWhoWin;
}

void _Game::moveRight()
{
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1))
	{
		_Common::playSound(_turn);
		if (_b->getCheckAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_x += 4;
		_Common::gotoXY(_x, _y);
		printTurnSymbol();
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
		if (_b->getCheckAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_x -= 4;
		_Common::gotoXY(_x, _y);
		printTurnSymbol();
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
		if (_b->getCheckAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_y += 2;
		_Common::gotoXY(_x, _y);
		printTurnSymbol();
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
		if (_b->getCheckAtXY(_x, _y) == 0)
		{
			_Common::gotoXY(_x, _y);
			putchar(32);
		}
		_y -= 2;
		_Common::gotoXY(_x, _y);
		printTurnSymbol();
	}
	else
	{
		_Common::playSound(4);
	}
}

void _Game::printTurnSymbol()
{
	if (_b->getCheckAtXY(_x,_y))
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
			{
				_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
			}
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
	

void _Game::printInterface()
{
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_b->drawBoard();
	if (_loadSymbols)
	{
		printLoadedSymbols();
		_loadSymbols = 0;
	}
	_Menu::printRectangle(69, 1, 33, 10);
	_Menu::printRectangle(69, 14, 33, 10);
	_Common::gotoXY(82, 3);
	cout << "Player 1:";
	_Common::gotoXY(86 - _p1Name.length() / 2, 4);
	cout << _p1Name;
	_Common::gotoXY(79, 5);
	cout << "Winning scores:";
	string score1 = to_string(_countP1Wins) + "/" + to_string(_countRounds);
	_Common::gotoXY(86 - score1.find('/'), 6);
	cout << score1;
	_Common::gotoXY(84,7);
	cout << "Moves:";
	_Common::gotoXY(86, 8);
	cout << _b->getCountX();
	if (_turn)
	{
		_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
		_Common::gotoXY(83, 9);
		cout << "IN TURN!";
	}
	_Common::gotoXY(82, 16);
	cout << "Player 2:";
	_Common::gotoXY(86 - _p2Name.length() / 2, 17);
	cout << _p2Name;
	_Common::gotoXY(79, 18);
	cout << "Winning scores:";
	string score2 = to_string(_countP2Wins) + "/" + to_string(_countRounds);
	_Common::gotoXY(86 - score2.find('/'), 19);
	cout << score2;
	_Common::gotoXY(84, 20);
	cout << "Moves:";
	_Common::gotoXY(86, 21);
	cout << _b->getCountO();
	if (!_turn)
	{
		_Common::setConsoleColor(BRIGHT_WHITE, RED);
		_Common::gotoXY(83, 22);
		cout << "IN TURN!";
	}
	_Menu::printRectangle(69, 27, 14, 2);
	_Common::gotoXY(73, 28);
	cout << "H : Help";
	_Menu::printRectangle(88, 27, 14, 2);
	_Common::gotoXY(91, 28);
	cout << "Esc : Exit";
}

void _Game::moveToDirection(int x, int y)
{
	while (_x < x)
	{
		Sleep(300);
		moveRight();
	}
	while (_x > x)
	{
		Sleep(300);
		moveLeft();
	}
	while (_y < y)
	{
		Sleep(300);
		moveDown();
	}
	while (_y > y)
	{
		Sleep(300);
		moveUp();
	}
}

void _Game::setUpGame(int mode, string fileName)
{
	if (mode == 3)
	{
		string fullPath = "load\\" + fileName + ".txt";
		ifstream inFile(fullPath);
		getline(inFile, _p1Name);
		getline(inFile, _p2Name);
		inFile >> _mode;
		inFile >> _countRounds;
		inFile >> _countP1Wins;
		inFile >> _countP2Wins;
		inFile >> _finish;
		if (!_finish)
		{
			_loadSymbols = true;
			_b->loadBoard(inFile);
		}
		inFile.close();
	}
	else
	{
		_Common::clearConsole();
		_Menu::printLogo();
		_mode = mode;
		_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_BLUE);
		_Common::gotoXY(35, 18);
		cout << "Enter player 1's name:  ";
		_Common::showCursor(true);
		getline(cin, _p1Name);
		if (_mode == 0)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, LIGHT_RED);
			_Common::gotoXY(35, 21);
			cout << "Enter player 2's name:  ";
			getline(cin, _p2Name);
			_Common::showCursor(false);
		}
		else
		{
			_p2Name = "Computer";
		}
		_Common::showCursor(false);
		_b->resetData();
	}
}

void _Game::printWinPos()
{
	_Point* win = _b->getWinPos();
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	char arr[] = { 'D','M','M','T','Q' };
	int symbol = (_turn) ? 88 : 79;  //hieu ung cho nay
	for (int i = 0; i < 5; i++)
	{
		_Common::gotoXY(win[i].getX(), win[i].getY());
		putchar(arr[i]);
	}
	delete[] win;
	Sleep(3000);
}

void _Game::saveData()
{
	string path;
	if (_countRounds % 2 == 1 && (!_finish || _loop))
	{
		path = "load\\" + _p2Name + "-" + _p1Name + ".txt";
	}
	else
	{
		path = "load\\" + _p1Name + "-" + _p2Name + ".txt";
	}
	ofstream outFile(path);
	outFile << _p1Name << endl;
	outFile << _p2Name << endl;
	outFile << _mode << endl;
	outFile << _countRounds << endl;
	outFile << _countP1Wins << endl;
	outFile << _countP2Wins << endl;
	outFile << _finish << endl;
	if (!_finish)
	{
		_b->saveBoard(outFile);
	}
	outFile.close();
}

void _Game::printLoadedSymbols()
{
	for (int i = 0; i < _b->getSize(); i++)
	{
		for (int j = 0; j < _b->getSize(); j++)
		{
			_x = _b->getXAt(i, j);
			_y = _b->getYAt(i, j);
			_Common::gotoXY(_x, _y);
			int c = _b->getCheckAtXY(_x, _y);
			if (c == 1)
			{
				_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
				putchar(88);
			}
			else if(c == -1)
			{
				_Common::setConsoleColor(BRIGHT_WHITE, RED);
				putchar(79);
			}
		}
	}
	if (_b->getCountX() > _b->getCountO())
	{
		_Common::setConsoleColor(BRIGHT_WHITE, RED);
		_turn = 0;
	}
	else
	{
		_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
		_turn = 1;
	}
}

void _Game::askContinue()
{
	_Common::gotoXY(38, 21);
	cout << "Do you want to play another round?";
	string str[2] = { "Yes", "No" };
	int left[] = { 38,42,48,61,65,70 }, word[] = { 32,32,175,174 }, color[] = { BLACK, GREEN }, top = 24;
	bool choice = 1;
	auto print1 = [&]()
	{
		int i = 0;
		while (i < 2)
		{
			_Common::playSound(2);
			_Common::setConsoleColor(BRIGHT_WHITE, color[i]);
			_Common::gotoXY(left[choice * 3], top);        putchar(word[i * 2]);
			_Common::gotoXY(left[choice * 3 + 1], top);    cout << str[choice];
			_Common::gotoXY(left[choice * 3 + 2], top);    putchar(word[i * 2 + 1]);
			if (!i++)
				choice = !choice;
		}
	};
	print1();
	while (true)
	{
		int key = _Common::getConsoleInput();
		if ((key == 3 && choice == 1) || (key == 4 && choice == 0))
		{
			print1();
		}
		else if (key == 6)
		{
			if (!choice)
			{
				_b->resetData();
				_loop = 1;
				_changeTurn = 1;
			}
			else
			{
				_loop = 0;
			}
			return;
		}
		else
		{
			_Common::playSound(4);
		}
	}
}