#include "Date.h"

namespace YearMonths
{
    enum Months { Jan=1, Feb=2, Mar=3, Apr=4, May=5, Jun=6, Jul=7, Aug=8, Sep=9, Oct=10, Nov=11, Dec=12 };

    char* selectMonth(int month)
    {
        if (month == Months::Jan) // Enumerator must be qualified by enum type
        { return "Jan";}
		if (month == Months::Feb) // Enumerator must be qualified by enum type
        { return "Feb";}
		if (month == Months::Mar)
        { return "Mar";}
		if (month == Months::Apr)
        { return "Apr";}
		if (month == Months::May)
        { return "May";}
		if (month == Months::Jun)
        { return "Jun";}
		if (month == Months::Jul)
        { return "Jul";}
		if (month == Months::Aug)
        { return "Aug";}
		if (month == Months::Sep)
        { return "Sep";}
		if (month == Months::Oct)
        { return "Oct";}
		if (month == Months::Nov)
        { return "Nov";}
		if (month == Months::Dec)
        { return "Dec";}
    }
}

bool is_number(const std::string& s)
{
	bool has_only_digits = true;
	for (size_t n = 0; n < s.length(); n++)
	  {
	  if (!isdigit( s[ n ] ))
		{
		has_only_digits = false;
		break;
		}
	  return has_only_digits;
  }
}
Date::Date()
{
	
}
Date::Date(string line)
{

		line.erase( std::remove(line.begin(),line.end(), ' '), line.end() );

		//month
		string token = line.substr(0,3);
		if (is_number(token)) _month = YearMonths::selectMonth(atoi(token.c_str()));
		else _month=token;
		//day
		token = line.substr(4,2);
		_day = atoi(token.c_str());
		//year
		token = line.substr(7, 4);
		_year = atoi(token.c_str());
		
}
Date::Date (string day,string month,string year)
{
	_day = atoi(day.c_str());
	if (is_number(month)) _month = YearMonths::selectMonth(atoi(month.c_str()));
	else _month=month;
	_year = atoi(year.c_str());
}

int Date::get_day()
{
	return _day;
}

string Date::get_month()
{
	return _month;
}

int Date::get_year()
{
	return _year;
}

bool Date::operator==(const Date& right)const
{
	string m = _month;
	std::transform(m.begin(), m.end(), m.begin(), ::tolower);
	string &wr = const_cast <string &> (right._month);
	string r = wr;
	std::transform(r.begin(), r.end(), r.begin(), ::tolower);
	if (_day == right._day)
	{
		if (m.compare(r)==0)
		{
			if (_year == right._year)
			{
				return true;
			}
		}
	}
	return false;
}
