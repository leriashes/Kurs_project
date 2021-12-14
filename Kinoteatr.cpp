#include "Kinoteatr.h"

void Kinoteatr::new_name()
{
	do
	{
		cout << "Введите название кинотеатра:";
		cin >> name;
	} while (name == "");
}

void Kinoteatr::new_kassir()
{
	string FIO;
	
	do
	{
		cout << "Введите ФИО кассира: ";
		cin >> FIO;
		//проверка на существование данного кассира в базе???
	} while (FIO == "");
	

}
