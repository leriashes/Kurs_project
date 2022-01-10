#include "Cinema.h"
#include "conio.h"
#include "File_O.h"
#include "Time.h"
#include "Menu.h"



bool Cinema::CheckNameBron(int num)
{
	for (int u = 0; u < films_number; u++)
	{
		if (films[u].name == bron[num][4])
		{

			return true;
		}
	}
	return false;
}

void Cinema::ChangeFilmBron(int num_punkt, string new_znach, string old_znach)
{
	for (int y = 0; y < broni_number; y++)
	{
		if (bron[y][num_punkt] == old_znach)
		{
			cout << "���������� �������!!!";
			cout << new_znach;
			cout << old_znach;
			_getch();
			bron[y][num_punkt] = new_znach;
		}
	}
	
}

int Cinema::SearchBron(string code)	//������ ������� ����� 
{
	for (int i = 0; i < broni_number; i++)
	{
		if (code == bron[i][2])
		{
			return i;
		}
	}
	
	return -1;
}

void Cinema::List_bron()
{
	for (int o = 0; o < broni_number; o++)
	{
		cout << bron[o][1] << bron[o][2];
	}
}

void Cinema::ChangeName()
{
	cout << "������� �������� ����������: " << name << "";
	InputName();
	return;
}

void Cinema::ChangeAdress()
{
	cout << "������� ���� ����������: " << address << "";
	InputAdress();
	return;
}

void Cinema::ChangeINN()
{
	cout << "������� ���: " << inn;
	InputINN();
	return;
}

void Cinema::ChangeRNM()
{
	cout << "������� ���: " << rnm;
	InputRNM();
	return;
}

void Cinema::ChangeCashier()
{
	int func;
	
	Menu menu(cashiers_number);

	do
	{
		ListCashier(0);
		cout << "\n\n0) �����\n\n1) �������� �������\n2) ������� �������\n";
		menu.ChooseItem();
		func = menu.GetItem();
	} while (func < 0 || func > promo_number);
	
	if (func == 1)
	{
		if (cashiers_number >= 5)
		{
			cout << "������� ������ �� �������� ������, ��� ��������� ������.";
		}
		else
		{
			cashiers_number++;
			do
			{
				NameOut();
				cout << "������� ������ ������ �������: ";
				getline(cin, cashiers[cashiers_number]);
			} while (cashiers[cashiers_number] == "");
		}
	}
	else if (func == 2)
	{
		if (cashiers_number > 0)
		{
			NameOut();
			ListCashier(1);
			int number;
			cout << "������� ���������� ����� ������� ��� ��������: ";
			do
			{
				number = _getch();
			} while (number < '1' && number - 48 > cashiers_number);
			for (int t = number - 48; t < cashiers_number; t++)
			{
				cashiers[t] = cashiers[t + 1];
			}
			cashiers_number--;
		}
		else
		{
			cout << "�� ���� ������ �� ������";
		}
	}

	return;
}

void Cinema::ListCashier(int k)
{
	system("cls");
	
	for (int i = 1; i <= cashiers_number; i++)
	{
		if (k == 1)
		{
			cout << i << ") ";
		}
		cout << cashiers[i] << "\n";
	}
}


void Cinema::ListPromo(int k)
{
	for (int y = 1; y <= promo_number; y++)
	{
		if (k == 1)
		{
			cout << y << ") ";
		}
		cout <<  promo[y][0] << " (" + promo[y][1] << "%)\n\n";
	}
}

void Cinema::DelPromo()
{
	int num;
	NameOut();
	ListPromo(1);		//����� ���� ����������
	cout << "����� ��������� ��� ��������: ";
	//������� �������� � ����
	Menu menu(promo_number);

	do
	{
		menu.ChooseItem();
		num = menu.GetItem();
	} while (num < 0 || num > promo_number);

	if (num != 0)
	{
		for (int u = num - 48; u < promo_number; u++)
		{
			promo[u][0] = promo[u + 1][0];
			promo[u][1] = promo[u + 1][1];
		}
		promo_number--;
	}

	return;
}

void Cinema::RedPromo()
{
	int num;
	NameOut();
	ListPromo(1);		//����� ���� ����������
	cout << "����� ��������� ��� ��������������: ";
	Menu menu(promo_number);

	do
	{
		menu.ChooseItem();
		num = menu.GetItem();
	} while (num < 0 || num > promo_number);

	if (num != 0)
	{
		NameOut();
		cout << "��������: \"" << promo[num][0] << " (" << promo[num][1] << "%)";
		cout << "\n\n1) ��������\n2) �������";
		int func;
		do
		{
			func = _getch();
		} while (func != '1' && func != '2');
		string temp = "";
		if (func == '1')
		{
			string old = "������� �������� ��������� \"" + promo[num][0] + "\"\n\n";

			promo[num][0] = NewPromoName(old);
		}
		else if (func == '2')
		{
			string old = "������� ������� ��������� \"" + promo[num][0] + "\" (" + promo[num][1] + "%)\n\n";
			promo[num][1] = NewPromoValue(old);
		}
	}
}

void Cinema::NewPromo()
{
	if (promo_number >= 9)
	{
		system("cls");
		cout << "���������� ���������� �����������. ������� ����� �������� ������, ��� ��������� �����";
	}
	else
	{
		promo_number++;
		promo[promo_number][0] = NewPromoName("");
		promo[promo_number][1] = NewPromoValue("");
	}
}

string Cinema::NewPromoName(string message)
{
	string temp = "";
	do
	{
		system("cls");
		cout << message;
		cout << "�������� ���������: ";
		getline(cin, temp);
		for (int y = 0; y < temp.size(); y++)
		{
			if (temp[y] == ' ')
			{
				temp == "";
			}
		}
	} while (temp == "");
	return temp;
}

string Cinema::NewPromoValue(string message)
{
	string temp = "";
	do
	{
		system("cls");
		cout << message;
		cout << "������� �������: ";
		getline(cin, temp);
		if (temp[temp.size() - 1] == '%' || temp[temp.size() - 1] == ' ')
		{
			temp.resize(temp.size() - 1);       //������� ����� �������� ��� �������
		}
		if (temp.size() < 3 && temp[0] != '0')
		{	//�������� �� ������ ������ �� ���� ��� �� �� %%

			for (int t = 0; t < temp.size(); t++)
			{
				if (temp[t] < '0' || temp[t] > '9')
				{
					temp = "";
				}
			}
		}
		else
		{
			temp = "";
		}
	} while (temp == "");
	if (atoi(temp.c_str()) < 100)
	{
		return temp;
		
	}
}

void Cinema::DelFilm(int num_film)
{
	for (int i = num_film; i < films_number - 1; i++)
	{
		films[i] = films[i + 1];
	}
	films_number = films_number - 1;

}

void Cinema::ChangeFilm(int num_punkt, int num_film)
{
	string old;
	if (num_punkt == 0)
	{
		NameOut();
		cout << "1) ��������\n2) �����������������\n3) ���������� �����������\n4) ������� ��������\n5) ������� ����\n6) ��������\n7) ����� �������\n8) ��������� �������\n9) ������ ����";
		cout << "\n\n������� ����� ����� ��� �������� ���������: ";
	}
	else if (num_punkt == 1 || num_punkt == -1)	//�������� ������
	{
		old = films[num_film].name;
		do
		{
			if (num_punkt == 1)
			{
				NameOut();
				cout << "������� �������� ������: " << films[num_film].name << "\n";
			}
			cout << "�������� ������: ";
			getline(cin, films[num_film].name);
		} while (films[num_film].name == "");
		ChangeFilmBron(4, films[num_film].name, old);
	}
	else if (num_punkt == 2 || num_punkt == -2)	//���������������� ������
	{
		do
		{
			if (num_punkt == 2)
			{
				NameOut();
				cout << "������� ����������������� ������: " << films[num_film].duration << " ���.";
			}
			string temp = "";
			cout << "\n����������������� ������ (���.): ";
			getline(cin, films[num_film].duration);		//�������� �� ���������� ������ ��������
			for (int y = 0; y < (films[num_film].duration).length(); y++)		//�������� �� ���������� ������ ��������
			{
				if (isdigit(films[num_film].duration[y]))
				{
					temp = temp + films[num_film].duration[y];
				}
			}
			if (temp != "")
			{
				if (3 * atoi(temp.c_str()) + 2 * 15 <= 13 * 60)
				{
					films[num_film].duration = temp;
				}
				else
				{
					films[num_film].duration = "";
				}
			}
		} while (films[num_film].duration == "");
	}
	else if (num_punkt == 3 || num_punkt == -3)	//���������� �����������
	{
		do
		{
			if (num_punkt == 3)
			{
				NameOut();
				cout << "������� ���������� ����������� ������: " << films[num_film].age ;
			}
			string temp;
			cout << "\n���������� ����������� ������: ";
			getline(cin, films[num_film].age);
			for (int y = 0; y < (films[num_film].age).length(); y++)		//�������� �� ���������� ������ ��������
			{
				if (films[num_film].age[y] >= '0' && films[num_film].age[y] <= '9')
				{
					temp = temp + films[num_film].age[y];
				}
			}
			films[num_film].age = temp + "+";
		} while (films[num_film].age == "");
	}
	else if (num_punkt == 4 || num_punkt == -4)	//������� ��������
	{
		do
		{
			if (num_punkt == 4)
			{
				NameOut();
				cout << "������� ������� �������� ������: " << films[num_film].short_description;
			}
			cout << "\n������� �������� ������: ";
			getline(cin, films[num_film].short_description);
		} while (films[num_film].short_description == "");
	}
	else if (num_punkt == 5 || num_punkt == -5)	//������� ����
	{
		do
		{
			if (num_punkt == 5)
			{
				NameOut();
				cout << "������� ������ � ������� ���� ������: " << films[num_film].main_role;
			}
			cout << "\n������� ���� ������: ";	//����� �����������!!!
			getline(cin, films[num_film].main_role);
		} while (films[num_film].main_role == "");
	}
	else if (num_punkt == 6 || num_punkt == -6)	//��������(-�)
	{
		do
		{
			if (num_punkt == 6)
			{
				NameOut();
				cout << "������� ��������(-�) ������: " << films[num_film].rejisser;
			}
			cout << "\n��������(-�) ������: ";
			getline(cin, films[num_film].rejisser);
		} while (films[num_film].rejisser == "");
	}
	else if (num_punkt == 7)		//�������������� ������� ������
	{
		system("cls");
		cout << "�������� ����� ������ ��� ��������������: ";
		for (int i = 0; i < 3; i++)
		{
			cout << "\n" << i + 1 << ") " << films[num_film].time[i];
		}	
		int num;
		do
		{
			num = _getch();
		} while (num < '0' || num > '3');
		int time;
		bool good = false;
		system("cls");
		cout << "������� �����: " << films[num_film].time[num - 49];
		do
		{
			cout << "\n\n\n������� ����� ����� ������: ";
			int temp;
			if (num - 48 == 1)
			{
				temp = 8 * 60;
			}
			else
			{
				temp = DeConvert_Time(films[num_film].time[num - 49]);
			}

			time = CheckTime(temp, num - 49, atoi(films[num_film].duration.c_str()));
			int check;
			if (num - 48 < 3)
			{
				check = DeConvert_Time(films[num_film].time[num - 49]);
			}
			else
			{
				check = 21 * 60;
			}
			if (time + atoi(films[num_film].duration.c_str()) + 15 <= check)
			{
				cout << "time = " << time;
				cout << "\n\n CHECK: " << check;
				_getch();
				films[num_film].time[num - 49] = films[num_film].time[num - 49 + 3] = films[num_film].time[num - 49 + 6] = Convert_Time(time);
				good = true;
			}
			else
			{
				cout << "\n����� �� ������������� �������.\n\n";
			}
		} while (good != true);
		 
	}
	else if (num_punkt == -7)	//����� ������ ������
	{
		if (num_punkt == -7)
		{ 
			int first_time, second_time, third_time;
			int m, h;

			h = (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) / 60;
			m = (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) % 60;
			cout << "\n\n����� ������ ����� ��� ������� ������: 08:00\n";
			cout << "\n����� ������� ����� ��� ������� ������: ";
			
			if (h < 10)
				cout << 0;
			cout << h << ":";
			if (m < 10)
				cout << 0;
			cout << m;
			
			//TimeAuto(atoi(films[num_film].duration.c_str()));

			first_time = CheckTime(8 * 60, 1, atoi(films[num_film].duration.c_str()));	//
			if (first_time != 0)
			{
				h = (first_time + 15 + (atoi(films[num_film].duration.c_str()))) / 60;
				m = (first_time + 15 + (atoi(films[num_film].duration.c_str()))) % 60;
				cout << "\n\n����� ������ ����� ��� ������� ������: ";
				if (h < 10)
					cout << 0;
				cout << h << ":";
				if (m < 10)
					cout << 0;
				cout << m << "\n";

				h = (21 * 60 - 15 - 2 * (atoi(films[num_film].duration.c_str()))) / 60;
				m = (21 * 60 - 15 - 2 * (atoi(films[num_film].duration.c_str()))) % 60;
				cout << "\n����� ������� ����� ��� ������� ������: ";
				if (h < 10)
						cout << 0;
				cout << h << ":";
				if (m < 10)
					cout << 0;
				cout << m << "\n";

				second_time = CheckTime(first_time, 2, atoi(films[num_film].duration.c_str()));	//
				if (second_time != 0)
				{
					h = (second_time + 15 + (atoi(films[num_film].duration.c_str()))) / 60;
					m = (second_time + 15 + (atoi(films[num_film].duration.c_str()))) % 60;
					cout << "\n\n����� ������ ����� ��� �������� ������: ";
					if (h < 10)
						cout << 0;
					cout << h << ":";
					if (m < 10)
						cout << 0;
					cout << m << "\n";

					h = (21 * 60 - (atoi(films[num_film].duration.c_str()))) / 60;
					m = (21 * 60 - (atoi(films[num_film].duration.c_str()))) % 60;
					cout << "\n����� ������� ����� ��� �������� ������: ";
					if (h < 10)
						cout << 0;
					cout << h << ":";
					if (m < 10)
						cout << 0;
					cout << m << "\n";

					third_time = CheckTime(second_time, 3, atoi(films[num_film].duration.c_str()));	//
					if (third_time != 0)
					{
						films[num_film].time[0] = films[num_film].time[3] = films[num_film].time[6] = Convert_Time(first_time);
						films[num_film].time[1] = films[num_film].time[4] = films[num_film].time[7] = Convert_Time(second_time);
						films[num_film].time[2] = films[num_film].time[5] = films[num_film].time[8] = Convert_Time(third_time);
					}
				}
			}
		}
	}
	else if (num_punkt == 8 || num_punkt == -8)	//��������� �������
	{
		if (num_punkt == -8)
		{
			PriceInput(num_film, 0);
			PriceInput(num_film, 1);
			PriceInput(num_film, 2);
		}
		else
		{
			system("cls");
			for (int i = 0; i < 3; i++)
			{
				cout << (i + 1) << ") " << films[num_film].price[i] << "���.  (" << films[num_film].time[i] << ")\n";
			}
			cout << "\n\n�������� ����� ��� �������������� ��������� ������: ";

			int num;
			do
			{
				num = _getch();
			} while (num < '0' && num >'3');
			PriceInput(num_film, num - 49);
		}

	}
	else if (num_punkt == 9 || num_punkt == -9)	//��� ������
	{
		NameOut();
		if (films_number > 9)
		{
			cout << "��������� ���� ����������\n\n������� ����� ������� ��� �������� � ����";
			_getch();
		}
		else
		{

			int zals[9];
			for (int o = 0; o < 9; o++)
			{
				zals[o] = o + 1;
			}
			for (int i = 0; i < 9; i++)
			{
				for (int u = 0; u < 9; u++)
				{
					if (zals[u] == atoi(films[i].number_zal.c_str()))
					{
						zals[u] = -20;
					}
				}
			}

			cout << "��������� ����: ";
			for (int y = 0; y < 9; y++)
			{
				if (zals[y] > 0)
				{
					cout << zals[y] << "   ";
				}
			}

			bool zall = false;
			int num;
			cout << "\n\n������� ����� ����: ";
			do
			{
				num = _getch();
				if (num > '0' && num < '10')
				{
					for (int t = 0; t < 9; t++)
					{
						if (zals[t] == num - 48)
						{
							zall = true;
						}
					}
				}
			} while (zall != true);
			films[num_film].number_zal = to_string(num - 48);
		}
	}
	
}

int Cinema::CheckTime(int time, int num_seans, int duration)
{
	string temp;
	do
	{
		if (num_seans == 1)
		{
			cout << "\n\n������� ����� ������� ������ (������: 12:40): ";
		}
		else if (num_seans == 2)
		{
			cout << "\n������� ����� ������� ������ (������: 12:40): ";
		}
		else if (num_seans == 3)
		{
			cout << "\n������� ����� �������� ������ (������: 12:40): ";
		}
		getline(cin, temp);
		int minutes;
		int hours;
		if (temp.length() == 4 || temp.length() == 5)	//������ �������� �� ������������ ����� �������
		{
			if (temp[1] == ':' || temp[2] == ':')
			{
				int k;
				int o;
				if (temp[1] == ':')
				{
					k = 2;
					o = 0;
				}
				else
				{
					k = 3;
					o = 1;
				}
				if (isdigit(int(temp[0])) && isdigit(int(temp[o])) && isdigit(int(temp[k])) && isdigit(int(temp[k + 1])))			//�������� �� �������������� ���� ��������� � ������
				{
					minutes = (int(temp[k]) - 48) * 10 + (int(temp[k + 1]) - 48);
					if (temp[2] == ':')
					{
						hours = (int(temp[0]) - 48) * 600 + (int(temp[1]) - 48) * 60;
					}
					else
					{
						hours = (int(temp[0]) - 48) * 60;
					}
					if ((hours >= 8 * 60 && hours < 60 * 21) && minutes < 60)
					{
						if (((3 - num_seans) * 15 + (4 - num_seans) * duration + hours + minutes) <= 21 * 60)
						{
							if (num_seans != 1)
							{
								if (hours + minutes - duration - 15 >= time)
								{
									return (hours + minutes);
								}
							}
							else if (hours + minutes >= time)
							{
								return (hours + minutes);
							}
						}
						else
						{
							cout << "����� �� ������������� �������!";
						}
					}
					else
					{
						cout << "����� �� ������������� �������!";
					}
				}
				else
				{
					cout << "�������� �������������. ��������� �������";
				}
			}
			else
			{
				cout << "�������� �������������. ��������� �������";
			}
		}
		else
		{
			cout << "�������� �������������. ��������� �������";
		}
		cout << "\n\n";
	} while (true);
}

void Cinema::TimeAuto(int duration)
{

	if (8 * 60 + duration <= 14 * 60)
	{
		if (14 * 60 + 2 * duration + 2 * 15 <= 21 * 60)
		{
			cout << "\n\n\n�������������� ������������ ������� �������: ";
			cout << "\n\n1) 8:00\n2) 14:00\n3) " << (21 * 60 - duration) / 60;
			int temp =  ((21 * 60 - duration) - ((21 * 60 - duration) /  60 * 60));
			if (temp < 10)
			{
				cout << ":0" << temp;
			}
			else
			{
				cout << ":" << temp;
			}
		}
	}
	return;
}

string Cinema::Convert_Time(int time)
{
	int temp;
	string ret;
	ret = to_string(time / 60);
	if (atoi(ret.c_str()) < 10)
	{
		ret = "0" + ret;
	}
	ret = ret + ":";
	temp = time - time / 60 * 60;
	if (temp < 10)
	{
		ret = ret + "0" + to_string(temp);
	}
	else
	{
		ret = ret + to_string(temp);
	}
	return ret;
}

int Cinema::DeConvert_Time(string time)
{
	int times;
	times = (int(time[0]) - 48) * 10 * 60 + (int(time[1] - 48) * 60) + (int(time[3]) - 48) * 10 + (int(time[4]) - 48);
	return times;
}

void Cinema::ListSell()
{
	int func;
	do
	{
		system("cls");
		cout << "������� �� �������: " << otchet_today;
		cout << "\n������� �� ��� �����: " << otchet_vsego;
		cout << "\n\n1) �������� ������� �� �������\n2) �������� ������� �� ��� �����\n\n0) �����";
		do
		{
			func = _getch();
		} while (func < '0' || func > '2');
		if (func == '1')
		{
			otchet_today = "0";
		}
		else if (func == '2')
		{
			otchet_vsego = "0";
		}
	} while (func != '0');
}

void Cinema::InputName()
{
	do
	{
		cout << "\n\n������� �������� ����������: ";
		getline(cin, name);
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{
		cout << "\n\n������� ��� �������: ";
		getline(cin, full_name);
	} while (full_name == "");

	return;
}

void Cinema::InputINN()
{
	do
	{
		cout << "\n\n������� ��� ����������: ";
		getline(cin, inn);
	} while (inn == "");

	return;
}

void Cinema::InputAdress()
{
	do
	{
		cout << "\n\n������� ����� ����������: ";
		getline(cin, address);
	} while (address == "");

	return;
}

void Cinema::InputRNM()
{
	do
	{
		cout << "\n\n������� ���: ";
		getline(cin, rnm);
	} while (rnm == "");

	return;
}

void Cinema::NewHallCinema(int number_film)
{
	for (int i = 0; i < 9; i++)
	{
		films[number_film].rand[i] = "0";
		films[number_film].mesta[i] = NewHall();
	}

	return;
}

void Cinema::PriceInput(int num_film, int num)
{
	string temp, yuop;
	do
	{
		NameOut();
		cout << "������� ��������� ������ ��� ������ � " << films[num_film].time[num] << ": ";
		getline(cin, temp);
		for (int y = 0; y < temp.size(); y++)
		{
			if (isdigit(temp[y]))
			{
				yuop = yuop + temp[y];
			}
		}
	} while (yuop == "");
	films[num_film].price[num + 3] = films[num_film].price[num + 6] = films[num_film].price[num] = yuop;

	return;
}

void Cinema::NameOut()
{
	if (name != "")
	{
		system("cls");
		cout << "��������� '" << name << "'\n\n";
	}
	else
		system("cls");

	return;
}

string Cinema::NewHall()
{
	string temp;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int num = rand() % 3;
		temp = temp + to_string(num);
	}

	return temp;
}