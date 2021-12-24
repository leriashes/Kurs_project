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
	PrintResult();
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
		PrintInfo();
		cout << "\n\nДля покупки нажмите '1'. \nДля бронирования нажмите '2'.\nДля выбора ещё одного места нажмите '3'.";
		menu.items_number = 3;

		do
		{
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



	//Место свободно
	/*if (a == 0 || a == 3 && t)
	{
		if (!cancel)
		{
			if (!t)
			{
				mesta[(ryad - 1) * 10 + mesto - 65] = 3;

				num_tick += 1;

				string line;
				int r = film + 12 + 26 * (den - 1) + 13 * (den - 1) + 13 * (vremya - 1);
				for (int i = r, k = 0; i < r + 10; i++)
				{
					line = prokat[i];
					for (int j = 0; j < 10; j++, k++)
						line[j] = mesta[k] + 48;
					prokat[i] = line;
				}
			}

			t = 0;

			action = ch_mode("\n\nДля покупки нажмите '1'. \nДля бронирования нажмите '2'.\nДля выбора ещё одного места нажмите '3'.", 1, 1, den);
		}
		else
		{
			action = ch_mode("\n\nМесто свободно!\nДля выбора другого места нажмите '1'.", 1, 1, den);

			if (action == 1 || action == -3)
				action = -3;
			else
				ch_action(0);
		}
	}
	//Место забронировано
	else if (a == 1)
	{
		if (cancel)
		{
			if (!t)
			{
				mesta[(ryad - 1) * 10 + mesto - 65] = 3;

				num_tick += 1;

				string line;
				int r = film + 12 + 26 * (den - 1) + 13 * (den - 1) + 13 * (vremya - 1);
				for (int i = r, k = 0; i < r + 10; i++)
				{
					line = prokat[i];
					for (int j = 0; j < 10; j++, k++)
						line[j] = mesta[k] + 48;
					prokat[i] = line;
				}
			}

			t = 0;

			action = ch_mode("\n\nДля аннулирования брони нажмите '1'. \nДля выбора ещё одного места нажмите '2'.", 1, 1, den);

			if (action == 1)
				action = 4;
			else if (action == 2)
				action = 3;
		}
		else
		{
			action = ch_mode("\n\nМесто уже забронировано!\nДля выбора другого места нажмите '1'.", 1, 1, den);

			if (action == 1 || action == -3)
				action = -3;
			else
				ch_action(0);
		}
	}
	//Место оплачено
	else if (a == 2)
	{
		if (cancel)
		{
			if (!t)
			{
				mesta[(ryad - 1) * 10 + mesto - 65] = 3;

				num_tick += 1;

				string line;
				int r = film + 12 + 26 * (den - 1) + 13 * (den - 1) + 13 * (vremya - 1);
				for (int i = r, k = 0; i < r + 10; i++)
				{
					line = prokat[i];
					for (int j = 0; j < 10; j++, k++)
						line[j] = mesta[k] + 48;
					prokat[i] = line;
				}
			}

			t = 0;

			action = ch_mode("\n\nДля аннулирования покупки нажмите '1'. \nДля выбора ещё одного места нажмите '2'.", 1, 1, den);

			if (action == 1)
				action = 4;
			else if (action == 2)
				action = 3;
		}
		else
		{
			action = ch_mode("\n\nМесто уже оплачено!\nДля выбора другого места нажмите '1'.", 1, 1, den);

			if (action == 1 || action == -3)
				action = -3;
			else
				ch_action(0);
		}

	}
	//Место уже выбрано
	else if (a == 3)
	{
		action = ch_mode("\n\nМесто уже выбрано!\nДля выбора ещё одного места нажмите '1'.", 1, 1, den);

		if (action == 1 || action == -3)
			action = -3;
		else
			ch_action(0);
	}

	if (action > 0 && action < 5)
		b_mesto[num_tick] = (ryad - 1) * 10 + mesto - 64;

	if (action == 1)
		pokupka();
	else if (action == 2)
		bron();
	else if (action != -3 && action != 3 && action != 4)
		ch_action(1);
	else if (action == 4)
		annul();

	if (action == 3 || action == -3)
		ch_place();

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
		//cout << "   Цена: " << cinem[film + 10 + (den - 1) * 39 + 13 * (vremya - 1) + 12] << " руб.";
		//cout << "   Зал: " << prokat[film + 4];
	}

	if (row != 0)
		printf("   Ряд: %d", row);

	if (seat != 0)
		printf("   Место: %c", seat);*/

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
		//cout << "   Цена: " << cinem[film + 10 + (den - 1) * 39 + 13 * (vremya - 1) + 12] << " руб.";
		//cout << "   Зал: " << prokat[film + 4];
	}

	if (row != 0)
		printf("   Ряд: %d", row);

	if (seat != 0)
		printf("   Место: %c", seat);

	return;
}

void Order::PrintResult()
{
	cinema->NameOut();

	cout << "Фильм: " << cinema->films[film - 1].name;
	cout << "\n\nДата: " << Time::RetDate(day - 1).erase(0, 3);
	cout << "   Время: " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1];
		//cout << "   Цена: " << cinem[film + 10 + (den - 1) * 39 + 13 * (vremya - 1) + 12] << " руб.";
		//cout << "   Зал: " << prokat[film + 4];
	
	cout << "\nМеста:";

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
	{
		row = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3");
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3"), 1, "4");
		seat = row % 10 + 65;
		row = row / 10 + 1;
		cout << "\nРяд: " << row;
		cout << "   Место: " << seat;

	}

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "3");
	}

	return;
}


