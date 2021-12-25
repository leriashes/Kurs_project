#include <algorithm>
#include "Order.h"
#include "Menu.h"
using namespace std;

Order::Order()
{
	film = 0;
	day = 0;
	time = 0;
	row = 0;
	seat = 0;
	cinema = NULL;
}

int Order::ChoosePlace()
{
	row = 0;
	seat = 0;

	PrintInfo();

	cout << "\n\nВыберите место (введите номер ряда и букву): ";

	char symbol = _getch();
	symbol -= 48;

	if (symbol == -21)
	{
		Menu menu;
		menu.Escape();
		ChoosePlace();
	}
	else if (symbol > 16 && symbol < 27 || symbol > 48 && symbol < 59)
	{
		seat = symbol + 48;

		if (symbol > 48 && symbol < 59)
			seat -= 32;

		ChooseRow();
	}
	else if (symbol > 0 && symbol < 10)
	{
		row = symbol;
		ChooseRow();
	}
	else if (symbol != 0)
		ChoosePlace();

	static int f = 0;
	if (row == 0 || seat == 0)
	{
		f = 1;

		while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
		{
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3"), 1, "0");
		}
	}
	else
	{
		ChooseAction();
	}

	return f;
}

int Order::ChooseRow()
{
	int a = row;
	if (row == 1)
		row = 0;

	PrintInfo();
	row = a;

	char symbol;

	if (row == 1 && seat != 0)
	{
		row = 0;
		cout << "\n\nВыберите ряд: 1";
		symbol = _getch() - 48;

		if (symbol == -21)
		{
			Menu menu;
			menu.Escape();
			row = 1;
			ChooseRow();
		}
		else if (symbol == 0)
			row = 10;
		else if (symbol + 48 == 13)
			row = 1;
		else
		{
			row = 1;
			ChooseRow();
		}
	}
	else if (row == 1 && seat == 0)
	{
		row = 0;
		cout << "\n\nВыберите место (введите номер ряда и букву): 1";
		symbol = _getch() - 48;

		if (symbol == -21)
		{
			Menu menu;
			menu.Escape();
			row = 1;
			ChooseRow();
		}
		else if (symbol == 0)
		{
			row = 10;
			ChooseSeat();
		}
		else if (symbol + 48 == 13)
		{
			row = 1;
			ChooseSeat();
		}
		else if (symbol > 16 && symbol < 27 || symbol > 48 && symbol < 59)
		{
			seat = symbol + 48;

			if (symbol > 48 && symbol < 59)
				seat -= 32;

			row = 1;
			ChooseSeat();
		}
		else
		{
			row = 1;
			ChooseRow();
		}
	}
	else if (row == 0)
	{
		cout << "\n\nВыберите ряд: ";
		symbol = _getch() - 48;

		if (symbol == -21)
		{
			Menu menu;
			menu.Escape();
			ChooseRow();
		}
		else if (symbol == 0)
			ChoosePlace();
		else
		{
			row = symbol;
			ChooseRow();
		}
	}
	else if (row > 1 && row < 10)
		ChooseSeat();
	else
	{
		row = 0;
		ChooseRow();
	}

	return 0;
}

int Order::ChooseSeat()
{
	PrintInfo();

	if (seat == 0)
	{
		cout << "\n\nВыберите место: ";
		char symbol = _getch() - 48;

		if (symbol == -21)
		{
			Menu menu;
			menu.Escape();
			ChooseSeat();
		}
		else if (symbol > 16 && symbol < 27 || symbol > 48 && symbol < 59)
		{
			seat = symbol + 48;

			if (symbol > 48 && symbol < 59)
				seat -= 32;
		}
		else if (symbol == 0)
			ChoosePlace();
		else
			ChooseSeat();
	}

	return 0;
}

void Order::Buy()
{
	Menu menu(3);
	
	do
	{
		PrintResult();
		cout << "\nДля оплаты наличными нажмите '1'.\nДля оплаты картой нажмите '2'.\nДля ввода промокода нажмите '3'.";

		menu.ChooseItem();
		if (menu.GetItem() == 0)
		{
			while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
			{
				cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "3");
			}
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "0" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);

			ChooseAction();
		}
		else if (menu.GetItem() == 1)
		{
			;
		}
		else if (menu.GetItem() == 2)
		{
			PrintResult();
		}
		else if (menu.GetItem() == 3)
		{
			;
		}
	} while (menu.GetItem() < 0);

	return;
}

void Order::ChooseAction()
{
	//PrintInfo();

	string str = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 65, 1);
	Menu menu;

	if (str == "0")
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "3" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);
		/*
		PrintInfo();
		cout << "\n\nДля покупки нажмите '1'. \nДля бронирования нажмите '2'.\nДля выбора ещё одного места нажмите '3'.";
		menu.items_number = 3;
		*/

		do
		{
			PrintInfo();
			cout << "\n\nДля покупки нажмите '1'. \nДля бронирования нажмите '2'.\nДля выбора ещё одного места нажмите '3'.";
			menu.items_number = 3;

			menu.ChooseItem();
			if (menu.GetItem() == 0)
			{
				cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "0" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);
				ChoosePlace();
			}
			else if (menu.GetItem() == 1)
			{
				Buy();
			}
			//покупка
			else if (menu.GetItem() == 2)
				//бронь
				;
			else if (menu.GetItem() == 3)
				ChoosePlace();
			else
				//esc
				;
		} while (menu.GetItem() < 0);
	}
	else if (str == "1")
	{
		cout << "\n\nМесто уже забронировано!\nДля выбора другого места нажмите '1'.";
		menu.items_number = 1;
	}
	else if (str == "2")
	{
		cout << "\n\nМесто уже оплачено!\nДля выбора другого места нажмите '1'.";
		menu.items_number = 1;
	}
	else if (str == "3")
	{
		cout << "\n\nМесто уже выбрано!\nДля выбора ещё одного места нажмите '1'.";
		menu.items_number = 1;
	}

	return;
}

void Order::PrintInfo()
{
	Menu menu;
	menu.cinema = cinema;
	menu.num_day = day;
	menu.num_film = film;
	menu.num_time = time;
	menu.Description();

	if (day != 0)
		cout << "\n\nДата: " << Time::RetDate(day - 1).erase(0, 3);

	if (time != 0)
	{
		cout << "   Время: " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1];
		cout << "   Цена: " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " руб.";
		cout << "   Зал: " << cinema->films[film - 1].number_zal;
	}

	if (row != 0)
	{
		cout << "   Ряд: " << row;
	}

	if (seat != 0)
	{
		cout << "   Место: " << seat;
	}

	return;
}

void Order::PrintResult()
{
	cinema->NameOut();

	cout << "Фильм: " << cinema->films[film - 1].name;
	cout << "\n\nДата: " << Time::RetDate(day - 1).erase(0, 3);
	cout << "   Время: " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1];
	cout << "   Цена: " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " руб.";
	cout << "   Зал: " << cinema->films[film - 1].number_zal;
	
	cout << "\n\nМеста:";

	int num = 0;
	int cost = stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]);

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
	{
		row = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3");
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3"), 1, "4");
		seat = row % 10 + 65;
		row = row / 10 + 1;
		cout << "\nРяд: " << row;
		cout << "   Место: " << seat;

		num++;
	}

	cout << "\n\nИТОГО К ОПЛАТЕ: " << num * cost << " рублей\n";
	

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "3");
	}

	return;
}


