﻿#include "_Menu.h"
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
	_Common::playSound(8);
	printAnimation();
	bool loadMenu = 1;
	while (true)
	{
		if(loadMenu)
			mainMenu();
		switch(_Common::getConsoleInput())
		{
		case 2:
			changeOption(0,1);
			loadMenu = 0;
			break;
		case 5:
			changeOption(1,1);
			loadMenu = 0;
			break;
		case 6:
			if (current_option == 0)
				loadMenu = 0;
			else
				loadMenu = 1;
			function_map[options[current_option]]();
			break;
		default:
			_Common::playSound(4);
			loadMenu = 0;
		}
	}

	_Common::clearConsole();
}

void _Menu::printLogo()
{
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
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
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
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_Common::clearConsole();
	char symbolpos[] = { 5,0,19,0,33,0,47,0,61,0,75,0,89,0,103,0,12,6,96,6,5,12,19,
				               12,33,12,47,12,61,12,75,12,89,12,103,12,12,18,26,18,40,18,
		                       54,18,68,18,82,18,96,18,5,24,19,24,33,24,47,24,61,24,75,24,
		                       89,24,103,24,12,30,26,30,40,30,54,30,68,30,82,30,96,30 };
	int n = (sizeof(symbolpos) / sizeof(symbolpos[0]))/2;
	bool turn = 0; 
	unsigned char symbol[] = { 79,88 };

	unsigned char C[] = { 32,219,219,219,219,219,219,187,219,219,201,205,205,205,205,188,219,219,186,32,32,32,32,32,
						  219,219,186,32,32,32,32,32,200,219,219,219,219,219,219,187,32,200,205,205,205,205,205,188 };
	unsigned char O[] = { 32,219,219,219,219,219,219,187,32,219,219,201,205,205,205,219,219,187,219,219,186,32,32,32,219,219,186,
						  219,219,186,32,32,32,219,219,186,200,219,219,219,219,219,219,201,188,32,200,205,205,205,205,205,188,32 };
	unsigned char A[] = { 32,219,219,219,219,219,187,32,219,219,201,205,205,219,219,187,219,219,219,219,219,219,219,186,
						  219,219,201,205,205,219,219,186,219,219,186,32,32,219,219,186,200,205,188,32,32,200,205,188 };
	unsigned char R[] = { 219,219,219,219,219,219,187,32,219,219,201,205,205,219,219,187,219,219,219,219,219,219,201,188,
						  219,219,201,205,205,219,219,187,219,219,186,32,32,219,219,186,200,205,188,32,32,200,205,188 };
	unsigned char* word[] = { C,O,C,A,R,O };
	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };
	int wide[] = { 8,9,8,8,8,9 }; int left[] = { 27, 35, 49, 57, 65, 73 };
	int colorcount = 0;
	int loop = 11;
	while (loop--)
	{
		for (int i = 0; i < n; i += 2)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, getRandomInt(0,15));
			_Common::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
			putchar(symbol[turn]);
		}
		for (int i = 1; i < n; i += 2)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, getRandomInt(0, 15));
			_Common::gotoXY(symbolpos[i * 2], symbolpos[i * 2 + 1]);
			putchar(symbol[!turn]);
		}
		for (int i = 0; i < 6; i++)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, color[colorcount % 6]);
			for (int j = 0; j < 6; j++)
			{
				_Common::gotoXY(left[i], 4 + j);
				for (int k = 0; k < wide[i]; k++)
					putchar(word[i][j * wide[i] + k]);
			}
			Sleep(50);
		}
		colorcount++;
		turn = !turn;
		Sleep(250);
	}
}

void _Menu::changeOption(bool direction, bool flag) //0: lên, 1: xuống
{
	int top = 21;
	if ((direction == 0 && (current_option == 4 || current_option == 0))
		|| (direction == 1 && (current_option == 3 || current_option == 7)))
	{
		_Common::playSound(4);
		return;
	}
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	_Common::gotoXY(54 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
	cout << options[current_option];
	if (flag)
	{
		_Common::gotoXY(44, top + current_option % 4 * 2);
		putchar(32);
		_Common::gotoXY(64, top + current_option % 4 * 2);
		putchar(32);
	}
	(direction == 1) ? current_option++ : current_option--;
	if(flag)
	{
		_Common::playSound(2);
		_Common::setConsoleColor(BRIGHT_WHITE, RED);
		_Common::gotoXY(44, top + current_option % 4 * 2);
		putchar(175);
		_Common::gotoXY(54 - (int)options[current_option].length() / 2, top + current_option % 4 * 2);
		cout << options[current_option];
		_Common::gotoXY(64, top + current_option % 4 * 2);
		putchar(174);
	}
}

void _Menu::mainMenu()
{
	_Common::setConsoleColor(BRIGHT_WHITE, RED);
	_Common::clearConsole();
	printLogo();
	printOptionsBoard();
	current_option = 3;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void _Menu::playMenu()
{
	current_option = 7;
	changeOption(0, 0);
	changeOption(0, 0);
	changeOption(0, 1);
}

void _Menu::playPvP()
{
	_Game g;
	g.setUpGame(0);
	g.startGame();
}

void _Menu::helpScreen()
{
	_Common::showCursor(false);
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

	_Common::setConsoleColor(BRIGHT_WHITE, RED);
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

	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(49, 27, 8, 2);
	_Common::setConsoleColor(BRIGHT_WHITE, RED);
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
	_Common::showCursor(false);
	_Common::clearConsole();
	_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	printRectangle(36, 18, 35, 8);
	printRectangle(39, 23, 7, 2);
	printRectangle(62, 23, 6, 2);
	_Common::setConsoleColor(BRIGHT_WHITE, RED);
	printLogo();
	_Common::gotoXY(44, 20);
	cout << "Do you want to exit?";
	string str[2] = { "Yes", "No" };
	int left[] = { 37,42,49,60,65,71 }, word[] = { 32,32,175,174 }, color[] = { BLACK, RED }, top = 24;
	bool choice = 0;
	bool loop = 1;
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
			if(!i++)
				choice = !choice;
		}
	};
	print1();
	while (loop)
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
				_Common::clearConsole();
				exit(0);
			}
			return;
		}
		else
		{
			_Common::playSound(4);
		}
	}
}

void _Menu::playPvC1()
{
	_Game g;
	g.setUpGame(1);
	g.startGame();
}

void _Menu::playPvC2()
{
	_Game g;
	g.setUpGame(2);
	g.startGame();
}

void _Menu::loadScreen() 
{
	_Common::clearConsole();
	vector<string> fileName;
	for (auto& p : filesystem::recursive_directory_iterator("load"))
	{
		if (p.path().extension() == ".txt")
		{ 
			string temp = p.path().filename().string();
			temp.erase(temp.find_last_of('.'));
			fileName.push_back(temp);
		}
	}
	if (!fileName.size())
	{
		_Common::gotoXY(42, 15);
		cout << "No game files were found!";
		Sleep(3000);
		return;
	}
	int file = 8;
	changeFile(3, fileName, file);
	bool chosen = 0;
	while (!chosen)
	{
		int key = _Common::getConsoleInput();
		if (key == 6)
		{
			_Game g;
			g.setUpGame(3, fileName[file]);
			g.startGame();
			chosen = 1;
		}
		else if (key > 1 && key < 6)
		{
			changeFile(key, fileName, file);
		}
		else if (key == 1)
		{
			chosen = 1;
		}
		else
		{
			_Common::playSound(4);
		}
	}
}

void _Menu::changeFile(int key, vector<string>& fileName, int& file)
{
	if (key == 3 || key == 4)
	{
		if (key == 3 && file > 7)
		{
			_Common::playSound(2);
			file = (file / 8 - 1) * 8;
		}
		else if (key == 4 && file/8 < fileName.size()/8)
		{
			file = (file / 8 + 1) * 8;
		}
		else
		{
			_Common::playSound(4);
			return;
		}
		_Common::playSound(2);
		_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
		int i = 0;
		for (i = file + 1; i < file + 8; i++)
		{
			_Common::gotoXY(0, 9 + i % 8 * 2);
			for (int j = 0; j < 107; j++)
				putchar(32);
			if (i < fileName.size())
			{
				_Common::gotoXY(54 - fileName[i].find('-'), 9 + i % 8 * 2);
				cout << fileName[i];
			}
		}
		_Common::gotoXY(15, 16);
		(file - 8 < 0) ? putchar(32) : putchar(60);
		_Common::gotoXY(93, 16);
		(file + 8 >= fileName.size()) ? putchar(32) : putchar(62);
		_Common::setConsoleColor(BRIGHT_WHITE, RED);
		_Common::gotoXY(0, 9);
		for (int j = 0; j < 107; j++)
			putchar(32);
		_Common::gotoXY(54 - fileName[file].find('-'), 9);
		cout << fileName[file];
	}
	else if (key == 2 || key == 5)
	{
		if (key == 2 && file % 8 > 0) 
		{
			_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
			_Common::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
			cout << fileName[file];
			file--;
		}
		else if (key == 5 && file % 8 < 7 && file < fileName.size() - 1)
		{
			_Common::setConsoleColor(BRIGHT_WHITE, BLACK);
			_Common::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
			cout << fileName[file];
			file++;
		}
		else
		{
			_Common::playSound(4);
			return;
		}
		_Common::setConsoleColor(BRIGHT_WHITE, RED);
		_Common::gotoXY(54 - fileName[file].find('-'), 9 + file % 8 * 2);
		cout << fileName[file];
	}
}