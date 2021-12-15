#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <iostream>
#include <conio.h>
#include "Kinoteatr.h"
#include "Time.h"


using namespace std;

/*Menu::Menu()
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

void Menu::print()
{
	printf("%s", menu_text);
}
*/

void Menu::Start_menu()
{
	system("cls");
	cout << "Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n";
	item_num = 2;
}

void Menu::User_kassir()
{
	system("cls");
	cout << "********name_kinofeatre!!!*******\n\n";
	cout << "1) Просмотр списка фильмов\n2) Вход в режим администратора\n\nESC - Выход";
	item_num = 2;
}


void Menu::Input_number()
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

void Menu::Spisok_kino(Kinoteatr kinoteatr)
{
	system("cls");
	cout << "********name_kinofeatre!!!*******\n\n";
	cout << "0) Возврат в меню\n\n";
	cout << "Список фильмов:\n\n";
	for (int i = 0; i < kinoteatr.kol_vo_filmov; i++)
	{
		cout << i + 1 << ") " << kinoteatr.filmi[i].name << " (" << kinoteatr.filmi[i].age << ")\n";
	}
	cout << "\n\nВыберите фильм (введите номер) ";
	item_num = kinoteatr.kol_vo_filmov;
}



void Menu::Opisanie(Kinoteatr kinoteatr)
{
	
	const time_t tm = time(nullptr);

	char buf[64];
	strftime(buf, std::size(buf), "%d.%m.%Y", localtime(&tm));
	std::cout << buf << std::endl;
			

	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	std::cout << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday << "\n";
	
	

	system("cls");

	
	
	/*
	cout << "yesterday : " << convTime(yesterday) << endl;
	cout << "present   : " << convTime(present) << endl;
	cout << "tommorow  : " << convTime(tommorow) << endl;
	*/
	Time uni;
	//uni.date_ret(0);
	uni.convTime(tm);
	
	cout << "\n\nНазвание: " << kinoteatr.filmi[menu_number - 1].name;
	cout << "\n\nОписание: " << kinoteatr.filmi[menu_number - 1].short_description;
	cout << "\n\nПродолжительность: " << kinoteatr.filmi[menu_number - 1].duration;
	cout << "\n\nРежиссер(-ы): " << kinoteatr.filmi[menu_number - 1].rejisser;
	cout << "\n\nВ главных ролях: " << kinoteatr.filmi[menu_number - 1].main_role;
	
	
	int k;
	int n;
	if (num_time < 0)
	{
		cout << "\n\nРасписание сеансов:";
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
			//cout << "\n\n" << uni.date_ret(i) << "   Время   Цена билета";

			for (int j = 0; j < 3; j++)
			{

				cout << "\n                " << kinoteatr.filmi[num_film - 1].time[3 * i + j] << "    " << kinoteatr.filmi[num_film - 1].price[3 * i + j] << " руб.";
			}
		}

		if (num_day < 0)
		{

			//cout << "\n\n1) " << uni.date_ret(0) << "\n2) " << uni.date_ret(1) << "\n3) " << uni.date_ret(2) << "\n\nВыберите дату: ";
		}
		else
		{
			cout << "\n\n";
			for (int i = 0; i < 3; i++)
			{
				cout << "\n" << (i + 1) << ") " << kinoteatr.filmi[(num_film - 1)].time[(num_day - 1) * 3 + i];
			}
			cout << "\n\nВыберите время: ";
		}
		item_num = 3;
	}
	/*else
	{
		//cout << kinoteatr.filmi[num_film - 1].mesta[(num_day - 1) * 3 + (num_time - 1)];	//тест
		cout << "\n\n A B C D E F G H I J";
		for (int i = 0; i < 10; i++)
		{
			cout << "\n" << (i + 1) << "  ";
			for (int j = 0; j < 10; j++)
			{
				if (kinoteatr.filmi[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '0')	//место свободно
				{
					cout << "- ";
				}
				else if (kinoteatr.filmi[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '1')	//место забронировано
				{
					cout << "? ";
				}
				else if (kinoteatr.filmi[(num_film - 1)].mesta[(num_day - 1) * +(num_time - 1)][i * 10 + j] == '2')	//место выкуплено
				{
					cout << "X ";
				}
			}
		}
		cout << "\n\nВведите место: ";
	}*/
}

void Menu::File_choice(int k)
{
	cout << "1) Открыть файл по умолчанию в домашнем каталоге (\"kino_v_teatre\")\n2) Открыть файл по заданному пути";
	if (k == 1)
	{
		cout << "\n3)Создание нового файла\n\nESC - выход";
		item_num = 3;
	}
	else
	{
		cout << "\n\nESC - выход";
		item_num = 2;
	}

}


