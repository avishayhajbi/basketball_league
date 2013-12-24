#ifndef BASKETBALL_LEAGUE_H
#define BASKETBALL_LEAGUE_H
#define _CRT_SECURE_NO_WARNINGS

#include <algorithm> // std::sort
#include <iomanip> // std::format table
#include <locale> // for substring
#include <stdio.h>
#include <time.h>  /* time_t, time, ctime */
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
	void writeToOUTPUTfile (string line);
	void writeToFileinTheMiddel(string line);
	void interpretGamesToTeamsStatus(Game* game);
	void start(int argc, char* argv[]);
	void printLeagueTabel();
	void sortTable();
	void readUserFileAction(int argc,char* argv[]);
	void replace_line_in_file(string search_string , string replace_string);
	void addGame (string line);
	void updateGameDetails(string home,string guest, string score);
	void updateGame(string gameNumber,string date);
	string getGameDetails(int i);
	string getFullGameDetails(int i);
	string getFullGameDetails(Game * game);
	void removeLine(string line);
};



#endif
