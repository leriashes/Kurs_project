#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Program.h"
#include "Menu.h"
#include "File_O.h"
#include "Cinema.h"
using namespace std;

void Program::Start(Cinema cinema)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu menu;
	File_O file_stream;

	//Menu menu1("Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n", 2);
	//menu1.print();
	//menu1.input_number();

	do
	{
		//ввод пути к БД
		do
		{
			system("cls");
			menu.File(2);
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

		} while (!file_stream.CheckPath());

		menu.Start();
		menu.ChooseItem();

		if (menu.GetItem() == 1)
		{
			menu.Cashier();
			if (menu.GetItem() == 1)
			{
				menu.FilmList(cinema);
				//открытие меню со списком фильмов
			}
		}
		else if (menu.GetItem() == 2)
		{
			//администратор
			//ввод пароля администратора
			menu.File(1);
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

		}
	} while (menu.GetItem() != 0);

	//std::cout << "Hello World!\n";
}
