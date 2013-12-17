#include "LeagueMaker.h"

LeagueMaker::LeagueMaker()
{
	_basketball_league= NULL;

	
}

void LeagueMaker::create_basketball_league()
{
	_basketball_league = new Basketball_league();
}

void LeagueMaker::exit_and_delete_data()
{
}
Basketball_league* LeagueMaker::get_basketball_league()
{
	return _basketball_league;
}
