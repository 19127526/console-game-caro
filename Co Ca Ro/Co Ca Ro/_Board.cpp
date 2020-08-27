﻿#include "_Board.h"

_Board::_Board(int p_size, int pX, int pY) :
	_size(p_size), _left(pX), _top(pY)
{
	_pArr = new _Point * [p_size];
	for (int i = 0; i < p_size; i++)
		_pArr[i] = new _Point[p_size];
	_countX = _countO = 0;
	_winPos = nullptr;
}

_Board::~_Board()
{
	for (int i = 0; i < _size; i++)
		delete[] _pArr[i];
	delete[] _pArr,
		_pArr = nullptr;
	delete[] _winPos;
	_winPos = nullptr;
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

	_Common::setConsoleColor(WHITE, BLACK);
	_Common::clearConsole();
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	//ve khung trang
	for (int i = 0; i < _size * 2 + 1; i++)
	{
		_Common::gotoXY(_left, _top + i);
		for (int col = 0; col < _size * 4 + 3; col++)
		{
			putchar(32);
		}
	}

	//Ve duong up
	_Common::gotoXY(_left + 1, _top);
	putchar(201);
	for (int i = 1; i < _size * 4; i++)
	{
		//Sleep(10);
		if (i % 4 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);


	//Ve duong ben phai
	for (int i = 1; i < _size * 2; i++)
	{
		//Sleep(20);
		_Common::gotoXY(_size * 4 + _left + 1, i + _top);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(182);
	}
	_Common::gotoXY(_size * 4 + _left + 1, _size * 2 + _top);
	putchar(188);


	//Ve duong down
	for (int i = 1; i < _size * 4; i++)
	{
		_Common::gotoXY(_size * 4 + _left - i + 1, _size * 2 + _top);
		//Sleep(10);
		if (i % 4 == 0)
			putchar(207);
		else
			putchar(205);
	}
	_Common::gotoXY(_left + 1, _size * 2 + _top);
	putchar(200);

	//Ve duong ben trai
	for (int i = 1; i < _size * 2; i++)
	{
		//Sleep(20);
		_Common::gotoXY(_left + 1, _size * 2 + _top - i);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(199);
	}

	//Ve cac duong doc
	for (int i = 1; i < _size * 2; i++)
	{
		for (int j = 4; j < _size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				_Common::gotoXY(j + _left + 1, i + _top);
				putchar(179);
			}
		}
		//	Sleep(20);
	}

	//Ve cac duong ngang
	for (int i = 1; i < _size * 4; i++)
	{
		for (int j = 2; j < _size * 2; j += 2)
		{
			_Common::gotoXY(i + _left + 1, j + _top);
			if (i % 4 == 0)
				putchar(197);
			else
				putchar(196);
		}
		//Sleep(10);
	}
}


int _Board::checkBoard(int pX, int pY, bool pTurn)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
			{
				if (_pArr[i][j].getCheck() == 0)
				{
					if (pTurn)
					{
						_countX++;
						_pArr[i][j].setCheck(-1);
					}
					else
					{
						_countO++;
						_pArr[i][j].setCheck(1);
					}
					return _pArr[i][j].getCheck();
				}
				else
					return 0;
			}
		}
	}
	throw "Problem with cursor";
}

int _Board::testBoard(int pX, int pY) //i,j la row,col cua bang
{
	if (_countX + _countO == _size * _size)
		return 0; // draw
	int i, j;
	[&] {
		for (i = 0; i < _size; i++)
		{
			for (j = 0; j < _size; j++)
			{
				if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
					return;
			}
		}
	}();
	int turn = _pArr[i][j].getCheck();
	if (turn == 1)
	{
		if (checkRow(i, j, turn) || checkCol(i, j, turn) || checkDiag1(i, j, turn) || checkDiag2(i, j, turn))
			return 1;
	}
	else
	{
		if (checkRow(i, j, turn) || checkCol(i, j, turn) || checkDiag1(i, j, turn) || checkDiag2(i, j, turn))
			return -1;
	}
	return 2; // continue
}

bool _Board::isPlacedAtXY(int pX, int pY)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
				return _pArr[i][j].getCheck() != 0;
		}
	}
	throw "Problem with cursor position";
}

bool _Board::checkRow(int i, int j, int turn)
{
	int up = 0, down = 0;
	int count = 0, col = i;
	// kiểm tra hàng
	while (col <= _size - 1 && _pArr[col][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (col == _size - 1)
		{
			count++;
			down = col;
			break;
		}
		else
		{
			count++;
			col++;
			down = col;
		}
	}
	count--;
	col = i;
	while (col >= 0 && _pArr[col][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (col == 0)
		{
			count++;
			up = col;
			break;
		}
		else
		{
			count++;
			col--;
			up = col;
		}
	}
	if (count > 4)
	{
		if ((down == _size - 1 && _pArr[down][j].getCheck() == turn))
		{
			_winPos = new _Point[5]{ {down,j},{down - 1,j },{down - 2,j },{down - 3,j },{down - 4,j } };
			return true;
		}
		else if ((up == 0 && _pArr[up][j].getCheck() == turn))
		{
			_winPos = new _Point[5]{ {up,j},{up + 1,j },{up + 2,j },{up + 3,j },{up + 4,j } };
			return true;
		}
		else if (_pArr[down][j].getCheck() == -turn && _pArr[up][j].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {down - 1,j},{down - 2,j },{down - 3,j },{down - 4,j },{down - 5,j } };
			return true;
		}
		else if (_pArr[up][j].getCheck() == -turn && _pArr[down][j].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {up + 1,j},{up + 2 + 1,j + 1},{up + 3,j + 2},{up + 4,j + 3},{up + 5,j + 4} };
			return true;
		}
		else if (_pArr[up][j].getCheck() == _pArr[down][j].getCheck() && _pArr[down][j].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {down - 1,j},{down - 2,j },{down - 3,j },{down - 4,j },{down - 5,j } };
			return true;
		}
	}
	return false;
}

bool _Board::checkCol(int i, int j, int turn)
{
	int left = 0, right = 0;
	int count = 0, row = j;
	// kiểm tra cột
	while (row <= _size - 1 && _pArr[i][row].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (row == _size - 1)
		{
			count++;
			right = row;
			break;
		}
		else
		{
			count++;
			row++;
			right = row;
		}
	}
	count--;
	row = j;
	while (row >= 0 && _pArr[i][row].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == turn)
	{
		if (row == 0)
		{
			count++;
			left = row;
			break;
		}
		else
		{
			count++;
			row--;
			left = row;
		}
	}
	if (count > 4)
	{
		if (right == _size - 1 && _pArr[i][right].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {i,right},{i ,right - 1},{i ,right - 2},{i,right - 3},{i,right - 4} };
			return true;
		}
		else if (left == 0 && _pArr[i][left].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {i,left},{i ,left + 1},{i ,left + 2},{i,left + 3},{i,left + 4} };
			return true;
		}
		else if (_pArr[i][right].getCheck() == -turn && _pArr[i][left].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {i,right - 1},{i ,right - 2},{i ,right - 3},{i ,right - 4},{i ,right - 5} };
			return true;
		}
		else if (_pArr[i][left].getCheck() == -turn && _pArr[i][right].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {i,left + 1},{i ,left + 2},{i ,left + 3},{i ,left + 4},{i ,left + 5} };
			return true;
		}
		else if (_pArr[i][left].getCheck() == _pArr[i][right].getCheck() && _pArr[i][right].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {i,left + 1},{i ,left + 2},{i ,left + 3},{i ,left + 4},{i ,left + 5} };
			return true;
		}
	}
	return false;
}
bool _Board::checkDiag1(int i, int j, int turn)
{
	int LR_Col = 0, LR_Row = 0, UL_Col = 0, UL_Row = 0;
	// kiểm tra đường chéo 1
	int row = i, col = j, count = 0;
	while (col <= _size - 1 && row <= _size - 1 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((col == _size - 1 && row == _size - 1) || (col == _size - 1) || (row == _size - 1))
		{
			count++;
			LR_Col = col;
			LR_Row = row;
			break;
		}
		else
		{
			count++;
			row++;
			col++;
			LR_Col = col;
			LR_Row = row;
		}
	}
	row = i; col = j, count--;
	while (row >= 0 && col >= 0 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((col == 0 && row == 0) || (col == 0) || (row == 0))
		{
			count++;
			UL_Col = col;
			UL_Row = row;
			break;
		}
		else
		{
			count++;
			row--;
			col--;
			UL_Col = col;
			UL_Row = row;
		}
	}
	if (count > 4)
	{
		if (LR_Col == _size - 1 && _pArr[LR_Row][LR_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {LR_Row,LR_Col},{LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4} };
			return true;
		}
		else if (UL_Col == 0 && _pArr[UL_Row][UL_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {LR_Row,LR_Col},{LR_Row + 1 ,LR_Col + 1},{LR_Row + 2,LR_Col + 2},{LR_Row + 3,LR_Col + 3},{LR_Row + 4,LR_Col + 4} };
			return true;
		}
		else if (LR_Row == _size - 1 && _pArr[LR_Row][LR_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {LR_Row,LR_Col},{LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4} };
			return true;
		}
		else if (UL_Row == 0 && _pArr[UL_Row][UL_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {LR_Row,LR_Col},{LR_Row + 1 ,LR_Col + 1},{LR_Row + 2,LR_Col + 2},{LR_Row + 3,LR_Col + 3},{LR_Row + 4,LR_Col + 4} };
			return true;
		}
		else if (_pArr[LR_Row][LR_Col].getCheck() == -turn && _pArr[UL_Row][UL_Col].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {LR_Row - 1 ,LR_Col - 1},{LR_Row - 2,LR_Col - 2},{LR_Row - 3,LR_Col - 3},{LR_Row - 4,LR_Col - 4},{LR_Row - 5,LR_Col - 5} };
			return true;
		}
		else if (_pArr[UL_Row][UL_Col].getCheck() == -turn && _pArr[LR_Row][LR_Col].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {UL_Row + 1 ,UL_Col + 1},{UL_Row + 2,UL_Col + 2},{UL_Row + 3,UL_Col + 3},{UL_Row + 4,UL_Col + 4},{UL_Row + 5,UL_Col + 5} };
			return true;
		}
		else if (_pArr[UL_Row][UL_Col].getCheck() == _pArr[LR_Row][LR_Col].getCheck() && _pArr[LR_Row][LR_Col].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {UL_Row + 1 ,UL_Col + 1},{UL_Row + 2,UL_Col + 2},{UL_Row + 3,UL_Col + 3},{UL_Row + 4,UL_Col + 4},{UL_Row + 5,UL_Col + 5} };
			return true;
		}
	}
	return false;
}
bool _Board::checkDiag2(int i, int j, int turn)
{
	int LL_Row = 0, LL_Col = 0, UR_Row = 0, UR_Col = 0;
	// kiểm tra đường chéo 2
	int row = i, col = j, count = 0;
	while (col >= 0 && row <= _size - 1 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((col == 0 && row == _size - 1) || (col == 0) || (row == _size - 1))
		{
			count++;
			LL_Col = col;
			LL_Row = row;
			break;
		}
		else
		{
			count++;
			row++;
			col--;
			LL_Col = col;
			LL_Row = row;
		}
	}
	row = i; col = j, count--;
	while (row >= 0 && col <= _size - 1 && _pArr[i][j].getCheck() == _pArr[row][col].getCheck() && _pArr[row][col].getCheck() == turn)
	{
		if ((row == 0 && col == _size - 1) || (col == _size - 1) || (row == 0))
		{
			count++;
			UR_Row = row;
			UR_Col = col;
			break;
		}
		else
		{
			count++;
			row--;
			col++;
			UR_Row = row;
			UR_Col = col;
		}
	}
	if (count > 4)
	{
		if (LL_Col == 0 && _pArr[LL_Row][LL_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {LL_Row,LL_Col},{LL_Row - 1 ,LL_Col + 1},{LL_Row - 2,LL_Col + 2},{LL_Row - 3,LL_Col + 3},{LL_Row - 4,LL_Col + 4} };
			return true;
		}
		else if (UR_Col == _size - 1 && _pArr[UR_Row][UR_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {UR_Row,UR_Col},{UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4} };
			return true;
		}
		else if (LL_Row == _size - 1 && _pArr[LL_Row][LL_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {LL_Row,LL_Col},{LL_Row - 1 ,LL_Col + 1},{LL_Row - 2,LL_Col + 2},{LL_Row - 3,LL_Col + 3},{LL_Row - 4,LL_Col + 4} };
			return true;
		}
		else if (UR_Row == 0 && _pArr[UR_Row][UR_Col].getCheck() == turn)
		{
			_winPos = new _Point[5]{ {UR_Row,UR_Col},{UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4} };
			return true;
		}
		else if (_pArr[LL_Row][LL_Col].getCheck() == -turn && _pArr[UR_Row][UR_Col].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {LL_Row - 1 ,LL_Col + 1},{LL_Row - 2,LL_Col + 2},{LL_Row - 3,LL_Col + 3},{LL_Row - 4,LL_Col + 4},{LL_Row - 5,LL_Col + 5} };
			return true;
		}
		else if (_pArr[UR_Row][UR_Col].getCheck() == -turn && _pArr[LL_Row][LL_Col].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {UR_Row + 5,UR_Col - 5},{UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4} };
			return true;
		}
		else if (_pArr[UR_Row][UR_Col].getCheck() == _pArr[LL_Row][LL_Col].getCheck() && _pArr[LL_Row][LL_Col].getCheck() != -turn)
		{
			_winPos = new _Point[5]{ {UR_Row,UR_Col},{UR_Row + 1 ,UR_Col - 1},{UR_Row + 2,UR_Col - 2},{UR_Row + 3,UR_Col - 3},{UR_Row + 4,UR_Col - 4} };
			return true;
		}

	}
	return false;
}
long _Board::scoreAtkCheckRow(int row, int col)
{
	long score_col = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && col + count1 < _size; count1++)
	{
		if (_pArr[row][col + count1].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row][col + count1].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row][col + count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && col + count2 < _size; count2++)
			{
				if (_pArr[row][col + count2].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row][col + count2].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row][col + count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && col - count1 >= 0; count1++)
	{
		if (_pArr[row][col - count1].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row][col - count1].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row][col - count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && col - count2 >= 0; count2++)
			{
				if (_pArr[row][col - count2].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row][col - count2].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row][col - count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_com1 == 2)
	{
		return 0;
	}
	if (score_com1 == 0)
	{
		score_col += atkPoint[score_player1] * 2;
	}
	else
	{
		score_col += atkPoint[score_player1];
	}
	if (score_com2 == 0)
	{
		score_col += atkPoint[score_player2] * 2;
	}
	else
	{
		score_col += atkPoint[score_player2];
	}
	if (score_player1 >= score_player2)
	{
		score_col--;
	}
	else
	{
		score_col -= 2;
	}
	if (score_player1 == 4)
	{
		score_col *= 2;
	}
	if (score_player1 == 0)
	{
		score_col += defPoint[score_com1] * 2;
	}
	else
	{
		score_col += defPoint[score_com1];
	}
	if (score_player2 == 0)
	{
		score_col += defPoint[score_com2] * 2;
	}
	else
	{
		score_col += defPoint[score_com2];
	}
	return score_col;
}
long _Board::scoreAtkCheckCol(int row, int col)
{
	long score_row = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && row + count1 < _size; count1++)
	{
		if (_pArr[row + count1][col].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row + count1][col].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row + count1][col].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row + count2 < _size; count2++)
			{
				if (_pArr[row + count2][col].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row + count2][col].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row + count2][col].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && row - count1 >= 0; count1++)
	{
		if (_pArr[row - count1][col].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row - count1][col].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row - count1][col].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row - count2 >= 0; count2++)
			{
				if (_pArr[row - count2][col].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row - count2][col].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row - count2][col].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_com1 == 2)
	{
		return 0;
	}
	if (score_com1 == 0)
	{
		score_row += atkPoint[score_player1] * 2;
	}
	else
	{
		score_row += atkPoint[score_player1];
	}
	if (score_com2 == 0)
	{
		score_row += atkPoint[score_player2] * 2;
	}
	else
	{
		score_row += atkPoint[score_player2];
	}
	if (score_player1 >= score_player2)
	{
		score_row--;
	}
	else
	{
		score_row -= 2;
	}
	if (score_player1 == 4)
	{
		score_row *= 2;
	}
	if (score_player1 == 0)
	{
		score_row += defPoint[score_com1] * 2;
	}
	else
	{
		score_row += defPoint[score_com1];
	}
	if (score_player2 == 0)
	{
		score_row += defPoint[score_com2] * 2;
	}
	else
	{
		score_row += defPoint[score_com2];
	}
	return score_row;
}
long _Board::scoreAtkCheckDiag1(int row, int col)
{
	long score_diag1 = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && row + count1 < _size && col + count1 < _size; count1++)
	{
		if (_pArr[row + count1][col + count1].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row + count1][col + count1].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row + count1][col + count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row + count2 < _size && col + count2 < _size; count2++)
			{
				if (_pArr[row + count2][col + count2].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row + count2][col + count2].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row + count2][col + count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && row - count1 >= 0 && col - count1 >= 0; count1++)
	{
		if (_pArr[row - count1][col - count1].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row - count1][col - count1].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row - count1][col - count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row - count2 >= 0 && col - count2 >= 0; count2++)
			{
				if (_pArr[row - count2][col - count2].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row - count2][col - count2].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row - count2][col - count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_com1 == 2)
	{
		return 0;
	}
	if (score_com1 == 0)
	{
		score_diag1 += atkPoint[score_player1] * 2;
	}
	else
	{
		score_diag1 += atkPoint[score_player1];
	}
	if (score_com2 == 0)
	{
		score_diag1 += atkPoint[score_player2] * 2;
	}
	else
	{
		score_diag1 += atkPoint[score_player2];
	}
	if (score_player1 >= score_player2)
	{
		score_diag1--;
	}
	else
	{
		score_diag1 -= 2;
	}
	if (score_player1 == 4)
	{
		score_diag1 *= 2;
	}
	if (score_player1 == 0)
	{
		score_diag1 += defPoint[score_com1] * 2;
	}
	else
	{
		score_diag1 += defPoint[score_com1];
	}
	if (score_player2 == 0)
	{
		score_diag1 += defPoint[score_com2] * 2;
	}
	else
	{
		score_diag1 += defPoint[score_com2];
	}
	return score_diag1;
}
long _Board::scoreAtkCheckDiag2(int row, int col)
{
	long score_diag2 = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && row + count1 < _size && col - count1 < _size; count1++)
	{
		if (_pArr[row + count1][col - count1].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row + count1][col - count1].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row + count1][col - count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row + count2 < _size && col - count2 < _size; count2++)
			{
				if (_pArr[row + count2][col - count2].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row + count2][col - count2].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row + count2][col - count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && row - count1 >= 0 && col + count1 >= 0; count1++)
	{
		if (_pArr[row - count1][col + count1].getCheck() == -1)
		{
			score_player1++;
		}
		if (_pArr[row - count1][col + count1].getCheck() == 1)
		{
			score_com1++;
			break;
		}
		if (_pArr[row - count1][col + count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row - count2 >= 0 && col + count2 >= 0; count2++)
			{
				if (_pArr[row - count2][col + count2].getCheck() == -1)
				{
					score_player2++;
				}
				if (_pArr[row - count2][col + count2].getCheck() == 1)
				{
					score_com2++;
					break;
				}
				if (_pArr[row - count2][col + count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_com1 == 2)
	{
		return 0;
	}
	if (score_com1 == 0)
	{
		score_diag2 += atkPoint[score_player1] * 2;
	}
	else
	{
		score_diag2 += atkPoint[score_player1];
	}
	if (score_com2 == 0)
	{
		score_diag2 += atkPoint[score_player2] * 2;
	}
	else
	{
		score_diag2 += atkPoint[score_player2];
	}
	if (score_player1 >= score_player2)
	{
		score_diag2--;
	}
	else
	{
		score_diag2 -= 2;
	}
	if (score_player1 == 4)
	{
		score_diag2 *= 2;
	}
	if (score_player1 == 0)
	{
		score_diag2 += defPoint[score_com1] * 2;
	}
	else
	{
		score_diag2 += defPoint[score_com1];
	}
	if (score_player2 == 0)
	{
		score_diag2 += defPoint[score_com2] * 2;
	}
	else
	{
		score_diag2 += defPoint[score_com2];
	}
	return score_diag2;
}
long _Board::scoreDefCheckRow(int row, int col)
{
	long  score_col = 0;
	long  score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && col + count1 < _size; count1++)
	{
		if (_pArr[row][col + count1].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row][col + count1].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row][col + count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && col + count2 < _size; count2++)
			{
				if (_pArr[row][col + count2].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row][col + count2].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row][col + count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && col - count1 >= 0; count1++)
	{
		if (_pArr[row][col - count1].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row][col - count1].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row][col - count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && col - count2 >= 0; count2++)
			{
				if (_pArr[row][col - count2].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row][col - count2].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row][col - count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_player1 == 2)
	{
		return 0;
	}
	if (score_player1 == 0)
	{
		score_col += defPoint[score_com1] * 2;
	}
	else
	{
		score_col += defPoint[score_com1];
	}
	if (score_com1 >= score_com2)
	{
		score_col--;
	}
	else
	{
		score_col -= 2;
	}
	if (score_com1 == 4)
	{
		score_col *= 2;
	}
	return score_col;
}
long _Board::scoreDefCheckCol(int row, int col)
{
	long score_row = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && row + count1 < _size; count1++)
	{
		if (_pArr[row + count1][col].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row + count1][col].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row + count1][col].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row + count2 < _size; count2++)
			{
				if (_pArr[row + count2][col].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row + count2][col].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row + count2][col].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && row - count1 >= 0; count1++)
	{
		if (_pArr[row - count1][col].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row - count1][col].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row - count1][col].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row - count2 >= 0; count2++)
			{
				if (_pArr[row - count2][col].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row - count2][col].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row - count2][col].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_player1 == 2)
	{
		return 0;
	}
	if (score_player1 == 0)
	{
		score_row += defPoint[score_com1] * 2;
	}
	else
	{
		score_row += defPoint[score_com1];
	}
	if (score_com1 >= score_com2)
	{
		score_row--;
	}
	else
	{
		score_row -= 2;
	}
	if (score_com1 == 4)
	{
		score_row *= 2;
	}
	return score_row;
}
long _Board::scoreDefCheckDiag1(int row, int col)
{
	long score_diag1 = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && row + count1 < _size && col + count1 < _size; count1++)
	{
		if (_pArr[row + count1][col + count1].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row + count1][col + count1].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row + count1][col + count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row + count2 < _size && col + count2 < _size; count2++)
			{
				if (_pArr[row + count2][col + count2].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row + count2][col + count2].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row + count2][col + count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && row - count1 >= 0 && col - count1 >= 0; count1++)
	{
		if (_pArr[row - count1][col - count1].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row - count1][col - count1].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row - count1][col - count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row - count2 >= 0 && col - count2 >= 0; count2++)
			{
				if (_pArr[row - count2][col - count2].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row - count2][col - count2].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row - count2][col - count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_player1 == 2)
	{
		return 0;
	}
	if (score_player1 == 0)
	{
		score_diag1 += defPoint[score_com1] * 2;
	}
	else
	{
		score_diag1 += defPoint[score_com1];
	}
	if (score_com1 >= score_com2)
	{
		score_diag1--;
	}
	else
	{
		score_diag1 -= 2;
	}
	if (score_com1 == 4)
	{
		score_diag1 *= 2;
	}
	return score_diag1;
}
long _Board::scoreDefCheckDiag2(int row, int col)
{
	long score_diag2 = 0;
	long score_attack = 0;
	int score_player1 = 0;
	int score_player2 = 0;
	int score_com1 = 0;
	int score_com2 = 0;
	for (int count1 = 1; count1 < 6 && row + count1 < _size && col - count1 < _size; count1++)
	{
		if (_pArr[row + count1][col - count1].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row + count1][col - count1].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row + count1][col - count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row + count2 < _size && col - count2 < _size; count2++)
			{
				if (_pArr[row + count2][col - count2].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row + count2][col - count2].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row + count2][col - count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	for (int count1 = 1; count1 < 6 && row - count1 >= 0 && col + count1 >= 0; count1++)
	{
		if (_pArr[row - count1][col + count1].getCheck() == -1)
		{
			score_player1++;
			break;
		}
		if (_pArr[row - count1][col + count1].getCheck() == 1)
		{
			score_com1++;
		}
		if (_pArr[row - count1][col + count1].getCheck() == 0)
		{
			for (int count2 = 2; count2 < 7 && row - count2 >= 0 && col + count2 >= 0; count2++)
			{
				if (_pArr[row - count2][col + count2].getCheck() == -1)
				{
					score_player2++;
					break;
				}
				if (_pArr[row - count2][col + count2].getCheck() == 1)
				{
					score_com2++;
				}
				if (_pArr[row - count2][col + count2].getCheck() == 0)
				{
					break;
				}
			}
			break;
		}
	}
	if (score_player1 == 2)
	{
		return 0;
	}
	if (score_player1 == 0)
	{
		score_diag2 += defPoint[score_com1] * 2;
	}
	else
	{
		score_diag2 += defPoint[score_com1];
	}
	if (score_com1 >= score_com2)
	{
		score_diag2--;
	}
	else
	{
		score_diag2 -= 2;
	}
	if (score_com1 == 4)
	{
		score_diag2 *= 2;
	}
	return score_diag2;
}

_Point _Board::PVC_hard()
{
	int row = 0;
	int col = 0;
	long point = 0;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			long atk = 0;
			long def = 0;
			if (_pArr[i][j].getCheck() == 0)
			{
				atk += scoreAtkCheckRow(i, j);
				atk += scoreAtkCheckCol(i, j);
				atk += scoreAtkCheckDiag1(i, j);
				atk += scoreAtkCheckDiag2(i, j);
				def += scoreDefCheckRow(i, j);
				def += scoreDefCheckCol(i, j);
				def += scoreDefCheckDiag1(i, j);
				def += scoreDefCheckDiag2(i, j);

				if (atk > def)
				{
					if (point < atk)
					{
						point = atk;
						row = i;
						col = j;
					}
				}
				else
				{
					if (point < def)
					{
						point = def;
						row = i;
						col = j;
					}
				}
			}
		}
	}
	return _Point(getXAt(row, col), getYAt(row, col));
}

_Point _Board::PVC_easy()
{
	static random_device rd;
	static mt19937 mt(rd());
	static uniform_int_distribution<int> dist(0, _size);
	int i, j;
	do
	{
		i = dist(mt) * 4, j = dist(mt) * 2;
	} while (!_pArr[i][j].getCheck());
	return _Point(getXAt(i, j), getYAt(i, j));
}

void _Board::loadData(ifstream& inFile)
{
	if (_size == 0)
		return;
	int check = 0;
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			inFile >> check;
			_pArr[i][j].setX(4 * j + _left + 3);
			_pArr[i][j].setY(2 * i + _top + 1);
			_pArr[i][j].setCheck(check);
			if (check == 1)
			{
				_countX++;
			}
			else if (check == -1)
			{
				_countO++;
			}
		}
	}
}

_Point* _Board::getWinPos()
{
	_Point* b = new _Point[5];
	for (int i = 0; i < 5; i++)
	{
		int x = _winPos[i].getX(), y = _winPos[i].getY();
		b[i].setX(getXAt(x, y)), b[i].setY(getYAt(x, y));
	}
	return b;
}