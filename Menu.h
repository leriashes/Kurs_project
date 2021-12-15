#pragma once
#include "Kinoteatr.h"
#include "Universal.h"

class Menu
{
	struct tm
	{
		int tm_sec;   // seconds of minutes from 0 to 61
		int tm_min;   // minutes of hour from 0 to 59
		int tm_hour;  // hours of day from 0 to 24
		int tm_mday;  // day of month from 1 to 31
		int tm_mon;   // month of year from 0 to 11
		int tm_year;  // year since 1900
		int tm_wday;  // days since sunday
		int tm_yday;  // days since January 1st
		int tm_isdst; // hours of daylight savings time
	};

public:
	int item_num;
	int menu_number;
	int num_day;	//номер дня при покупке билета
	int num_film;	//номер выбранного фильма
	int num_time;
	//char menu_text[512];

public:
	//Menu();
	//Menu(const char* menu_text, int item_num);
	//~Menu();
	//void print();

	void User_kassir();
	void Start_menu();
	void Input_number();
	void File_choice(int k);
	void Spisok_kino(Kinoteatr kinoteatr);
	void Opisanie(Kinoteatr kinoteatr);
};
