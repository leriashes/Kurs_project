#pragma once
#include "Cinema.h"
#include "File_O.h"
#include "Time.h"
#include "Order.h"

class Menu
{
public:
	int items_number;
	int item;

public:
	bool admin;
	Cinema* cinema;

	Menu();
	Menu(int item_num);
	~Menu();

	void Cashier();
	void Admin(File_O fileo);

	void ChooseItem();
	void File();	//перенести в файл?  убрать k?
	void FilmList();	//в фильм
	void Description(Order& order);	//в фильм или в заказ?

	void Escape();
	void ChangeProkat();

	int GetItem();
};
