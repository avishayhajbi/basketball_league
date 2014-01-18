#include "Game.h"



Game::Game()
{
}
Game::Game(string line)
{
}
//_home,_guest,_date,_round,_game,_finalScoreHOME,_finalScoreGUEST,_halftimeScoreHOME,_halftimeScoreGUEST
Game::Game(string home, string guest,Date* date, int round, int game, int finalScoreHOME, int finalScoreGUEST, int halftimeHOME, int halftimeGUEST)
{
	 _home= home;
	 _guest=guest;
	 _date=date;
	 _round=round;
	 _game=game;
	 _finalScoreHOME=finalScoreHOME;
	 _finalScoreGUEST=finalScoreGUEST;
	 _halftimeScoreHOME=halftimeHOME;
	 _halftimeScoreGUEST=halftimeGUEST;
}

string Game::get_home()
{
	return _home;
}

string Game::get_guest()
{
	return _guest;
}

Date* Game::get_date()
{
	return _date;
}

int Game::get_gameNumber()
{
	return _game;
}
int Game::get_round()
{
	return _round;
}

int Game::get_finalScoreHOME()
{
	return _finalScoreHOME;
}

int Game::get_finalScoreGUEST()
{
	return _finalScoreGUEST;
}

int Game::get_halftimeScoreHOME()
{
	return _halftimeScoreHOME;
}

int Game::get_halftimeScoreGUEST()
{
	return _halftimeScoreGUEST;
}

void Game::set_home(string replace)
{
	_home.replace(0,_home.length(),replace);
}
void Game::set_guest(string replace)
{
	_guest.replace(0,_guest.length(),replace);
}


void Game::set_finalScoreHOME(string replace)
{
	_finalScoreHOME= (atoi(replace.c_str()));
}
void Game::set_finalScoreGUEST(string replace)
{
	_finalScoreGUEST= (atoi (replace.c_str()));
}
void Game::set_date(Date* date)
{
	_date = date;
}
