#pragma once
#include "_Common.h"
#include "_Game.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <filesystem>
using namespace std;

class _Menu
{
private:
	static bool exitGame;
	static int current_option;
	const static string options[8];
public:
	static void mainScreen();
	static void mainMenu();
	static void playMenu();
	static void loadScreen();
	static void helpScreen();
	static void exitScreen();
	static void playPvP();
	static void playPvC1() {};
	static void playPvC2();
	static void printLogo();
	static void goBack() { return; }
	static void printOptionsBoard();
	static void fillMenuOptions();
	static void printAnimation();
	static void printRectangle(int, int, int, int);
	static void changeOption(bool);
	static void changeFile(int, vector<string>& fileName, int&);
};