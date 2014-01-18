#include "League.h"


string League::getGameDetails(int i,vector<Game*>_game)
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
	out.str("");
	send+= ":";
	out <<(_game[i]->get_finalScoreGUEST());
	send+= out.str();
	out.str("");
	send+= " (";
	out <<(_game[i]->get_halftimeScoreHOME());
	send+= out.str();
	out.str("");
	send+= ":";
	out <<(_game[i]->get_halftimeScoreGUEST());
	send+= out.str();
	out.str("");
	send+= ")";

	return 	send;

}

string League::getFullGameDetails(Game * game)
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
	out.str("");
	send+= ".";
	out <<(game->get_gameNumber());
	send+= out.str();
	out.str("");
	send+= ", ";
	send+= game->get_date()->get_month();
	send+= ". ";
	out <<(game->get_date()->get_day());
	send+= out.str();
	out.str("");
	send+= ", ";
	out <<(game->get_date()->get_year());
	send+= out.str();
	out.str("");
	send+= " ";
	send+= game->get_home();
	send+= " - ";
	send+= game->get_guest();
	send+= " ";
	out <<(game->get_finalScoreHOME());
	send+= out.str();
	out.str("");
	send+= ":";
	out <<(game->get_finalScoreGUEST());
	send+= out.str();
	out.str("");
	send+= " (";
	out <<(game->get_halftimeScoreHOME());
	send+= out.str();
	out.str("");
	send+= ":";
	out <<(game->get_halftimeScoreGUEST());
	send+= out.str();
	out.str("");
	send+= ")";
	return send;

}

string League::getFullGameDetails(int i,vector<Game*>_game)
{
	std::stringstream out;
	string send;
	//to_string();
	out <<(_game[i]->get_round());
	send+= out.str();
	out.str("");
	send+= ".";
	out <<(_game[i]->get_gameNumber());
	send+= out.str();
	out.str("");
	send+= ", ";
	send+= _game[i]->get_date()->get_month();
	send+= ". ";
	out <<(_game[i]->get_date()->get_day());
	send+= out.str();
	out.str("");
	send+= ", ";
	out <<(_game[i]->get_date()->get_year());
	send+= out.str();
	out.str("");
	send+= " ";
	send+= _game[i]->get_home();
	send+= " - ";
	send+= _game[i]->get_guest();
	send+= " ";
	out <<(_game[i]->get_finalScoreHOME());
	send+= out.str();
	out.str("");
	send+= ":";
	out <<(_game[i]->get_finalScoreGUEST());
	send+= out.str();
	out.str("");
	send+= " (";
	out <<(_game[i]->get_halftimeScoreHOME());
	send+= out.str();
	out.str("");
	send+= ":";
	out <<(_game[i]->get_halftimeScoreGUEST());
	send+= out.str();
	out.str("");
	send+= ")";
	return send;
}

/*check if the date is valid or not*/
Date* League::checkDate(string data)
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

//when the program starts it read from the data base
void League::readFromFile(fstream& file ,vector<Team*>& _team , vector<Game*> &_gameArr,int &_isOpen)
{
	/*
	this function reads league schedule from file
	*/
	
	string line;
	if (file.is_open())
	{
		while ( getline (file,line) )
		{
			if (line == "TEAM") // \r in linux
			{
				while (getline (file,line))
				{
					if (line == "END") break;
					_team.push_back(new Team(line));
				}
			}
			if (line == "START")
			{
				_isOpen=0;
				while ( getline (file, line))
				{
					if (line == "END") break;
					/* change by league type*/
					string _home;
					string _guest;
					Date* _date;
					int _round;
					int _game;
					int _finalScoreHOME;
					int _finalScoreGUEST;
					int _halftimeScoreHOME;
					int _halftimeScoreGUEST;

					//round
					string token = line.substr(0, 1);
					_round = atoi(token.c_str());
					//game
					token = line.substr(2,1);
					_game = atoi(token.c_str());
					//date
					token = line.substr(5,13);
					_date = new Date(token);

					//team names and score
					token = line.substr(19, line.length());
					string splited;
					int locationInLine=19;
					for (int i=0 ; i < token.length(); i++)
					{
						string temp = token.substr(i,1);
						if (token.length()>(i+4) && token.at(i)==' ' && token.at(i+1)=='-' && token.at(i+2)==' ')
						{
							_home=splited;
							locationInLine+=i+3;
							token=line.substr(locationInLine,line.length());
							splited.clear();
							break;
						}
						splited.append(temp);
					}
					for (int i=0 ; i < token.length(); i++)
					{
						string temp = token.substr(i,1);
						try{
							if (token.length()>(i+4) && atoi(temp.c_str())>0)
							{
								_guest=splited.substr(0,splited.length()-1);
								locationInLine+=i;
								token=line.substr(locationInLine,line.length());
								splited.clear();
								break;
							}
						}
						catch (exception e){};
						splited.append(temp);
					}
					int tempFound= token.find(':');
					locationInLine+=tempFound+1;
					string temp = token.substr(0, tempFound);
					_finalScoreHOME=atoi(temp.c_str());
					token=line.substr(locationInLine,line.length());

					tempFound= token.find(' ');
					locationInLine+=tempFound+1;
					temp = token.substr(0, tempFound);
					_finalScoreGUEST=atoi(temp.c_str());
					token=line.substr(locationInLine,line.length());

					tempFound= token.find('(');
					locationInLine+=tempFound+1;
					token=line.substr(locationInLine,line.length());

					tempFound= token.find(':');
					locationInLine+=tempFound+1;
					temp = token.substr(0, tempFound);
					_halftimeScoreHOME=atoi(temp.c_str());
					token=line.substr(locationInLine,line.length());

					tempFound= token.find(')');
					locationInLine+=tempFound+1;
					temp = token.substr(0, tempFound);
					_halftimeScoreGUEST=atoi(temp.c_str());

					/* end of change */
					Game* game = new Game(_home,_guest,_date,_round,_game,_finalScoreHOME,_finalScoreGUEST,_halftimeScoreHOME,_halftimeScoreGUEST);
					_gameArr.push_back(game);
					interpretGamesToTeamsStatus(_team,game);
				}
			}
		}
	}
	file.clear();
	file.seekg(0, file.beg);
}

void League::writeToFileinTheEnd(string line, fstream& file)
{
	/*
	write the data into the data base file
	*/
	string inbuf;
	vector<string> vec;
	file.clear();
	file.seekg(0, file.beg);
	while (getline(file, inbuf))
	{
		vec.push_back(inbuf);
	}
	if (vec[vec.size()-1].compare("END")||vec[vec.size()-1].compare("END"))
	{
		vec.insert(vec.begin()+(vec.size()-1),line);
	}

	file.close();
	file.clear();

	for(int i =0; i<vec.size();i++)
	{
		file<<(vec[i])<<endl;
	}

}

void League::replace_line_in_file(string search_string , string replace_string,fstream& file,vector<Team*>& _team , vector<Game*> &_game)
{
	
	string inbuf;
	vector<string> vec;
	file.clear();
	file.seekg(0, file.beg);
	while (getline(file, inbuf))
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
								vec.push_back(getFullGameDetails(i,_game));
							}
							else if (_game[i]->get_guest().compare(search_string)==0)
							{
								_game[i]->set_guest(replace_string);
								vec.push_back(getFullGameDetails(i,_game));
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

	file.close();
	file.clear();

	for(int i =0; i<vec.size();i++)
	{
		file<<(vec[i])<<endl;
	}
}

void League::addGame(string line,fstream&file, vector<Game*>_game)
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

			/*check if the game is legal*/
			Game* addgame= new Game(home,guest,date,atoi(round.c_str()),atoi(game.c_str()),atoi(finalScoreHOME.c_str()),atoi(finalScoreGUEST.c_str()),atoi(halftimeScoreHOME.c_str()),atoi(halftimeScoreGUEST.c_str()));

			//check if the game is already exist
			if(_game.at(_game.size()-1)->get_round() >= (addgame->get_round()) && _game.at(_game.size()-1)->get_gameNumber() < (addgame->get_gameNumber()))
				return;

			_game.push_back(addgame);
			writeToFileinTheEnd(getFullGameDetails(addgame),file);
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

void League::updateGameDetails(string home,string guest, string score,fstream& file,vector<Team*>_team , vector<Game*>_game)
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
			string oldGame = getFullGameDetails(_game[i]);
			//Game* newGame= new Game(getFullGameDetails(i,_game));
			_game[i]->set_finalScoreHOME(temp);
			_game[i]->set_finalScoreGUEST(temp2);
			/*	string oldScore;
			oldScore += to_string(_game[i]->get_finalScoreHOME());
			oldScore += ":";
			oldScore += to_string(_game[i]->get_finalScoreGUEST());*/
			replace_line_in_file(oldGame,getFullGameDetails(_game[i]), file, _team , _game);
			interpretGamesToTeamsStatus(_team, _game[i]);
			break;
		}
	}
}

void League::updateGame(string gameNumber,string date, fstream& file,vector<Team*>_team,vector<Game*>_game)
{
	for (int i=0 ; i< _game.size(); i++)
	{
		if (_game[i]->get_round()== atoi(gameNumber.c_str()))
		{

			string oldGame = getFullGameDetails(_game[i]);
			//Game* newGame= new Game(getFullGameDetails(i,_game));
			_game[i]->set_date(checkDate(date));
			/*	string oldScore;
			oldScore += to_string(_game[i]->get_finalScoreHOME());
			oldScore += ":";
			oldScore += to_string(_game[i]->get_finalScoreGUEST());*/
			replace_line_in_file(oldGame,getFullGameDetails(_game[i]), file, _team , _game);
			//_game.at(i) = newGame;
			interpretGamesToTeamsStatus(_team,_game[i]);
			break;
		}
	}
}

void League::removeLine(string line , fstream& file)
{
	/*
	delete the data from the data base file
	*/
	string inbuf;
	vector<string> vec;
	file.clear();
	file.seekg(0, file.beg);
	while (getline(file, inbuf))
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

	file.close();
	file.clear();

	for(int i =0; i<vec.size();i++)
	{
		file<<(vec[i])<<endl;
	}
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

void League::printLeagueTabel(vector<Team*>_team)
{
	int length=0;
	// taking the longest team name
	if (!_team.empty())
	{
	for (int i=0;i<_team.size(); i++)
	{
		if(_team[i]->get_teamName().length() > length)
		{
			length = _team[i]->get_teamName().length();
		}
	}

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
}

void League::sortTable(vector<Team*>_team)
{
	std::sort(_team.begin(),_team.end(),your_comparer);
}

void League::interpretGamesToTeamsStatus(vector<Team*>_team ,Game* game)
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
	sortTable(_team);
}

void League::writeToFileinTheMiddel(string line, fstream& file)
{
	/*
	write the data into the data base file
	*/
	string inbuf;
	vector<string> vec;
	file.clear();
	file.seekg(0, file.beg);
	while (getline(file, inbuf))
	{
		vec.push_back(inbuf);
	}

	/* here i decide when to insert my new line
	if (vec[vec.size()-1].compare("END")||vec[vec.size()-1].compare("END\n"))
	{
	vec.insert(vec.begin()+(vec.size()-1),line);
	}*/

	file.close();
	file.clear();
	

	for(int i =0; i<vec.size();i++)
	{
		file<<(vec[i])<<endl;
	}
}

void League::writeToOUTPUTfile(string line, fstream& file)
{
	 ifstream f(reinterpret_cast<char*>(&file));
        if (!f.good()) {
		file.open (reinterpret_cast<char*>(&file), ios::in | ios::out | ios::app );
	}else f.close();

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
	file.clear();
	file.seekg(0, file.beg);
	while (getline(file, inbuf))
	{
		vec.push_back(inbuf);
	}

	vec.insert(vec.begin()+(vec.size()),s);
	vec.insert(vec.begin()+(vec.size()),line);


	file.close();
	file.clear();
	file.open (reinterpret_cast<char*>(&file), ios::in | ios::out | ios::app );


	for(int i =0; i<vec.size();i++)
	{
		file<<(vec[i])<<endl;
	}

}