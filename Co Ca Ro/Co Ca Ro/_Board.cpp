#include "_Board.h"

int _Board::getSize() {
	return _size;
}
int _Board::getLeft() {
	return _left;
}
int _Board::getTop() {
	return _top;
}
int _Board::getXAt(int i, int j) {
	return _pArr[i][j].getX();
}
int _Board::getYAt(int i, int j) {
	return _pArr[i][j].getY();
}
_Board::_Board(int pSize, int pX, int pY) {
	_size = pSize;
	_left = pX;
	_top = pY;
	_pArr = new _Point * [pSize];
	for (int i = 0; i < pSize; i++) _pArr[i] = new _Point[pSize];
}
_Board::~_Board() {
	for (int i = 0; i < _size; i++) delete[] _pArr[i];
	delete[] _pArr;
}
void _Board::resetData() {
	if (_size == 0) return;  // Firstly calling constructor before calling resetData
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			_pArr[i][j].setX(4 * j + _left + 2);  // x-value of boardgame
			_pArr[i][j].setY(2 * i + _top + 1);  // y-value of boardgame
			_pArr[i][j].setCheck(0);
		}
	}
}
void _Board::drawBoard() {
	if (_pArr == NULL) return; // firstly call constructor
	for (int i = 0; i <= _size; i++) {
		for (int j = 0; j <= _size; j++) {
			_Common::gotoXY(_left + 4 * i, _top + 2 * j);
			printf(".");
		}
	}
	_Common::gotoXY(_pArr[0][0].getX(), _pArr[0][0].getY()); //move to the 1st cell
}
int _Board::checkboard(int pX, int pY, bool pTurn) {
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < _size; j++) {
			if (_pArr[i][j].getX() == pX && _pArr[i][j].getY() == pY && _pArr[i][j].getCheck() == 0) {
				if (pTurn) _pArr[i][j].setCheck(-1); // If current turn is true: c = -1
				else _pArr[i][j].setCheck(1); // If current turn is fasle : c = 1
				return _pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}
int _Board::testBoard() { // Defaultly returns 'Draw'
	return 0;
}
