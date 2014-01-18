#ifndef LEAGUE_MAKER_H
#define LEAGUE_MAKER_H


#include "Basketball_league.h"
#include "NBA_league.h"
#include "Soccer_league.h"

class LeagueMaker
{
private:
	Basketball_league* _basketball_league;
	NBA_league* _nba_league;
	Soccer_league* _soccer_league;

public:
	LeagueMaker();
	Basketball_league* get_basketball_league();
	NBA_league* get_NBA_league();
	Soccer_league* get_soccer_league();
	void create_basketball_league();
	void create_NBA_league();
	void create_soccer_league();
	void exit_and_delete_data();
	void start(int argc, char* argv[]);
};
#endif
