#include "Cinema.h"
#include "conio.h"
#include "File_O.h"

void Cinema::ChangeName()
{
	cout << "������� �������� ����������: " << name << "\n\n";
	InputName();
	
}

void Cinema::ChangeAdress()
{
	cout << "������� ���� ����������: " << address << "\n\n";
	InputAdress();
}

void Cinema::ChangeINN()
{
	system("cls");
	cout << "������� ���: " << inn;
	InputINN();
}

void Cinema::ChangeRNM()
{
	system("cls");
	cout << "������� ���: " << rnm;
	InputRNM();
}

void Cinema::ChangeCashier()
{
	ListCashier(0);
	//cout << "1) " << cashiers[0] << "\n2) " << cashiers[1];
	cout << "\n\n1) �������� �������\n2) ������� �������\n";
	int func;

	do
	{
		func = _getch();
	} while (func < '0' && func > '2');
	
	if (func == '1')
	{
		if (cashiers_number >= 5)
		{
			cout << "������� ������, ��� ��������� ������";
		}
		else
		{
			cashiers_number++;
			do
			{
				system("cls");
				cout << "������� ������ ������ �������: ";
				getline(cin, cashiers[cashiers_number]);
			} while (cashiers[cashiers_number] == "");
		}
	}
	else if (func == '2')
	{
		if (cashiers_number > 0)
		{
			system("cls");
			ListCashier(1);
			int number;
			cout << "������� ���������� ����� ������� ��� ��������: ";
			do
			{
				number = _getch();
			} while (number < '1' && number - 48 > cashier_number);
			for (int t = number - 48; t < cashier_number; t++)
			{
				cashiers[t] = cashiers[t + 1];
			}
			cashier_number--;
		}
		else
		{
			cout << "�� ���� ������ �� ������";
		}
	}

	//_getch();
}

void Cinema::ListCashier(int k)
{
	system("cls");
	
	for (int i = 1; i <= cashier_number; i++)
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
	system("cls");
	ListPromo(1);		//����� ���� ����������
	cout << "����� ��������� ��� ��������: ";
	//������� �������� � ����
	do
	{
		num = _getch();
	} while (num < '1' || num - 48 > promo_number);
	for (int u = num - 48; u < promo_number; u++)
	{
		promo[u][0] = promo[u + 1][0];
		promo[u][1] = promo[u + 1][1];
	}
	promo_number--;
}

void Cinema::RedPromo()
{
	int num;
	system("cls");
	ListPromo(1);		//����� ���� ����������
	cout << "����� ��������� ��� ��������������: ";
	//������� �������� � ����
	do
	{
		num = _getch();
	} while (num < '1' || num - 48 > promo_number);
	system("cls");
	cout << "��������: \"" << promo[num - 48][0] << " (" << promo[num - 48][1] << "%)";
	cout << "\n\n1) ��������\n2) �������";
	int func;
	do
	{
		func = _getch();
	} while (func != '1' && func != '2');
	string temp = "";
	if (func == '1')
	{
		string old = "������� �������� ��������� \"" + promo[num - 48][0] + "\"\n\n";
		
		promo[num - 48][0] = NewPromoName(old);
	}
	else if (func == '2')
	{
		string old = "������� ������� ��������� \"" + promo[num - 48][0] + "\" (" + promo[num - 48][1] + "%)\n\n";
		promo[num - 48][1] = NewPromoValue(old);
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
	//����� ���� ������� ����� ����, ������� �� ����������

	for (int i = num_film; i < films_number - 1; i++)
	{
		films[i] = films[i + 1];
	}
	films_number = films_number - 1;
}

void Cinema::ChangeFilm(int num_punkt, int num_film)
{
	if (num_punkt == 0)
	{
		system("cls");
		cout << "1) ��������\n2) �����������������\n3) ���������� �����������\n4) ������� ��������\n5) ������� ����\n6) ��������";
		cout << "\n\n������� ����� ��� �������� ���������: ";
	}
	else if (num_punkt == 1 || num_punkt == -1)	//�������� ������
	{
		do
		{
			if (num_punkt == 1)
			{
				system("cls");
				cout << "������� �������� ������: " << films[num_film].name;
			}
			cout << "\n�������� ������: ";
			getline(cin, films[num_film].name);
		} while (films[num_film].name == "");
	}
	else if (num_punkt == 2 || num_punkt == -2)	//���������������� ������
	{
		do
		{
			if (num_punkt == 2)
			{
				system("cls");
				cout << "������� ����������������� ������: " << films[num_film].duration << " ���.";
			}
			string temp;
			cout << "\n����������������� ������: ";
			getline(cin, films[num_film].duration);		//�������� �� ���������� ������ ��������
			for (int y = 0; y < (films[num_film].duration).length(); y++)		//�������� �� ���������� ������ ��������
			{
				if (films[num_film].duration[y] >= '0' && films[num_film].duration[y] <= '9')
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
				system("cls");
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
				system("cls");
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
				system("cls");
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
				system("cls");
				cout << "������� ��������(-�) ������: " << films[num_film].rejisser;
			}
			cout << "\n��������(-�) ������: ";
			getline(cin, films[num_film].rejisser);
		} while (films[num_film].rejisser == "");
	}
	else if (num_punkt == 7 || num_punkt == -7)	//����� � ��������� �������
	{
		if (num_punkt == -7)
		{ 
			//����� ������ � 9 �� 21;
			cout << "����� ������� ����� ��� ������� ������: ";
			cout << (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) / 60 << ":" << (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) % 60;
			//21*60
				//������� ����� �������� ��� ������ 15 �����
			int time_first, time_second, time_thord;
			TimeAuto(atoi(films[num_film].duration.c_str()));

			time_first = CheckTime(8 * 60, 1, atoi(films[num_film].duration.c_str()));	//
			if (time_first != 0)
			{
				time_second = CheckTime(time_first, 2, atoi(films[num_film].duration.c_str()));	//
				if (time_second != 0)
				{
					time_thord = CheckTime(time_second, 3, atoi(films[num_film].duration.c_str()));	//
					if (time_thord != 0)
					{
						films[num_film].time[0] = films[num_film].time[3] = films[num_film].time[6] = Convert_Time(time_first);
						films[num_film].time[1] = films[num_film].time[4] = films[num_film].time[7] = Convert_Time(time_second);
						films[num_film].time[2] = films[num_film].time[5] = films[num_film].time[8] = Convert_Time(time_thord);
					}
				}
			}
			

			/*
			cout << "\n\n������� ����� ������� ������ (������: 12:40): ";
			bool time = false;
			string temp;
			getline(cin, temp);
			int minutes;
			int hours;
			//�������� �� ������������ �����
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
						cout << "\n\n" << hours << "\n\n" << minutes << "\n\n" << int(temp[0]);
						if ((hours > 8 * 60  && hours < 60 * 21)  && minutes < 60)
						{
							cout << "������� �����!";
							time = true;
						}
					}
				}
				if (time)
				{
					cout << "������� ����� ������� ������: ";
					_getch();
				}
			}
			/*if (temp.length() == 4 || temp.length() == 5)	//������ �������� �� ������������ ����� �������
			{
				if (temp[1] == ':' || temp[2] == ':')	//������ �������� �� ������������ ����� �������
				{
					if (temp[0] = )
				}

			}
			for (int u = 0; u < temp.length(); u++)
			{
				if ()
			}
			films[num_film].duration;
			*/
		}
	}
	else if (num_punkt == 8 || num_punkt == -8)	//��������� �������
	{
		PriceInput(num_film, 0);
		PriceInput(num_film, 1);
		PriceInput(num_film, 2);
	}
	else if (num_punkt == 9 || num_punkt == -9)	//��� ������
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
		
		bool zall =  false;
		int num;
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




int Cinema::CheckTime(int time, int num_seans, int duration)
{
	string temp;
	do
	{
		if (num_seans == 1)
		{
			cout << "\n\n������� ����� ������� ������ (������: 12:40): ";
			TimeAuto(duration);
		}
		else if (num_seans == 2)
		{
			cout << "\n\n������� ����� ������� ������ (������: 12:40): ";
		}
		else if (num_seans == 3)
		{
			cout << "\n\n������� ����� �������� ������ (������: 12:40): ";
		}
		getline(cin, temp);
		int minutes;
		int hours;
		//�������� �� ������������ �����
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
	
	_getch();
}

string Cinema::Convert_Time(int time)
{
	int temp;
	string ret;
	//����������� � ���� � ������ � ������� �������, ���������� ����� :
	ret = to_string(time / 60) + ":";
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
		//�������� �� ������������� ������� ������� � ����???
	} while (full_name == "");
	
	//������������ �������
	return;
}

void Cinema::InputINN()
{
	do
	{
		cout << "\n\n������� ��� ����������: ";
		getline(cin, inn);
	} while (inn == "");
}

void Cinema::InputAdress()
{
	do
	{
		cout << "\n\n������� ����� ����������: ";
		getline(cin, address);
	} while (address == "");
}

void Cinema::InputRNM()
{
	do
	{
		cout << "\n\n������� ���: ";
		getline(cin, rnm);
	} while (rnm == "");
}

bool loadingCompl;
void PrintLoad()
{
	int i = 0;
	do
	{
		std::cout << '.';
		std::this_thread::sleep_for(0.3s);
		i++;
		if (i == 3)
		{
			i = 0;
			cout << "\b \b\b \b\b \b";
			std::this_thread::sleep_for(0.3s);
		}
	} while (!loadingCompl);
}

void Cinema::NewHallCinema(int number_film)
{
	for (int i = 0; i < 9; i++)
	{
		system("cls");
		/*cout << "\n\n��������";
		thread t(PrintLoad);
		*/
		loadingCompl = false;
		films[number_film].rand[i] = "0\0";
		films[number_film].mesta[i] = NewHall();
		/*cout << "������� ��������";
		_getch();
		*/

		loadingCompl = true;
	}
}

void Cinema::PriceInput(int num_film, int num)
{
	string temp, yuop;
	do
	{
		system("cls");
		cout << "������� ��������� ������ ��� ������ � " << films[num_film].time[num] << ": ";
		getline(cin, temp);	//�������� �� ������������ ����� ???? �������� �� ���� int
		for (int y = 0; y < temp.size(); y++)
		{
			if (isdigit(temp[y]))
			{
				yuop = yuop + temp[y];
			}
		}
	} while (yuop == "");
	films[num_film].price[num + 3] = films[num_film].price[num + 6] = films[num_film].price[num] = yuop;
}

void Cinema::NameOut()
{
	if (name != "")
	{
		system("cls");
		cout << "��������� '" << name << "'\n\n";
	}
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
	//cout << filmi[number_film].mesta[number];	//����
	//cout << filmi[number_film].mesta[(number_d - 1) * 3 + (number_t - 1)];	//����
	//_getch();
	return temp;
}