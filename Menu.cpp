#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <conio.h>
#include "Time.h"
using namespace std;

Menu::Menu()
{ 
	items_number = 0;
	item = 0;
	admin = false;
	num_day = num_film = num_time = 0;
	cinema = NULL;
}

/*
Menu::Menu(const char* menu_text, int item_num)
{
	strcpy(this->menu_text, menu_text);
	this->menu_text[511] = '\0';
	this->item_num = item_num;
}*/

Menu::Menu(int items_number)
{
	this->items_number = items_number;
	item = 0;
	admin = false;
	num_day = num_film = num_time = 0;
	cinema = NULL;
}

Menu::~Menu()
{
}

void Menu::Cashier() 
{
	cinema->NameOut();
	cout << "1) Просмотр списка фильмов\n2) Вход в режим администратора\n\nESC - Выход";
	items_number = 2;
}

void Menu::Admin()
{
	if (admin)
	{
		cinema->NameOut();
		File();
		cout << "\n4) Добавление или удаление фильма\n5) Редактирование информации о фильме\n6) Добавление или удаление промокода\n7) Аннулирование билета\n8) Редактирование информации о кинотеатре\n\nESC - Выход из режима администратора";
		items_number = 8;
	}
	//меню администратора
}

void Menu::ChooseItem()
{
	do
	{
		item = -2;

		char symbol;
		symbol = _getch();

		if (symbol == 27)
		{
			Escape();
			item = -1;
		}
		else if (symbol >= '1' && symbol <= '9')
		{
			item = symbol - 48;
		}

	} while (item < -1 || item > items_number);

	return;
}

// ПЕРЕНЕСТИ ВЫВОД СПИСКА В КИНОТЕАТР?
void Menu::FilmList()
{
	cout << "0) Возврат в меню\n\n";
	cout << "Список фильмов:\n\n";
	for (int i = 0; i < cinema->films_number; i++)
	{
		cout << i + 1 << ") " << cinema->films[i].name << " (" << cinema->films[i].age << ")\n";
	}
	cout << "\n\nВыберите фильм (введите номер): ";
	items_number = cinema->films_number;
}

void Menu::ChooseFilm()
{
	num_film = 0;
	char symbol;

	do
	{
		symbol = _getch();

		if (symbol >= '0' && symbol <= '9')
		{
			if (num_film * 10 + symbol - 48 <= cinema->films_number)
			{
				if (symbol >= '1' || symbol == '0' && num_film > 0)
				{
					num_film = num_film * 10 + symbol - 48;
					printf("%c", symbol);
				}
				else
				{ 
					num_film = 0;
					break;
				}
			}
		}
		else if (symbol == '\b' && num_film > 0)
		{
			num_film /= 10;
			printf("\b \b");
		}
		else if (symbol == 27)
		{
			num_film = -1;
			Escape();
			break;
		}

	} while (symbol != 13 || num_film <= 0);

	item = num_film;

	return;
}

void Menu::Description()
{
	system("cls");
	const time_t tm = time(nullptr);

	/*char buf[64];
	strftime(buf, size(buf), "%d.%m.%Y", localtime(&tm));
	cout << buf << endl;*/
			
	//time_t t = time(0);
	std::tm* now = localtime(&tm); //было localtime(&t)
	cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
	
	

	//system("cls");

	
	
	/*
	cout << "yesterday : " << ConvTime(yesterday) << endl;
	cout << "present   : " << ConvTime(present) << endl;
	cout << "tommorow  : " << ConvTime(tommorow) << endl;
	*/
	
	//uni.DateRet(0);
	//uni.ConvTime(tm);
	
	cout << "\n\nНазвание: " << cinema->films[num_film - 1].name;
	cout << "\n\nОписание: " << cinema->films[num_film - 1].short_description;
	cout << "\n\nПродолжительность: " << cinema->films[num_film - 1].duration;
	cout << "\n\nРежиссер(-ы): " << cinema->films[num_film - 1].rejisser;
	cout << "\n\nВ главных ролях: " << cinema->films[num_film - 1].main_role;
	
	
	int k;
	int n;
	if (num_time == 0)
	{
		cout << "\n\nРасписание сеансов:";
		if (num_day == 0)
		{
			k = 0;
			n = 3;
		}
		else
		{
			k = num_day - 1;
			n = num_day;
		}

		for (int i = k; i < n; i++)
		{
			cout << "\n\n" << Time::RetDate(i) << "   Время   Цена билета";

			for (int j = 0; j < 3; j++)
			{

				cout << "\n                " << cinema->films[num_film - 1].time[3 * i + j] << "    " << cinema->films[num_film - 1].price[3 * i + j] << " руб.";
			}
		}

		if (num_day == 0)
		{

			cout << "\n\n1) " << Time::RetDate(0) << "\n2) " << Time::RetDate(1) << "\n3) " << Time::RetDate(2) << "\n\nВыберите дату: ";
		}
		else
		{
			cout << "\n\n";
			for (int i = 0; i < 3; i++)
			{
				cout << "\n" << (i + 1) << ") " << cinema->films[num_film - 1].time[(num_day - 1) * 3 + i];
			}
			cout << "\n\nВыберите время: ";
		}
		items_number = 3;
	}
	else
	{
		//cout << kinoteatr.filmi[num_film - 1].mesta[(num_day - 1) * 3 + (num_time - 1)];	//тест
		cout << "\n\n A B C D E F G H I J";
		for (int i = 0; i < 10; i++)
		{
			cout << "\n" << (i + 1) << "  ";
			for (int j = 0; j < 10; j++)
			{
				if (cinema->films[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '0')	//место свободно
				{
					cout << "- ";
				}
				else if (cinema->films[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '1')	//место забронировано
				{
					cout << "? ";
				}
				else if (cinema->films[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '2')	//место выкуплено
				{
					cout << "X ";
				}
			}
		}
		//cout << "\n\nВведите место: ";


	}
}

void Menu::Escape()
{
	if (cinema != NULL && cinema->name != "")
		cinema->NameOut();
	else
		system("cls");
	cout << "Вы уверены что хотите выйти? \nДа - esc, нет - любая клавиша.";
	char choice = _getch();
	if (choice == 27)
		exit(0);
	return;
}

void Menu::Clear()
{
	num_day = num_film = num_time = 0;
}


//две функции без k ????????????????????????????????? создать статичсекую переменную
void Menu::File()
{
	system("cls");
	if (admin)
		cinema->NameOut();

	items_number = 3;

	cout << "1) Открыть файл по умолчанию в домашнем каталоге (\"kino_v_teatre\")\n2) Открыть файл по заданному пути";
	if (admin)
		cout << "\n3) Создание нового файла";
	else
		cout << "\n3) Вход в режим администратора\n\nESC - выход";
	
	return;
}

int Menu::GetItem()
{
    return item;
}


