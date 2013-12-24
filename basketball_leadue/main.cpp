#include "LeagueMaker.h"


int main(int argc, char* argv[])
{

	LeagueMaker* league = new LeagueMaker();
	league->create_basketball_league();
	league->get_basketball_league()->start( argc,  argv);

	system("PAUSE");
	return 0;
}