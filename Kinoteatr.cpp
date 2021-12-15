#include "Kinoteatr.h"
#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <conio.h>


void Kinoteatr::New_name()
{
	do
	{
		cout << "Введите название кинотеатра:";
		cin >> name;
	} while (name == "");
}

void Kinoteatr::New_kassir()
{
	string FIO;

	do
	{
		cout << "Введите ФИО кассира: ";
		cin >> FIO;
		//проверка на существование данного кассира в базе???
	} while (FIO == "");
}

string Kinoteatr::New_zal(int number_film, int number)
{
	string temp;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int num = rand() % 3;
		temp = temp + to_string(num);
	}
	//cout << filmi[number_film].mesta[number];	//тест
	//cout << filmi[number_film].mesta[(number_d - 1) * 3 + (number_t - 1)];	//тест
	//_getch();
	return (temp);
}
