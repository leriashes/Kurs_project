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
	cout << "��� ��������� ������ ������� ������� '1'.\n��� ����� � ����� �������������� ������� '2'.\n��� ������ ������� 'esc'.\n\n";
	item_num = 2;
}

void Menu::user_kassir() 
{
	cout << "name_kinofeatre";
	cout << "1) �������� ������ �������\n2) ���� � ����� ��������������\n\nESC - �����";
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
	cout << "1) ������� ���� �� ��������� � �������� �������� (\"kino_v_teatre\")\n2) ������� ���� �� ��������� ����\n\nESC - �����";
	item_num = 2;
}

