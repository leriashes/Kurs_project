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
	void File();
	void FilmList();
	void Description(Order& order);

	void Escape();
	void ChangeProkat();

	int GetItem();
};
