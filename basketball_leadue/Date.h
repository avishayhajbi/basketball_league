#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include <regex>

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

};

#endif
