#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include "Menu.h"

#include "File_O.h"
#include "Kinoteatr.h"
#include <conio.h>
using namespace std;

int main()
{
	//std::cout << "Hello World!\n";
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	File_O file_stream;
	Menu Menu;
	Kinoteatr kinoteatr;
	do
	{
		system("cls");
		Menu.File_choice(2);
		Menu.Input_number();
		if (Menu.menu_number == 2)	//ввод своего имени файла с кинотеатром
		{
			system("cls");
			file_stream.File_input();
		}

		file_stream.path = "kino_v_teatre.txt\0";
		if (file_stream.File_check())	//проверка на существование файла с таким названием
		{
			if (file_stream.File_check_compound(&kinoteatr.kol_vo_filmov) == 1)		//проверка файла на внутренее форматирование
			{
				//cout << kinoteatr.kol_vo_filmov;	//тест
				//cout << "Проверку прошел!";	//тест
				file_stream.File_read(&kinoteatr);	//чтение фильмов в массивчик
			}
		}
		//_getch();	//тест
		//cout << kinoteatr.filmi[0].name;
		//_getch();
	} while (file_stream.File_check() != 1);

	/// 
	/// ДОБАВИТЬ ДЛЯ ВСЕХ РЕЖИМОВ ВОЗМОЖНОСТЬ СМЕНЫ ТЕКСТОВИКА С БАЗОЙ
	/// 
	/// 

	Menu.User_kassir();
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
	} while (Menu.menu_number != 0);
}