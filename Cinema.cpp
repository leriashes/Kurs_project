#include "Cinema.h"

void Cinema::InputName()
{
	name = "";
	do
	{
		cout << "Введите название кинотеатра: ";
		cin >> name;
		cout << "\n";
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{
		cout << "Введите ФИО кассира: ";
		cin >> full_name;
		cout << "\n";
		//проверка на существование данного кассира в базе???
	} while (full_name == "");
	
	//присваивание кассиру
}
