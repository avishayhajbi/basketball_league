#include "Basketball_league.h"

Date* checkDate(string data)
{
	/*to hold date values*/

	/*char* day;*/  
	/*char* month;*/
	/*char* year;*/
	char* context = NULL;
	const char* dataCstr = data.c_str();
	char* lastTokenInData;
	char* tokenDataArr[20]; //hold inpyt tokens
	int tokenDataArrIndex = 0;
	/*bool isDateValidDate; /* if date validation is needed */

	char* dataCharPointer = new char[data.length() + 1];  /*allocate memory to char** array*/

	strcpy_s(dataCharPointer,data.length() + 1,dataCstr); /*copy string values by pointers to array*/
	lastTokenInData = strtok_s (dataCharPointer," .,/", &context); /*delimiters*/

	while (lastTokenInData != NULL) /*as long as line containes tokens*/
	{
		tokenDataArr[tokenDataArrIndex] = lastTokenInData; /*parsed token is copy to the array*/
		lastTokenInData = strtok_s (NULL," .,/",&context);

		tokenDataArrIndex++;
	}

	//printf ("day = %s\nmonth = %s\nyear = %s\n",tokenDataArr[0],tokenDataArr[1],tokenDataArr[2]); /* can show up to 20 tokens dependes on input*/
	//string s = "";
	//s.append(tokenDataArr[0]);s.append(".");s.append(tokenDataArr[1]);s.append(",");s.append(tokenDataArr[2]);
	Date* date;
	if (atoi(tokenDataArr[0])>12)
		date = new Date(tokenDataArr[0],tokenDataArr[1],tokenDataArr[2]);
	else  date = new Date(tokenDataArr[1],tokenDataArr[0],tokenDataArr[2]);
	delete [] dataCharPointer;
	//return s;
	return date;

}

Basketball_league::Basketball_league()
{
	int _isOpen=1;
	_game= vector<Game*> ();
	_game.begin();
	_team= vector<Team*> ();

	_dateBase = new DataBase();
}

void Basketball_league::start(int argc, char* argv[])
{
	readFromFile();
	string str="";
	bool loop=1; // starts with 1 value
	while (loop)
	{
		if (argc>1)
		{
			argc=0;
			readUserFileAction(argc,argv);
		}

		//getting the next action/request
		getline(cin,str);

		/*all the matches will be without spaces and with lower case*/
		str.erase( std::remove(str.begin(),str.end(),' '), str.end() );
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		// statments
		if (str.compare("showleague")==0)
		{
			printLeagueTabel();
		}
		//compare between dates

		if (str.find(".")!= std::string::npos || str.find(",")!= std::string::npos || str.find("/")!= std::string::npos)
		{
			//finally check if the input is date 
			Date* date = (checkDate(str));	
			for (int i=0; i< _game.size(); i++)
			{
				Date* d = _game[i]->get_date();
				if (*d==*date)
				{
					cout<<_game[i]->get_home()<<" - "<<_game[i]->get_guest()<<" "<<_game[i]->get_finalScoreHOME()<<"-"<<_game[i]->get_finalScoreGUEST()<<" ("<<_game[i]->get_halftimeScoreHOME()<<"-"<<_game[i]->get_halftimeScoreGUEST()<<")"<<endl;
				}
			}	

		}
		if (str.compare("admin"))
		{
			if (str.compare("addgame")==0)
			{
				if(_isOpen ==1 ) 
					writeToFile("END");
				_isOpen=0;
				string newGame;
				getline(cin,newGame);
				//check game input
			}
			if (str.compare("addteam")==0)
			{
				if(_isOpen==1)
				{
					//cout<<"insert team name"<<endl;
					string newTeam;
					getline(cin,newTeam);
					//adding new team to the data base
					writeToFile(newTeam);
				}
				else
				{
					cout<<"can not add team name because the league is already start"<<endl;
				}
			}
			if (str.compare("updateteamname")==0)
			{
				if(_isOpen==1)
				{
					//cout<<"insert 'old and new' team name"<<endl;
					string oldTeam;
					getline(cin,oldTeam);
					string newTeam;
					getline(cin,newTeam);
					//update team name into the data base
					replace_line_in_file(oldTeam , newTeam);
				}
				else
				{
					cout<<"can not update team name because the league is already start"<<endl;
				}
			}
		}

		if (str.compare("exit")==0)
		{
			_dateBase->get_file().close();
			loop=0;
		}
		cout<<endl;
	}		
}

void Basketball_league::set_isOpen(int num)
{
	_isOpen = num;
}

int Basketball_league::get_isOpen()
{
	return _isOpen;
}

vector<Team*> Basketball_league::get_teams()
{
	return get_teams();
}

vector<Game*> Basketball_league::get_games()
{
	return get_games();
}

void Basketball_league::readFromFile()
{
	/*
	this function reads league schedule from file
	*/
	string line;
	if (_dateBase->get_file().is_open())
	{
		while ( getline (_dateBase->get_file(),line) )
		{
			if (line == "TEAM")
			{
				while (getline (_dateBase->get_file(),line))
				{
					if (line == "END") break;
					_team.push_back(new Team(line));
				}
			}
			if (line == "START")
			{
				_isOpen=0;
				while ( getline (_dateBase->get_file(), line))
				{
					if (line == "END") break;
					_game.push_back(new Game(line));
					interpretGamesToTeamsStatus(_game.at(_game.size()-1));
				}
			}
		}
	}
	_dateBase->get_file().clear();
	_dateBase->get_file().seekg(0, _dateBase->get_file().beg);


}

void Basketball_league::writeToFile(string line)
{
	/*
	write the data into the data base file 
	*/
	_dateBase->get_file()<<line<<endl;
}

void Basketball_league::interpretGamesToTeamsStatus(Game* game)
{
	/*
	interpret game score to teame status 
	*/
	for (int i=0 ; i<_team.size(); i++)
	{
		if (game->get_home().compare(_team[i]->get_teamName())==0)
		{
			/*
			home team
			update team status
			*/
			_team[i]->increment_gameCounter(1);
			_team[i]->set_fail(game->get_finalScoreGUEST());
			_team[i]->set_success(game->get_finalScoreHOME());
			if (game->get_finalScoreHOME()>game->get_finalScoreGUEST())
				_team[i]->increment_leaguePoints(2);
			else _team[i]->increment_leaguePoints(1);
		}
		if (game->get_guest().compare(_team[i]->get_teamName())==0)
		{
			/*
			guest team
			update team status
			*/
			_team[i]->increment_gameCounter(1);
			_team[i]->set_fail(game->get_finalScoreHOME());
			_team[i]->set_success(game->get_finalScoreGUEST());
			if (game->get_finalScoreHOME()<game->get_finalScoreGUEST())
				_team[i]->increment_leaguePoints(2);
			else _team[i]->increment_leaguePoints(1);
		}
	}

	sortTable();

}

DataBase* Basketball_league::get_dataBase()
{
	return _dateBase;
}

/*template table format*/
template<typename T> void printElement(T t, const int& width)
{
	const char separator    = ' ';
	cout << left << setw(width) << setfill(separator) << t;
}
/*end template table format*/

void Basketball_league::printLeagueTabel()
{
	int length=0;
	// taking the longest team name
	for (int i=0;i<_team.size(); i++)
	{
		if(_team[i]->get_teamName().length() > length)
		{
			length = _team[i]->get_teamName().length();
		}
	}
	/* another sort template
	char buf[1000];
	char pattern[]  = "%00s %15s %10s %10s %10s";
	sprintf_s(buf, pattern, "team name" ,  "game", "points" ,"total" , "score" );
	cout << buf << endl;

	cout << left << setw(nameWidth) << setfill(separator) << "Bob";
	printElement(_team[i]->get_teamName(), nameWidth);
	char buf[1000];
	*/

	for (int i=0;i<_team.size(); i++)
	{
		if (i==0)
		{
			cout << setw(length+2) << left << "Team Name ";
			cout << setw(7) << left << "Games ";
			cout << setw(7) << left << "Points " ;
			cout << setw(7) << left << "Total ";
			cout << setw(7) << left << "Score " <<endl;
			cout << "---------------------------------------------"<<endl;
		}
		cout<< setw(length+4) << left << _team[i]->get_teamName();
		cout<< setw(7)<< left << _team[i]->get_gameConter();
		cout<< setw(6)<< left << _team[i]->get_leaguePoints();
		cout<< setw(7)<< left << _team[i]->get_fail();
		cout<< setw(6)<< left << _team[i]->get_success()<<endl;
	}
	cout << "---------------------------------------------"<<endl;
}

/* start sort function */
bool your_comparer( Team* left,  Team* right)
{
	// return true if left should come before right, false otherwise
	if (left->get_leaguePoints() > right->get_leaguePoints())
		return true;
	else if (left->get_leaguePoints() == right->get_leaguePoints())
	{
		if (left->get_success() > right->get_success())
			return true;
		else return false;
	}
	else return false;
}
/* end sort function */

void Basketball_league::sortTable ()
{
	sort (_team.begin(), _team.end(), your_comparer);
}

void Basketball_league::readUserFileAction(int argc,char* argv[])
{
	ifstream userfile;
	userfile.open (argv[1], ios::in | ios::out | ios::app);
	string str="";

	while ( getline (userfile,str) )
	{
		str.erase( std::remove(str.begin(),str.end(),' '), str.end() );
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		//if then else like the function above
		// statments
		if (str.compare("showleague")==0)
		{
			printLeagueTabel();
		}
		//compare between dates

		if (str.find(".")!= std::string::npos || str.find(",")!= std::string::npos || str.find("/")!= std::string::npos)
		{
			//finally check if the input is date 
			Date* date = (checkDate(str));	
			for (int i=0; i< _game.size(); i++)
			{
				Date* d = _game[i]->get_date();
				if (*d==*date)
				{
					cout<<_game[i]->get_home()<<" - "<<_game[i]->get_guest()<<" "<<_game[i]->get_finalScoreHOME()<<"-"<<_game[i]->get_finalScoreGUEST()<<" ("<<_game[i]->get_halftimeScoreHOME()<<"-"<<_game[i]->get_halftimeScoreGUEST()<<")"<<endl;
				}
			}	

		}
		if (str.compare("admin"))
		{
			if (str.compare("addgame")==0)
			{
				if(_isOpen ==1 ) 
					writeToFile("END");
				_isOpen=0;
				string newGame;
				getline(cin,newGame);
				//check game input
			}
			if (str.compare("addteam")==0)
			{
				if(_isOpen==1)
				{
					//cout<<"insert team name"<<endl;
					string newTeam;
					getline(cin,newTeam);
					//adding new team to the data base
					writeToFile(newTeam);
				}
				else
				{
					cout<<"can not add team name because the league is already start"<<endl;
				}
			}
			if (str.compare("updateteamname")==0)
			{
				if(_isOpen==1)
				{
					//cout<<"insert 'old and new' team name"<<endl;
					string oldTeam;
					getline(cin,oldTeam);
					string newTeam;
					getline(cin,newTeam);
					//update team name into the data base
					replace_line_in_file(oldTeam , newTeam);
				}
				else
				{
					cout<<"can not update team name because the league is already start"<<endl;
				}
			}
		}

		if (str.compare("exit")==0)
		{
			_dateBase->get_file().close();
		}
		cout<<endl;
	}
}

void Basketball_league::replace_line_in_file(string search_string , string replace_string)
{

	string inbuf;
	vector<string> vec;
	_dateBase->get_file().clear();
	_dateBase->get_file().seekg(0, _dateBase->get_file().beg);
	while (getline(_dateBase->get_file(), inbuf))
	{
		if(inbuf.compare(search_string)==0)
			vec.push_back(replace_string);
		else vec.push_back(inbuf);
	}

	_dateBase->get_file().close();
	system("DEL /F basketball2013.txt");
	_dateBase = new DataBase();

	for(int i =0; i<vec.size();i++)
	{
		writeToFile(vec[i]);
	}
}