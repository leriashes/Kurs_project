#include "Time.h" 

bool Time::loadingComplete = true;

string Time::RetDate(int n, int type)
{
	time_t days[4]; //today, tommorow, day after tommorow 

	time(&days[0]);
	days[1] = days[0] + 24 * 3600;
	days[2] = days[0] + 2 * 24 * 3600;
	days[3] = days[0] + 3 * 24 * 3600;
	return ConvTime(days[n], type);
}

string Time::ConvTime(time_t t, int type)
{
	string week[7] = { "ом", "бр", "яп", "вр", "ор", "яа", "бя" };
	tm* ptm = gmtime(&t);
	string result = "";
	if (type == 0)
	{
		if (ptm->tm_wday == 0)
		{
			ptm->tm_wday = 7;
		}
		result = week[ptm->tm_wday - 1] + " ";
	}
	if (to_string(ptm->tm_mday).size() == 1)
	{
		result = result + "0";
	}
	result = result + to_string(ptm->tm_mday) + ".";
	if (to_string(ptm->tm_mon + 1).size() == 1)
	{
		result = result + "0";
	}
	result = result + to_string(ptm->tm_mon + 1) + "." + to_string(ptm->tm_year + 1900);
	return result;
}


string Time::RetTime()
{
	std::time_t t = std::time(0);
	std::tm* local = std::localtime(&t);
	return "0";
}


void Time::PrintLoading()
{
	int i = 0;
	do
	{
		std::cout << '.';
		std::this_thread::sleep_for(0.3s);
		i++;
		if (i == 3)
		{
			i = 0;
			cout << "\b \b\b \b\b \b";
			std::this_thread::sleep_for(0.3s);
		}
	} while (!loadingComplete);
}
