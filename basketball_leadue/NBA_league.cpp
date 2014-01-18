#include "NBA_league.h"

static char*  db= NULL;
static char*  output=NULL;
static char*  user=NULL;

/*check if the date is valid or not*/
Date* NBA_league::checkDate(string data)
{
	return League::checkDate(data);
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
NBA_league::NBA_league()
{
	_isOpen=1;
	_game= vector<Game*> ();
	_team= vector<Team*> ();
	_dateBase = new DataBase();
	//_dateBase->initDB();
}

void NBA_league::readFromFile(fstream& file , vector<Team*>& _team , vector<Game*>& _game ,int &_isOpen)
{
	League::readFromFile( file ,  _team , _game ,_isOpen);
}

//controll the program navigation
void NBA_league::start(string str)
{

	while(!str.substr(0,1).compare(" "))
		str=str.substr(1,str.length());

	if (str.length()<2)return;
	//getting the next action/request fron the user
inputerror: 
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

	}
	// statments
	if (str.compare("showleague")==0)
	{
		printLeagueTabel(_team);
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
	else if (str.substr(0,4).compare("show")==0 && (str.length()-4)>=2 && realInput.substr(0,5).compare("show ")==0 && realInput.substr(0,5).compare("Show ")==0)
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
				cout<<getGameDetails(i,_game)<<endl;
				break;
			}
		}
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
				cout<<getGameDetails(i,_game)<<endl;
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
			addGame(newGame,_dateBase->get_file(),_game);
			//_game.push_back(new Game(newGame));
			//writeToFileinTheEnd(newGame);
			interpretGamesToTeamsStatus(_team,_game.at(_game.size()-1));
			string output = "user add a new game ";
			output+=newGame;
			writeToOUTPUTfile(output,_dateBase->get_output());
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
						writeToFileinTheEnd(newTeam,_dateBase->get_file());
						string output = "user add a new team ";
						output+=newTeam;
						writeToOUTPUTfile(output,_dateBase->get_output());
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
			replace_line_in_file(oldTeam , newTeam, _dateBase->get_file(), _team , _game);
			string output = "user replace team name ";
			output+= oldTeam;
			output+=" to ";
			output+=newTeam;
			writeToOUTPUTfile(output,_dateBase->get_output());
			//cout<< "Team name updated"<<endl;
		}
		if (strAdmin.substr(0,14).compare("correctiongame")==0)
		{
			strAdmin = strAdmin.substr(strAdmin.find("game")+4,strAdmin.length());
			string gameNumber = strAdmin.substr(0,1);
			string sdate = strAdmin.substr(2,strAdmin.length());
			Date* date = checkDate(strAdmin.substr(2,strAdmin.length()));
			updateGame(gameNumber, sdate,_dateBase->get_file(),_team,_game);
		}
		if (strAdmin.substr(0,16).compare("correctiondelete")==0)
		{
			if(_isOpen)
			{
				int location = realInput.find("delete");
				string teamToRemove = realInput.substr(location+7,realInput.length());
				removeLine(teamToRemove,_dateBase->get_file());
				for (int i=0; i<_team.size();i++)
				{
					if (_team[i]->get_teamName().compare(teamToRemove)==0)
					{
						_team.erase(_team.begin()+i);
						string output = "user delete team ";
						output+= teamToRemove;
						writeToOUTPUTfile(output,_dateBase->get_output());
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
			updateGameDetails(home,guest,score,_dateBase->get_file(),_team,_game);
			interpretGamesToTeamsStatus(_team,_game.at(_game.size()-1));

		}
	}
	if (str.compare("exit")==0)
	{
		_dateBase->get_file().close();
		return;
	}

}

//read commands file if the user insert before or after the program lunched
void NBA_league::readUserFileAction(char* dbS , char* outputS , char* userS)
{


	if (db == NULL)
	{


		db = dbS;
		_dateBase = new DataBase(dbS);
		user = userS;
		output= outputS;
		_dateBase->set_output(outputS);
		readFromFile(_dateBase->get_file() , _team , _game , _isOpen);

	}
	if (user == NULL)
		return;
	ifstream userfile;
	userfile.open (userS, ios::in | ios::out | ios::app);
	userfile.clear();
	userfile.seekg(0, _dateBase->get_file().beg);
	string str="";

	while ( getline (userfile,str) )
	{
		//real input because i change it to lower case and without spaces
		string realInput = str;

		/*all the matches will be without spaces and with lower case*/
		str.erase( std::remove(str.begin(),str.end(),' '), str.end() );
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		// statments
		if (str.compare("showleague")==0)
		{
			printLeagueTabel(_team);
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
					cout<<getGameDetails(i,_game)<<endl;
					break;
				}
			}
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
					cout<<getGameDetails(i,_game)<<endl;
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
				addGame(newGame,_dateBase->get_file(),_game);
				//_game.push_back(new Game(newGame));
				//writeToFileinTheEnd(newGame);
				interpretGamesToTeamsStatus(_team,_game.at(_game.size()-1));
				string output = "user add a new game ";
				output+=newGame;
				writeToOUTPUTfile(output,_dateBase->get_output());
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
							writeToFileinTheEnd(newTeam,_dateBase->get_file());
							string output = "user add a new team ";
							output+=newTeam;
							writeToOUTPUTfile(output,_dateBase->get_output());
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
				replace_line_in_file(oldTeam , newTeam, _dateBase->get_file(), _team , _game);
				string output = "user replace team name ";
				output+= oldTeam;
				output+=" to ";
				output+=newTeam;
				writeToOUTPUTfile(output,_dateBase->get_output());
				//cout<< "Team name updated"<<endl;
			}
			if (strAdmin.substr(0,14).compare("correctiongame")==0)
			{
				strAdmin = strAdmin.substr(strAdmin.find("game")+4,strAdmin.length());
				string gameNumber = strAdmin.substr(0,1);
				string sdate = strAdmin.substr(2,strAdmin.length());
				Date* date = checkDate(strAdmin.substr(2,strAdmin.length()));
				updateGame(gameNumber, sdate,_dateBase->get_file(),_team,_game);
			}
			if (strAdmin.substr(0,16).compare("correctiondelete")==0)
			{
				if(_isOpen)
				{
					int location = realInput.find("delete");
					string teamToRemove = realInput.substr(location+7,realInput.length());
					removeLine(teamToRemove,_dateBase->get_file());
					for (int i=0; i<_team.size();i++)
					{
						if (_team[i]->get_teamName().compare(teamToRemove)==0)
						{
							_team.erase(_team.begin()+i);
							string output = "user delete team ";
							output+= teamToRemove;
							writeToOUTPUTfile(output,_dateBase->get_output());
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
				updateGameDetails(home,guest,score,_dateBase->get_file(),_team,_game);
				interpretGamesToTeamsStatus(_team,_game.at(_game.size()-1));

			}
		}
		cout<<endl;
	}
}


void NBA_league::set_isOpen(int num)
{
	_isOpen = num;
}

int NBA_league::get_isOpen()
{
	return _isOpen;
}

vector<Team*> NBA_league::get_teams()
{
	return get_teams();
}

vector<Game*> NBA_league::get_games()
{
	return get_games();
}

//add a new line into the data base
void NBA_league::writeToFileinTheEnd(string line, fstream& file)
{
	League::writeToFileinTheEnd(line, file);
}

void NBA_league::writeToOUTPUTfile(string line, fstream& file)
{
	League::writeToOUTPUTfile(line,file);
}

//add a new line into the data base
void NBA_league::writeToFileinTheMiddel(string line, fstream& file)
{
	League::writeToFileinTheMiddel(line,file);
}

//interpret the team status into my vareables
void NBA_league::interpretGamesToTeamsStatus(vector<Team*>_team ,Game* game)
{
	//League::interpretGamesToTeamsStatus(_team,game);

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
			else _team[i]->increment_leaguePoints(0);
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
			else _team[i]->increment_leaguePoints(0);
		}
	}
	sortTable(_team);
}

DataBase* NBA_league::get_dataBase()
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
void NBA_league::printLeagueTabel(vector<Team*>_team)
{
	League::printLeagueTabel(_team);
}

//sort the table
void NBA_league::sortTable (vector<Team*>_team)
{
	League::sortTable(_team);
}

//change line in the file if they macth
void NBA_league::replace_line_in_file(string search_string , string replace_string,fstream& file,vector<Team*>& _team , vector<Game*> &_game)
{
	League::replace_line_in_file( search_string ,  replace_string, file, _team , _game);
}

void NBA_league::addGame(string line,fstream&file, vector<Game*>_game)
{
	League::addGame(line,file,_game);
}

void NBA_league::removeLine (string line , fstream& file)
{
	League::removeLine(line,file);
}

void NBA_league::updateGameDetails(string home,string guest, string score,fstream& file,vector<Team*>_team ,vector<Game*>_game)
{
	League::updateGameDetails(home,guest,score,file,_team,_game);
}

void NBA_league::updateGame(string gameNumber,string date, fstream& file,vector<Team*>_team,vector<Game*>_game )
{
	League::updateGame(gameNumber,date, file,_team,_game);
}

string NBA_league:: getGameDetails(int i,vector<Game*>_game)
{
	/*
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	*/
	return League::getGameDetails(i,_game);
}

string NBA_league:: getFullGameDetails(Game * game)
{
	/*
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	*/
	return League::getFullGameDetails(game);

}

string NBA_league:: getFullGameDetails(int i,vector<Game*>_game)
{
	return League::getFullGameDetails(i,_game);
}
