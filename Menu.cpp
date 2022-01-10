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
	cinema = NULL;
}

Menu::Menu(int items_number)
{
	this->items_number = items_number;
	item = 0;
	admin = false;
	cinema = NULL;
}

Menu::~Menu()
{
}

void Menu::Cashier() 
{
	if (cinema != NULL && cinema->name != "")
		cinema->NameOut();
	else
		system("cls");
	cout << "1) Просмотр списка фильмов\n2) Оплата забронированных билетов\n3) Вход в режим администратора\n\nESC - Выход";
	items_number = 3;

	return;
}

void Menu::Admin(File_O fileo)
{
	items_number = 3;
	if (cinema != NULL && cinema->name != "")
		cinema->NameOut();
	else
		system("cls");
	cout << "0) Выход из режима администратора\n\n1) Открыть файл по умолчанию в домашнем каталоге (\"kino_v_teatre\")\n2) Открыть файл по заданному пути\n3) Создание нового файла\n";
	if (fileo.path != "" && fileo.path != "0")
	{
		cout << "4) Редактирование информации о фильмах в прокате\n5) Редактирование информации о промокодах\n6) Аннулирование билета\n7) Редактирование информации о кинотеатре\n8) Просмотр отчетов о продажах";
		items_number = 8;
	}

	return;
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
		else if (symbol >= '0' && symbol <= '9')
		{
			item = symbol - 48;
		}

	} while (item < -1 || item > items_number);

	return;
}

void Menu::FilmList()
{
	cout << "0) Возврат в меню\n\n";
	if (cinema->films_number > 0)
	{
		cout << "Список фильмов:\n\n";
		for (int i = 0; i < cinema->films_number; i++)
		{
			cout << i + 1 << ") " << cinema->films[i].name << " (" << cinema->films[i].age << ")\n";
		}
		cout << "\n\nВыберите фильм (введите номер): ";
		items_number = cinema->films_number;
	}
	else
	{
		cout << "Список фильмов пуст.";
		items_number = 0;
	}

	return;
}

void Menu::Description(Order& order)
{
	cinema->NameOut();
	cout << "0 - назад\n";
	const time_t tm = time(nullptr);
	std::tm* now = localtime(&tm);
	
	cout << "\nНазвание: " << cinema->films[order.film - 1].name;
	cout << "\n\nОписание: " << cinema->films[order.film - 1].short_description;
	cout << "\n\nПродолжительность (мин.): " << cinema->films[order.film - 1].duration;
	cout << "\n\nВозрастное ограничение: " << cinema->films[order.film - 1].age;
	cout << "\n\nРежиссер(-ы): " << cinema->films[order.film - 1].rejisser;
	cout << "\n\nВ главных ролях: " << cinema->films[order.film - 1].main_role;
	
	
	int k;
	int n;
	if (order.time == 0)
	{
		cout << "\n\nРасписание сеансов:";
		if (order.day == 0)
		{
			k = 0;
			n = 3;
		}
		else
		{
			k = order.day - 1;
			n = order.day;
		}

		for (int i = k; i < n; i++)
		{
			cout << "\n\n" << Time::RetDate(i) << "   Время   Цена билета";

			for (int j = 0; j < 3; j++)
			{

				cout << "\n                " << cinema->films[order.film - 1].time[3 * i + j] << "    " << cinema->films[order.film - 1].price[3 * i + j] << " руб.";
			}
		}

		if (order.day == 0)
		{

			cout << "\n\n1) " << Time::RetDate(0) << "\n2) " << Time::RetDate(1) << "\n3) " << Time::RetDate(2) << "\n\nВыберите дату: ";
		}
		else
		{
			cout << "\n\n";
			for (int i = 0; i < 3; i++)
			{
				cout << "\n" << (i + 1) << ") " << cinema->films[order.film - 1].time[(order.day - 1) * 3 + i];
			}
			cout << "\n\nВыберите время: ";
		}
		items_number = 3;
	}
	else
	{
		cout << "\n\n   A B C D E F G H I J";
		for (int i = 0; i < 10; i++)
		{
			cout << "\n" << (i + 1) << "  ";

			if (i == 9)
			{
				cout << "\b";
			}
			for (int j = 0; j < 10; j++)
			{
				if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '0')	//место свободно
				{
					cout << "- ";
				}
				else if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '1')	//место забронировано
				{
					cout << "? ";
				}
				else if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '2')	//место выкуплено
				{
					cout << "X ";
				}
				else if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '3')	//место выкуплено
				{
					cout << "O ";
				}
			}
		}

		cout << "\n\n  '-' - пустые места\n  '?' - зарезервированные места\n  'X' - выкупленные места\n  'O' - выбранное Вами место";
	}

	return;
}

void Menu::Escape()
{
	if (cinema != NULL && cinema->name != "")
	{
		cinema->NameOut();
	}
	else
	{
		system("cls");
	}
	cout << "\nПрибыль за сегодня: " << cinema->otchet_today;
	
	cout << "\n\nВы уверены что хотите выйти? \nДа - esc, нет - любая клавиша.";
	char choice = _getch();
	if (choice == 27)
		exit(0);
	return;
}

void Menu::ChangeProkat()
{
	if (cinema != NULL && cinema->name != "")
		cinema->NameOut();
	else
		system("cls");
	cout << "0) Назад\n\n1) Удаление фильма из проката\n2) Редактирование информации о фильме\n3) Добавление фильма в прокат";
	items_number = 3;
	return;
}

void Menu::File()
{
	items_number = 3;
	cout << "1) Открыть файл по умолчанию в домашнем каталоге (\"kino_v_teatre\")\n2) Открыть файл по заданному пути\n3) Вход в режим администратора\n\nESC - выход";
	
	return;
}

int Menu::GetItem()
{
    return item;
}