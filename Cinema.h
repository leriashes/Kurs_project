#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Film.h"
using namespace std;

class Cinema
{
public:
	int films_number;	//количество фильмов в прокате

private:
	string name;	//название кинотеатра
	string address;	//адрес кинотеатра
	string cashiers[5];	//кассиры кинотеатра		// сделать класс кассиров с информацией о них?

	string inn;		//данные для чека
	string rnm;		//данные для чека
	string otchet_vsego;	//сумма выручки за весь период
	string otchet_today;	//сумма выручки за сегодняшний день
	string promo[10][2];	//промокоды
	int promo_number = 0;
	int cashiers_number = 0;
	
	

	Film films[10];
	
public:
	void ChangeName();	//измение названия кинотеатра
	void ChangeAdress();	//измение адреса кинотеатра
	void ChangeINN();		//изменение ИНН кинотеатра
	void ChangeRNM();		//изменение РНМ кинотеатра
	void ChangeCashier();	//изменение кассиров
	void check_cash();

	/// 
	/// Перенести в класс USER
	/// 
	void ListPromo(int k);	//вывод списка промокодов
	void DelPromo();		//удаление промокода
	void RedPromo();		//редактирование информации о промокоде
	void NewPromo();		//добавление нового промокода
	string NewPromoName(string message);
	string NewPromoValue(string message);

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
	friend class Order;
};

