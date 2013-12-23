#include "DataBase.h"

DataBase::DataBase()
{
	try 
	{
		
		// The file exists, and is open for input
		_myfile.open ("db_basketball2013.txt", ios::in | ios::out | ios::app );
		//_output.open("db_basketball2013.txt", ios::in | ios::out | ios::app );	

	}
	catch (exception e)
	{
		cout<<"can not open data base file"<<endl;
	}
}

fstream& DataBase::get_file()
{
	return _myfile;
}
fstream& DataBase::get_output()
{

	return _output;
}
void DataBase::initDB()
{
	
	ifstream my_file("db_basketball2013.txt");
		if (my_file.good())
		{
			my_file.close();
		  _myfile.open ("db_basketball2013.txt", ios::in | ios::out | ios::app );
		}
		// The file exists, and is open for input
		else 
		{
			_myfile.open ("db_basketball2013.txt", ios::in | ios::out | ios::app );
			_myfile <<"basketball_league2013"<<endl;
			_myfile <<"TEAM"<<endl;
			_myfile <<"END"<<endl;
		}
		_output.open("db_basketball2013.txt", ios::in | ios::out | ios::app );	

		
}