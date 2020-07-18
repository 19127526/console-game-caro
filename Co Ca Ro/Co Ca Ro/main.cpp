#include "_Board.h"
#include "_Common.h"
#include "_Game.h"
#include "_Point.h"
using namespace std;

int  main() {
	_Common::fixConsoleWindow();
	_Game g(10, 10, 10); // Tu dieu chinh
	g.startGame();
	while (g.isContinue()) {
		g.waitKeyBoard();
		if (g.getCommand() == 27) g.exitGame();
		else {
			switch (g.getCommand()) {
			case 'A':
				g.moveLeft();
				break;
			case 'W':
				g.moveUp();
				break;
			case 'S':
				g.moveDown();
				break;
			case 'D':
				g.moveRight();
				break;
			case 13:
				//Mark the board, then check and process win/ lose/darw/continue
				if (g.processCheckBoard()) {
					switch (g.processFinish()) {
					case -1:case1:case 0:
						if (g.askContinue() != 'Y') g.exitGame();
						else g.startGame();
					}
				}
			}
		}
	}
	return 0;
}
