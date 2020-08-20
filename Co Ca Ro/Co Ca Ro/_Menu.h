#pragma once
#include "_Common.h"
#include "_Game.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <thread>
#define VERTICAL_CENTER 54
#define NUM_OPTIONS 4
#define BLOCK_WIDTH 14
#define BLOCK_HEIGHT 2
#define MOVE_UP 0
#define MOVE_DOWN 1

using namespace std;

class _Menu
{
private:
	static int current_option;
	const static string options[8];
	static bool is_continue;
public:
	static void mainScreen();
	static void mainMenu();
	static void playMenu();
	static void loadScreen() {}
	static void aboutScreen();
	static void exitScreen() {}
	static void playPvP();
	static void printLogo();
	static void goBack() { return; };
	static void printOptionsBoard();
	static void fillMenuOptions();
	static void printAnimation();
	static void printSmallButton(int, int);
	static bool Move(bool);
};