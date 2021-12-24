#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Film
{
private:
	string name;	//название фильма
	string age;		//возрастное ограничение
	string duration;	//продолжительность фильма
	string rejisser;//режиссеры
	string short_description;	//краткое описание фильма
	string main_role;	//главные роли
	string number_zal;	//номер зала для показа

	//??????????
	string price[9];	//стоимость билета		//??????????
	string time[9];	//время сеанса		//??????????
	string mesta[9];	//места в зале		//??????????
	string rand[9];

	friend class File_O;
	friend class Menu;
	friend class Order;
	friend class Cinema;
};

