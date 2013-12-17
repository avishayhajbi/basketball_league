#include "DataBase.h"

DataBase::DataBase()
{
	try 
	{
		_myfile.open ("basketball2013.txt", ios::in | ios::out | ios::app );
		//_out.open("basketball2013.txt", std::ios::app);	
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
