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

	if (menu.GetItem() != 0)
	{
		do
		{

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
			}
			else if (menu.GetItem() == 2 || menu.admin)
			{
				//администратор
				//ввод пароля администратора


				// сделать выход из режима администратора
				menu.admin = true;
				menu.File();
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
	}
}
