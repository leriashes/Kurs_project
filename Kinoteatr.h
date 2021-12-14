#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
using namespace std;

class Kinoteatr
{
public:
	string name;	//название кинотеатра
	string adress;	//адрес кинотеатра
	string kassirs[5];	//кассиры кинотеатра
	string inn;		//данные для чека
	string rnm;		//данные для чека
	
	int kol_vo_filmov;	//количество фильмов в прокате

	struct film
	{
		string name;	//название фильма
		string age;		//возрастное ограничени
		string duration;	//продолжительность фильма
		string rejisser;//режиссеры
		string short_description;	//краткое описание фильма
		string main_role;	//главные роли
		string price[9];	//стоимость билета
		string time[9];	//время сеанса
		string mesta[9];	//места в зале
	};
	film filmi[10];
	

	void new_name();	//Ввод название кинотеатра
	void new_kassir();	//ввод ФИО кассира

};

