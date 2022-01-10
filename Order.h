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
	int sum;

public:
	int film;
	int day;
	int time;
	Cinema* cinema;

	Order();

	int ChoosePlace();
	int ChooseRow();
	int ChooseSeat();
	void Buy(bool reserved);
	void Reserve();
	void ChooseAction();
	void PayReserve(int number);

	void PrintInfo();
	void PrintResult();

	void Check(bool card);
	void Tickets();
	void Clean();
};