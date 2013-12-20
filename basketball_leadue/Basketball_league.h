#ifndef BASKETBALL_LEAGUE_H
#define BASKETBALL_LEAGUE_H

#include <algorithm> // std::sort
#include <iomanip> // std::format table
#include <locale> // for substring
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdio.h>
#include "DataBase.h"

using namespace std;

#include "League.h"
#include "Game.h"
#include "Team.h"



class Basketball_league : public League
{
private:
	int _isOpen;
	vector<Game*> _game;
	vector<Team*> _team;
	DataBase* _dateBase;
public:
	Basketball_league();
	void set_isOpen(int num);
	int get_isOpen();
	DataBase* get_dataBase();
	vector<Team*> get_teams();
	vector<Game*> get_games();
	void readFromFile();
	void writeToFileinTheEnd(string line);
	void writeToFileinTheMiddel(string line);
	void interpretGamesToTeamsStatus(Game* game);
	void start(int argc, char* argv[]);
	void printLeagueTabel();
	void sortTable();
	void readUserFileAction(int argc,char* argv[]);
	void replace_line_in_file(string search_string , string replace_string);
	string addGame (string line);
	string getGameDetails(int i);
	string getFullGameDetails(int i);
};
#endif
