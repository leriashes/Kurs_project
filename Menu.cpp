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
	cout << "Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n";
	items_number = 2;
}*/

void Menu::Cashier() 
{
	cinema->NameOut();
	cout << "1) Просмотр списка фильмов\n2) Вход в режим администратора\n\nESC - Выход";
	items_number = 2;
}

void Menu::Admin()
{
	if (admin)
	{
		cinema->NameOut();
		File();
		cout << "4) Добавление или удаление фильма\n5) Редактирование информации о фильме\n6) Добавление или удаление промокода\n7) Аннулирование билета\n8) Редактирование информации о кинотеатре\n\nESC - Выход из режима администратора";
		items_number = 8;
	}
	//меню администратора
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

// ПЕРЕНЕСТИ ВЫВОД СПИСКА В КИНОТЕАТР?
void Menu::FilmList()
{
	cout << "Список фильмов:\n\n";
	for (int i = 0; i < cinema->films_number; i++)
	{
		cout << i + 1 << ") " << cinema->films[i].name << " (" << cinema->films[i].age << ")\n";
	}
	_getch();
}


//две функции без k ????????????????????????????????? создать статичсекую переменную
void Menu::File()
{
	system("cls");
	if (admin)
		cinema->NameOut();

	items_number = 2;

	cout << "1) Открыть файл по умолчанию в домашнем каталоге (\"kino_v_teatre\")\n2) Открыть файл по заданному пути";
	if (admin)
	{
		cout << "\n3) Создание нового файла";
		items_number = 3;
	}
	else
		cout << "\n\nESC - выход";
	
	return;
}

int Menu::GetItem()
{
    return item;
}


