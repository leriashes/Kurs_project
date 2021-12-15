#include "Time.h"

string Time::date_ret(int n)
{
	time_t present;
	time_t tommorow_1;
	time_t tommorow_2;

	time(&present);
	tommorow_1 = present + 24 * 3600;
	tommorow_2 = present + 2 * 24 * 3600;
	if (n == 0)
	{
		return(convTime(present));
	}
	else if (n == 1)
	{
		return(convTime(tommorow_1));
	}
	else if (n == 2)
	{
		return(convTime(tommorow_2));
	}

}

string Time::convTime(time_t t)
{
	tm* ptm = gmtime(&t);
	string str;
	return (week[ptm->tm_wday - 1] + " " + to_string(ptm->tm_mday) + "." + to_string(ptm->tm_mon + 1) + "." + to_string(ptm->tm_year + 1900));
}
