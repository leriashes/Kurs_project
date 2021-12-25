#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include "Order.h"
#include "Menu.h"
#include <ctime>
#include <fcntl.h>
#include <io.h>

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
			;
		}
		else if (menu.GetItem() == 2)
		{
			PrintResult();
			cout << "\n������ ������ �������!\n\n";
			Check();
			cout << "\n\n������� ����� ������� ��� �����������...";
			_getch();
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
		cout << "\n\n��� ������� ������� '1'. \n��� ������������ ������� '2'.\n��� ������ ��� ������ ����� ������� '3'.";
		menu.items_number = 3;
		*/

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
			//�������
			else if (menu.GetItem() == 2)
				//�����
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
		cout << "\n\n����� ��� �������������!\n��� ������ ������� ����� ������� '1'.";
		menu.items_number = 1;
	}
	else if (str == "2")
	{
		cout << "\n\n����� ��� ��������!\n��� ������ ������� ����� ������� '1'.";
		menu.items_number = 1;
	}
	else if (str == "3")
	{
		cout << "\n\n����� ��� �������!\n��� ������ ��� ������ ����� ������� '1'.";
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

	int num = 0;
	int cost = stoi(cinema->films[film - 1].price[(day - 1) * 3 + time - 1]);

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

	cout << "\n\n����� � ������: " << num * cost << " ������\n";
	

	while (cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4") != string::npos)
	{
		cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].replace(cinema->films[film - 1].mesta[time - 1 + (day - 1) * 3].find("4"), 1, "3");
	}

	return;
}

void Order::Check()
{
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
		cout << " ";

	cout << "|\n|" << cinema->address;

	for (int i = 0; i < 36 - cinema->address.length(); i++)
		cout << " ";

	cout << "|\n|           ��������  ���            |\n";

	string str = "";
	for (int i = 0; i < 5; ++i)
	{
		str += to_string(rand() % 10);
	}

	cout << "|��� �: " << str;
	
	for (int i = 0; i < 29 - str.length(); i++)
		cout << " ";

	str = cinema->cashiers[rand() % (cinema->cashiers_number - 1) + 1];
	cout << "|\n|������: " << str;

	for (int i = 0; i < 28 - str.length(); i++)
		cout << " ";

	d = rand() % 365 + 1;
	cout << "|\n|�����: " << d;

	for (k = 0; d > 0; k++)
		d /= 10;

	for (int i = 0; i < 29 - k; i++)
		cout << " ";

	/*cout << "|\n|�����: " << kassa[0];

	space(28);

	cout << "|\n|";

	cout << name_of_film;

	space(36 - name_of_film.length());

	cout << "|\n|";
	cout << cost / (num_tick + 1) << ".00 X " << num_tick + 1 << " ��";

	for (d = cost / (num_tick + 1), k = 0; d > 0; k++)
		d /= 10;

	for (d = num_tick + 1; d > 0; k++)
		d /= 10;

	for (d = cost; d > 0; k++)
		d /= 10;

	space(22 - k);

	//��� ������������ ������� (3 ������ ��� ����� �����
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	wcout << L"\u2261";

	_setmode(_fileno(stdout), O_TEXT);
	_setmode(_fileno(stdin), O_TEXT);

	cout << cost << " ���|\n";

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
	if (nal)
	{
		cout << "|\n|��������:";

		for (d = sum, k = 0; d > 0; k++)
			d /= 10;

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
			k = 1;
		else
			for (k = 0; d > 0; k++)
				d /= 10;

		space(25 - k);

		_setmode(_fileno(stdout), _O_U16TEXT);
		_setmode(_fileno(stdin), _O_U16TEXT);

		wcout << L"\u2261";

		_setmode(_fileno(stdout), O_TEXT);
		_setmode(_fileno(stdin), O_TEXT);
		cout << sum - cost << " ���|";
	}
	//���� �����
	else
	{

		cout << "|\n|�����������:";

		for (d = cost, k = 0; d > 0; k++)
			d /= 10;

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

	srand(time(NULL));
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

	if (!nal)
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
		cout << "|������: " << kassir[0];

		space(15);
		printf("|");

		cout << "\n|���� ���:                   nalog.ru|";
		cout << "\n|���:            ��� \"����\" (\"���-�\")|";
		cout << "\n|���� ���:              www.nfd-ya.ru|";

		cout << "\n|������� ����� �� PROKAT             |\n";


		string bank[3] = { "��������", "�������������", "���" };
		srand(time(NULL));
		random_shuffle(begin(bank), end(bank));
		//��� ����� ������
		int len = bank[0].length();
		//(28- len) / 2 - ��������� � ������ �������
		cout << "|";
		space((29 - len) / 2);

		cout << "��� \"" << bank[0] << "\"";
		space((29 - len) / 2);

		cout << " ";
		if (bank[0] == "��������")
			cout << " ";

		cout << "|\n|��� �: " << check[1];

		for (d = check[1], k = 0; d > 0; k++)
			d /= 10;

		space(29 - k);

		cout << "|\n|               ������               |\n";
		cout << "|              ��������              |\n";
		cout << "|�����: " << cost << ".00 RUB";

		for (d = cost, k = 0; d > 0; k++)
			d /= 10;

		space(22 - k);

		cout << "|\n|�������� � ��������� ����� 0%       |\n";

		string karta[3] = { "Visa", "���", "MasterCard" };
		srand(time(NULL));
		random_shuffle(begin(karta), end(karta));

		cout << "|�����: " << karta[0];
		space(29 - karta[0].length());

		cout << "|\n";

		int kod[89999];
		for (int j = 0, i = 10000; i < 99999; i++, j++)
			kod[j] = i;
		srand(time(NULL));
		random_shuffle(begin(kod), end(kod));

		cout << "|��� �����������: " << kod[0];
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
		}*/

	///}
}


