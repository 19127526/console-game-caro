#include "_Menu.h"

int _Menu::current_option;
const string _Menu::options[8] = { "Play", "Load", "Help", "Exit", " PvP ", "PvC(easy)", "PvC(hard)", "Back" };

void _Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], loadScreen},
		{options[2], helpScreen},
		{options[3], exitScreen},
		{options[4], playPvP},
		{options[5], playPvC1},
		{options[6], playPvC2},
		{options[7], goBack} };
	while (true)
	{
		mainMenu();
		while (true)
		{
			switch (_Common::getConsoleInput())
			{
			case 2:
				changeOption(0);
				break;
			case 5:
				changeOption(1);
				break;
			case 6:
				_Common::playSound(3);
				function_map[options[current_option]]();
				break;
			default:
				_Common::playSound(4);
				continue;
			}
		}

	};
}

void _Menu::printLogo()
{
	_Common::setConsoleColor(BRIGHT_WHITE, GRAY);
	_Common::clearConsole();
	unsigned char logo[] = {
		32,219,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,32,32,32,32,32,219,219,219,219,219,219,187,32,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,219,219,219,219,219,219,187,32,
219,219,201,205,205,205,205,188,219,219,201,205,205,205,219,219,187,32,32,32,32,32,219,219,201,205,205,205,205,188,219,219,201,205,205,219,219,187,219,219,201,205,205,219,219,187,219,219,201,205,205,205,219,219,187,
219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,219,219,219,219,219,186,219,219,219,219,219,219,201,188,219,219,186,32,32,32,219,219,186,
219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,201,205,205,219,219,186,219,219,201,205,205,219,219,187,219,219,186,32,32,32,219,219,186,
200,219,219,219,219,219,219,187,200,219,219,219,219,219,219,201,188,32,32,32,32,32,200,219,219,219,219,219,219,187,219,219,186,32,32,219,219,186,219,219,186,32,32,219,219,186,200,219,219,219,219,219,219,201,188,
32,200,205,205,205,205,205,188,32,200,205,205,205,205,205,188,32,32,32,32,32,32,32,200,205,205,205,205,205,188,200,205,188,32,32,200,205,188,200,205,188,32,32,200,205,188,32,200,205,205,205,205,205,188,32 };
	int top = 4, left = 27;
	int num_lines = 6, num_chars = 55;
	for (int i = 0; i < num_lines; i++)
	{
		_Common::gotoXY(left, i + top);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i*num_chars + j]);
	}
}

void _Menu::printOptionsBoard()
{
	_Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
	int left = 48;
	int top = 20;
	_Common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < 8; i++)
	{
		_Common::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			_Common::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	_Common::gotoXY(left, top + 8);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

void _Menu::printAnimation()
{
	char pos[] = { 5,0,19,0,33,0,47,0,61,0,75,0,89,0,103,0,12,6,96,6,5,12,
		           19,12,33,12,47,12,61,12,75,12,89,12,103,12,12,18,26,18,
		           40,18,54,18,68,18,82,18,96,18,5,24,19,24,33,24,75,24,89,
		           24,103,24,12,30,26,30,40,30,54,30,68,30,82,30,96,30 };
	int n = (sizeof(pos) / sizeof(pos[0]))/2;
	int a = 79, b = 88;
	int c = LIGHT_BLUE, d = LIGHT_RED;
	int loop = 5;
	while (loop--)
	{
		for (int i = 0; i < n; i += 2)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, c);
			_Common::gotoXY(pos[i * 2], pos[i * 2 + 1]);
			putchar(a);
		}
		for (int i = 1; i < n; i += 2)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, d);
			_Common::gotoXY(pos[i * 2], pos[i * 2 + 1]);
			putchar(b);
		}
		swap(a, b), swap(c, d);
		Sleep(400);
	}
	for (int i = 0; i < n * 2; i+=2)
	{
		_Common::gotoXY(pos[i], pos[i + 1]);
		putchar(32);
	}
}

void _Menu::fillMenuOptions()
{
	int top = 21;
	int offset = (current_option < 4) ? 0 : 4;

	_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	for (int i = 0; i < 4; i++)
	{
		_Common::gotoXY(54 - (int)options[i+offset].length()/2 , top + i * 2);
		cout << options[i+offset];
	}
}

bool _Menu::changeOption(bool direction) //0 for up, 1 for down
{
	int top = 21;
	if ((direction == 0 && (current_option == 4 || current_option == 0))
		|| (direction == 1 && (current_option == 3 || current_option == 7)))
	{
		_Common::playSound(4);
		return false;
	}
	_Common::playSound(2);
	if (current_option == -1)
	{
		current_option = 0;
	}
	else if(current_option == 8)
	{
		current_option = 4;
	}
	else
	{
		_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
		_Common::gotoXY(44, top + current_option % 4 * 2);
		putchar(32);
		_Common::gotoXY(54 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		_Common::gotoXY(64, top + current_option % 4 * 2);
		putchar(32);
		(direction == 1) ? current_option++ : current_option--;
	}
	_Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	_Common::gotoXY(44, top + current_option % 4 * 2);
	putchar(175);
	_Common::gotoXY(54 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];
	_Common::gotoXY(64, top + current_option % 4 * 2);
	putchar(174);
	return true;
}

void _Menu::mainMenu()
{
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_Common::clearConsole();
	printLogo();
	//printAnimation();
	printOptionsBoard();
	current_option = -1;
	fillMenuOptions();
	changeOption(1);
}

void _Menu::playMenu()
{
	current_option = 8;
	fillMenuOptions();
	changeOption(1);
}

void _Menu::playPvP()
{
	_Game g(0);
	g.startGame();
}

void _Menu::helpScreen()
{
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_Common::clearConsole();
	int left = 13, top = 2, width = 81, height = 23;
	int line1 = 6, line2 = 19, line3 = 24;
	printRectangle(left, top, width, height);
	_Common::gotoXY(left + 1, line1);
	for (int i = 0; i < width; i++)
	{
		putchar(196);
	}
	_Common::gotoXY(left+1, line2);
	for (int i = 0; i <width; i++)
	{
		putchar(196);
	}
	for (int i = 1; i < height; i++)
	{
		_Common::gotoXY(line3, top + i);
		putchar(179);
	}
	_Common::gotoXY(line3, line1);
	putchar(197);
	_Common::gotoXY(line3, line2);
	putchar(197);


	_Common::gotoXY(left + 3, top + 2);
	cout << "Moves:";
	_Common::gotoXY(left + 20, top + 1);
	putchar(249); cout << "Up:    W, up arrow";
	_Common::gotoXY(left + 52, top + 1);
	putchar(249); cout << "Down:  S, down arrow";
	_Common::gotoXY(left + 20, top + 3);
	putchar(249); cout << "Left:  A, left arrow";
	_Common::gotoXY(left + 52, top + 3);
	putchar(249); cout << "Right: D, right arrow";


	_Common::gotoXY(left + 3, top + 10);
	cout << "Rules:";
	_Common::gotoXY(left + 13, top + 5);
	int left1 = left + 13;
	putchar(249); cout << "The player representing the 'X' symbol gets to take the first turn";
	_Common::gotoXY(left1, top + 6);
	cout << " followed by the player representing the 'O' symbol.";
	_Common::gotoXY(left1, top + 8);
	putchar(249); cout << "Players take turns placing their symbol on an open intersection";
	_Common::gotoXY(left1, top + 9);
	cout << " on the board.";
	_Common::gotoXY(left1, top + 11);
	putchar(249); cout << "The player that manages to create exactly five in a row first,";
	_Common::gotoXY(left1, top + 12);
	cout << " without being blocked by another color or symbol at either end";
	_Common::gotoXY(left1, top + 13);
	cout << " wins the round.";
	_Common::gotoXY(left1, top + 15);
	putchar(249); cout << "The row can be horizontal, vertical, or diagonal as long as";
	_Common::gotoXY(left1, top + 16);
	cout << " it is unbroken.";

	_Common::gotoXY(left + 3, top + 20);
	cout << "About:";
	_Common::gotoXY(left + 28, top + 18);
	cout << "Teacher:            Truong Toan Thinh";
	_Common::gotoXY(left + 28, top + 19);
	cout << "Teaching assistant: Nguyen Hai Dang";
	_Common::gotoXY(left + 13, top + 21);
	cout << "+ Nguyen Xuan Phat (19127504)       + Pham Tien Quan     (19127526)";
	_Common::gotoXY(left + 13, top + 22);
	cout << "+ Dang Tu Thieu    (19127557)       + Luong Truong Thinh (19127559)";

	printRectangle(49, 27, 8, 2);
	_Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	_Common::gotoXY(47, 28);
	putchar(175);
	_Common::gotoXY(52, 28);
	cout << "Back";
	_Common::gotoXY(60, 28);
	putchar(174);
	while (_Common::getConsoleInput() != 6)
	{
		_Common::playSound(4);
	}
}

void _Menu::printRectangle(int left, int top, int width, int height)
{
	_Common::gotoXY(left, top);
	putchar(218);
	for(int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for(; i < height; i++)
	{ 
		_Common::gotoXY(left, top + i + 1);
		putchar(179);
		_Common::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	_Common::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void _Menu::exitScreen()
{
	_Common::clearConsole();
	printLogo();
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(36, 18, 35, 8);
	_Common::gotoXY(44, 20);
	cout << "Do you want to exit?";
	printRectangle(39, 23, 7, 2);
	_Common::gotoXY(42, 24);
	cout << "Yes";
	printRectangle(62, 23, 6, 2);
	_Common::gotoXY(65, 24);
	cout << "No";
	cin.get();
}

void _Menu::playPvC1()
{
	_Game g(1);
	g.startGame();
}
