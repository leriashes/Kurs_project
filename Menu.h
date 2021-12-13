#pragma once
class Menu
{
public:
	int item_num;
	int menu_number;
	char menu_text[512];

public:
	Menu();
	Menu(const char* menu_text,  int item_num);
	~Menu();

	void user_kassir();
	void start_menu();
	void print();
	void input_number();
	void file_choice();
};
