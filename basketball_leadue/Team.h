#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
using namespace std;
class Team
{
private:
	int _gameCounter;

	int _leaguePoints;

	int _success;

	int _fail;

	string _teameName;


public:
	Team();

	Team(string name);

	Team(int gameCounter, int leagePoint, int success, int fail, string teamName);

	int get_gameConter();

	void increment_gameCounter(int num);

	int get_leaguePoints();

	void increment_leaguePoints(int num);

	int get_success();

	void set_success(int num);

	int get_fail();

	void set_fail(int num);

	string get_teamName();

};
#endif
