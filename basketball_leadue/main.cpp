#include "LeagueMaker.h"


int main(int argc, char* argv[])
{

	LeagueMaker* league = new LeagueMaker();
	league->create_basketball_league();
	league->create_NBA_league();
	league->create_soccer_league();
	league->start( argc,  argv);

	return 0;
}
