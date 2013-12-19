#include "Basketball_league.h"
/*צריך לבדוק מצב אם הקובץ קיים או לא כדי לדעת אם לתת לו כתיבה ראשונית של כותרות או לא*/
/*בכל מחזור יש משחק אחד לכל קבוצה אם קבוצהלא שיחקה אז לא קרהכלו ולא מוסיפים אותה*/

//check if the date is valid or not
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
	tokenDataArr[2]="";
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
	else  
	{
		if (strcmp(tokenDataArr[0],"0")==0)
			tokenDataArr[0]="NONE";
		date = new Date(tokenDataArr[1],tokenDataArr[0],tokenDataArr[2]);
	}

	delete [] dataCharPointer;
	//return s;
	return date;

}


//the 2 function below are for compare thats another way to compare between 2 strings
//templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
	my_equal( const std::locale& loc ) : loc_(loc) {}
	bool operator()(charT ch1, charT ch2) {
		return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
	}
private:
	const std::locale& loc_;
};

//find substring (case insensitive)
template<typename T>
int ci_find_substr( const T& str1, const T& str2, const std::locale& loc = std::locale() )
{
	T::const_iterator it = std::search( str1.begin(), str1.end(), 
		str2.begin(), str2.end(), my_equal<T::value_type>(loc) );
	if ( it != str1.end() ) return it - str1.begin();
	else return -1; // not found
}

//initialize the  varialbies
Basketball_league::Basketball_league()
{
	_isOpen=1;
	_game= vector<Game*> ();
	_team= vector<Team*> ();
	_dateBase = new DataBase();

}

//controll the program navigation
void Basketball_league::start(int argc, char* argv[])
{
	readFromFile();
	string str="";
	bool loop=1; // starts with 1 value
	while (loop)
	{
		//if there is a user file to read and he inserted before lunce the program
		if (argc>1)
		{
			readUserFileAction(argc,argv);
			argc=0;	
		}

		//getting the next action/request fron the user
inputerror: getline(cin,str);
		//real input because i change it to lower case and without spaces 
		string realInput = str;
		/*all the matches will be without spaces and with lower case*/
		str.erase( std::remove(str.begin(),str.end(),' '), str.end() );
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		//check if str starts with '.' it should be a regex
		if (str.substr(0,1).compare(".")==0)
		{
			goto inputerror;
		}

		// statments
		if (str.compare("showleague")==0)
		{
			printLeagueTabel();
		}
		//display the team names
		else if (str.compare("showteams")==0)
		{
			cout<<"Team Name"<<endl;
			cout<<"-----------"<<endl;
			for (int i=0 ; i< _team.size();i++)
			{
				cout<<_team[i]->get_teamName()<<endl;
			}

		}
		//display a specific game
		else if (str.substr(0,4).compare("show")==0 && (str.length()-4)>1)
		{
			//split the string into 2 parts each one of then is a team
			str = str.substr(4,str.length());
			int locationInLine=0;
			string splited,home,guest;
			for (int i=0 ; i < realInput.length(); i++)
			{
				string temp = realInput.substr(i,1);
				if (realInput.length()>(i+4) && realInput.at(i)==' ' && realInput.at(i+1)=='-' && realInput.at(i+2)==' ')
				{
					home=splited;
					locationInLine+=i+3;
					guest=realInput.substr(locationInLine,realInput.length());
					splited.clear();
					break;
				}
				splited.append(temp);
			}
			home = home.substr(5,home.length());
			//search the requested game in reverse order to get the latest game
			for (int i=_game.size()-1; i >= 0; i--)
			{
				if (home.compare(_game[i]->get_home())==0 && guest.compare(_game[i]->get_guest().substr(0,(_game[i]->get_guest().length()-1)))==0) 
				{
					cout<<home<<" - "<<guest<<" "<<_game[i]->get_finalScoreHOME()<<"-"<<_game[i]->get_finalScoreGUEST()<<" ("<<_game[i]->get_halftimeScoreHOME()<<"-"<<_game[i]->get_halftimeScoreGUEST()<<")"<<endl;
					break;
				}
			}
		}
		std::string txt = ".txt";
		//another way to find substring
		int isTXT = ci_find_substr( str, txt );
		//if we detect a string with .txt its a file
		if (isTXT>0)
		{
			char* temp = const_cast<char*>(str.c_str());
			//another way to copy
			//std::copy(str.begin(), str.end(), argv[1]);
			argv[1]=temp;
			//don't forget the terminating \0
			argv[1][str.size()+1] = '\0'; 
			readUserFileAction(argc,argv);
		}
		//check if we have date elements like . , / and it start with game namber
		else if (str.find("game")!= std::string::npos&&(str.find(".")!= std::string::npos || str.find(",")!= std::string::npos || str.find("/")!= std::string::npos))
		{
			//delete the word 'game' from the input string and keep only the number
			int gameNumber=0;
			if(str.substr(5,6).compare(",") || str.substr(5,6).compare("."))
				gameNumber = atoi(str.substr(4,5).c_str());
			string strGame=str.substr(6,str.length());
			//finally check if the input is date 
			Date* date = (checkDate(strGame));		
			for (int i=0; i< _game.size(); i++)
			{
				Date* d = _game[i]->get_date();
				if (*d==*date && _game[i]->get_round() == gameNumber)
				{
					//display the asks games
					cout<<_game[i]->get_home()<<" - "<<_game[i]->get_guest()<<" "<<_game[i]->get_finalScoreHOME()<<"-"<<_game[i]->get_finalScoreGUEST()<<" ("<<_game[i]->get_halftimeScoreHOME()<<"-"<<_game[i]->get_halftimeScoreGUEST()<<")"<<endl;
				}
			}
			cout<<endl;
		}

		//access allow only if you are the manager
		if (str.substr(0,5).compare("admin")==0)
		{
			//remove the admin word from the beginning and keep the left string
			string strAdmin = str.substr(5,str.length());

			if (strAdmin.compare("addgame")==0)
			{
				//close the ream registeration
				if(_isOpen==1 ) 
				{
					_dateBase->get_file()<<("START")<<endl;
					_dateBase->get_file()<<("END")<<endl;
					_isOpen=0;
				}
				string newGame;
				cout<<"insert new game: ";
				getline(cin,newGame);
				//check if the game is correct by names and game number
				newGame = addGame(newGame);
				_game.push_back(new Game(newGame));
				interpretGamesToTeamsStatus(_game.at(_game.size()-1));
				writeToFileinTheEnd(newGame);
			}
			//register teams
			if (strAdmin.compare("registerteams")==0)
			{

				if(_isOpen==1)
				{
					string newTeam;int check=1;
					vector<string> vec;
					//save my list in vector to comper with the input string
					for (int i=0;i<_team.size();i++)
					{
						vec.push_back(_team[i]->get_teamName());
					}
					cout<<"insert team names: "<<endl;
					//check is the inset team is not exist and exit when ; insert
					while (!newTeam.compare(";")==0)
					{
						getline(cin,newTeam);
						for (int i=0;i<vec.size();i++)
						{
							if(newTeam.compare(vec[i])==0)
							{
								cout<<"team "<<newTeam<< " is already registered"<<endl;
								check=0;
							}
						}
						if (check==1 && !newTeam.compare(";")==0)
						{
							writeToFileinTheEnd(newTeam);
							_team.push_back(new Team(newTeam));
						}
						check=1;					
					}
					cout<< "Teams was added"<<endl;
				}
				else
				{
					cout<<"cannot add new teams because the league is already started"<<endl;
				}
			}
			//update team name
			if (strAdmin.compare("updateteamname")==0)
			{
				string oldTeam;
				if(_isOpen==1)
				{
					//cout<<"insert 'old and new' team name"<<endl;
					cout<<"Old Team Name: ";
					getline(cin,oldTeam);
					string newTeam;
					cout<<"New Team Name: ";
					getline(cin,newTeam);
					//update team name into the data base
					replace_line_in_file(oldTeam , newTeam);
					cout<< "Team name updated"<<endl;
				}
				else
				{
					cout<<"cannot update "<<oldTeam<<" because the league is already started"<<endl;
				}
			}
		}

		if (str.compare("exit")==0)
		{
			_dateBase->get_file().close();
			loop=0;
		}
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

//when the program starts it read from the data base
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

//add a new line into the data base
void Basketball_league::writeToFileinTheEnd(string line)
{
	/*
	write the data into the data base file 
	*/
	string inbuf;
	vector<string> vec;
	_dateBase->get_file().clear();
	_dateBase->get_file().seekg(0, _dateBase->get_file().beg);
	while (getline(_dateBase->get_file(), inbuf))
	{
		vec.push_back(inbuf);
	}
	if (vec[vec.size()-1].compare("END")||vec[vec.size()-1].compare("END\n"))
	{
		vec.insert(vec.begin()+(vec.size()-1),line);
	}

	_dateBase->get_file().close();
	system("DEL /F basketball2013.txt");
	_dateBase = new DataBase();

	for(int i =0; i<vec.size();i++)
	{
		_dateBase->get_file()<<(vec[i])<<endl;
	}

}

//interpret the team status into my vareables
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

//print league table
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
	cout << "---------------------------------------------"<<endl<<endl;

}

/* start sort function (it sort the table teams)*/
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

//sort the table
void Basketball_league::sortTable ()
{
	sort (_team.begin(), _team.end(), your_comparer);
}

//read commands file if the user insert before or after the program lunched
void Basketball_league::readUserFileAction(int argc,char* argv[])
{
	ifstream userfile;
	userfile.open (argv[1], ios::in | ios::out | ios::app);
	userfile.clear();
	userfile.seekg(0, _dateBase->get_file().beg);
	string str="";

	while ( getline (userfile,str) )
	{
		//real input because i change it to lower case and without spaces
		string realInput = str;

		str.erase( std::remove(str.begin(),str.end(),' '), str.end() );
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		/*all the matches will be without spaces and with lower case*/
		str.erase( std::remove(str.begin(),str.end(),' '), str.end() );
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		// statments
		if (str.compare("showleague")==0)
		{
			printLeagueTabel();
		}
		//display the team names
		else if (str.compare("showteams")==0)
		{
			cout<<"Team Name"<<endl;
			cout<<"-----------"<<endl;
			for (int i=0 ; i< _team.size();i++)
			{
				cout<<_team[i]->get_teamName()<<endl;
			}

		}
		//display a specific game
		else if (str.substr(0,4).compare("show")==0 && (str.length()-4)>=2)
		{
			//split the string into 2 parts each one of then is a team name
			str = str.substr(4,str.length());
			int locationInLine=0;
			string splited,home,guest;
			for (int i=0 ; i < realInput.length(); i++)
			{
				string temp = realInput.substr(i,1);
				if (realInput.length()>(i+4) && realInput.at(i)==' ' && realInput.at(i+1)=='-' && realInput.at(i+2)==' ')
				{
					home=splited;
					locationInLine+=i+3;
					guest=realInput.substr(locationInLine,realInput.length());
					splited.clear();
					break;
				}
				splited.append(temp);
			}
			home = home.substr(5,home.length()-1);
			//search the requested game in reverse order to get the latest game
			for (int i=_game.size()-1; i >= 0 ; i--)
			{
				if (home.compare(_game[i]->get_home())==0 && guest.compare(_game[i]->get_guest().substr(0,(_game[i]->get_guest().length()-1)))==0) 
				{
					cout<<home<<" - "<<guest<<" "<<_game[i]->get_finalScoreHOME()<<"-"<<_game[i]->get_finalScoreGUEST()<<" ("<<_game[i]->get_halftimeScoreHOME()<<"-"<<_game[i]->get_halftimeScoreGUEST()<<")"<<endl;
					break;
				}
			}
		}

		std::string txt = ".txt";
		//another way to find substring
		int isTXT = ci_find_substr( str, txt );
		//if we detect a string with .txt its a file
		if (isTXT>0)
		{
			char* temp = const_cast<char*>(str.c_str());
			//another way to copy
			//std::copy(str.begin(), str.end(), argv[1]);
			argv[1]=temp;
			//don't forget the terminating \0
			argv[1][str.size()+1] = '\0'; 
			readUserFileAction(argc,argv);
		}

		//check if we have date elements like . , / and it start with game namber
		else if (str.find("game")!= std::string::npos&&(str.find(".")!= std::string::npos || str.find(",")!= std::string::npos || str.find("/")!= std::string::npos))
		{
			//delete the word 'game' from the input string and keep only the number
			int gameNumber=0;
			if(str.substr(5,6).compare(",") || str.substr(5,6).compare("."))
				gameNumber = atoi(str.substr(4,5).c_str());
			string strGame=str.substr(6,str.length());
			//finally check if the input is date 
			Date* date = (checkDate(strGame));		
			for (int i=0; i< _game.size(); i++)
			{
				Date* d = _game[i]->get_date();
				if (*d==*date && _game[i]->get_round() == gameNumber)
				{
					//display the asks games
					cout<<_game[i]->get_home()<<" - "<<_game[i]->get_guest()<<" "<<_game[i]->get_finalScoreHOME()<<"-"<<_game[i]->get_finalScoreGUEST()<<" ("<<_game[i]->get_halftimeScoreHOME()<<"-"<<_game[i]->get_halftimeScoreGUEST()<<")"<<endl;
				}
			}
			cout<<endl;
		}

		//access allow only if you are the manager
		if (str.substr(0,5).compare("admin")==0)
		{
			//remove the admin word from the beginning and keep the left string
			string strAdmin = str.substr(5,str.length());

			if (strAdmin.compare("addgame")==0)
			{
				//close the ream registeration
				if(_isOpen==1 ) 
				{
					_dateBase->get_file()<<("START")<<endl;
					_dateBase->get_file()<<("END")<<endl;
					_isOpen=0;
				}
				string newGame;
				cout<<"insert new game: ";
				getline(cin,newGame);
				//check if the game is correct by names and game number
				newGame = addGame(newGame);
				_game.push_back(new Game(newGame));
				interpretGamesToTeamsStatus(_game.at(_game.size()-1));
				writeToFileinTheEnd(newGame);
			}
			//register teams
			if (strAdmin.compare("registerteams")==0)
			{

				if(_isOpen==1)
				{
					string newTeam;int check=1;
					vector<string> vec;
					//save my list in vector to comper with the input string
					for (int i=0;i<_team.size();i++)
					{
						vec.push_back(_team[i]->get_teamName());
					}
					cout<<"insert team names: "<<endl;
					//check is the inset team is not exist and exit when ; insert
					while (!newTeam.compare(";")==0)
					{
						getline(cin,newTeam);
						for (int i=0;i<vec.size();i++)
						{
							if(newTeam.compare(vec[i])==0)
							{
								cout<<"team "<<newTeam<< " is already registered"<<endl;
								check=0;
							}
						}
						if (check==1 && !newTeam.compare(";")==0)
						{
							writeToFileinTheEnd(newTeam);
							_team.push_back(new Team(newTeam));
						}
						check=1;					
					}
					cout<< "Teams was added"<<endl;
				}
				else
				{
					cout<<"cannot add new teams because the league is already started"<<endl;
				}
			}
			//update team name
			if (strAdmin.compare("updateteamname")==0)
			{
				string oldTeam;
				if(_isOpen==1)
				{
					//cout<<"insert 'old and new' team name"<<endl;
					cout<<"Old Team Name: ";
					getline(cin,oldTeam);
					string newTeam;
					cout<<"New Team Name: ";
					getline(cin,newTeam);
					//update team name into the data base
					replace_line_in_file(oldTeam , newTeam);
					cout<< "Team name updated"<<endl;
				}
				else
				{
					cout<<"cannot update "<<oldTeam<<" because the league is already started"<<endl;
				}
			}
		}
		cout<<endl;
	}
}

//change line in the file if they macth
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
		_dateBase->get_file()<<(vec[i])<<endl;
	}
}

string Basketball_league::addGame(string line)
{
	/*
	that the string i want to create
	"3.2, Oct. 27, 2013 Irroni Ashdod - Hapoel Ramat-Gan 90-98 (63-51)"
	*/
	string _home;
	string _guest;
	Date* _date;
	int _round;
	int _game;
	int _finalScoreHOME;
	int _finalScoreGUEST;
	int _halftimeScoreHOME;
	int _halftimeScoreGUEST;



	return "3.2, Oct. 27, 2013 Irroni Ashdod - Hapoel Ramat-Gan 90-98 (63-51)";
}