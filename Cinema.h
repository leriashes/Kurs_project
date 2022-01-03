#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Film.h"
#include <thread>
using namespace std;

class Cinema
{
public:
	int films_number;	//количество фильмов в прокате
	int broni_number = 0;	//количество забронированных билетов
	int broni_zapis = 0;	//количество забронированных билетов под запись в файл

private:
	string name;	//название кинотеатра
	string address;	//адрес кинотеатра
	string cashiers[5];	//кассиры кинотеатра		// сделать класс кассиров с информацией о них?
	string id_cinema;
	string bron[100][8];

	string inn;		//данные для чека
	string rnm;		//данные для чека
	string otchet_vsego;	//сумма выручки за весь период
	string otchet_today;	//сумма выручки за сегодняшний день
	string promo[10][2];	//промокоды
	int promo_number = 0;
	int cashiers_number = 0;
	


	
	Film films[10];
	
public:
	bool CheckNameBron(int num);	//проверка имени фильма бронирования
	bool CheckDayBron(int num);	//проверка дня бронирования
	bool CheckPositionBron(int num);

	void BuyBron();		//проверка и выкуп билетов из брони
	void ChangeNameFilmBron(string new_znach, string old_znach);	//внесение изменений в информацию о фильме, если такие брони были
	void ChangeTimeFilmBron(string NameFilm, string NewTime, string OldTime);

	int SearchBron(string code);	//поиск брони по номеру
	void List_bron();	//вывод всех бронирований
	void ChangeName();	//измение названия кинотеатра
	void ChangeAdress();	//измение адреса кинотеатра
	void ChangeINN();		//изменение ИНН кинотеатра
	void ChangeRNM();		//изменение РНМ кинотеатра

	void ChangeCashier();	//изменение кассиров
	void ListCashier(int k);	//вывод кассиров

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
	string Convert_Time(int time);
	int DeConvert_Time(string time);
	void ListSell();

	void InputName();	//Ввод названия кинотеатра
	void InputCashier();	//ввод ФИО кассира
	void InputINN();		//ввод ИНН
	void InputAdress();		//ввод адреса
	void InputRNM();		//ввод РНМ
	void NewHallCinema(int number_film);	//генерация наполненности зала для нового фильма	
	void PriceInput(int num_film, int num);

	string NewHall();	//генерация зала (посадка)

	void NameOut();	//вывод названия кинотеатра

	friend class File_O;
	friend class Menu;
	friend class Order;
};

