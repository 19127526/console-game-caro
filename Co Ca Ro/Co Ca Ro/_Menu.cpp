#include "_Menu.h"

int _Menu::current_option;
const string _Menu::options[8] = { "Begin", "Load", "About", "Exit", " PvP ", "PvC(easy)", "PvC(hard)", "Back" };

void _Menu::mainScreen()
{
	unordered_map<string, void(*)()> function_map = {
		{options[0], playMenu},
		{options[1], loadScreen},
		{options[2], aboutScreen},
		{options[3], exitScreen},
		{options[4], playPvP},
		{options[7], goBack} };
	while (current_option != 3)
	{
		mainMenu();
		function_map[options[current_option]]();
		if(current_option > 3)
			function_map[options[current_option]]();
	};
}

void _Menu::printLogo()
{
	_Common::setConsoleColor(BRIGHT_WHITE, GRAY);
	_Common::clearConsole();
	unsigned char logo[] = {
		32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,219,219,219,219,187,32,32,
		32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,219,219,201,205,219,219,187,32,
		32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,200,205,188,32,200,205,188,32,
		32,219,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,32,32,32,32,32,219,219,219,219,219,219,187,32,219,219,219,219,219,187,32,219,219,219,219,219,219,187,32,32,219,219,219,219,219,219,187,32,
		219,219,201,205,205,205,205,188,219,219,201,205,205,205,219,219,187,32,32,32,32,32,219,219,201,205,205,205,205,188,219,219,201,205,205,219,219,187,219,219,201,205,205,219,219,187,219,219,201,205,205,205,219,219,187,
		219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,219,219,219,219,219,186,219,219,219,219,219,219,201,188,219,219,186,32,32,32,219,219,186,
		219,219,186,32,32,32,32,32,219,219,186,32,32,32,219,219,186,32,32,32,32,32,219,219,186,32,32,32,32,32,219,219,201,205,205,219,219,186,219,219,201,205,205,219,219,187,219,219,186,32,32,32,219,219,186,
		200,219,219,219,219,219,219,187,200,219,219,219,219,219,219,201,188,32,32,32,32,32,200,219,219,219,219,219,219,187,219,219,186,32,32,219,219,186,219,219,186,32,32,219,219,186,200,219,219,219,219,219,219,201,188,
		32,200,205,205,205,205,205,188,32,200,205,205,205,205,205,188,32,32,32,32,32,32,32,200,205,205,205,205,205,188,200,205,188,32,32,200,205,188,200,205,188,32,32,200,205,188,32,200,205,205,205,205,205,188,32 };
	int top = 2;
	int num_lines = 9;
	int num_chars = 55;
	for (int i = 0; i < num_lines; i++)
	{
		int left = VERTICAL_CENTER - 55/2;
		_Common::gotoXY(left, i + top);
		for (int j = 0; j < num_chars; j++)
			putchar(logo[i*num_chars + j]);
	}
}

void _Menu::printOptionsBoard()
{
	_Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
	int left = VERTICAL_CENTER - BLOCK_WIDTH / 2;
	int top = 20;
	_Common::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < BLOCK_WIDTH - 2; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < NUM_OPTIONS * BLOCK_HEIGHT; i++)
	{
		_Common::gotoXY(left + 1, top + i);
		if (i % BLOCK_HEIGHT != 0)
		{
			putchar(186);
			_Common::gotoXY(left + BLOCK_WIDTH - 1, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < BLOCK_WIDTH - 2; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	_Common::gotoXY(left + 1, top + NUM_OPTIONS * 2);
	putchar(200);
	for (int i = 1; i < BLOCK_WIDTH - 2; i++)
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
		Sleep(1000);
	}
}

void _Menu::fillMenuOptions()
{
	int top = 21;
	int offset = (current_option < 4) ? 0 : 4;

	_Common::setConsoleColor(BRIGHT_WHITE, BLUE);
	for (int i = 0; i < NUM_OPTIONS; i++)
	{
		_Common::gotoXY(VERTICAL_CENTER - (int)options[i+offset].length()/2 , top + i * 2);
		cout << options[i+offset];
	}
}

bool _Menu::Move(bool direction) //0 for up, 1 for down
{
	int top = 21;
	if ((direction == 0 && (current_option == 4 || current_option == 0)) 
		|| (direction == 1 && (current_option == 3 || current_option == 7)))
		return false;
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
		_Common::gotoXY(VERTICAL_CENTER - 10, top + current_option % 4 * 2);
		putchar(32);
		_Common::gotoXY(VERTICAL_CENTER - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		_Common::gotoXY(VERTICAL_CENTER + 10, top + current_option % 4 * 2);
		putchar(32);
		(direction == 1) ? current_option++ : current_option--;
	}
	_Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	_Common::gotoXY(VERTICAL_CENTER - 10, top + current_option % 4 * 2);
	putchar(175);
	_Common::gotoXY(VERTICAL_CENTER - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];
	_Common::gotoXY(VERTICAL_CENTER + 10, top + current_option % 4 * 2);
	putchar(174);
	return true;
}

void _Menu::mainMenu()
{
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_Common::clearConsole();
	printLogo();
	printOptionsBoard();
	current_option = -1;
	fillMenuOptions();
	Move(MOVE_DOWN);
	while(true)
	{
		switch (_Common::getConsoleInput())
		{
		case 2:
			Move(MOVE_UP);
			break;
		case 5:
			Move(MOVE_DOWN);
			break;
		case 6:
			return;
		default:
			break;
			//error sound
		}
	}
}

void _Menu::playMenu()
{
	current_option = 8;
	fillMenuOptions();
	Move(MOVE_DOWN);
	while (true)
	{
		switch (_Common::getConsoleInput())
		{
		case 2:
			Move(MOVE_UP);
			break;
		case 5:
			Move(MOVE_DOWN);
			break;
		case 6:
			return;
		default:
			break;
			//error sound
		}
	}
}

void _Menu::playPvP()
{
	_Game g;
	g.startGame();
}

void _Menu::aboutScreen()
{
	_Common::clearConsole();
	_Common::setConsoleColor(WHITE, BLACK);
	for (int i = 0; i < 23; i++)
	{
		_Common::gotoXY(10, 4 + i);
		for (int j = 0; j < 89; j++)
			putchar(32);
	}
	printSmallButton(49, 23);
	_Common::gotoXY(52, 24);
	cout << "Back";
	_Common::gotoXY(10, 4 + 2);
	cout << "Up:    W, up   arrow\n";
	cout << "Down:  S, down arrow\n";
	cout << "Left:  A, left arrow\n";
	cout << "Right: D, right arrow\n";
	cout << "Rules:\n";
	cout << "The player representing the 'X' symbol gets to take the first turn\nfollowed by the player representing the 'O' symbol.\n";
	cout << "Players take turns placing their symbol on an open intersection on the board.\n";
	cout << "The player that manages to create exactly five in a row first,\nwithout being blocked by another color \nor symbol at either end wins the round.\n";
	cout << "The row can be horizontal, vertical, or diagonal as long as it is unbroken.\n";
	cout << "The player must create five in a row ";
	cout << "More than five symbol in a row do not count (overlines)\n";
	cout << "Teacher: \n";
	cout << "Teaching assistant: \n";
	cout << "Students: \n";
	cin.get();
}

void _Menu::printSmallButton(int left, int top)
{
	_Common::gotoXY(left, top);
	putchar(218);
	for(int i = 0; i < 9; i++)
		putchar(196);
	putchar(191);

	_Common::gotoXY(left, top + 1);
	putchar(179);
	_Common::gotoXY(left + 10, top + 1);
	putchar(179);

	_Common::gotoXY(left, top + 2);
	putchar(192);
	for (int i = 0; i < 9; i++)
		putchar(196);
	putchar(217);
}