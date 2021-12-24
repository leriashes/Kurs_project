#include "Cinema.h"
#include "conio.h"

void Cinema::ChangeName()
{
	cout << "������� �������� ����������: " << name << "\n\n";
	InputName();
	
}

void Cinema::ChangeAdress()
{
	cout << "������� ���� ����������: " << adress << "\n\n";
	InputAdress();
}

void Cinema::ChangeInn()
{
	system("cls");
	cout << "������� ���: " << inn;
	InputINN();
}

void Cinema::ChangeRnm()
{
	system("cls");
	cout << "������� ���: " << rnm;
	InputRNM();
}

void Cinema::ChangeCashier()
{
	system("cls");
	cout << "1) " << cashiers[0] << "\n2) " << cashiers[1];
	_getch();
}

void Cinema::check_cash()
{
	cout << cashiers[0] << "\n";
	cout << cashiers[1] << "\n";
	cout << cashiers[2] << "\n";
	cout << cashiers[3] << "\n";
}

void Cinema::ListPromo(int k)
{
	for (int y = 1; y <= promo_numbers; y++)
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
	} while (num < '1' || num - 48 > promo_numbers);
	for (int u = num - 48; u < promo_numbers; u++)
	{
		promo[u][0] = promo[u + 1][0];
		promo[u][1] = promo[u + 1][1];
	}
	promo_numbers--;
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
	} while (num < '1' || num - 48 > promo_numbers);
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
	if (promo_numbers >= 9)
	{
		system("cls");
		cout << "���������� ���������� �����������. ������� ����� �������� ������, ��� ��������� �����";
	}
	else
	{
		promo_numbers++;
		promo[promo_numbers][0] = NewPromoName("");
		promo[promo_numbers][1] = NewPromoValue("");
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

			time_first = CheckTime(9 * 60, 1, atoi(films[num_film].duration.c_str()));	//
			if (time_first != 0)
			{
				time_second = CheckTime(time_first, 2, atoi(films[num_film].duration.c_str()));	//
				if (time_second != 0)
				{
					time_thord = CheckTime(time_second, 3, atoi(films[num_film].duration.c_str()));	//
					if (time_thord != 0)
					{
						//��� ������ ������� �����, ���������� ��������� ��� ����� �������
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
					if ((hours > 8 * 60 && hours < 60 * 21) && minutes < 60)
					{
						if (((3 - num_seans) * 15 + (4 - num_seans) * duration + hours + minutes) <= 21 * 60)
						{
							if (hours + minutes - duration - 15 >= time)
							{
								return (hours + minutes);
							}
						}
						else
						{
							cout << "����� �� ������������� �������!";
						}
					}
				}
			}
		}
	} while (true);
}

void Cinema::TimeAuto(int duration)
{
	/*
	int raznica;
	raznica = (13 * 60 - duration * 3 + 15 * 2 ) / 2;

	cout << raznica;

	cout << "������ �����: 8:00";

	cout << "\n������ ����� : " << ((21 * 60 - duration) - 2 * 15) / 60  << ":" << (((21 * 60 - duration) - (((21 * 60 - duration) - 2 * 15) / 60)) / 60);

	cout << "������ �����: " << (21 * 60 - duration) / 60 << ":" << ((21 * 60 - ((21 * 60 - duration) / 60)) / 60);
	_getch();
	*/
}

void Cinema::InputName()
{
	//name = "";
	do
	{
		cout << "������� �������� ����������: ";
		getline(cin, name);
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{

		cout << "������� ��� �������: ";
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
		system("cls");
		cout << "������� ��� ����������: ";
		getline(cin, inn);
	} while (inn == "");
}

void Cinema::InputAdress()
{
	do
	{
		cout << "������� ����� ����������: ";
		getline(cin, adress);
	} while (adress == "");
}

void Cinema::InputRNM()
{
	do
	{
		cout << "������� ���: ";
		getline(cin, rnm);
	} while (rnm == "");
}

void Cinema::NameOut()
{
	system("cls");
	cout << "��������� '" << name << "'\n\n";

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