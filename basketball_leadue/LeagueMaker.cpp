#include "LeagueMaker.h"

LeagueMaker::LeagueMaker()
{
	_basketball_league= NULL;
	_nba_league = NULL;
	_soccer_league=NULL;
	
}

void LeagueMaker::create_basketball_league()
{
	_basketball_league = new Basketball_league();
}
void LeagueMaker::create_NBA_league()
{
	_nba_league = new NBA_league();
}
void LeagueMaker::create_soccer_league()
{
	_soccer_league = new Soccer_league();
}
void LeagueMaker::exit_and_delete_data(){}
Basketball_league* LeagueMaker::get_basketball_league()
{
	return _basketball_league;
}
NBA_league* LeagueMaker::get_NBA_league()
{
	return _nba_league;
}
Soccer_league* LeagueMaker::get_soccer_league()
{
	return _soccer_league;
}
void LeagueMaker::start(int argc , char* argv[])
{
	if (argc > 1)
    {
	
			char *Bdb,*Buser,*Boutput;
			char *Sdb,*Suser,*Soutput;
			char *Ndb,*Nuser,*Noutput;
			Bdb = new char();
			Buser = new char();
			Boutput = new char();
			Sdb = new char();
			Suser = new char();
			Soutput = new char();
			Ndb = new char();
			Nuser = new char();
			Noutput = new char();
			string s="";
			for (int i=0; i < argc ; i++)
			{
				// read  user files
				s = argv[i];
				if (s.compare("-db")==0)
				{
					s = argv[i+1];
					if (s.substr(s.length()-1,s.length()).compare("1")==0)
					Bdb= argv[i];
					if (s.substr(s.length()-1,s.length()).compare("2")==0)
					Ndb= argv[i];
					if (s.substr(s.length()-1,s.length()).compare("3")==0)
					Sdb= argv[i];
				}
				if (s.compare("-i")==0)
				{
					s = argv[i+1];
					if (s.substr(s.length()-1,s.length()).compare("1")==0)
					std::strcpy(Buser, argv[i]);
					if (s.substr(s.length()-1,s.length()).compare("2")==0)
					std::strcpy(Nuser, argv[i]);
					if (s.substr(s.length()-1,s.length()).compare("3")==0)
					std::strcpy(Suser, argv[i]);
				}
				if (s.compare("-o")==0)
				{
					s = argv[i+1];
					if (s.substr(s.length()-1,s.length()).compare("1")==0)
					std::strcpy(Boutput, argv[i]);
					if (s.substr(s.length()-1,s.length()).compare("2")==0)
					std::strcpy(Noutput, argv[i]);
					if (s.substr(s.length()-1,s.length()).compare("3")==0)
					std::strcpy(Soutput, argv[i]);
				}
				s.clear();
			}
			get_basketball_league()->readUserFileAction(Buser,Bdb,Boutput);
			get_NBA_league()->readUserFileAction(Nuser,Ndb,Noutput);
			get_soccer_league()->readUserFileAction(Suser,Sdb,Soutput);
	}

		//get input from the user
		string str="";
		while (true)
		{
			getline(cin,str);
			while(!str.substr(0,1).compare(" "))
					str=str.substr(1,str.length());
			if (str.substr(0,1).compare("1")==0)
			{
				get_basketball_league()->start(str.substr(1,str.length()));
			}
			if (str.substr(0,1).compare("2")==0)
			{
				get_NBA_league()->start(str.substr(1,str.length()));
			}
			if (str.substr(0,1).compare("3")==0)
			{
				get_soccer_league()->start(str.substr(1,str.length()));
			}
			if (str.substr(0,1).compare("0")==0 || str.compare("exit")==0)
			{
				get_basketball_league()->get_dataBase()->get_file().close();
				get_NBA_league()->get_dataBase()->get_file().close();
				get_soccer_league()->get_dataBase()->get_file().close();
				return;
			}
			str.clear();
		}
    
}
