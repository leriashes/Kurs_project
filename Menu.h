#pragma once
#include "Cinema.h"
#include "File_O.h"

class Menu
{
private:
	int items_number;
	int item;
	string text;

public:
	Menu();
	Menu(string menu_text,  int item_num);
	~Menu();

	void Cashier();
	void Start();
	void Print();
	void ChooseItem();
	void File(int k);	//перенести в файл?  убрать k?
	void FilmList(Cinema cinema);

	int GetItem();
};
