#include "DataBase.h"


DataBase::DataBase()
{
    _myfile.open("");
    _output.open("");
}

DataBase::DataBase(char* db)
{
	try
	{
	     ifstream f(db);
        if (f.good()) {
            f.close();
            _myfile.open (db, ios::in | ios::out | ios::app );
        }
		// The file exists, and is open for input
		else
            {
                _myfile.open (db, ios::in | ios::out | ios::app );
                _myfile<<db<<endl;
                _myfile<<"TEAM"<<endl;
                _myfile<<"END"<<endl;
            }
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
void DataBase::set_output(char* out)
{
    if (out != NULL)
    _output.open (out, ios::in | ios::out | ios::app );
    else _output.close();
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
			_myfile <<"basketball_league2013.txt"<<endl;
			_myfile <<"TEAM"<<endl;
			_myfile <<"END"<<endl;
		}
		_output.open("db_basketball2013.txt", ios::in | ios::out | ios::app );


}
