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
	admin = false;
}

Menu::Menu(string text, int items_number)
{
	this->text = text;
	this->items_number = items_number;
	item = 0;
	admin = false;
}

Menu::~Menu()
{
}

/*void Menu::Start()
{
	cinema->NameOut();
	cout << "��� ��������� ������ ������� ������� '1'.\n��� ����� � ����� �������������� ������� '2'.\n��� ������ ������� 'esc'.\n\n";
	items_number = 2;
}*/

void Menu::Cashier() 
{
	cinema->NameOut();
	cout << "1) �������� ������ �������\n2) ���� � ����� ��������������\n\nESC - �����";
	items_number = 2;
}

void Menu::Admin()
{
	if (admin)
	{
		cinema->NameOut();
		File();
		cout << "4) ���������� ��� �������� ������\n5) �������������� ���������� � ������\n6) ���������� ��� �������� ���������\n7) ������������� ������\n8) �������������� ���������� � ����������\n\nESC - ����� �� ������ ��������������";
		items_number = 8;
	}
	//���� ��������������
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

// ��������� ����� ������ � ���������?
void Menu::FilmList()
{
	cout << "������ �������:\n\n";
	for (int i = 0; i < cinema->films_number; i++)
	{
		cout << i + 1 << ") " << cinema->films[i].name << " (" << cinema->films[i].age << ")\n";
	}
	_getch();
}


//��� ������� ��� k ????????????????????????????????? ������� ����������� ����������
void Menu::File()
{
	system("cls");
	if (admin)
		cinema->NameOut();

	items_number = 2;

	cout << "1) ������� ���� �� ��������� � �������� �������� (\"kino_v_teatre\")\n2) ������� ���� �� ��������� ����";
	if (admin)
	{
		cout << "\n3) �������� ������ �����";
		items_number = 3;
	}
	else
		cout << "\n\nESC - �����";
	
	return;
}

int Menu::GetItem()
{
    return item;
}


