#pragma once
#include "Cinema.h"
#include "File_O.h"

class Menu
{
private:
	int items_number;
	int item;
	string text;	//???? где используется

public:
	bool admin;
	Cinema* cinema;

	Menu();
	Menu(string menu_text,  int item_num);
	~Menu();

	void Cashier();
	void Admin();
	//void Start();
	void Print();
	void ChooseItem();
	void File();	//перенести в файл?  убрать k?
	void FilmList();

	int GetItem();
};
