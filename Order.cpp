#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include "Order.h"
#include "Menu.h"
#include "User.h"
#include <ctime>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>

using namespace std;

Order::Order()
{
	film = 0;
	day = 0;
	time = 0;
	row = 0;
	seat = 0;
	num = 0;
	sale = 0;
	sum = 0;
	cinema = NULL;
}

int Order::ChoosePlace()
{
	row = 0;
	seat = 0;

	PrintInfo();

	cout << "\n\n�������� ����� (������� ����� ���� � �����): ";

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
		{
			seat -= 32;
		}

		ChooseRow();
	}
	else if (symbol > 0 && symbol < 10)
	{
		row = symbol;
		ChooseRow();
	}
	else if (symbol != 0)
	{
		ChoosePlace();
	}

	static int f = 0;
	if (row == 0 || seat == 0)
	{
		f = 1;

		while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
		{
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3"), 1, "0");
		}
	}
	else if (film != 0)
	{
		ChooseAction();
	}

	return f;
}

int Order::ChooseRow()
{
	int a = row;
	if (row == 1)
	{
		row = 0;
	}

	PrintInfo();
	row = a;

	char symbol;

	if (row == 1 && seat != 0)
	{
		row = 0;
		cout << "\n\n�������� ���: 1";
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
		}
		else if (symbol + 48 == 13)
		{
			row = 1;
		}
		else
		{
			row = 1;
			ChooseRow();
		}
	}
	else if (row == 1 && seat == 0)
	{
		row = 0;
		cout << "\n\n�������� ����� (������� ����� ���� � �����): 1";
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
			{
				seat -= 32;
			}

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
		cout << "\n\n�������� ���: ";
		symbol = _getch() - 48;

		if (symbol == -21)
		{
			Menu menu;
			menu.Escape();
			ChooseRow();
		}
		else if (symbol == 0)
		{
			ChoosePlace();
		}
		else
		{
			row = symbol;
			ChooseRow();
		}
	}
	else if (row > 1 && row < 10)
	{
		ChooseSeat();
	}
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
		cout << "\n\n�������� �����: ";
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
			{
				seat -= 32;
			}
		}
		else if (symbol == 0)
		{
			ChoosePlace();
		}
		else
		{
			ChooseSeat();
		}
	}

	return 0;
}

void Order::Buy(bool reserved)
{
	Menu menu(3);
	
	do
	{
		PrintResult();
		cout << "\n��� ������ ��������� ������� '1'.\n��� ������ ������ ������� '2'.\n��� ����� ��������� ������� '3'.";

		menu.ChooseItem();
		if (menu.GetItem() == 0)
		{
			while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
			{
				if (!reserved)
				{
					cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "3");
				}
				else
				{
					cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "1");
				}
			}

			if (!reserved)
			{
				cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "0" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);
				ChooseAction();
			}
			
		}
		else if (menu.GetItem() == 1)
		{
			int x = 1, cost = stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]);
			while (x == 1)
			{
				string opl = "\n������� �������� �����: ";
				sum = 0;
				int b;
				char d;

				while (true)
				{
					PrintResult();
					cout << opl;

					do
					{
						b = -2;

						char symbol;
						symbol = _getch();

						if (symbol == 27)
						{
							menu.Escape();
							b = -1;
						}
						else if (symbol >= '0' && symbol <= '9' || symbol == '\r')
						{
							b = symbol - 48;
						}
					} while ((b < -1 || b > 9) && b + 48 != 13);

					if (b == 0 && sum > 0)
					{
						d = b + 48;
						opl += d;
						sum *= 10;
					}
					else if (b > 0 && b < 10)
					{
						d = b + 48;
						opl += d;
						sum = sum * 10 + b;
					}
					else if (b + 48 == 13)
						break;
				}

				if (sum < num * (cost - sale))
				{
					do
					{
						cout << "\n������������ �������! ������� ����� ������� ����� ��������� ������.";

						x = _getch();

						if (x == 27)
						{
							menu.Escape();
						}
						else
						{
							x = 1;
						}
					} while (x != 1);
				}
				else if (sum == num * (cost - sale))
				{
					cout << "\n������ ������ �������!";
					sale = 0;

					x = 0;
					Check(false);
					cout << "\n\n������� ����� ������� ��� �����������...";
					_getch();
					sum = 0;

					cinema->NameOut();
					Tickets();
					cout << "\n\n������� ����� ������� ��� �����������...";
					_getch();
					film = 0;
				}
				else
				{
					int change;
					string str = "\n������ ������ �������! \n\n���� �����: ";
				
					change = sum - num * (cost - sale);

					int k = change, i = 0;

					while (k > 0)
					{
						k /= 10;
						i++;
					}

					while (i > 0)
					{
						if (i == 1)
						{
							k = change % 10;
							str += (k + 48);
							break;
						}
						else
						{
							k = (change % int(pow(10, i))) / int(pow(10, i - 1));
							str += (k + 48);
							i--;
						}
					}

					str += " ���.";

					cout << str;

					x = 0;
					Check(false);
					cout << "\n\n������� ����� ������� ��� �����������...";
					_getch();
					sum = 0;
					
					cinema->NameOut();
					Tickets();
					cout << "\n\n������� ����� ������� ��� �����������...";
					_getch();
					sale = 0;
					film = 0;
				}
			}
		}
		else if (menu.GetItem() == 2)
		{
			PrintResult();
			cout << "\n������ ������ �������!\n\n";
			Check(true);
			cout << "\n\n������� ����� ������� ��� �����������...";
			_getch();

			cinema->NameOut();
			Tickets();
			cout << "\n\n������� ����� ������� ��� �����������...";
			_getch();
			sale = 0;
			film = 0;
		}
		else if (menu.GetItem() == 3)
		{
			string promokod;

			do
			{
				cout << "\n\n������� ��������: ";
				getline(cin, promokod);
			} while (promokod == "");

			for (int i = 0; i < cinema->promo_number; i++)
			{
				if (promokod == cinema->promo[i + 1][0])
				{
					sale = stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]) * stoi(cinema->promo[i + 1][1]) / 100;
					break;
				}
			}
			Buy(reserved);
		}
	} while (menu.GetItem() < 0);

	return;
}

void Order::Reserve()
{
	PrintResult();

	string kod = "\n�� 30 ����� �� ������ ����� ������������. ��� ������ ������ �� ����� �������� ���: ";
	int x;
	string doub = "";
	bool res_good;
	do
	{
		res_good = true;
		doub = cinema->NewID();
		/*for (int i = 0; i < 5; ++i)
		{
			doub = doub + to_string(rand() % 10);
		}
		*/
		for (int u = 0; u < cinema->broni_number; u++)
		{
			if (cinema->bron[u][2] == doub)
			{
				res_good = false;	//��� �����, ���� ������������������
			}
		}
	} while (res_good != true);
	x = atoi(doub.c_str());
	/*
	do
	{
		srand(std::time(0));
		x = rand() % 1000000 + 1;
		for (int n = 0; n < cinema->broni_number; n++)
		{
			if (cinema->bron[n][2] == to_string(x))
			{
				res_good = false;	//��� �����, ���� ������������������
			}
		}
	} while (res_good != true);
	*/
	int k = x, i = 0;

	while (k > 0)
	{
		k /= 10;
		i++;
	}

	if (i < 5)
	{
		int t = 5 - i;

		while (t > 0)
		{
			kod += "0";
			t--;
		}
	}

	while (i > 0)
	{
		if (i == 1)
		{
			k = x % 10;
			kod += (k + 48);
			break;
		}
		else
		{
			k = (x % int(pow(10, i))) / int(pow(10, i - 1));
			kod += (k + 48);
			i--;
		}
	}

	Menu menu;
	do
	{
		cout << kod;

		x = _getch();

		if (x == 27)
		{
			menu.Escape();
		}

		else
		{
			x = 1;
		}
	} while (x != 1);
	int o = 0;
	string bronka = "";
	for (int t = 0; t < 100; t++)
	{
		if (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3][t] == '4')
		{
			bronka = bronka + to_string(t) + " ";
		}
	}
	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "1");
	}
	string temp;
	cinema->bron[cinema->broni_number][1] = cinema->id_cinema;
	cinema->bron[cinema->broni_number][2] = doub;
	cinema->bron[cinema->broni_number][3] = cinema->films[film - 1].name;
	temp = Time::RetDate(0, 1);
	cinema->bron[cinema->broni_number][4] = temp;	//������� ����
	cinema->bron[cinema->broni_number][5] = cinema->films[film - 1].time[time - 1];
	temp = Time::RetDate(day - 1, 1);
	cinema->bron[cinema->broni_number][6] = temp;			//����
	cinema->bron[cinema->broni_number][7] = bronka;			//�����
	cinema->broni_zapis = cinema->broni_zapis + 1;
	cinema->broni_number = cinema->broni_number + 1;
	//���������� ����� ����� ������������ �������
	film = 0;


}

void Order::ChooseAction()
{
	string str = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 65, 1);
	Menu menu;

	if (str == "0")
	{
		if (User::GetAdmin())
		{
			PrintInfo();
			cout << "\n\n����� ��������!\n��� ������ ������� ����� ������� '1'.";
			menu.items_number = 1;
			do
			{
				menu.ChooseItem();
			} while (menu.GetItem() < 0);
			ChoosePlace();
		}
		else
		{
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "3" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);

			do
			{
				PrintInfo();
				cout << "\n\n��� ������� ������� '1'. \n��� ������������ ������� '2'.\n��� ������ ��� ������ ����� ������� '3'.";
				menu.items_number = 3;

				menu.ChooseItem();
				if (menu.GetItem() == 0)
				{
					cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "0" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);
					ChoosePlace();
				}
				else if (menu.GetItem() == 1)
				{
					Buy(false);
				}
				else if (menu.GetItem() == 2)
				{
					Reserve();
				}
				else if (menu.GetItem() == 3)
				{
					ChoosePlace();
				}
			} while (menu.GetItem() < 0);
		}
	}
	else if (str == "1")
	{
		if (User::GetAdmin())
		{
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "0" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);
			ChoosePlace();
		}
		else
		{
			PrintInfo();
			cout << "\n\n����� ��� �������������!\n��� ������ ������� ����� ������� '1'.";
			menu.items_number = 1;
			do
			{
				menu.ChooseItem();
			} while (menu.GetItem() < 0);
			ChoosePlace();
		}
	}
	else if (str == "2")
	{
		if (User::GetAdmin())
		{
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, (row - 1) * 10 + seat - 65) + "0" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr((row - 1) * 10 + seat - 64);
			ChoosePlace();
			
		}
		else
		{
			PrintInfo();
			cout << "\n\n����� ��� ��������!\n��� ������ ������� ����� ������� '1'.";
			menu.items_number = 1;
			do
			{
				menu.ChooseItem();
			} while (menu.GetItem() < 0);
			ChoosePlace();
		}
	}
	else if (str == "3")
	{
		PrintInfo();
		cout << "\n\n����� ��� �������!\n��� ������ ��� ������ ����� ������� '1'.";
		menu.items_number = 1;
		do
		{
			menu.ChooseItem();
		} while (menu.GetItem() < 0);
		ChoosePlace();
	}

	return;
}

void Order::PayReserve(int number)
{
	for (int i = 0; i < cinema->films_number; i++)
	{
		if (cinema->films[i].name == cinema->bron[number][3])
		{
			film = i + 1;

			for (int j = 0; j < 3; j++)
			{
				if (cinema->films[i].date[j] == cinema->bron[number][6])
				{
					day = j + 1;

					for (int k = 0; k < 3; k++)
					{
						if (cinema->films[i].time[k] == cinema->bron[number][5])
						{
							time = k + 1;
							break;
						}
					}
				}
			}
		}
	}

	cout << "\n\n�������� � ������ ORDER ��������";
	cout << "\n\n" << number;
	_getch();
	string seats = cinema->bron[number][7];
	string place;
	int place_number = 0;

	for (int i = 0; i < seats.length(); i++)
	{
		if (seats[i] != ' ' && seats[i] >= '0' && seats[i] <= '9')
		{
			place_number = place_number * 10 + seats[i] - 48;
		}
		else
		{
			cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3] = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(0, place_number) + "3" + cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].substr(place_number + 1);
			place_number = 0;
		}
	}
	
	cout << "����� ��������!";
	Buy(true);

	cout << "����� �������!";
	if (film == 0)
	{
		cinema->DelBron(number);
	}

	return;
}

void Order::PrintInfo()
{
	Menu menu;
	menu.cinema = cinema;
	menu.Description(*this);

	if (day != 0)
		cout << "\n\n����: " << Time::RetDate(day - 1, 1);

	if (time != 0)
	{
		cout << "   �����: " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1];
		cout << "   ����: " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " ���.";
		cout << "   ���: " << cinema->films[film - 1].number_zal;
	}

	if (row != 0)
	{
		cout << "   ���: " << row;
	}

	if (seat != 0)
	{
		cout << "   �����: " << seat;
	}

	return;
}

void Order::PrintResult()
{
	cinema->NameOut();
	cout << "0 - �����\n\n";

	cout << "�����: " << cinema->films[film - 1].name;
	cout << "\n\n����: " << Time::RetDate(day - 1, 1);
	cout << "   �����: " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1];
	cout << "   ����: " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " ���.";
	cout << "   ���: " << cinema->films[film - 1].number_zal;
	
	cout << "\n\n�����:";

	if (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
	{
		num = 0;
	}

	int cost = stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]);

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
	{
		row = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4");
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "5");
		seat = row % 10 + 65;
		row = row / 10 + 1;
		cout << "\n���: " << row;
		cout << "   �����: " << seat;
	}

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("5") != string::npos)
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("5"), 1, "4");
	}

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
	{
		row = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3");
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3"), 1, "4");
		seat = row % 10 + 65;
		row = row / 10 + 1;
		cout << "\n���: " << row;
		cout << "   �����: " << seat;

		num++;
	}

	cout << "\n\n����� � ������: " << num * (cost - sale) << " ������\n";

	return;
}

void space(int quan)
{
	for (int i = 0; i < quan; i++)
	{
		cout << " ";
	}

}


void Order::Check(bool card)
{
	int d, k;

	string name_of_film = cinema->films[film - 1].name;
	name_of_film += (" (" + cinema->films[film - 1].age + ")");
	/*
	time_t t;
	std::time(&t);

	int sec = localtime(&t)->tm_sec;
	int minute = localtime(&t)->tm_min;
	int hour = localtime(&t)->tm_hour;
	int da = localtime(&t)->tm_mday;
	int mo = localtime(&t)->tm_mon + 1;
	int yea = localtime(&t)->tm_year + 1900;
	*/
	cout << "\n\n|";

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	for (int i = 0; i < 18; i++)
	{
		wcout << L"\u005C";
		wcout << L"\u002F";
	}
	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	cout << "|\n|";

	string str;
	str = Time::RetDate(0, 1) + " " + Time::RetTime(1);
//	str = to_string(da) + '.' + to_string(mo) + '.' + to_string(yea) + "  " + to_string(hour) + ':' + to_string(minute) + ':' + to_string(sec);
	/*
	if (to_string(da).size() == 1)
	{
		str = "0";
	}
	str = str + to_string(da) + '.';
	if (to_string(mo).size() == 1)
	{
		str = str + "0";
	}
	str = str + to_string(mo) + '.' + to_string(yea) + "  " + to_string(hour) + ':' + to_string(minute) + ':' + to_string(sec);
	*/
	space(36 - str.length());

	cout << str;

	//cout << "|\n|��������� '" << cinema->name << "'";
	
	str = cinema->name;
	if (str.size() > 24)
	{
		str.erase(23, str.size());
	}
	cout << "|\n|��������� '" << str << "'";
	//for (int i = 0; i < 24 - cinema->name.length(); i++)
	space(24 - str.length());
	/*
	for (int i = 0; i < 24 - str.length(); i++)
	{
		cout << " ";
	}
	*/
	str = cinema->address;
	if (str.size() > 24)
	{
		str.erase(23, str.size());
	}
	cout << "|\n|" << str;
	//cout << "|\n|" << cinema->address;

	//for (int i = 0; i < 36 - cinema->address.length(); i++)
	space(36 - str.length());
	/*
	for (int i = 0; i < 36 - str.length(); i++)
	{
		cout << " ";
	}
	*/
	cout << "|\n|           ��������  ���            |\n";

	/*str = "";
	for (int i = 0; i < 5; ++i)
	{
		str += to_string(rand() % 10);
	}
	*/
	str = cinema->NewID();

	cout << "|��� �: " << str;
	
	space(29 - str.length());
	/*
	for (int i = 0; i < 29 - str.length(); i++)
	{
		cout << " ";
	}
	*/

	str = cinema->cashiers[rand() % cinema->cashiers_number + 1];
	if (str.size() > 23)
	{
		str.resize(23, str.size());
	}
	cout << "|\n|������: " << str;

	space(28 - str.length());
	/*for (int i = 0; i < 28 - str.length(); i++)
	{
		cout << " ";
	}
	*/

	d = rand() % 365 + 1;
	cout << "|\n|�����: " << d;

	for (k = 0; d > 0; k++)
	{
		d /= 10;
	}
	space(29 - k);
	/*
	for (int i = 0; i < 29 - k; i++)
	{
		cout << " ";
	}
	*/

	int kassa = (rand() % 5) + 1;
	cout << "|\n|�����: " << kassa;

	space(28);

	str = name_of_film;
	if (str.size() > 24)
	{
		str.erase(23, str.size());
	}
	cout << "|\n|" << str;
	//cout << name_of_film;

	space(36 - str.length());

	cout << "|\n|";

	int cost = atoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1].c_str());
	
	cinema->otchet_today = to_string(atoi(cinema->otchet_today.c_str()) + cost * num);
	cinema->otchet_vsego = to_string(atoi(cinema->otchet_vsego.c_str()) + cost * num);

	cout << cost - sale << ".00 X " << num << " ��";

	for (d = cost - sale, k = 0; d > 0; k++)
	{
		d /= 10;
	}

	for (d = num; d > 0; k++)
	{
		d /= 10;
	}

	for (d = (cost - sale) * num; d > 0; k++)
	{
		d /= 10;
	}
	space(22 - k);
	

	//��� ������������ ������� (3 ������ ��� ����� �����
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	wcout << L"\u2261";

	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	
	cout << (cost - sale) * num << " ���|\n";
	

	//����������� �����
	cout << "|";

	space(36);

	cout << "|\n|�����";

	for (d = num * (cost - sale), k = 0; d > 0; k++)
	{
		d /= 10;
	}

	space(26 - k);
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	wcout << L"\u2261";

	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	cout << num * (cost - sale) << " ���|\n";

	cout << "|� �.�. ��� 20%";

	for (d = 0.2 * num * (cost - sale), k = 0; d > 0; k++)
	{
		d /= 10;
	}

	space(17 - k);
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	wcout << L"\u2261";

	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	cout << (int)(0.2 * num * (cost - sale)) << " ���|\n";
	cout << "|������";

	space(30);
	//���� ��������
	if (!card)
	{
		cout << "|\n|��������:";
		for (d = sum, k = 0; d > 0; k++)
		{
			d /= 10;
		}

		space(22 - k);

		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);

		wcout << L"\u2261";

		_setmode(_fileno(stdout), O_TEXT);
		_setmode(_fileno(stdin), O_TEXT);

		cout << sum << " ���|\n";

		cout << "|";

		space(36);

		cout << "|\n|�����:";

		d = sum - num * cost + num * sale;
		if (d == 0)
		{
			k = 1;
		}
		else
		{
			for (k = 0; d > 0; k++)
			{
				d /= 10;
			}
		}
		space(25 - k);

		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);

		wcout << L"\u2261";

		_setmode(_fileno(stdout), O_TEXT);
		_setmode(_fileno(stdin), O_TEXT);
		cout << sum - cost * num + sale * num << " ���|";
	}
	else
	{

		cout << "|\n|�����������:";

		for (d = cost * num - sale * num, k = 0; d > 0; k++)
		{
			d /= 10;
		}

		space(19 - k);

		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);

		wcout << L"\u2261";

		_setmode(_fileno(stdout), O_TEXT);
		_setmode(_fileno(stdin), O_TEXT);

		cout << cost << " ���|";
	}

	//cout << "\n|���: 0000985218595136               |";
	cout << "\n|���: ";
	str = cinema->rnm;
	if (str.size() > 24)
	{
		str.erase(23, str.size());
	}
	cout << str;

	space(31 - str.length());
	/*
	for (int i = 0; i < 31 - str.length(); i++)
	{
		cout << " ";
	}
	*/
	cout << "|\n|���: ";
	str = cinema->inn;
	if (str.size() > 24)
	{
		str.erase(23, str.size());
	}
	cout << str;
	space(31 - str.length());
	/*
	for (int i = 0; i < 31 - str.length(); i++)
	{
		cout << " ";
	}
	*/
	cout << "|\n|���� ���:                   nalog.ru|";
	cout << "\n|���:            ��� \"����\" (\"���-�\")|";
	cout << "\n|���� ���:              www.nfd-ya.ru|";
	cout << "\n|                                    |\n|";

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	for (int i = 0; i < 11; i++)
	{
		wcout << L"\u00A0";
	}

	//����� ������� ������ ��� ��������
	wcout << L"\u250C";
	for (int i = 0; i < 12; i++)
	{
		wcout << L"\u2500";
	}

	wcout << L"\u2510";

	for (int i = 0; i < 11; i++)
	{
		wcout << L"\u00A0";
	}

	wcout << L"|\n";


	string qr[100] = { "\u2510", "\u2514", "\u2518" , "\u251C" , "\u2524" , "\u252C" , "\u2534" , "\u253C" , "\u2550" , "\u2551" , "\u2552" , "\u2554" , "\u2555" , "\u2556",
	"\u2557" , "\u2558" , "\u2559" , "\u255A" , "\u255B" , "\u255C" , "\u255D" , "\u255E" , "\u255F" , "\u2562" , "\u2561" , "\u2563" , "\u2564" , "\u2566" , "\u2567" , "\u2568",
	"\u2569" , "\u2256" , "\u256A" , "\u256B" , "\u256C" };
	//string* qre = L"\u2256";

	const wchar_t* text[112] = {
		L"\u253C" , L"\u2550" , L"\u2551" , L"\u2552" , L"\u2554" , L"\u2555" , L"\u2556",
		L"\u2557" , L"\u2558" , L"\u2559" , L"\u255A" , L"\u255B" , L"\u255C" , L"\u255D" , L"\u255E" , L"\u255F" , L"\u2562" , L"\u2561" , L"\u2563" , L"\u2564" , L"\u2566" , L"\u2567" , L"\u2568",
		L"\u2569" , L"\u2256" , L"\u256A" , L"\u256B" , L"\u256C",
			L"\u253C" , L"\u2550" , L"\u2551" , L"\u2552" , L"\u2554" , L"\u2555" , L"\u2556",
		L"\u2557" , L"\u2558" , L"\u2559" , L"\u255A" , L"\u255B" , L"\u255C" , L"\u255D" , L"\u255E" , L"\u255F" , L"\u2562" , L"\u2561" , L"\u2563" , L"\u2564" , L"\u2566" , L"\u2567" , L"\u2568",
		L"\u2569" , L"\u2256" , L"\u256A" , L"\u256B" , L"\u256C",
			L"\u253C" , L"\u2550" , L"\u2551" , L"\u2552" , L"\u2554" , L"\u2555" , L"\u2556",
		L"\u2557" , L"\u2558" , L"\u2559" , L"\u255A" , L"\u255B" , L"\u255C" , L"\u255D" , L"\u255E" , L"\u255F" , L"\u2562" , L"\u2561" , L"\u2563" , L"\u2564" , L"\u2566" , L"\u2567" , L"\u2568",
		L"\u2569" , L"\u2256" , L"\u256A" , L"\u256B" , L"\u256C",
			L"\u253C" , L"\u2550" , L"\u2551" , L"\u2552" , L"\u2554" , L"\u2555" , L"\u2556",
		L"\u2557" , L"\u2558" , L"\u2559" , L"\u255A" , L"\u255B" , L"\u255C" , L"\u255D" , L"\u255E" , L"\u255F" , L"\u2562" , L"\u2561" , L"\u2563" , L"\u2564" , L"\u2566" , L"\u2567" , L"\u2568",
		L"\u2569" , L"\u2256" , L"\u256A" , L"\u256B" , L"\u256C" };
	//std::wcout << text[1] << L'\n';

	srand(std::time(NULL));
	random_shuffle(begin(text), end(text));

	for (int k = 0, i = 0; i < 8; i++)
	{
		wcout << L"|";
		for (int j = 0; j < 11; j++)
		{
			wcout << L"\u00A0";
		}

		wcout << L"\u2502";
		for (int j = 0; j < 12; j++, k++)
		{
			wcout << text[k];
		}

		wcout << L"\u2502";

		for (int j = 0; j < 11; j++)
		{
			wcout << L"\u00A0";
		}

		wcout << L"|\n";
	}


	wcout << L"|";
	//����� ������ ������

	for (int i = 0; i < 11; i++)
	{
		wcout << L"\u00A0";
	}

	wcout << L"\u2514";

	for (int i = 0; i < 12; i++)
	{
		wcout << L"\u2500";
	}

	wcout << L"\u2518";

	for (int i = 0; i < 11; i++)
	{
		wcout << L"\u00A0";
	}

	wcout << L"|\n";
	wcout << L"|";

	for (int i = 0; i < 36; i++)
	{
		wcout << L"\u00A0";
	}

	wcout << L"|\n";

	//����� ������
	wcout << L"\u00A0";
	for (int i = 0; i < 18; i++)
	{

		wcout << L"\u005C";
		wcout << L"\u002F";
	}

	//������������ �� ��������
	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	if (card)
	{
		//������ ������� ���� ��� �����

		cout << "\n\n";

		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);
		wcout << L"|";
		for (int i = 0; i < 18; i++)
		{
			wcout << L"\u005C";
			wcout << L"\u002F";
		}
		wcout << L"|";
		_setmode(_fileno(stdout), O_TEXT);
		_setmode(_fileno(stdin), O_TEXT);

		cout << "\n|";

		//str = to_string(da) + '.' + to_string(mo) + '.' + to_string(yea) + "  " + to_string(hour) + ':' + to_string(minute) + ':' + to_string(sec);
		str = Time::RetDate(0, 1) + " " + Time::RetTime(1);
		/*if (to_string(da).size() == 1)
		{
			str = "0";
		}
		str = str + to_string(da) + '.';
		if (to_string(mo).size() == 1)
		{
			str = str + "0";
		}
		str = str + to_string(mo) + '.' + to_string(yea) + "  " + to_string(hour) + ':' + to_string(minute) + ':' + to_string(sec);
		*/
		space(36 - str.length());

		cout << str;

		cout << "|\n|�� ���: 0009865161651698            |\n";
		cout << "|�� ���: 0287619841532168            |\n";
		cout << "|������������ ��������               |\n";
		cout << "|���: ";
		str = cinema->inn;
		if (str.size() > 24)
		{
			str.erase(23, str.size());
		}
		cout << str;
		space(31 - str.length());
		/*
		for (int i = 0; i < 31 - str.length(); i++)
		{
			cout << " ";
		}
		*/
		cout << "|\n|��: 9285000123456782                |\n";
		
		/*str = "";
		for (int i = 0; i < 5; ++i)
		{
			str += to_string(rand() % 10);
		}
		*/
		str = cinema->NewID();
		cout << "|��� �: " << str;

		space(29 - str.length());
		/*
		for (int i = 0; i < 29 - str.length(); i++)
		{
			cout << " ";
		}
		*/

		int iRand = (rand() % (cinema->cashiers_number)) + 1;
		str = cinema->cashiers[iRand];
		if (str.size() > 24)
		{
			str.erase(23, str.size());
		}
		//str = cinema->cashiers[rand() % (cinema->cashiers_number - 1) + 1];
		cout << "|\n|������: " << str;

		space(28 - str.length());
		/*
		for (int i = 0; i < 28 - str.length(); i++)
		{
			cout << " ";
		}
		*/


		printf("|");

		cout << "\n|���� ���:                   nalog.ru|";
		cout << "\n|���:            ��� \"����\" (\"���-�\")|";
		cout << "\n|���� ���:              www.nfd-ya.ru|\n|";

		str = cinema->address;
		if (str.size() > 24)
		{
			str.erase(23, str.size());
		}
		//�out << "\n|" << cinema->address;
		cout << str;
		//for (int i = 0; i < 36 - cinema->address.length(); i++)
		space(36 - str.length());
		/*
		for (int i = 0; i < 36 - str.length(); i++)
		{
			cout << " ";
		}
		*/

		string bank[3] = { "��������", "�������������", "���" };
		random_shuffle(begin(bank), end(bank));
		//��� ����� ������
		int len = bank[0].length();
		//(28- len) / 2 - ��������� � ������ �������
		cout << "|\n|";
		space((29 - len) / 2);

		cout << "��� \"" << bank[0] << "\"";
		space((29 - len) / 2);

		cout << " ";
		if (bank[0] == "��������")
		{
			cout << " ";
		}

		str = "";
		for (int i = 0; i < 5; ++i)
		{
			str += to_string(rand() % 10);
		}

		cout << "|\n|��� �: " << str;


		for (d = atoi(str.c_str()), k = 0; d > 0; k++)
		{
			d /= 10;
		}
		space(29 - k);

		cout << "|\n|               ������               |\n";
		cout << "|              ��������              |\n";
		cout << "|�����: " << cost << ".00 RUB";

		for (d = cost, k = 0; d > 0; k++)
		{
			d /= 10;
		}

		space(22 - k);

		cout << "|\n|�������� � ��������� ����� 0%       |\n";

		string karta[3] = { "Visa", "���", "MasterCard" };
		srand(std::time(NULL));
		random_shuffle(begin(karta), end(karta));

		cout << "|�����: " << karta[0];
		space(29 - karta[0].length());

		cout << "|\n";

		str = "";
		for (int i = 0; i < 5; ++i)
		{
			str += to_string(rand() % 10);
		}

		cout << "|��� �����������: " << str;
		space(14);
		cout << "|\n|                                    |\n";

		cout << "|----------------------------        |\n";
		cout << "|     ������� �������                |\n";

		//����� ������
		wcout << L"\u00A0";
		for (int i = 0; i < 18; i++)
		{
			wcout << L"\u005C";
			wcout << L"\u002F";
		}
	}

	return;
}

void Order::Tickets()
{
	cinema->NameOut();

	string name_of_film = cinema->films[film - 1].name;
	name_of_film += (" (" + cinema->films[film - 1].age + ")");

	int n1 = name_of_film.length();

	cout << "\n";
	for (int i = 0; i < 39; i++)
	{
		cout << "_";
	}

	for (int i = 0; i < num; i++)
	{
		row = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4");
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "2");
		seat = row % 10 + 65;
		row = row / 10 + 1;

		cout << "\n|" << cinema->name;
		space(23 - cinema->name.length());
		/*
		for (int j = 0; j < 23 - cinema->name.length(); j++)
		{
			cout << " ";
		}
		*/

		cout << " ���������|   |";

		cout << "\n|" << cinema->address;
		space(33 - cinema->address.length());
		/*
		for (int j = 0; j < 33 - cinema->address.length(); j++)
		{
			cout << " ";
		}
		*/

		cout << "| � |";

		cout << "\n|                                 | � |";

		cout << "\n|" << name_of_film;
		space(33 - n1);
		/*
		for (int j = 0; j < 33 - n1; j++)
		{
			cout << " ";
		}
		*/

		cout << "| � |";

		cout << "\n|                                 | � |";
		cout << "\n|��� " << cinema->films[film - 1].number_zal << "    ��� " << row;

		if (row != 10)
		{
			cout << " ";
		}

		cout << "    ����� " << seat << "       | � | ";
		cout << "\n|                                 | � |";

		cout << "\n|���� " << Time::RetDate(day - 1, 1) << "    ������ " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1] << "  | � |";
		cout << "\n|                                 | � |";

		cout << "\n|���� ������  " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " ���.            |   |\n";

		for (int j = 0; j < 39; j++)
		{
			printf("-");
		}
	}
	
	return;
}

void Order::Clean()
{
	day = time = film = row = seat = 0;
	return;
}


