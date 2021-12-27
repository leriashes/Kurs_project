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
		cout << "\n\n�������� ���: ";
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
		cout << "\n��� ������ ��������� ������� '1'.\n��� ������ ������ ������� '2'.\n��� ����� ��������� ������� '3'.";

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
			int x = 1, sum, cost = stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]);
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

				if (sum < num * cost - sale)
				{
					do
					{
						cout << "\n������������ �������! ������� ����� ������� ����� ��������� ������.";

						x = _getch();

						if (x == 27)
							menu.Escape();
						else
							x = 1;
					} while (x != 1);
				}
				else if (sum == num * cost - sale)
				{
					cout << "\n������ ������ �������!";
					sale = 0;

					x = 0;
					Check();
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
				
					change = sum - num * cost + sale;

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
					Check();
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
			Check();
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
				if (promokod == cinema->promo[i][0])
				{
					sale = num * stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]) * stoi(cinema->promo[i][1]) / 100;
					break;
				}
			Buy();
		}
	} while (menu.GetItem() < 0);

	return;
}

void Order::Reserve()
{
	PrintResult();

	string kod = "\n�� 30 ����� �� ������ ����� ������������. ��� ������ ������ �� ����� �������� ���: ";

	int x;

	srand(std::time(0));
	x = rand() % 100000 + 1;

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
			menu.Escape();
		else
			x = 1;
	} while (x != 1);

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "1");
	}
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
					Buy();
				}
				else if (menu.GetItem() == 2)
				{
					Reserve();
				}
				else if (menu.GetItem() == 3)
					ChoosePlace();

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

void Order::PrintInfo()
{
	Menu menu;
	menu.cinema = cinema;
	menu.Description(*this);

	if (day != 0)
		cout << "\n\n����: " << Time::RetDate(day - 1).erase(0, 3);

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

	cout << "�����: " << cinema->films[film - 1].name;
	cout << "\n\n����: " << Time::RetDate(day - 1).erase(0, 3);
	cout << "   �����: " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1];
	cout << "   ����: " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " ���.";
	cout << "   ���: " << cinema->films[film - 1].number_zal;
	
	cout << "\n\n�����:";

	if (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("3") != string::npos)
		num = 0;

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
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("5"), 1, "4");

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

	cout << "\n\n����� � ������: " << num * cost - sale << " ������\n";

	return;
}
void space(int quan)
{
	for (int i = 0; i < quan; i++)
	{
		cout << " ";
	}

}


void Order::Check()
{
	//int num = 0;
	int d, k;

	string name_of_film = cinema->films[film - 1].name;
	name_of_film += (" (" + cinema->films[film - 1].age + ")");

	time_t t;
	std::time(&t);

	int sec = localtime(&t)->tm_sec;
	int minute = localtime(&t)->tm_min;
	int hour = localtime(&t)->tm_hour;
	int da = localtime(&t)->tm_mday;
	int mo = localtime(&t)->tm_mon + 1;
	int yea = localtime(&t)->tm_year + 1900;

	printf("\n\n|");

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

	string taima;

	taima = to_string(da) + '.' + to_string(mo) + '.' + to_string(yea) + "  " + to_string(hour) + ':' + to_string(minute) + ':' + to_string(sec);
	int tima;
	tima = taima.length();

	for (int i = 0; i < 36 - tima; i++)
		cout << " ";

	cout << taima;

	cout << "|\n|��������� '" << cinema->name << "'";

	for (int i = 0; i < 24 - cinema->name.length(); i++)
	{
		cout << " ";
	}

	cout << "|\n|" << cinema->address;

	for (int i = 0; i < 36 - cinema->address.length(); i++)
	{
		cout << " ";
	}
	cout << "|\n|           ��������  ���            |\n";

	string str = "";
	for (int i = 0; i < 5; ++i)
	{
		str += to_string(rand() % 10);
	}

	cout << "|��� �: " << str;
	
	for (int i = 0; i < 29 - str.length(); i++)
		cout << " ";


	int iRand = (rand() % (cinema->cashiers_number)) + 1;
	str = cinema->cashiers[iRand];
	//str = cinema->cashiers[rand() % (cinema->cashiers_number - 1) + 1];
	cout << "|\n|������: " << str;

	for (int i = 0; i < 28 - str.length(); i++)
	{
		cout << " ";
	}

	d = rand() % 365 + 1;
	cout << "|\n|�����: " << d;

	for (k = 0; d > 0; k++)
		d /= 10;

	for (int i = 0; i < 29 - k; i++)
		cout << " ";

	int kassa= (rand() % 5) + 1;
	cout << "|\n|�����: " << kassa;

	space(28);

	cout << "|\n|";

	cout << name_of_film;

	space(36 - name_of_film.length());

	cout << "|\n|";

	int cost = atoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1].c_str());
	
	cout << cost / (num + 1) << ".00 X " << num + 1 << " ��";

	for (d = cost / (num + 1), k = 0; d > 0; k++)
	{
		d /= 10;
	}

	for (d = num + 1; d > 0; k++)
	{
		d /= 10;
	}

	for (d = cost; d > 0; k++)
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

	
	cout << cost << " ���|\n";		//����
	

	//����������� �����
	cout << "|";

	space(36);

	cout << "|\n|�����";

	for (d = cost, k = 0; d > 0; k++)
		d /= 10;

	space(26 - k);
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	wcout << L"\u2261";

	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	cout << cost << " ���|\n";

	cout << "|� �.�. ��� 20%";

	for (d = 0.2 * cost, k = 0; d > 0; k++)
		d /= 10;

	space(17 - k);
	
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	wcout << L"\u2261";

	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	cout << (0.2 * cost) << " ���|\n";
	cout << "|������";

	space(30);
	//���� ��������
	if (true)
	{
		cout << "|\n|��������:";
		int sum = cost * num;
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

		d = sum - cost;
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
		cout << sum - cost << " ���|";
	}
	else
	{

		cout << "|\n|�����������:";

		for (d = cost, k = 0; d > 0; k++)
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

	cout << "\n|���: 0000985218595136               |";
	cout << "\n|���: 2223486316                     |";
	cout << "\n|���� ���:                   nalog.ru|";
	cout << "\n|���:            ��� \"����\" (\"���-�\")|";
	cout << "\n|���� ���:              www.nfd-ya.ru|";
	cout << "\n|                                    |\n|";

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	for (int i = 0; i < 11; i++)
		wcout << L"\u00A0";

	//����� ������� ������ ��� ��������
	wcout << L"\u250C";
	for (int i = 0; i < 12; i++)
		wcout << L"\u2500";

	wcout << L"\u2510";

	for (int i = 0; i < 11; i++)
		wcout << L"\u00A0";

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
			wcout << L"\u00A0";

		wcout << L"\u2502";
		for (int j = 0; j < 12; j++, k++)
			wcout << text[k];
		wcout << L"\u2502";

		for (int j = 0; j < 11; j++)
			wcout << L"\u00A0";
		wcout << L"|\n";
	}


	wcout << L"|";
	//����� ������ ������

	for (int i = 0; i < 11; i++)
		wcout << L"\u00A0";
	wcout << L"\u2514";

	for (int i = 0; i < 12; i++)
		wcout << L"\u2500";
	wcout << L"\u2518";

	for (int i = 0; i < 11; i++)
		wcout << L"\u00A0";
	wcout << L"|\n";
	wcout << L"|";

	for (int i = 0; i < 36; i++)
		wcout << L"\u00A0";
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

	if (true)
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

		space(36 - tima);

		cout << taima;

		cout << "|\n|�� ���: 0009865161651698            |\n";
		cout << "|�� ���: 0287619841532168            |\n";
		cout << "|������������ ��������               |\n";
		cout << "|���: 2223486316                     |\n";
		cout << "|��: 9285000123456782                |\n";
		string str = "";
		for (int i = 0; i < 5; ++i)
		{
			str += to_string(rand() % 10);
		}

		cout << "|��� �: " << str;

		for (int i = 0; i < 29 - str.length(); i++)
		{
			cout << " ";
		}

		int iRand = (rand() % (cinema->cashiers_number)) + 1;
		str = cinema->cashiers[iRand];
		//str = cinema->cashiers[rand() % (cinema->cashiers_number - 1) + 1];
		cout << "|\n|������: " << str;

		for (int i = 0; i < 28 - str.length(); i++)
		{
			cout << " ";
		}


		printf("|");

		cout << "\n|���� ���:                   nalog.ru|";
		cout << "\n|���:            ��� \"����\" (\"���-�\")|";
		cout << "\n|���� ���:              www.nfd-ya.ru|";

		cout << "\n|" << cinema->address;

		for (int i = 0; i < 36 - cinema->address.length(); i++)
		{
			cout << " ";
		}


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
			d /= 10;

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

		///}
	}
}

void Order::CheckNal()
{


}

void Order::CheckKarta()
{


}

void Order::Tickets()
{
	cinema->NameOut();

	string name_of_film = cinema->films[film - 1].name;
	name_of_film += (" (" + cinema->films[film - 1].age + ")");

	int n1 = name_of_film.length();


	cout << "\n";
	for (int i = 0; i < 39; i++)
		cout << "_";

	for (int i = 0; i < num; i++)
	{
		row = cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4");
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "2");
		seat = row % 10 + 65;
		row = row / 10 + 1;

		cout << "\n|" << cinema->name;
		for (int j = 0; j < 23 -cinema->name.length(); j++)
			cout << " ";
		cout << " ���������|   |";

		cout << "\n|" << cinema->address;
		for (int j = 0; j < 33 - cinema->address.length(); j++)
			cout << " ";
		cout << "| � |";

		cout << "\n|                                 | � |";

		cout << "\n|" << name_of_film;
		for (int j = 0; j < 33 - n1; j++)
			cout << " ";
		cout << "| � |";

		cout << "\n|                                 | � |";
		cout << "\n|��� " << cinema->films[film - 1].number_zal << "    ��� " << row;

		if (row != 10)
			cout << " ";

		cout << "    ����� " << seat << "       | � | ";
		cout << "\n|                                 | � |";

		cout << "\n|���� " << Time::RetDate(day - 1).erase(0, 3) << "    ������ " << cinema->films[film - 1].time[(day - 1) * 3 + time - 1] << "  | � |";
		cout << "\n|                                 | � |";

		cout << "\n|���� ������  " << cinema->films[film - 1].price[(day - 1) * 3 + time - 1] << " ���.            |   |\n";

		for (int j = 0; j < 39; j++)
			printf("-");
	}

	return;
}

void Order::Clean()
{
	day = time = film = row = seat = 0;
	return;
}


