#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
#include "conio.h"
#include "Cinema.h"
using namespace std;

class Order
{
private:
	int row;
	char seat;

public:
	int film;
	int day;
	int time;
	Cinema* cinema;

	Order();

	int ChoosePlace();
	int ChooseRow();
	int ChooseSeat();

	void PrintInfo();
};