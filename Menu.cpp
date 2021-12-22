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

	//������������� ���������
}

/*
Menu::Menu(const char* menu_text, int item_num)
{
	strcpy(this->menu_text, menu_text);
	this->menu_text[511] = '\0';
	this->item_num = item_num;
}*/

Menu::Menu(int items_number)
{
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
		cout << "\n4) ���������� ��� �������� ������\n5) �������������� ���������� � ������\n6) ���������� ��� �������� ���������\n7) ������������� ������\n8) �������������� ���������� � ����������\n\nESC - ����� �� ������ ��������������";
		items_number = 8;
	}
	//���� ��������������
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
	cout << "0) ������� � ����\n\n";
	cout << "������ �������:\n\n";
	for (int i = 0; i < cinema->films_number; i++)
	{
		cout << i + 1 << ") " << cinema->films[i].name << " (" << cinema->films[i].age << ")\n";
	}
	cout << "\n\n�������� ����� (������� �����): ";
	items_number = cinema->films_number;
}

void Menu::ChooseFilm()
{
	num_film = 0;
	char symbol;

	do
	{
		symbol = _getch();

		if (symbol >= '0' && symbol <= '9')
		{
			if (num_film * 10 + symbol - 48 <= cinema->films_number)
			{
				if (symbol >= '1' || symbol == '0' && num_film > 0)
				{
					num_film = num_film * 10 + symbol - 48;
					printf("%c", symbol);
				}
				else
				{ 
					num_film = 0;
					break;
				}
			}
		}
		else if (symbol == '\b' && num_film > 0)
		{
			num_film /= 10;
			printf("\b \b");
		}

	} while (symbol != 13 || num_film <= 0);

	item = num_film;

	return;
}

void Menu::Description()
{
	system("cls");
	const time_t tm = time(nullptr);

	char buf[64];
	strftime(buf, std::size(buf), "%d.%m.%Y", localtime(&tm));
	std::cout << buf << std::endl;
			

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
	
	

	//system("cls");

	
	
	/*
	cout << "yesterday : " << convTime(yesterday) << endl;
	cout << "present   : " << convTime(present) << endl;
	cout << "tommorow  : " << convTime(tommorow) << endl;
	*/
	Time uni;
	uni.date_ret(0);
	uni.convTime(tm);
	
	cout << "\n\n��������: " << cinema->films[num_film - 1].name;
	cout << "\n\n��������: " << cinema->films[num_film - 1].short_description;
	cout << "\n\n�����������������: " << cinema->films[num_film - 1].duration;
	cout << "\n\n��������(-�): " << cinema->films[num_film - 1].rejisser;
	cout << "\n\n� ������� �����: " << cinema->films[num_film - 1].main_role;
	
	
	int k;
	int n;
	if (num_time < 0)
	{
		cout << "\n\n���������� �������:";
		if (num_day < 0)
		{
			k = 0;
			n = 3;
		}
		else
		{
			k = num_day - 1;
			n = num_day;
		}

		for (int i = k; i < n; i++)
		{
			cout << "\n\n" << uni.date_ret(i) << "   �����   ���� ������";

			for (int j = 0; j < 3; j++)
			{

				cout << "\n                " << cinema->films[num_film - 1].time[3 * i + j] << "    " << cinema->films[num_film - 1].price[3 * i + j] << " ���.";
			}
		}

		if (num_day < 0)
		{

			cout << "\n\n1) " << uni.date_ret(0) << "\n2) " << uni.date_ret(1) << "\n3) " << uni.date_ret(2) << "\n\n�������� ����: ";
		}
		else
		{
			cout << "\n\n";
			for (int i = 0; i < 3; i++)
			{
				cout << "\n" << (i + 1) << ") " << cinema->films[(num_film - 1)].time[(num_day - 1) * 3 + i];
			}
			cout << "\n\n�������� �����: ";
		}
		items_number = 3;
	}
	/*
	else
	{
		//cout << kinoteatr.filmi[num_film - 1].mesta[(num_day - 1) * 3 + (num_time - 1)];	//����
		cout << "\n\n A B C D E F G H I J";
		for (int i = 0; i < 10; i++)
		{
			cout << "\n" << (i + 1) << "  ";
			for (int j = 0; j < 10; j++)
			{
				if (cinema->films[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '0')	//����� ��������
				{
					cout << "- ";
				}
				else if (cinema->films[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '1')	//����� �������������
				{
					cout << "? ";
				}
				else if (cinema->films[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '2')	//����� ���������
				{
					cout << "X ";
				}
			}
		}
		cout << "\n\n������� �����: ";
	}
	*/
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


