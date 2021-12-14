#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <conio.h>
using namespace std;

Menu::Menu()
{ 
	text = "Menu text";
	items_number = 0;
	item = 0;
}

Menu::Menu(string text, int items_number)
{
	this->text = text;
	this->items_number = items_number;
	item = 0;
}

Menu::~Menu()
{
}

void Menu::Start()
{
	system("cls");
	cout << "��� ��������� ������ ������� ������� '1'.\n��� ����� � ����� �������������� ������� '2'.\n��� ������ ������� 'esc'.\n\n";
	item = 2;
}

void Menu::Cashier() 
{
	cout << "name_kinofeatre";
	cout << "1) �������� ������ �������\n2) ���� � ����� ��������������\n\nESC - �����";
	item = 2;
}

void Menu::Print()
{
	cout << text;
}

void Menu::ChooseItem()
{
	do 
	{
		item = -1;

		char symbol;
		symbol = _getch();

		if (symbol == 27)
		{
			item = 0;
		}
		else if (symbol >= '1' && symbol <= '9')
		{
			item = symbol - 48;
		}

	} while (item < 0 || item > items_number);
}

// ��������� ����� ������ � ���������
void Menu::FilmList(Cinema cinema)
{
	cout << "������ �������:\n\n";
	/*for (int i = 0; i < cinema.kol_vo_film; i++)
	{
		cout << i + 1 << ") " << kinoteatr.filmi[i].name << " (" << kinoteatr.filmi[i].age << ")\n";
	}*/
	_getch();
}

void Menu::ChooseFile(int k)
{
	cout << "1) ������� ���� �� ��������� � �������� �������� (\"kino_v_teatre\")\n2) ������� ���� �� ��������� ����";
	if (k == 1)
	{
		cout << "\n3)�������� ������ �����\n\nESC - �����";
		item = 3;
	}
	else
	{
		cout << "\n\nESC - �����";
		item = 2;
	}
	
}

int Menu::GetItem()
{
    return item;
}


