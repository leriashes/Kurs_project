#include "Time.h"

string Time::RetDate(int n)
{
	time_t days[3];	//today, tommorow, day after tommorow

	time(&days[0]);
	days[1] = days[0] + 24 * 3600;
	days[2] = days[0] + 2 * 24 * 3600;

	return ConvTime(days[n]);
}

string Time::ConvTime(time_t t)
{
	string week[7] = { "ÏÍ", "ÂÒ", "ÑĞ", "×Ò", "ÏÒ", "ÑÁ", "ÂÑ" };
	tm* ptm = gmtime(&t);
	if (ptm->tm_wday == 0)
		ptm->tm_wday = 7;
	string result = week[ptm->tm_wday - 1] + " " + to_string(ptm->tm_mday) + "." + to_string(ptm->tm_mon + 1) + "." + to_string(ptm->tm_year + 1900);
	return result;
}
