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
	int films_number;		
	int broni_number = 0;		
	int broni_zapis = 0;	
private:
	string name;		
	string address;		
	string cashiers[5];		
	string id_cinema;
	string bron[100][8];

	string inn;			
	string rnm;			
	string otchet_vsego;		
	string otchet_today;		
	string promo[10][2];		
	int promo_number = 0;
	int cashiers_number = 0;
	Film films[10];
	
public:
	int SearchBron(string code);		
	bool CheckBron(int num);		
	bool CheckNameBron(int num);		
	bool CheckDayBron(int num);		
	bool CheckPositionBron(int num);	
	void ChangeNameFilmBron(string new_znach, string old_znach);		
	void ChangeTimeFilmBron(string NameFilm, string NewTime, string OldTime);
	void DelBron(int num);

	
	void List_bron();		
	void ChangeName();		
	void ChangeAdress();		
	void ChangeINN();			
	void ChangeRNM();		
	void ChangeCashier();		
	void ListCashier(int k);	
	void ListPromo(int k);		
	void DelPromo();			
	void RedPromo();			
	void NewPromo();			
	string NewPromoName(string message);
	string NewPromoValue(string message);

	void DelFilm(int num_film);		
	void ChangeFilm(int num_punkt, int num_film);
	int CheckTime(int time, int num_seans, int duration);
	void TimeAuto(int duration);
	string Convert_Time(int time);
	int DeConvert_Time(string time);	
	void ListSell();

	void InputName();		
	void InputCashier();		
	void InputINN();			
	void InputAdress();			
	void InputRNM();			
	void NewHallCinema(int number_film);		
	void PriceInput(int num_film, int num);
	void NewCinema();
	string NewID();

	string NewHall();	
	void NameOut();	
	friend class File_O;
	friend class Menu;
	friend class Order;
};

