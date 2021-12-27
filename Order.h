#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "conio.h"
#include <Windows.h>
#include "Cinema.h"
#include <time.h>
using namespace std;

class Order
{
private:
	int row;
	char seat;
	int num;
	int sale;

public:
	int film;
	int day;
	int time;
	Cinema* cinema;

	Order();

	int ChoosePlace();
	int ChooseRow();
	int ChooseSeat();
	void Buy();
	void Reserve();
	void ChooseAction();

	void PrintInfo();
	void PrintResult();

	void Check();
	void Tickets();
	void Clean();

	void CheckNal();
	void CheckKarta();
};