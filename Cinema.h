#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
#include "Film.h"
using namespace std;

class Cinema
{
public:
	int films_number;	//количество фильмов в прокате

private:
	string name;	//название кинотеатра
	string adress;	//адрес кинотеатра
	string cashiers[5];	//кассиры кинотеатра		// сделать класс кассиров с информацией о них?

	string inn;		//данные для чека
	string rnm;		//данные для чека
	
	

	Film films[10];
	
public:
	void ChangeName();	//измение названия кинотеатра
	void ChangeAdress();	//измение адреса кинотеатра
	void ChangeInn();		//изменение ИНН кинотеатра
	void ChangeRnm();		//изменение РНМ кинотеатра
	void ChangeCashier();	//изменение кассиров
	void check_cash();

	void DelFilm(int num_film);
	void ChangeFilm(int num_punkt, int num_film);
	int CheckTime(int time, int num_seans, int duration);
	void TimeAuto(int duration);

	void InputName();	//Ввод названия кинотеатра
	void InputCashier();	//ввод ФИО кассира
	void InputINN();		//ввод ИНН
	void InputAdress();		//ввод адреса
	void InputRNM();		//ввод РНМ

	string NewHall();	//генерация зала (посадка)

	void NameOut();	//вывод названия кинотеатра

	friend class File_O;
	friend class Menu;
};

