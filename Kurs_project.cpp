#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include "Menu.h"
#include "File_O.h"
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu nem;
	File_O file_stream;
	
	//Menu menu1("Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n", 2);
	//menu1.print();
	//menu1.input_number();
	
	do
	{
		nem.start_menu();
		nem.input_number();
		if (nem.menu_number == 1)
		{
			nem.user_kassir();
			if (nem.menu_number == 1)
			{

			}
		}
		else if (nem.menu_number == 2)
		{
			//администратор
			//ввод пароля администратора
			nem.file_choice();
			nem.input_number();

			if (nem.menu_number == 1)
			{
				string path;
				path = "kino_v_teatre.txt\0";
				file_stream.file_open(path);
			}
			else if (nem.menu_number == 2);
			{

			}
			
		}
	} while (nem.menu_number != 0);

    //std::cout << "Hello World!\n";
}
