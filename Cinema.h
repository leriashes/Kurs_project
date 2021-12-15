#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
#include "Film.h"
using namespace std;

class Cinema
{
private:
	string name;	//название кинотеатра
	string adress;	//адрес кинотеатра
	string cashiers[5];	//кассиры кинотеатра		// сделать класс кассиров с информацией о них?

	string inn;		//данные для чека
	string rnm;		//данные для чека
	
	int films_number;	//количество фильмов в прокате

	Film films[10];
	
public:
	void InputName();	//Ввод название кинотеатра
	void InputCashier();	//ввод ФИО кассира
	string NewHall(int number_film, int number);

	void NameOut();

	friend class File_O;
	friend class Menu;
};

