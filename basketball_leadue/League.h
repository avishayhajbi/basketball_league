#ifndef LEAGUE_H
#define LEAGUE_H
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

#include <algorithm> // std::sort
#include <iomanip> // std::format table
#include <locale> // for substring
#include <time.h>  /* time_t, time, ctime */

#include "Game.h"
#include "Team.h"
#include "Date.h"
using namespace std;

class League
{
public:
	virtual Date* checkDate(string data);
	virtual void interpretGamesToTeamsStatus(vector<Team*>_team ,Game* game);
	virtual void readFromFile(fstream& file , vector<Team*> &_team , vector<Game*> &_game,int &_isOpen);
	virtual void writeToFileinTheMiddel(string line, fstream& file);
	virtual void writeToOUTPUTfile (string line, fstream& file);
	virtual void writeToFileinTheEnd(string line , fstream& file);
	virtual void replace_line_in_file(string search_string , string replace_string,fstream& file,vector<Team*>& _team , vector<Game*> &_game);
	virtual void addGame (string line,fstream&file, vector<Game*>_game);
	virtual void updateGameDetails(string home,string guest, string score,fstream& file,vector<Team*>_team , vector<Game*>_game);
	virtual void updateGame(string gameNumber,string date, fstream& file,vector<Team*>_team,vector<Game*>_game);
	virtual void removeLine(string line , fstream& file);
	virtual void printLeagueTabel(vector<Team*>_team);
	virtual void sortTable(vector<Team*>_team);
	virtual string getFullGameDetails(Game * game);
	virtual string getGameDetails(int i,vector<Game*>_game);
	virtual string getFullGameDetails(int i,vector<Game*>_game);
};
#endif
