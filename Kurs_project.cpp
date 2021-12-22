#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "File_O.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Cinema cinema;
	Menu menu;
	File_O file_stream;
	bool f;

	menu.cinema = &cinema;

	//ввод пути к БД
	do
	{
		system("cls");
		menu.File();
		menu.ChooseItem();
		if (menu.GetItem() == 1)	//файл с кинотеатром указан по default
		{
			file_stream.path = "kino_v_teatre.txt";
			if (file_stream.CheckCompound())		//проверка файла на внутренее форматирование
			{
				file_stream.Read(cinema);	//чтение фильмов в массивчик
			}
		}
		else if (menu.GetItem() == 2)	//ввод своего имени файла с кинотеатром
		{
			file_stream.InputPath();
		}

	} while (menu.GetItem() == 0 || !file_stream.CheckPath());

	f = true; 

	while (true)
	{
		if (!menu.admin && f)
		{
			menu.Cashier();
			menu.ChooseItem();
			menu.Clear();
		}

		if ((menu.GetItem() == 1 || menu.GetItem() == 0 && !f) && !menu.admin)
		{
			cinema.NameOut();
			if (menu.num_film == 0)
			{
				menu.FilmList();
				menu.ChooseFilm();
			}

			if (menu.num_film == 0)
				f = true;
			else
			{
				if (menu.num_day == 0)
				{
					menu.Description();	//ввод даты посещения
					menu.ChooseItem();
					menu.num_day = menu.GetItem();
				}

				if (menu.num_day != 0 && menu.num_time == 0)
				{
					menu.Description();	//ввод времени посещения
					menu.ChooseItem();
					menu.num_time = menu.GetItem();
				}

				if (menu.num_time != 0)
				{
					menu.Description();	//вывод мест в кинотеатре


					_getch();
				}

				f = menu.GetItem() != 0;
			}
			
		}
		else if (menu.GetItem() == 2 && f || menu.admin)
		{
			//администратор
			//ввод пароля администратора


			// сделать выход из режима администратора
			menu.admin = true;
			menu.Admin();
			//menu.File();
			menu.ChooseItem();

			if (menu.GetItem() == 1)
			{
				file_stream.path = "kino_v_teatre.txt";
				file_stream.CheckPath();
			}
			else if (menu.GetItem() == 2)
			{
				file_stream.InputPath();
			}
			else if (menu.GetItem() == 3)
			{
				//создание нового файла
			}
			else if (menu.GetItem() == 4)
			{
				//создание нового файла
			}
			else if (menu.GetItem() == 5)
			{
				//создание нового файла
			}
			else if (menu.GetItem() == 6)
			{
				//создание нового файла
			}
			else if (menu.GetItem() == 7)
			{
				//создание нового файла
			}
			else if (menu.GetItem() == 8)
			{
				//создание нового файла
			}
			else if (menu.GetItem() == 0)
			{
				menu.admin = false;
				f = true;
				//изменение 
			}

		}

	}

	

	/// 
	/// ДОБАВИТЬ ДЛЯ ВСЕХ РЕЖИМОВ ВОЗМОЖНОСТЬ СМЕНЫ ТЕКСТОВИКА С БАЗОЙ
	/// 
	/// 

	/*Menu.User_kassir();
	Menu.Input_number();
	do
	{
		if (Menu.menu_number == 1)
		{
			Menu.Spisok_kino(kinoteatr);	//Выбор фильма для посещения
			Menu.Input_number();
			Menu.num_film = Menu.menu_number;
			Menu.num_day = -1;
			if (Menu.menu_number != 0)	//переход к описанию фильма
			{
				Menu.num_time = -1;
				Menu.Opisanie(kinoteatr);	//ввод даты посещения
				Menu.Input_number();
				Menu.num_day = Menu.menu_number;	//день на покупку/бронь билета

				Menu.Opisanie(kinoteatr);	//ввод времени посещения
				Menu.Input_number();
				Menu.num_time = Menu.menu_number;

				Menu.Opisanie(kinoteatr);	//вывод мест в кинотеатре
				///
				///обработка введеного места
				///
				/// 
				_getch();
			}
		}
	} while (nem.menu_number != 0);*/
	
}
