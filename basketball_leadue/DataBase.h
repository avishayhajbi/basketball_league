#ifndef DATA_BASE_H
#define DATA_BASE_H
#define _CRT_SECURE_NO_DEPRECATE
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

class DataBase
{
private:
	fstream _myfile;
	fstream _output;
public:
	DataBase();
	DataBase(char* db);
	fstream& get_file();
	fstream& get_output();
	void set_output(char* out);
	void initDB ();

};
#endif
