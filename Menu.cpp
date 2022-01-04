#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <conio.h>
#include "Time.h"
using namespace std;

Menu::Menu()
{ 
	items_number = 0;
	item = 0;
	admin = false;
	cinema = NULL;
}

Menu::Menu(int items_number)
{
	this->items_number = items_number;
	item = 0;
	admin = false;
	cinema = NULL;
}

Menu::~Menu()
{
}

void Menu::Cashier() 
{
	if (cinema != NULL && cinema->name != "")
	{
		cinema->NameOut();
	}
	else
	{
		system("cls");
	}
	cout << "1) �������� ������ �������\n2) ������ ��������������� �������\n3) ���� � ����� ��������������\n\nESC - �����";
	items_number = 3;

	return;
}

void Menu::Admin(File_O fileo)
{
	items_number = 3;
	if (cinema != NULL && cinema->name != "")
	{
		cinema->NameOut();
	}
	else
	{
		system("cls");
	}
	cout << "0) ����� �� ������ ��������������\n\n1) ������� ���� �� ��������� � �������� �������� (\"kino_v_teatre\")\n2) ������� ���� �� ��������� ����\n3) �������� ������ �����\n";
	if (fileo.path != "" && fileo.path != "0")
	{
		cout << "4) �������������� ���������� � ������� � �������\n5) �������������� ���������� � ����������\n6) ������������� ������\n7) �������������� ���������� � ����������\n8) �������� ������� � ��������";
		items_number = 8;
	}

	return;
}

void Menu::ChooseItem()
{
	do
	{
		item = -2;

		char symbol;
		symbol = _getch();

		if (symbol == 27)
		{
			Escape();
			item = -1;
		}
		else if (symbol >= '0' && symbol <= '9')
		{
			item = symbol - 48;
		}

	} while (item < -1 || item > items_number);

	return;
}

// ��������� ����� ������ � ���������?
void Menu::FilmList()
{
	cout << "0) ������� � ����\n\n";
	if (cinema->films_number > 0)
	{
		cout << "������ �������:\n\n";
		for (int i = 0; i < cinema->films_number; i++)
		{
			cout << i + 1 << ") " << cinema->films[i].name << " (" << cinema->films[i].age << ")\n";
		}
		cout << "\n\n�������� ����� (������� �����): ";		//????? ���� ��
		items_number = cinema->films_number;
	}
	else
	{
		cout << "������ ������� ����.";
		items_number = 0;
	}

	return;
}

void Menu::Description(Order& order)
{
	cinema->NameOut();
	cout << "0 - �����\n";
	/*
	const time_t tm = time(nullptr);
	std::tm* now = localtime(&tm);
	*/

	cout << "\n��������: " << cinema->films[order.film - 1].name;
	cout << "\n\n��������: " << cinema->films[order.film - 1].short_description;
	cout << "\n\n����������������� (���.): " << cinema->films[order.film - 1].duration;
	cout << "\n\n���������� �����������: " << cinema->films[order.film - 1].age;
	cout << "\n\n��������(-�): " << cinema->films[order.film - 1].rejisser;
	cout << "\n\n� ������� �����: " << cinema->films[order.film - 1].main_role;
	
	
	int k;
	int n;
	if (order.time == 0)
	{
		cout << "\n\n���������� �������:";
		if (order.day == 0)
		{
			k = 0;
			n = 3;
		}
		else
		{
			k = order.day - 1;
			n = order.day;
		}

		for (int i = k; i < n; i++)
		{
			cout << "\n\n" << Time::RetDate(i, 0) << "   �����   ���� ������";

			for (int j = 0; j < 3; j++)
			{
				if (i == 0)
				{
					if (cinema->DeConvert_Time(cinema->films[order.film - 1].time[3 * i + j]) > cinema->DeConvert_Time(Time::RetTime(0)))
					{
						cout << "\n                " << cinema->films[order.film - 1].time[3 * i + j] << "    " << cinema->films[order.film - 1].price[3 * i + j] << " ���.";
					}
				}
				else
				{
					cout << "\n                " << cinema->films[order.film - 1].time[3 * i + j] << "    " << cinema->films[order.film - 1].price[3 * i + j] << " ���.";
				}
			}
		}

		if (order.day == 0)
		{

			cout << "\n\n1) " << Time::RetDate(0, 0) << "\n2) " << Time::RetDate(1, 0) << "\n3) " << Time::RetDate(2, 0) << "\n\n�������� ����: ";
			items_number = 3;
		}
		else
		{
			cout << "\n\n";
			int k = 0;
			for (int i = 0; i < 3; i++)
			{
				if (order.day == 1)
				{
					if (cinema->DeConvert_Time(cinema->films[order.film - 1].time[(order.day - 1) * 3 + i]) > cinema->DeConvert_Time(Time::RetTime(0)))
					{
						k++;
						cout << k << ") " << cinema->films[order.film - 1].time[(order.day - 1) * 3 + i] << "\n";
					}
					items_number = k;
				}
				else
				{
					cout << (i + 1) << ") " << cinema->films[order.film - 1].time[(order.day - 1) * 3 + i] << "\n";
					items_number = k = 3;
			
				}
				//cout << "\n" << (i + 1) << ") " << cinema->films[order.film - 1].time[(order.day - 1) * 3 + i];
			}
			if (k != 0)
			{
				cout << "\n\n�������� �����: ";
			}
			else
			{
				cout << "������ �� ������ ����� ������� �����������.\n������� \"0\" ��� �������� � ���� ����� ����";

			}
			
			
		}
		
	}
	else
	{
		int h = 0;
		/*if (order.day == 1)
		{
			for (int i = 0; i < 3; i++)
			{
				if (cinema->DeConvert_Time(cinema->films[order.film - 1].time[(order.day - 1) * 3 + i]) > cinema->DeConvert_Time(Time::RetTime(0)))
				{
					h++;
				}
			}
			if (h != 3)
			{
				order.time = order.time + (3 - h);
			}
		}*/
		cout << "\n\n   A B C D E F G H I J";
		for (int i = 0; i < 10; i++)
		{
			cout << "\n" << (i + 1) << "  ";

			if (i == 9)
			{
				cout << "\b";
			}
			for (int j = 0; j < 10; j++)
			{
				if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '0')	//����� ��������
				{
					cout << "- ";
				}
				else if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '1')	//����� �������������
				{
					cout << "? ";
				}
				else if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '2')	//����� ���������
				{
					cout << "X ";
				}
				else if (cinema->films[(order.film - 1)].mesta[(order.day - 1) * 3 + (order.time - 1)][i * 10 + j] == '3')	//����� ���������
				{
					cout << "O ";
				}
			}
		}

		cout << "\n\n  '-' - ������ �����\n  '?' - ����������������� �����\n  'X' - ����������� �����\n  'O' - ��������� ���� �����";
	}

	return;
}

void Menu::Escape()
{
	if (cinema != NULL && cinema->name != "")
	{
		cinema->NameOut();
	}
	else
	{
		system("cls");
	}
	cout << "\n������� �� �������: " << cinema->otchet_today << "������.";
	
	cout << "\n\n�� ������� ��� ������ �����? \n�� - esc, ��� - ����� �������.";
	char choice = _getch();
	if (choice == 27)
	{
		exit(0);
	}
	return;
}

void Menu::ChangeProkat()
{
	if (cinema != NULL && cinema->name != "")
	{
		cinema->NameOut();
	}
	else
	{
		system("cls");
	}
	cout << "0) �����\n\n1) �������� ������ �� �������\n2) �������������� ���������� � ������\n3) ���������� ������ � ������";
	items_number = 3;
	return;
}

void Menu::File()
{
	items_number = 3;
	cout << "1) ������� ���� �� ��������� � �������� �������� (\"kino_v_teatre\")\n2) ������� ���� �� ��������� ����\n3) ���� � ����� ��������������\n\nESC - �����";
	
	return;
}

int Menu::GetItem()
{
    return item;
}


