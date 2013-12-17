#ifndef GAME_H
#define GAME_H
#include <regex>
#include <sstream>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include "Date.h"
using namespace std;

class Game
{
private:
	string _home;

	string _guest;

	Date* _date;

	int _round;
	
	int _game;

	int _finalScoreHOME;

	int _finalScoreGUEST;

	int _halftimeScoreHOME;

	int _halftimeScoreGUEST;


public:
	Game();
	Game(string line);
	Game(Date* date, string home, string guest, int round, int finalScoreHOME, int finalScoreGUEST, int halftimeHOME, int halftimeGUEST, int game);

	string get_home();

	string get_guest();

	Date* get_date();
	
	int get_gameNumber();

	int get_finalScoreHOME();

	int get_finalScoreGUEST();

	int get_halftimeScoreHOME();

	int get_halftimeScoreGUEST();


};
#endif
