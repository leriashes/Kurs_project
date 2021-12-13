#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <conio.h>
using namespace std;

Menu::Menu()
{ }
Menu::Menu(const char* menu_text, int item_num)
{
	strcpy(this->menu_text, menu_text);
	this->menu_text[511] = '\0';

	this->item_num = item_num;
}

Menu::~Menu()
{
}

void Menu::start_menu()
{
	system("cls");
	cout << "Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n";
	item_num = 2;
}

void Menu::user_kassir() 
{
	cout << "name_kinofeatre";
	cout << "1) Просмотр списка фильмов\n2) Вход в режим администартора\n\nESC - Выход";
	item_num = 2;
}

void Menu::print()
{
	printf("%s", menu_text);
}

void Menu::input_number()
{
	do 
	{
		menu_number = -1;

		char symbol;
		symbol = _getch();

		if (symbol == 27)
		{
			menu_number = 0;
		}
		else if (symbol >= '1' && symbol <= '9')
		{
			menu_number = symbol - 48;
		}

	} while (menu_number < 0 || menu_number > item_num);
}

void Menu::file_choice()
{
	cout << "1) Открыть файл по умолчанию в домашнем каталоге (\"kino_v_teatre\")\n2) Открыть файл по заданному пути\n\nESC - выход";
	item_num = 2;
}

