#pragma once
class Menu
{
private:
	int item_num;
	int menu_number;
	char menu_text[512];

public:
	Menu(const char* menu_text,  int item_num);
	~Menu();

	void print();
	void input_number();
};
