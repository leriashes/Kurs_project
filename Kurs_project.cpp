#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "File_O.h"
#include "Program.h"
using namespace std;

int main()
{
	Cinema cinema;
	Program::Start(cinema);
	
	//Menu menu1("Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n", 2);
	//menu1.print();
	//menu1.input_number();
	
	/*do
	{
		do
		{
			system("cls");
			nem.file_choice(2);
			nem.input_number();
			if (nem.menu_number == 1)	//файл с кинотеатром указан по default
			{
				file_stream.path = "kino_v_teatre.txt\0";
				if (file_stream.file_check_compound(file_stream.path) == 1)		//проверка файла на внутренее форматирование
				{
					file_stream.file_read(file_stream.path);	//чтение фильмов в массивчик
				}
				//_getch();	//тест
			}
			else if (nem.menu_number == 2)	//ввод своего имени файла с кинотеатром
			{
				file_stream.file_input();
			}
		} while (file_stream.file_check(file_stream.path) != 1);


		nem.start_menu();
		nem.input_number();
		
		if (nem.menu_number == 1)
		{
			nem.user_kassir();
			nem.input_number();
			if (nem.menu_number == 1)
			{
				nem.spisok_kino(kinoteatr);

				//открытие меню со списком фильмов
			}
		}
		else if (nem.menu_number == 2)
		{
			//администратор
			//ввод пароля администратора
			nem.file_choice(1);
			nem.input_number();

			if (nem.menu_number == 1)
			{
				string path;
				path = "kino_v_teatre.txt\0";
				file_stream.file_check(path);
			}
			else if (nem.menu_number == 2)
			{
				file_stream.file_input();

			}
			else if (nem.menu_number == 3)
			{
				//создание нового файла
			}
			
		}
	} while (nem.menu_number != 0);

    //std::cout << "Hello World!\n";*/
	
}
