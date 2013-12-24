#include "Basketball_league.h"
/*צריך לבדוק מצב אם הקובץ קיים או לא כדי לדעת אם לתת לו כתיבה ראשונית של כותרות או לא*/
/*קובץ לוג לא תקין הוא מדפיס כפול*/
/*לעשות עדכון משחק*/



//check if the date is valid or not
Date* checkDate(string data)
{
std::stringstream stringStream(data);
std::string line;
vector<string>wordVector;
while(std::getline(stringStream, line)) 
{
    std::size_t prev = 0, pos;
    while ((pos = line.find_first_of(" .,/", prev)) != std::string::npos)
    {
        if (pos > prev)
            wordVector.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
    }
    if (prev < line.length())
        wordVector.push_back(line.substr(prev, std::string::npos));
}

	Date* date;
	//wordVector is my date array
	if (!atoi(wordVector[0].c_str())>0) 
		date = new Date(wordVector[1],wordVector[0],wordVector[2]);
	else date = new Date(wordVector[0],wordVector[1],wordVector[2]);
	return date;
	
}

void showHelp()
{
	cout<< "Commands:" << endl<< endl;
	cout<< "help - display this help menu" << endl<< endl;
	cout<< "Show the league - shows league build" << endl<< endl;
	cout<< "Show teams listing - shows the teams in the league" << endl<< endl;
	cout<< "show - the word show + pick teams name and a date, and get a specific game information" << endl<< endl;
	cout<< "Show a match score - shows a specific match score <home> : <guest>"<<endl<< endl;
	cout<< "admin - for admin use only" << endl<< endl;  
	cout<< "addgame - adds a game" << endl<< endl;
	cout<< "Teams listing - Teams listing begins with a line of Register Teams followed by team-names, each on a separate line." << endl<< endl;
	cout<< "Game listing - Game listing begins with a line of Game <game-number>, <date> followed by lines of matche scores <home>: <guest>." << endl<< endl;
	cout<< "Correction team name - the option to change the name of a team" << endl<< endl;
	cout<< "exit - closing the program" << endl<< endl;
	cout<< "Correction - <home-team> - <guest-team> <correct-score> , changing a wrong game score" << endl<< endl;
	cout<< "Correction Game - <game-number>, <correct-date> , changing game number and date"<<endl<< endl;
	cout<< "Replacement Correction - We use the words Replace . . . By , and then new item that got assigned" << endl<< endl;
	cout<< "Correction Delete - use this function and then the <unambiguous-data-to-be-deleted> to delete it " << endl<< endl;
}

/*
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
*/

//initialize the  varialbies
Basketball_league::Basketball_league()
{
	_isOpen=1;
	_game= vector<Game*> ();
	_team= vector<Team*> ();
	_dateBase = new DataBase();
	//_dateBase->initDB();
}

//controll the program navigation
void Basketball_league::start(int argc, char* argv[])
{
	checkDate("20/10/2013");
	checkDate("oct. 21,2013");
	


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
		if (str.substr(0,1).compare(".")==0||str.substr(0,1).compare(",")==0||str.substr(0,1).compare("/")==0)
		{
			goto inputerror;
		}
		if (str.compare("help")==0)
		{
			showHelp();
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
				if (home.compare(_game[i]->get_home())==0 && guest.compare(_game[i]->get_guest().substr(0,(_game[i]->get_guest().length())))==0) 
				{
					cout<<getGameDetails(i)<<endl;
					break;
				}
			}
		}

		std::string txt = ".txt";
		//another way to find substring
		//int isTXT = ci_find_substr( str, txt );
		//if we detect a string with .txt its a file
		if (txt.find(".txt")>1)
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
					cout<<getGameDetails(i)<<endl;
				}
			}
			cout<<endl;
		}

		//access allow only if you are the manager
		if (str.substr(0,5).compare("admin")==0)
		{
			//remove the admin word from the beginning and keep the left string
			string strAdmin = str.substr(5,str.length());

			if (strAdmin.substr(0,7).compare("addgame")==0)
			{
				//close the ream registeration
				if(_isOpen==1 ) 
				{
					_dateBase->get_file()<<("START")<<endl;
					_dateBase->get_file()<<("END")<<endl;
					_isOpen=0;
				}

				int location= realInput.find("game");
				string newGame = realInput.substr(location+4,realInput.length());
				//check if the game is correct by names and game number and act.
				addGame(newGame);
				//_game.push_back(new Game(newGame));
				//writeToFileinTheEnd(newGame);
				interpretGamesToTeamsStatus(_game.at(_game.size()-1));
				string output = "user add a new game ";
				output+=newGame;
				writeToOUTPUTfile(output);
			}
			//register teams
			if (strAdmin.substr(0,13).compare("registerteams")==0)
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
					//cout<<"insert team names: "<<endl;
					//check is the inset team is not exist and exit when ; insert
					while (!newTeam.compare(";")==0)
					{
						
						getline (cin,newTeam);
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
							string output = "user add a new team ";
							output+=newTeam;
							writeToOUTPUTfile(output);
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
			if (strAdmin.substr(0,17).compare("correctionreplace")==0)
			{
				int location = realInput.find("replace");
				realInput = realInput.substr(location+8,realInput.length());
				//seperate the old team name and new team name
				int locationInLine=0;
				string splited,oldTeam,newTeam;
				string temp = realInput;
				oldTeam = temp.substr(0,realInput.find("by")-1);
				newTeam = temp.substr(realInput.find("by ")+3,temp.length());

				/*for (int i=0 ; i < realInput.length(); i++)
				{
				string temp = realInput.substr(i,1);
				if (realInput.length()>(i+4) && realInput.at(i)==' ' && realInput.at(i+1)=='-' && realInput.at(i+2)==' ')
				{
				oldTeam=splited;
				locationInLine+=i+3;
				newTeam=realInput.substr(locationInLine,realInput.length());
				splited.clear();
				break;
				}
				splited.append(temp);
				}*/

				//update team name into the data base
				replace_line_in_file(oldTeam , newTeam);
				string output = "user replace team name ";
				output+= oldTeam;
				output+=" to ";
				output+=newTeam;
				writeToOUTPUTfile(output);
				//cout<< "Team name updated"<<endl;	
			}
			if (strAdmin.substr(0,14).compare("correctiongame")==0)
			{
				strAdmin = strAdmin.substr(strAdmin.find("game")+4,strAdmin.length());
				string gameNumber = strAdmin.substr(0,1);
				string sdate = strAdmin.substr(2,strAdmin.length());
				Date* date = checkDate(strAdmin.substr(2,strAdmin.length()));
				updateGame(gameNumber, sdate);
			}
			if (strAdmin.substr(0,16).compare("correctiondelete")==0)
			{
				if(_isOpen)
				{
					int location = realInput.find("delete");
					string teamToRemove = realInput.substr(location+7,realInput.length());
					removeLine(teamToRemove);
					for (int i=0; i<_team.size();i++)
					{
						if (_team[i]->get_teamName().compare(teamToRemove)==0)
						{
							_team.erase(_team.begin()+i);
							string output = "user delete team ";
							output+= teamToRemove;
							writeToOUTPUTfile(output);
							break;
						}
					}
				}
				else cout<<"cannot delete team because the league is already started"<<endl;

			}
			if (strAdmin.substr(0,10).compare("correction")==0 && strAdmin.find('-') != std::string::npos )
			{
				realInput = realInput.substr(realInput.find("correction")+11,realInput.length());
				int locationInLine=0;
				string splited,home,guest;
				string temp = realInput;
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
				string score;
				for (int i=0 ; i < guest.length(); i++)
				{
					string temp = guest.substr(i,1);
					try{
						if (guest.length()>(i+4) && atoi(temp.c_str())>0)
						{
							score = guest;
							guest=splited.substr(0,splited.length()-1);
							locationInLine+=i;
							score=score.substr(guest.length()+1,score.length());
							splited.clear();
							break;
						}
					}
					catch(exception e){};
					splited.append(temp);
				}
				updateGameDetails(home,guest,score);
				interpretGamesToTeamsStatus(_game.at(_game.size()-1));

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
	system("DEL /F db_basketball2013.txt");
	_dateBase = new DataBase();

	for(int i =0; i<vec.size();i++)
	{
		_dateBase->get_file()<<(vec[i])<<endl;
	}

}

void Basketball_league::writeToOUTPUTfile(string line)
{
	static int c=0;
	if (c==0)
	{
		_dateBase->get_output().open ("output.txt", ios::in | ios::out | ios::app );
	}

	/*
	write the data into the data base file 
	*/
	time_t t1 = time(0);   // get time now
	struct tm * now = localtime( & t1 );

	std::stringstream out;
	//out << i;
	//s += out.str();
	string s;
	out << (now->tm_year + 1900);
	s+= out.str();
	s+='-';
	out << (now->tm_mon + 1);
	s+= out.str();
	s+='-';
	out << (now->tm_mday);
	s+= out.str();
	s+=", ";
	out << (now->tm_hour);
	s+= out.str();
	s+=":";
	out << (now->tm_min);
	s+= out.str();
	s+=":";
	out << (now->tm_sec);
	s+= out.str();
	string inbuf;
	vector<string> vec;
	_dateBase->get_output().clear();
	_dateBase->get_output().seekg(0, _dateBase->get_output().beg);
	while (getline(_dateBase->get_output(), inbuf))
	{
		vec.push_back(inbuf);
	}

	vec.insert(vec.begin()+(vec.size()),s);
	vec.insert(vec.begin()+(vec.size()),line);


	_dateBase->get_output().close();
	system("DEL /F outout.txt");
	_dateBase->get_output().open ("output.txt", ios::in | ios::out | ios::app );


	for(int i =0; i<vec.size();i++)
	{
		_dateBase->get_output()<<(vec[i])<<endl;
	}

}

//add a new line into the data base
void Basketball_league::writeToFileinTheMiddel(string line)
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

	/* here i decide when to insert my new line
	if (vec[vec.size()-1].compare("END")||vec[vec.size()-1].compare("END\n"))
	{
	vec.insert(vec.begin()+(vec.size()-1),line);
	}*/

	_dateBase->get_file().close();
	system("DEL /F db_basketball2013.txt");
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
				if (home.compare(_game[i]->get_home())==0 && guest.compare(_game[i]->get_guest().substr(0,(_game[i]->get_guest().length())))==0) 
				{
					cout<<getGameDetails(i)<<endl;
					break;
				}
			}
		}

		std::string txt = ".txt";
		//another way to find substring
		//int isTXT = ci_find_substr( str, txt );
		//if we detect a string with .txt its a file
		if (txt.find(".txt")>1)
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
					cout<<getGameDetails(i)<<endl;
				}
			}
			cout<<endl;
		}

		//access allow only if you are the manager
		if (str.substr(0,5).compare("admin")==0)
		{
			//remove the admin word from the beginning and keep the left string
			string strAdmin = str.substr(5,str.length());

			if (strAdmin.substr(0,7).compare("addgame")==0)
			{
				//close the ream registeration
				if(_isOpen==1 ) 
				{
					_dateBase->get_file()<<("START")<<endl;
					_dateBase->get_file()<<("END")<<endl;
					_isOpen=0;
				}

				int location= realInput.find("game");
				string newGame = realInput.substr(location+4,realInput.length());
				//check if the game is correct by names and game number and act.
				addGame(newGame);
				//_game.push_back(new Game(newGame));
				//writeToFileinTheEnd(newGame);
				interpretGamesToTeamsStatus(_game.at(_game.size()-1));
				string output = "user add a new game ";
				output+=newGame;
				writeToOUTPUTfile(output);
			}
			//register teams
			if (strAdmin.substr(0,13).compare("registerteams")==0)
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
					//cout<<"insert team names: "<<endl;
					//check is the inset team is not exist and exit when ; insert
					while (!newTeam.compare(";")==0)
					{
						getline (userfile,newTeam);
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
							string output = "user add a new team ";
							output+=newTeam;
							writeToOUTPUTfile(output);
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
			if (strAdmin.substr(0,17).compare("correctionreplace")==0)
			{
				int location = realInput.find("replace");
				realInput = realInput.substr(location+8,realInput.length());
				//seperate the old team name and new team name
				int locationInLine=0;
				string splited,oldTeam,newTeam;
				string temp = realInput;
				oldTeam = temp.substr(0,realInput.find("by")-1);
				newTeam = temp.substr(realInput.find("by ")+3,temp.length());

				/*for (int i=0 ; i < realInput.length(); i++)
				{
				string temp = realInput.substr(i,1);
				if (realInput.length()>(i+4) && realInput.at(i)==' ' && realInput.at(i+1)=='-' && realInput.at(i+2)==' ')
				{
				oldTeam=splited;
				locationInLine+=i+3;
				newTeam=realInput.substr(locationInLine,realInput.length());
				splited.clear();
				break;
				}
				splited.append(temp);
				}*/

				//update team name into the data base
				replace_line_in_file(oldTeam , newTeam);
				string output = "user replace team name ";
				output+= oldTeam;
				output+=" to ";
				output+=newTeam;
				writeToOUTPUTfile(output);
				//cout<< "Team name updated"<<endl;	
			}
			if (strAdmin.substr(0,14).compare("correctiongame")==0)
			{
				strAdmin = strAdmin.substr(strAdmin.find("game")+4,strAdmin.length());
				string gameNumber = strAdmin.substr(0,1);
				string sdate = strAdmin.substr(2,strAdmin.length());
				Date* date = checkDate(strAdmin.substr(2,strAdmin.length()));
				updateGame(gameNumber, sdate);
			}
			if (strAdmin.substr(0,16).compare("correctiondelete")==0)
			{
				if(_isOpen)
				{
					int location = realInput.find("delete");
					string teamToRemove = realInput.substr(location+7,realInput.length());
					removeLine(teamToRemove);
					for (int i=0; i<_team.size();i++)
					{
						if (_team[i]->get_teamName().compare(teamToRemove)==0)
						{
							_team.erase(_team.begin()+i);
							string output = "user delete team ";
							output+= teamToRemove;
							writeToOUTPUTfile(output);
							break;
						}
					}
				}
				else cout<<"cannot delete team because the league is already started"<<endl;

			}
			if (strAdmin.substr(0,10).compare("correction")==0 && strAdmin.find('-') != std::string::npos )
			{
				realInput = realInput.substr(realInput.find("correction")+11,realInput.length());
				int locationInLine=0;
				string splited,home,guest;
				string temp = realInput;
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
				string score;
				for (int i=0 ; i < guest.length(); i++)
				{
					string temp = guest.substr(i,1);
					try{
						if (guest.length()>(i+4) && atoi(temp.c_str()))
						{
							score = guest;
							guest=splited.substr(0,splited.length()-1);
							locationInLine+=i;
							score=score.substr(guest.length()+1,score.length());
							splited.clear();
							break;
						}
					}
					catch(exception e){};
					splited.append(temp);
				}
				updateGameDetails(home,guest,score);
				interpretGamesToTeamsStatus(_game.at(_game.size()-1));

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
		if(inbuf.find(search_string)!= std::string::npos)
		{
			//seperate the exactly word from the sentence.
			string round = inbuf.substr(0,1);	
			string game = inbuf.substr(2,3);
			game = game.substr(0,1);
			//here the value will be changed only if is a teame name we are looking for
			try{
				if (atoi(round.c_str())>0 && atoi(game.c_str())>0)
				{
					for (int i=0;i<_game.size(); i++)
					{
						//looking for the exactly game
						if (_game[i]->get_round()==atoi(round.c_str()) && _game[i]->get_gameNumber()==atoi(game.substr(0,1).c_str()))
						{
							//if the search_string match replace her with the replace_string
							if (_game[i]->get_home().compare(search_string)==0)
							{
								_game[i]->set_home(replace_string);
								vec.push_back(getFullGameDetails(i));
							}
							else if (_game[i]->get_guest().compare(search_string)==0)
							{
								_game[i]->set_guest(replace_string);
								vec.push_back(getFullGameDetails(i));
							}
						}
					}
				}

				else 
				{
					vec.push_back(replace_string);
					for (int i=0; i<_team.size(); i++)
					{
						if (_team[i]->get_teamName().compare(search_string)==0)
						{
							_team[i]->set_teamName(replace_string);
						}
					}
				}
			}
			catch (exception e){};
		}
		else vec.push_back(inbuf);

	}

	_dateBase->get_file().close();
	system("DEL /F db_basketball2013.txt");
	_dateBase = new DataBase();

	for(int i =0; i<vec.size();i++)
	{
		_dateBase->get_file()<<(vec[i])<<endl;
	}
}

void Basketball_league::addGame(string line)
{
	/*
	this is the string i want to create
	"1.1, Oct. 27, 2013 Irroni Ashdod - Hapoel Ramat-Gan 90-98 (63-51)"
	*/

	if (line.substr(0,1).compare(" ")==0)
		line= line.substr(1,line.length());

	string home;
	string guest;
	Date* date;
	string round;
	string game;
	string finalScoreHOME;
	string finalScoreGUEST;
	string halftimeScoreHOME;
	string halftimeScoreGUEST;


	int location=0;
	/*round = line.substr(location,1);
	location+=2;
	game = line.substr(location,1);
	location+=3;*/
	// his input
	round= line.substr(0,1);
	line= line.substr(1,line.length());
	if (_game.size()==0)
		game="1";
	else {
		std::stringstream out;
		out<<(_game[_game.size()-1]->get_gameNumber()+1);
		game = out.str();
	}
	try{
		if (atoi(round.c_str())>0 && atoi(game.c_str())>0)
		{
			string splited;
			// how to create only date token ??
			line = line.substr(location, line.length());
			date = checkDate(line);
			line = line.substr(11,line.length());
			string temp = line.substr(0,line.find(" "));
			try{
				if (atoi(temp.c_str())>0)
				{
					line= line.substr(temp.length(),line.length());
				}
			}
			catch(exception e){};
			if (line.at(0)==' ')
			{
				line= line.substr(1,line.length());
			}

			//team names and score
			string token = line;
			temp.clear();
			splited.clear();
			int locationInLine=0;
			for (int i=0 ; i < token.length(); i++)
			{
				string temp = token.substr(i,1);	
				if (token.length()>(i+4) && token.at(i)==' ' && token.at(i+1)=='-' && token.at(i+2)==' ')
				{
					home=splited;
					locationInLine+=i+3;
					token=line.substr(locationInLine,line.length());
					splited.clear();
					break;
				}
				splited.append(temp);
			}
			int check =1;
			for (int i=0 ; i < token.length(); i++)
			{
				string temp = token.substr(i,1);
				try{
					if (token.length()>(i+4) && atoi(temp.c_str())>0)
					{
						guest=splited.substr(0,splited.length()-1);
						locationInLine+=i;
						token=line.substr(locationInLine,line.length());
						splited.clear();
						check=0;
						break;
					}
				}
				catch(exception e){}
				splited.append(temp);
			}
			if (check)
			{
				guest=token;
				finalScoreHOME="0";
				finalScoreGUEST="0";
				halftimeScoreHOME="0";
				halftimeScoreGUEST="0";

			}
			else
			{
				int tempFound= token.find(':');
				locationInLine+=tempFound+1;
				temp = token.substr(0, tempFound);
				finalScoreHOME=temp;
				token=line.substr(locationInLine,line.length());

				tempFound= token.find(' ');
				locationInLine+=tempFound+1;
				temp = token.substr(0, tempFound);
				finalScoreGUEST=temp;
				token=line.substr(locationInLine,line.length());

				tempFound= token.find('(');
				locationInLine+=tempFound+1;
				token=line.substr(locationInLine,line.length());

				tempFound= token.find(':');
				locationInLine+=tempFound+1;
				temp = token.substr(0, tempFound);
				halftimeScoreHOME=temp;
				token=line.substr(locationInLine,line.length());

				tempFound= token.find(')');
				locationInLine+=tempFound+1;
				temp = token.substr(0, tempFound);
				halftimeScoreGUEST=temp;
			}
			std::stringstream out;
			//out << i;
			//s += out.str();
			//"1.1, Oct. 27, 2013 Irroni Ashdod - Hapoel Ramat-Gan 90-98 (63-51)"
			string newGame;
			newGame+= round;
			newGame+= ".";
			newGame+= game;
			newGame+= ", ";
			newGame+= date->get_month();
			newGame+= ". ";
			out << (date->get_day());
			newGame+= out.str();
			newGame+= ", ";
			out << (date->get_year());
			newGame+= out.str();
			newGame+= " ";
			newGame+= home;
			newGame+= " - ";
			newGame+= guest;
			newGame+= " ";
			newGame+= finalScoreHOME;
			newGame+= ":";
			newGame+= finalScoreGUEST;
			newGame+= " (";
			newGame+= halftimeScoreHOME;
			newGame+= ":";
			newGame+= halftimeScoreGUEST;
			newGame+= ")";

			/*check if the game is legal*/
			Game* addgame= new Game(newGame);

			//check if the game is already exist
			if(_game.at(_game.size()-1)->get_round() >= (addgame->get_round()) && _game.at(_game.size()-1)->get_gameNumber() < (addgame->get_gameNumber()))
				return;


			_game.push_back(addgame);
			writeToFileinTheEnd(newGame);
		}
	}
	catch(exception e) {}

	/*
	this is the string i want to create
	"1.1, Oct. 27, 2013 Irroni Ashdod - Hapoel Ramat-Gan 90-98 (63-51)"
	*/
	//_game.push_back(new Game(newGame));
	//writeToFileinTheEnd(newGame);
}

string Basketball_league:: getGameDetails(int i)
{
	/*
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	*/
	std::stringstream out;
	//out << i;
	//s += out.str();
	string send;
	send+= _game[i]->get_home();
	send+= " - ";
	send+= _game[i]->get_guest();
	send+= " ";
	out <<(_game[i]->get_finalScoreHOME());
	send+= out.str();
	send+= ":";
	out <<(_game[i]->get_finalScoreGUEST());
	send+= out.str();
	send+= " (";
	out <<(_game[i]->get_halftimeScoreHOME());
	send+= out.str();
	send+= ":";
	out <<(_game[i]->get_halftimeScoreGUEST());
	send+= out.str();
	send+= ")";

	return 	send;

}

string Basketball_league:: getFullGameDetails(Game * game)
{
	/*
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	*/
	//to_string();
	std::stringstream out;
	string send;
	out <<(game->get_round());
	send+= out.str();
	send+= ".";
	out <<(game->get_gameNumber());
	send+= out.str();
	send+= ", ";
	send+= game->get_date()->get_month();
	send+= ". ";
	out <<(game->get_date()->get_day());
	send+= out.str();
	send+= ", ";
	out <<(game->get_date()->get_year());
	send+= out.str();
	send+= " ";
	send+= game->get_home();
	send+= " - ";
	send+= game->get_guest();
	send+= " ";
	out <<(game->get_finalScoreHOME());
	send+= out.str();
	send+= ":";
	out <<(game->get_finalScoreGUEST());
	send+= out.str();
	send+= " (";
	out <<(game->get_halftimeScoreHOME());
	send+= out.str();
	send+= ":";
	out <<(game->get_halftimeScoreGUEST());
	send+= out.str();
	send+= ")";
	return send;

}

string Basketball_league:: getFullGameDetails(int i)
{
	std::stringstream out;
	string send;
	//to_string();
	out <<(_game[i]->get_round());
	send+= out.str();
	send+= ".";
	out <<(_game[i]->get_gameNumber());
	send+= out.str();
	send+= ", ";
	send+= _game[i]->get_date()->get_month();
	send+= ". ";
	out <<(_game[i]->get_date()->get_day());
	send+= out.str();
	send+= ", ";
	out <<(_game[i]->get_date()->get_year());
	send+= out.str();
	send+= " ";
	send+= _game[i]->get_home();
	send+= " - ";
	send+= _game[i]->get_guest();
	send+= " ";
	out <<(_game[i]->get_finalScoreHOME());
	send+= out.str();
	send+= ":";
	out <<(_game[i]->get_finalScoreGUEST());
	send+= out.str();
	send+= " (";
	out <<(_game[i]->get_halftimeScoreHOME());
	send+= out.str();
	send+= ":";
	out <<(_game[i]->get_halftimeScoreGUEST());
	send+= out.str();
	send+= ")";
	return send;
}

void Basketball_league::removeLine (string line)
{
	/*
	delete the data from the data base file 
	*/
	string inbuf;
	vector<string> vec;
	_dateBase->get_file().clear();
	_dateBase->get_file().seekg(0, _dateBase->get_file().beg);
	while (getline(_dateBase->get_file(), inbuf))
	{
		vec.push_back(inbuf);
	}

	for (int i=0; i < vec.size(); i++)
	{
		if (vec[i].compare(line)==0)
		{
			vec.erase(vec.begin()+i);
			break;
		}
	}

	_dateBase->get_file().close();
	system("DEL /F db_basketball2013.txt");
	_dateBase = new DataBase();

	for(int i =0; i<vec.size();i++)
	{
		_dateBase->get_file()<<(vec[i])<<endl;
	}
}

void Basketball_league::updateGameDetails(string home,string guest, string score)
{
	string compare;
	compare += home;
	compare += " - ";
	compare += guest;
	for (int i=0 ; i< _game.size(); i++)
	{
		if (_game[i]->get_home().compare(home)==0 && _game[i]->get_guest().compare(guest)==0)
		{
			int tempFound= score.find(':');
			int  loc=tempFound+1;
			string temp = score.substr(0, tempFound);
			string temp2 = score.substr(temp.length()+1, temp.length());

			Game* newGame= new Game(getFullGameDetails(i));
			newGame->set_finalScoreHOME(temp);
			newGame->set_finalScoreGUEST(temp2);
			/*	string oldScore;
			oldScore += to_string(_game[i]->get_finalScoreHOME());
			oldScore += ":";
			oldScore += to_string(_game[i]->get_finalScoreGUEST());*/
			replace_line_in_file(getFullGameDetails(i),getFullGameDetails(newGame));
			_game.at(i) = newGame;
			interpretGamesToTeamsStatus(_game[i]);
			break;
		}
	}

}

void Basketball_league::updateGame(string gameNumber,string date)
{
	for (int i=0 ; i< _game.size(); i++)
	{
		if (_game[i]->get_round()== atoi(gameNumber.c_str()))
		{

			Game* newGame= new Game(getFullGameDetails(i));
			newGame->set_date(checkDate(date));

			/*	string oldScore;
			oldScore += to_string(_game[i]->get_finalScoreHOME());
			oldScore += ":";
			oldScore += to_string(_game[i]->get_finalScoreGUEST());*/
			replace_line_in_file(getFullGameDetails(i),getFullGameDetails(newGame));
			_game.at(i) = newGame;
			interpretGamesToTeamsStatus(_game[i]);
			break;
		}
	}
}