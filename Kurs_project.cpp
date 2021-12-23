#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "Order.h"
#include "File_O.h"
#include "User.h"
#include <thread>
using namespace std;



bool loadingComplete;
void PrintLoading()
{
	int i = 0;
	do
	{
		std::cout << '.';
		std::this_thread::sleep_for(0.3s);
		i++;
		if (i == 3)
		{
			i = 0;
			cout << "\b \b\b \b\b \b";
			std::this_thread::sleep_for(0.3s);
		}
	} while (!loadingComplete);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Cinema cinema;
	Order order;
	Menu menu;
	File_O file_stream;

	string error = "";
	bool f, n;

	order.cinema = menu.cinema = &cinema;
	
	//ввод пути к БД
	do
	{
		system("cls");
		if (file_stream.path != "0" && error != "\0")
		{
			cout << error << "\n\n";
		}

		menu.File();
		menu.ChooseItem();
		
		if (menu.GetItem() == 3)
			User::Admin(cinema, file_stream);
		else
		{
			file_stream.path = "kino_v_teatre.txt";

			if (menu.GetItem() == 2)	//ввод своего имени файла с кинотеатром
			{
				file_stream.InputPath();
			}

			//происходит проверка где-то тут!
			if (file_stream.path != "0")
			{
				if (file_stream.CheckCompound())		//проверка файла на внутренее форматирование
				{
					system("cls");
					cout << "Идёт считывание данных из файла. \n\nОжидайте";
					thread t(PrintLoading);

					loadingComplete = false;
					file_stream.Read(cinema);
					loadingComplete = true;
					t.join();
				}
				else
				{
					error = "Файл \"" + file_stream.path + "\" не удовлетворяет условиям форматирования.\n";
				}
			}
		}
	} while (menu.GetItem() == 0 || file_stream.path == "0" || !file_stream.CheckPath() || !file_stream.CheckCompound());

	f = n = true;

	while (true)
	{
  		if (!User::GetAdmin() && f && menu.num_film == 0)
		{
			menu.Cashier();
			menu.ChooseItem();
			menu.Clean();

			n = false;
		}

 		if ((menu.GetItem() == 1 || menu.GetItem() <= 0 && !f || n) && !User::GetAdmin())
		{
			n = true;
			cinema.NameOut();
			if (menu.num_film <= 0)
			{
				menu.FilmList();
				menu.ChooseFilm();
				order.film = menu.num_film;

				if (menu.num_film == 0)
					f = true;
				else if (menu.num_film == -1)
					f = false;
			}

			if (menu.num_film > 0)
			{
				f = false;

				if (menu.num_day <= 0)
				{
					menu.Description();	//ввод даты посещения
					menu.ChooseItem();
					menu.num_day = menu.GetItem();
					order.day = menu.num_day;

					if (menu.num_day == -1)
						menu.num_day = 0;
				}

				if (menu.num_day != 0 && menu.num_time == 0)
				{
					menu.Description();	//ввод времени посещения
					menu.ChooseItem();
					menu.num_time = menu.GetItem();
					order.time = menu.num_time;

					if (menu.num_time == -1)
						menu.num_time = 0;
				}

				if (menu.num_time != 0)
				{
					//вывод мест в кинотеатре
					if (order.ChoosePlace())
						menu.num_time = 0;
					else
						menu.Clean();
					//order.PrintInfo();

					//_getch();
				}

				//f = menu.GetItem() != 0;
			}
			
		}
		else if (menu.GetItem() == 2 || User::GetAdmin())
		{
			User::Admin(cinema, file_stream);
		}
	}

	/// ДОБАВИТЬ ДЛЯ ВСЕХ РЕЖИМОВ ВОЗМОЖНОСТЬ СМЕНЫ ТЕКСТОВИКА С БАЗОЙ
	
	return 0;
}
