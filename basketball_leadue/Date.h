#ifndef DATE_H
#define DATE_H
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
//#include <regex>
#include <cctype>
#include <stdio.h>
using namespace std;


class Date
{
private:
	int _day;
	string _month;
	int _year;
public:
	Date();
	Date (string day,string month,string year);
	Date(string line);
	int get_day();
	string get_month();
	int get_year();
	Date* get_date();
	bool operator==(const Date& right)const;
	int getSize();
};

#endif
