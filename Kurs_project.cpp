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
	
	f = false;
	//ввод пути к БД
	do
	{
		system("cls");
		if (file_stream.path != "0" && error != "\0")
		{
			cout << error << "\n\n";
		}

		menu.File();

		do
		{
			menu.ChooseItem();
		} while (menu.GetItem() == 0);
		
		if (menu.GetItem() == 3)
		{
			User::Admin(cinema, file_stream);
		}
		else if (menu.GetItem() > 0)
		{
			file_stream.path = "kino_v_teatre.txt";

			if (menu.GetItem() == 2)	//ввод своего имени файла с кинотеатром
			{
				file_stream.InputPath();
			}

			f = true;
			//происходит проверка где-то тут!
			if (file_stream.path != "0" && file_stream.CheckPath())
			{
				if (file_stream.CheckCompound())		//проверка файла на внутренее форматирование
				{
					f = false;
					system("cls");
					cout << "Идёт считывание данных из файла. \n\nОжидайте";
					thread t(Time::PrintLoading);

					Time::loadingComplete = false;
					file_stream.Read(cinema);
					file_stream.ReadBron(cinema);
					Time::loadingComplete = true;
					t.join();

					_getch();
				}
				else
				{
					error = "Файл \"" + file_stream.path + "\" не удовлетворяет условиям форматирования.\n";
				}
			}
		}
	} while (menu.GetItem() == -1 || f || menu.GetItem() == 3);

	f = n = true;

	while (true)
	{
		if (!User::GetAdmin() && f && order.film == 0)
		{
			menu.Cashier();
			do
			{
				menu.ChooseItem();
			} while (menu.GetItem() == 0);
			order.Clean();

			n = false;
		}

		if ((menu.GetItem() == 1 || menu.GetItem() <= 0 && !f || n) && !User::GetAdmin())
		{
			n = true;
			cinema.NameOut();
			if (order.film <= 0)
			{
				menu.FilmList();
				menu.items_number = cinema.films_number;
				menu.ChooseItem();
				order.film =  menu.GetItem();

				if (order.film == 0)
				{
					f = true;
				}
				else if (order.film == -1)
				{
					f = false;
				}
			}

			if (order.film > 0)
			{
				f = false;

				if (order.day <= 0)
				{
					menu.Description(order);	//ввод даты посещения
					menu.ChooseItem();
					order.day = menu.GetItem();
					order.day = order.day;

					if (order.day == -1)
					{
						order.day = 0;
					}
					else if (order.day == 0)
					{
						order.film = 0;
					}
				}

				if (order.day != 0 && order.time == 0)
				{
					menu.Description(order);	//ввод времени посещения
					menu.ChooseItem();
					order.time = menu.GetItem();
					order.time = order.time;

					if (order.time == -1)
					{
						order.time = 0;
					}
					else if (order.time == 0)
					{
						order.day = 0;
					}
				}

				if (order.time != 0)
				{
					//вывод мест в кинотеатре
					if (order.ChoosePlace())
					{
						order.time = 0;
					}
					else
					{
						//order.ChooseAction();
						order.Clean();
						file_stream.Write(cinema);
						file_stream.WriteNewBron(cinema);
					}
				}
				

			}

		}
		else if (menu.GetItem() == 2 && !User::GetAdmin())
		{
			cinema.NameOut();
			cout << "Введите код заказа: ";

			string code = "";
			//Ввод пароля
			char symbol;
			do
			{
				symbol = _getch();
				if (symbol != 8 && symbol >= '0' && symbol <= '9')
				{
					cout << "*";
					code += symbol;
				}

				//Если нажата клавиша backspace
				if (symbol == 8)
				{
					if (code.length() > 0)
					{
						cout << "\b \b";
						code.pop_back();
					}
				}

			} while (code.length() < 6);
			int number = cinema.SearchBron(code);
			if (number != -1)
			{
				//сверка названий фильмов
				if (cinema.CheckNameBron(number))
				{

					//сверка дней
				}
				

			}
			else
			{
				cout << "Код брони введен неверно!";
			}

		}
		else if (menu.GetItem() == 3 || User::GetAdmin())
		{
			User::Admin(cinema, file_stream);
		}
	}
	
	return 0;
}
