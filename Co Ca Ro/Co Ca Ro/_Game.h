#pragma once
#include "_Board.h"
class _Game{
	_Board* _b; // mot bang game
	bool _turn; // tra ve: true : nguoi 1 : false : nguoi 2
	int _x, _y; // Vi tri hien tai cua con tro
	int _command; // phim nhap cua nguoi choi
	bool _loop; // Check xem nguoi dung co thoat khoi tro choi hay khong
public:
	_Game(int, int, int);
	~_Game();
	int getCommand();
	bool isContinue();
	char waitKeyBoard(); // Nhan phim tu nguoi dung
	char askContinue();
	void startGame(); // Ham bat dau game
	void exitGame(); // Ham ket thuc game
	int processFinish();
	bool processCheckBoard();
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
};

