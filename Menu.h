#pragma once
#include "Cinema.h"
#include "File_O.h"
#include "Time.h"

class Menu
{
public:
	int items_number;
	int item;

	//связь с меню??
	int num_day;	//номер дня при покупке билета
	int num_film;	//номер выбранного фильма
	int num_time;
	//char menu_text[512];

public:
	bool admin;
	Cinema* cinema;

	Menu();
	Menu(int item_num);
	~Menu();

	void Cashier();
	void Admin();

	void ChooseItem();
	void ChooseFilm();
	void File();	//перенести в файл?  убрать k?
	void FilmList();	//в фильм
	void Description();	//в фильм или в заказ?

	void Escape();
	void Clear();
	void ChangeProkat();

	int GetItem();
};
