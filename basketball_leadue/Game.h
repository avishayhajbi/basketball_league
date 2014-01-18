#ifndef GAME_H
#define GAME_H
#include <sstream>
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
	Game(string home, string guest,Date* date, int round, int game, int finalScoreHOME, int finalScoreGUEST, int halftimeHOME, int halftimeGUEST);
	string get_home();
	string get_guest();
	Date* get_date();	
	int get_gameNumber();
	int get_round();
	int get_finalScoreHOME();
	int get_finalScoreGUEST();
	int get_halftimeScoreHOME();
	int get_halftimeScoreGUEST();

	void set_home(string replace);
	void set_guest(string replace);
	void set_finalScoreHOME(string replace);
	void set_finalScoreGUEST(string replace);
	void set_date(Date* date);

};
#endif
