#include "_Board.h"

_Board::_Board(const char& p_size, const int& pX, const int& pY) :
	_size(p_size), _left(pX), _top(pY)
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

	_Common::setConsoleColor(WHITE, BLACK);
	_Common::clearConsole();
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	//ve khung trang
	for (int i = 0; i < _size * 2 + 1; i++)
	{
		_Common::gotoXY(_left, _top + i);
		for (int k = 0; k < _size * 4 + 3; k++)
		{
			putchar(32);
		}
	}

	//Ve duong tren
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


	//Ve duong duoi
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

int _Board::testBoard(int pX, int pY) //i,j la dong,cot cua bang
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
	int turn1 = _pArr[i][j].getCheck();
	if (turn1 == 1)
	{
		if (checkWin(i, j, turn1))
			return 1;
	}
	else
		if (checkWin(i, j, turn1))
			return -1;

	return 2; // continue
}

bool _Board::isPlacedAtXY(int pX, int pY)
{
	for (int i = 0; i < _size; i++)
	{
		for (int j = 0; j < _size; j++)
		{
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY)
			{
				return _pArr[i][j].getCheck() != 0;
			}
		}
	}
	throw "Problem with cursor";
}

//bool _Board::CheckHang(int i, int j, int check) // Kiem tra hang
//{
//	int d = 0, k = i, h, duoi = 0, tren  = 0, phai  =0;
//	while (k <= _size - 1 && _pArr[k][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
//	{
//		if (k == _size - 1)
//		{
//			d++;
//			duoi = k;
//			break;
//		}
//		else
//		{
//			d++;
//			k++;
//			duoi = k;
//		}
//	}
//	d--;
//	k = i;
//	while (k >= 0 && _pArr[k][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
//	{
//		if (k == 0)
//		{
//			d++;
//			tren = k;
//			break;
//		}
//		else
//		{
//			d++;
//			k--;
//			tren = k;
//		}
//	}
//	if (duoi != phai)
//	{
//		if (d > 4)
//		{
//			if (((duoi == _size - 1) && (_pArr[duoi][j].getCheck() == check)) || ((tren == 0) && (_pArr[tren][j].getCheck() == check)))
//			{
//				return true;
//			}
//			else if (_pArr[duoi][j].getCheck() == -check && _pArr[tren][j].getCheck() != -check)
//			{
//				return true;
//			}
//			else if (_pArr[tren][j].getCheck() == -check && _pArr[duoi][j].getCheck() != -check)
//			{
//				return true;
//			}
//			else if ((_pArr[tren][j].getCheck() == _pArr[duoi][j].getCheck() && _pArr[duoi][j].getCheck() != -check))
//			{
//				return true;
//			}
//			else if ((_pArr[tren][j].getCheck() == _pArr[duoi][j].getCheck() && _pArr[duoi][j].getCheck() == -check))
//			{
//
//			}
//		}
//	}
//}
//bool _Board::CheckCot(int i, int j, int check)
//{
//	int d = 0, h = j, phai, trai;
//	while (h <= _size - 1 && _pArr[i][h].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
//	{
//		if (h == _size - 1)
//		{
//			d++;
//			phai = h;
//			break;
//		}
//		else
//		{
//			d++;
//			h++;
//			phai = h;
//		}
//	}
//	d--;
//	h = j;
//	while (h >= 0 && _pArr[i][h].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
//	{
//		if (h == 0)
//		{
//			d++;
//			trai = h;
//			break;
//		}
//		else
//		{
//			d++;
//			h--;
//			trai = h;
//		}
//	}
//	if (d > 4)
//	{
//		if (((phai == _size - 1) && (_pArr[i][phai].getCheck() == check)) || ((trai == 0) && (_pArr[i][trai].getCheck() == check)))
//		{
//			return true;
//		}
//		if ((_pArr[i][trai].getCheck() == _pArr[i][phai].getCheck() && _pArr[i][phai].getCheck() == -check))
//		{
//
//		}
//		else if (_pArr[i][phai].getCheck() == -check && _pArr[i][trai].getCheck() != -check)
//		{
//			return true;
//		}
//		else if (_pArr[i][trai].getCheck() == -check && _pArr[i][phai].getCheck() != -check)
//		{
//			return true;
//		}
//		else if ((_pArr[i][trai].getCheck() == _pArr[i][phai].getCheck() && _pArr[i][phai].getCheck() != -check))
//		{
//			return true;
//		}
//	}
//}
//bool _Board::CheckCheo1(int i, int j, int check)
//{
//	int cotduoiphai = 0, hangduoiphai = 0, cottrentrai = 0, hangtrentrai = 0;
//	int h = i, k = j, d = 0;
//	while (k <= _size - 1 && h <= _size - 1 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
//	{
//		if ((k == _size - 1 && h == _size - 1) || (k == _size - 1) || (h == _size - 1))
//		{
//			d++;
//			cotduoiphai = k;
//			hangduoiphai = h;
//			break;
//		}
//		else
//		{
//			d++;
//			h++;
//			k++;
//			cotduoiphai = k;
//			hangduoiphai = h;
//		}
//	}
//	h = i; k = j, d--;
//	while (h >= 0 && k >= 0 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
//	{
//		if ((k == 0 && h == 0) || (k == 0) || (h == 0))
//		{
//			d++;
//			cottrentrai = k;
//			hangtrentrai = h;
//			break;
//		}
//		else
//		{
//			d++;
//			h--;
//			k--;
//			cottrentrai = k;
//			hangtrentrai = h;
//		}
//	}
//	if (d > 4)
//	{
//		if (((cotduoiphai == _size - 1) && (_pArr[hangduoiphai][cotduoiphai].getCheck() == check)) || ((cottrentrai == 0) && (_pArr[hangtrentrai][cottrentrai].getCheck() == check)))
//		{
//			return true;
//		}
//		else if (((hangduoiphai == _size - 1) && (_pArr[hangduoiphai][cotduoiphai].getCheck() == check)) || ((hangtrentrai == 0) && (_pArr[hangtrentrai][cottrentrai].getCheck() == check)))
//		{
//			return true;
//		}
//		if ((_pArr[hangtrentrai][cottrentrai].getCheck() == _pArr[hangduoiphai][cotduoiphai].getCheck() && _pArr[hangduoiphai][cotduoiphai].getCheck() == -check))
//		{
//
//		}
//		else if (_pArr[hangduoiphai][cotduoiphai].getCheck() == -check && _pArr[hangtrentrai][cottrentrai].getCheck() != -check)
//		{
//			return true;
//		}
//		else if (_pArr[hangtrentrai][cottrentrai].getCheck() == -check && _pArr[hangduoiphai][cotduoiphai].getCheck() != -check)
//		{
//			return true;
//		}
//		else if ((_pArr[hangtrentrai][cottrentrai].getCheck() == _pArr[hangduoiphai][cotduoiphai].getCheck() && _pArr[hangduoiphai][cotduoiphai].getCheck() != -check))
//		{
//			return true;
//		}
//	}
//}
//bool _Board::CheckCheo2(int i, int j, int check)
//{
//	int hangduoitrai = 0, cotduoitrai = 0, hangtrenphai = 0, cottrenphai = 0;
//	int h = i, k = j, d = 0;
//	while (k >= 0 && h <= _size - 1 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
//	{
//		if ((k == 0 && h == _size - 1) || (k == 0) || (h == _size - 1))
//		{
//			d++;
//			cotduoitrai = k;
//			hangduoitrai = h;
//			break;
//		}
//		else
//		{
//			d++;
//			h++;
//			k--;
//			cotduoitrai = k;
//			hangduoitrai = h;
//		}
//	}
//	h = i; k = j, d--;
//	while (h >= 0 && k <= _size - 1 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
//	{
//		if ((h == 0 && k == _size - 1) || (k == _size - 1) || (h == 0))
//		{
//			d++;
//			hangtrenphai = h;
//			cottrenphai = k;
//			break;
//		}
//		else
//		{
//			d++;
//			h--;
//			k++;
//			hangtrenphai = h;
//			cottrenphai = k;
//		}
//	}
//	if (d > 4)
//	{
//		if (((cotduoitrai == 0) && (_pArr[hangduoitrai][cotduoitrai].getCheck() == check)) || ((cottrenphai == _size - 1) && (_pArr[hangtrenphai][cottrenphai].getCheck() == check)))
//		{
//			return true;
//		}
//		else if (((hangduoitrai == _size - 1) && (_pArr[hangduoitrai][cotduoitrai].getCheck() == check)) || ((hangtrenphai == 0) && (_pArr[hangtrenphai][cottrenphai].getCheck() == check)))
//		{
//			return true;
//		}
//		if ((_pArr[hangtrenphai][cottrenphai].getCheck() == _pArr[hangduoitrai][cotduoitrai].getCheck() && _pArr[hangduoitrai][cotduoitrai].getCheck() == -check))
//		{
//
//		}
//		else if (_pArr[hangduoitrai][cotduoitrai].getCheck() == -check && _pArr[hangtrenphai][cottrenphai].getCheck() != -check)
//		{
//			return true;
//		}
//		else if (_pArr[hangtrenphai][cottrenphai].getCheck() == -check && _pArr[hangduoitrai][cotduoitrai].getCheck() != -check)
//		{
//			return true;
//		}
//		else if ((_pArr[hangtrenphai][cottrenphai].getCheck() == _pArr[hangduoitrai][cotduoitrai].getCheck() && _pArr[hangduoitrai][cotduoitrai].getCheck() != -check))
//		{
//			return true;
//		}
//	}
//}
//
//bool _Board::checkWin(int i, int j, int check)
//{
//	int a = i, b = j;
//	if (CheckHang(a, b, check))
//		return true;
//	if(CheckCot(a, b, check))
//		return true;
//	if(CheckCheo1(a, b, check))
//		return true;
//	if(CheckCheo2(a, b, check))
//		return true;
//	return false;
//}

bool _Board::checkWin(int i, int j, int check) {
	int tren = 0, duoi = 0, trai = 0, phai = 0;
	int d = 0, k = i, h;
	// kiểm tra hàng
	while (k <= _size - 1 && _pArr[k][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
	{
		if (k == _size - 1)
		{
			d++;
			duoi = k;
			break;
		}
		else
		{
			d++;
			k++;
			duoi = k;
		}
	}
	d--;
	k = i;
	while (k >= 0 && _pArr[k][j].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
	{
		if (k == 0)
		{
			d++;
			tren = k;
			break;
		}
		else
		{
			d++;
			k--;
			tren = k;
		}
	}
	if (duoi != phai)
	{
		if (d > 4)
		{
			if (((duoi == _size - 1) && (_pArr[duoi][j].getCheck() == check)) || ((tren == 0) && (_pArr[tren][j].getCheck() == check)))
			{
				return true;
			}
			else if (_pArr[duoi][j].getCheck() == -check && _pArr[tren][j].getCheck() != -check)
			{
				return true;
			}
			else if (_pArr[tren][j].getCheck() == -check && _pArr[duoi][j].getCheck() != -check)
			{
				return true;
			}
			else if ((_pArr[tren][j].getCheck() == _pArr[duoi][j].getCheck() && _pArr[duoi][j].getCheck() != -check))
			{
				return true;
			}
			else if ((_pArr[tren][j].getCheck() == _pArr[duoi][j].getCheck() && _pArr[duoi][j].getCheck() == -check))
			{

			}
		}
	}
	d = 0; h = j;
	// kiểm tra cột
	while (h <= _size - 1 && _pArr[i][h].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
	{
		if (h == _size - 1)
		{
			d++;
			phai = h;
			break;
		}
		else
		{
			d++;
			h++;
			phai = h;
		}
	}
	d--;
	h = j;
	while (h >= 0 && _pArr[i][h].getCheck() == _pArr[i][j].getCheck() && _pArr[i][j].getCheck() == check)
	{
		if (h == 0)
		{
			d++;
			trai = h;
			break;
		}
		else
		{
			d++;
			h--;
			trai = h;
		}
	}
	if (d > 4)
	{
		if (((phai == _size - 1) && (_pArr[i][phai].getCheck() == check)) || ((trai == 0) && (_pArr[i][trai].getCheck() == check)))
		{
			return true;
		}
		if ((_pArr[i][trai].getCheck() == _pArr[i][phai].getCheck() && _pArr[i][phai].getCheck() == -check))
		{

		}
		else if (_pArr[i][phai].getCheck() == -check && _pArr[i][trai].getCheck() != -check)
		{
			return true;
		}
		else if (_pArr[i][trai].getCheck() == -check && _pArr[i][phai].getCheck() != -check)
		{
			return true;
		}
		else if ((_pArr[i][trai].getCheck() == _pArr[i][phai].getCheck() && _pArr[i][phai].getCheck() != -check))
		{
			return true;
		}
	}
	int cotduoiphai = 0, hangduoiphai = 0, cottrentrai = 0, hangtrentrai = 0;
	// kiểm tra đường chéo 1
	h = i; k = j; d = 0;
	while (k <= _size - 1 && h <= _size - 1 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
	{
		if ((k == _size - 1 && h == _size - 1) || (k == _size - 1) || (h == _size - 1))
		{
			d++;
			cotduoiphai = k;
			hangduoiphai = h;
			break;
		}
		else
		{
			d++;
			h++;
			k++;
			cotduoiphai = k;
			hangduoiphai = h;
		}
	}
	h = i; k = j, d--;
	while (h >= 0 && k >= 0 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
	{
		if ((k == 0 && h == 0) || (k == 0) || (h == 0))
		{
			d++;
			cottrentrai = k;
			hangtrentrai = h;
			break;
		}
		else
		{
			d++;
			h--;
			k--;
			cottrentrai = k;
			hangtrentrai = h;
		}
	}
	if (d > 4)
	{
		if (((cotduoiphai == _size - 1) && (_pArr[hangduoiphai][cotduoiphai].getCheck() == check)) || ((cottrentrai == 0) && (_pArr[hangtrentrai][cottrentrai].getCheck() == check)))
		{
			return true;
		}
		else if (((hangduoiphai == _size - 1) && (_pArr[hangduoiphai][cotduoiphai].getCheck() == check)) || ((hangtrentrai == 0) && (_pArr[hangtrentrai][cottrentrai].getCheck() == check)))
		{
			return true;
		}
		if ((_pArr[hangtrentrai][cottrentrai].getCheck() == _pArr[hangduoiphai][cotduoiphai].getCheck() && _pArr[hangduoiphai][cotduoiphai].getCheck() == -check))
		{

		}
		else if (_pArr[hangduoiphai][cotduoiphai].getCheck() == -check && _pArr[hangtrentrai][cottrentrai].getCheck() != -check)
		{
			return true;
		}
		else if (_pArr[hangtrentrai][cottrentrai].getCheck() == -check && _pArr[hangduoiphai][cotduoiphai].getCheck() != -check)
		{
			return true;
		}
		else if ((_pArr[hangtrentrai][cottrentrai].getCheck() == _pArr[hangduoiphai][cotduoiphai].getCheck() && _pArr[hangduoiphai][cotduoiphai].getCheck() != -check))
		{
			return true;
		}
	}
	int hangduoitrai = 0, cotduoitrai = 0, hangtrenphai = 0, cottrenphai = 0;
	// kiểm tra đường chéo 2
	h = i; k = j; d = 0;
	while (k >= 0 && h <= _size - 1 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
	{
		if ((k == 0 && h == _size - 1) || (k == 0) || (h == _size - 1))
		{
			d++;
			cotduoitrai = k;
			hangduoitrai = h;
			break;
		}
		else
		{
			d++;
			h++;
			k--;
			cotduoitrai = k;
			hangduoitrai = h;
		}
	}
	h = i; k = j, d--;
	while (h >= 0 && k <= _size - 1 && _pArr[i][j].getCheck() == _pArr[h][k].getCheck() && _pArr[h][k].getCheck() == check)
	{
		if ((h == 0 && k == _size - 1) || (k == _size - 1) || (h == 0))
		{
			d++;
			hangtrenphai = h;
			cottrenphai = k;
			break;
		}
		else
		{
			d++;
			h--;
			k++;
			hangtrenphai = h;
			cottrenphai = k;
		}
	}
	if (d > 4)
	{
		if (((cotduoitrai == 0) && (_pArr[hangduoitrai][cotduoitrai].getCheck() == check)) || ((cottrenphai == _size - 1) && (_pArr[hangtrenphai][cottrenphai].getCheck() == check)))
		{
			return true;
		}
		else if (((hangduoitrai == _size - 1) && (_pArr[hangduoitrai][cotduoitrai].getCheck() == check)) || ((hangtrenphai == 0) && (_pArr[hangtrenphai][cottrenphai].getCheck() == check)))
		{
			return true;
		}
		if ((_pArr[hangtrenphai][cottrenphai].getCheck() == _pArr[hangduoitrai][cotduoitrai].getCheck() && _pArr[hangduoitrai][cotduoitrai].getCheck() == -check))
		{

		}
		else if (_pArr[hangduoitrai][cotduoitrai].getCheck() == -check && _pArr[hangtrenphai][cottrenphai].getCheck() != -check)
		{
			return true;
		}
		else if (_pArr[hangtrenphai][cottrenphai].getCheck() == -check && _pArr[hangduoitrai][cotduoitrai].getCheck() != -check)
		{
			return true;
		}
		else if ((_pArr[hangtrenphai][cottrenphai].getCheck() == _pArr[hangduoitrai][cotduoitrai].getCheck() && _pArr[hangduoitrai][cotduoitrai].getCheck() != -check))
		{
			return true;
		}
	}
	return false;
}