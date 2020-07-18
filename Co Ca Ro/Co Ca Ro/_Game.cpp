#include "_Game.h"
#include "_Common.h"
#include<conio.h>
#include "_Board.h"
_Game::_Game(int pSize, int pLeft, int pTop) {
	_b = new _Board(pSize, pLeft, pTop);
	_loop = _turn = true;
	_command = -1; // Gan lan luot va khoa mac dinh
	_x = pLeft; _y = pTop;
}
_Game::~_Game() {delete _b;}
int _Game::getCommand() {
	return _command;
}
bool _Game::isContinue() {
	return _loop;
}
char _Game::waitKeyBoard() {
	_command = toupper(_getch());
	return _command;
}
char _Game::askContinue() {
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 4);
	return waitKeyBoard();
}
void _Game::startGame() {
	system("cls");
	_b->resetData(); // Cai dat du lieu goc
	_b->drawBoard(); // ve bang
	_x = _b->getXAt(0, 0);
	_y = _b->getYAt(0, 0);
}
void _Game::exitGame() {
	system("cls");
	// Maybe save game before stopping
	_loop = false;
}
int _Game::processFinish() {
	// Move to the reasonable place to print string win/lose/draw
	_Common::gotoXY(0, _b->getYAt(_b->getSize() - 1, _b->getSize() - 1) + 2);
	int pWhoWin = _b->testBoard();
	switch (pWhoWin) {
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
	_Common::gotoXY(_x, _y); // Return the current position of cursor
	return pWhoWin;
}
bool _Game::processCheckBoard() {
	switch (_b->checkboard(_x, _y, _turn)) {
	case -1:
		printf("X");
		break;
	case 1:
		printf("O");
		break;
	case 0: return false; // Tick the cell marked
	}
	return true;
	
}
void _Game::moveRight() {
	if (_x < _b->getXAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_x += 4;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveLeft() {
	if (_x > _b->getXAt(0, 0)) {
		_x -= 4;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveUp() {
	if (_y > _b->getYAt(0, 0)) {
		_y -= 2;
		_Common::gotoXY(_x, _y);
	}
}
void _Game::moveDown() {
	if (_y < _b->getYAt(_b->getSize() - 1, _b->getSize() - 1)) {
		_y += 2;
		_Common::gotoXY(_x, _y);
	}
}