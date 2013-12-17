

#include "Team.h"


Team::Team()
{
	_teameName = "";
	_gameCounter=0;
	_leaguePoints=0;
	_success=0;
	_fail=0;
}

Team::Team(string name)
{
	_teameName = name;
	_gameCounter=0;
	_leaguePoints=0;
	_success=0;
	_fail=0;
}

Team::Team(int gameCounter, int leagePoint, int success, int fail, string teamNamr)
{
}

int Team::get_gameConter()
{
	return _gameCounter;
}

void Team::increment_gameCounter(int num)
{
	_gameCounter += num;
}

int Team::get_leaguePoints()
{
	return _leaguePoints;
}

void Team::increment_leaguePoints(int num)
{
	_leaguePoints += num;
}

int Team::get_success()
{
	return _success;
}

void Team::set_success(int num)
{
	_success += num;
}

int Team::get_fail()
{
	return _fail;
}

void Team::set_fail(int num)
{
	_fail += num;
}

string Team::get_teamName()
{
	return _teameName;
}
