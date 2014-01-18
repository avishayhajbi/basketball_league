#ifndef BASKETBALL_LEAGUE_H
#define BASKETBALL_LEAGUE_H

#include "DataBase.h"
#include "League.h"

using namespace std;

class Basketball_league : public League
{
private:
	int _isOpen;
	vector<Game*> _game;
	vector<Team*> _team;
	DataBase* _dateBase;
	enum Months { Jan=1, Feb=2, Mar=3, Apr=4, May=5, Jun=6, Jul=7, Aug=8, Sep=9, Oct=10, Nov=11, Dec=12 };

public:
	Basketball_league();
	void set_isOpen(int num);
	int get_isOpen();
	DataBase* get_dataBase();
	vector<Team*> get_teams();
	vector<Game*> get_games();
	void start(string str);
	void readUserFileAction(char* argv,char* dbS , char* outputS);
	void writeToOUTPUTfile (string line, fstream& file);
	void writeToFileinTheMiddel(string line, fstream& file);
	void printLeagueTabel(vector<Team*>_team);
	void sortTable(vector<Team*>_team);
	void interpretGamesToTeamsStatus(vector<Team*>_team ,Game* game);
	string getFullGameDetails(Game * game);
	string getGameDetails(int i,vector<Game*>_game);
	string getFullGameDetails(int i,vector<Game*>_game);
	void removeLine(string line , fstream& file);
	void updateGameDetails(string home,string guest, string score,fstream& file,vector<Team*>_team , vector<Game*>_game);
	void updateGame(string gameNumber,string date, fstream& file,vector<Team*>_team,vector<Game*>_game);
	void addGame (string line,fstream&file, vector<Game*>_game);
	void replace_line_in_file(string search_string , string replace_string,fstream& file,vector<Team*>& _team , vector<Game*> &_game);
	void readFromFile(fstream& file , vector<Team*>& _team , vector<Game*>& _game ,int &_isOpen);
	void writeToFileinTheEnd(string line, fstream& file);
	Date* checkDate(string data);
};



#endif
