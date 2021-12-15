#pragma once
#include "Cinema.h"
#include "File_O.h"
#include "Time.h"

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
	int items_number;
	int item;
	int num_day;	//����� ��� ��� ������� ������
	int num_film;	//����� ���������� ������
	int num_time;
	//char menu_text[512];

public:
	bool admin;
	Cinema* cinema;

	Menu();
	Menu(int item_num);
	~Menu();

	void Cashier();
	void Admin();
	//void Start();
	void ChooseItem();
	void File();	//��������� � ����?  ������ k?
	void FilmList();
	void Description();

	int GetItem();
};
