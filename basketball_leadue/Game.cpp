#include "Game.h"



Game::Game()
{
}
Game::Game(string line)
{
		//round
		string token = line.substr(0, 1);
		_round = atoi(token.c_str());
		//game
		token = line.substr(2,1);
		_game = atoi(token.c_str());
		//date
		token = line.substr(5,13);
		_date = new Date(token);
		
		//team names and score
		token = line.substr(19, line.length());
		string splited;
		int locationInLine=19;
		for (int i=0 ; i < token.length(); i++)
		{
			string temp = token.substr(i,1);	
			if (token.length()>(i+4) && token.at(i)==' ' && token.at(i+1)=='-' && token.at(i+2)==' ')
			{
				_home=splited;
				locationInLine+=i+3;
				token=line.substr(locationInLine,line.length());
				splited.clear();
				break;
			}
			splited.append(temp);
		}
		for (int i=0 ; i < token.length(); i++)
		{
			string temp = token.substr(i,1);	
			regex integer("(\\+|-)?[[:digit:]]+");
			if (token.length()>(i+4) && regex_match(temp,integer))
			{
				_guest=splited;
				locationInLine+=i;
				token=line.substr(locationInLine,line.length());
				splited.clear();
				break;
			}
			splited.append(temp);
		}
		int tempFound= token.find('-');
		locationInLine+=tempFound+1;
		string temp = token.substr(0, tempFound);
		_finalScoreHOME=atoi(temp.c_str());
		token=line.substr(locationInLine,line.length());

		tempFound= token.find(' ');
		locationInLine+=tempFound+1;
		temp = token.substr(0, tempFound);
		_finalScoreGUEST=atoi(temp.c_str());
		token=line.substr(locationInLine,line.length());

		tempFound= token.find('(');
		locationInLine+=tempFound+1;
		token=line.substr(locationInLine,line.length());

		tempFound= token.find('-');
		locationInLine+=tempFound+1;
		temp = token.substr(0, tempFound);
		_halftimeScoreHOME=atoi(temp.c_str());
		token=line.substr(locationInLine,line.length());
		
		tempFound= token.find(')');
		locationInLine+=tempFound+1;
		temp = token.substr(0, tempFound);
		_halftimeScoreGUEST=atoi(temp.c_str());
		
}
Game::Game(Date* date, string home, string guest, int round, int finalScoreHOME, int finalScoreGUEST, int halftimeHOME, int halftimeGUEST,int game)
{
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

