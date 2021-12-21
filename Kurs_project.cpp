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

	} while (menu.GetItem() != 0 && !file_stream.CheckPath());


	// ДЛЯ ВЫХОДА ИЗ ПРОГРАММЫ СДЕЛАТЬ ДРУГОЙ КОД!
	if (menu.GetItem() != 0)
	{
		do
		{
			f = false;
			if (!menu.admin)
			{
				menu.Cashier();
				menu.ChooseItem();
			}

			//переделать в режим кассира
			if (menu.GetItem() == 1 && !menu.admin)
			{
				cinema.NameOut();
				menu.FilmList();
				menu.ChooseFilm();
				if (menu.GetItem() != 0)
				{
					menu.Description();
					_getch();
				}
			}
			else if (menu.GetItem() == 2 || menu.admin)
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
		} while (menu.GetItem() != 0 || f);
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
