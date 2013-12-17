#ifndef LEAGUE_MAKER_H
#define LEAGUE_MAKER_H


#include "Basketball_league.h"


class LeagueMaker
{
private:
	Basketball_league* _basketball_league;

public:
	LeagueMaker();

	Basketball_league* get_basketball_league();

	void create_basketball_league();

	void exit_and_delete_data();

};
#endif
