#include "Cinema.h"
#include "conio.h"

void Cinema::ChangeName()
{
	cout << "Текущее название кинотеатра: " << name << "\n\n";
	InputName();
	
}

void Cinema::ChangeAdress()
{
	cout << "Текущий адес кинотеатра: " << adress << "\n\n";
	InputAdress();
}

void Cinema::ChangeInn()
{
	system("cls");
	cout << "Текущий ИНН: " << inn;
	InputINN();
}

void Cinema::ChangeRnm()
{
	system("cls");
	cout << "Текущий РНМ: " << rnm;
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
	ListPromo(1);		//вывод всех промокодов
	cout << "Номер промокода для удаления: ";
	//функция возврата в меню
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
	ListPromo(1);		//вывод всех промокодов
	cout << "Номер промокода для редактирования: ";
	//функция возврата в меню
	do
	{
		num = _getch();
	} while (num < '1' || num - 48 > promo_numbers);
	system("cls");
	cout << "Промокод: \"" << promo[num - 48][0] << " (" << promo[num - 48][1] << "%)";
	cout << "\n\n1) Название\n2) Номинал";
	int func;
	do
	{
		func = _getch();
	} while (func != '1' && func != '2');
	string temp = "";
	if (func == '1')
	{
		string old = "Текущее название промокода \"" + promo[num - 48][0] + "\"\n\n";
		
		promo[num - 48][0] = NewPromoName(old);
	}
	else if (func == '2')
	{
		string old = "Текущий номинал промокода \"" + promo[num - 48][0] + "\" (" + promo[num - 48][1] + "%)\n\n";
		promo[num - 48][1] = NewPromoValue(old);
	}
}

void Cinema::NewPromo()
{
	if (promo_numbers >= 9)
	{
		system("cls");
		cout << "Количество промокодов максимально. Удалите любой промокод прежде, чем добавлять новый";
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
		cout << "Название промокода: ";
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
		cout << "Введите номинал: ";
		getline(cin, temp);
		if (temp[temp.size() - 1] == '%' || temp[temp.size() - 1] == ' ')
		{
			temp.resize(temp.size() - 1);       //обрезка знака процента или пробела
		}
		if (temp.size() < 3 && temp[0] != '0')
		{	//проверка на состав только из цифр или же из %%

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
	//сдвиг всех фильмов через цикл, начиная от удаляемого

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
		cout << "1) Название\n2) Продолжительность\n3) Возрастное ограничение\n4) Краткое описание\n5) Главные роли\n6) Режиссер";
		cout << "\n\nВведите пункт для внесения изменений: ";
	}
	else if (num_punkt == 1 || num_punkt == -1)	//название фильма
	{
		do
		{
			if (num_punkt == 1)
			{
				system("cls");
				cout << "Текущее название фильма: " << films[num_film].name;
			}
			cout << "\nНазвание фильма: ";
			getline(cin, films[num_film].name);
		} while (films[num_film].name == "");
	}
	else if (num_punkt == 2 || num_punkt == -2)	//продожительность фильма
	{
		do
		{
			if (num_punkt == 2)
			{
				system("cls");
				cout << "Текущая продолжительность фильма: " << films[num_film].duration << " мин.";
			}
			string temp;
			cout << "\nПродолжительность фильма: ";
			getline(cin, films[num_film].duration);		//проверка на отсутствие лишних символов
			for (int y = 0; y < (films[num_film].duration).length(); y++)		//проверка на отсутствие лишних символов
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
	else if (num_punkt == 3 || num_punkt == -3)	//возрастное ограничение
	{
		do
		{
			if (num_punkt == 3)
			{
				system("cls");
				cout << "Текущее возрастное ограничение фильма: " << films[num_film].age ;
			}
			string temp;
			cout << "\nВозрастное ограничение фильма: ";
			getline(cin, films[num_film].age);
			for (int y = 0; y < (films[num_film].age).length(); y++)		//проверка на отсутствие лишних символов
			{
				if (films[num_film].age[y] >= '0' && films[num_film].age[y] <= '9')
				{
					temp = temp + films[num_film].age[y];
				}
			}
			films[num_film].age = temp + "+";
		} while (films[num_film].age == "");
	}
	else if (num_punkt == 4 || num_punkt == -4)	//краткое описание
	{
		do
		{
			if (num_punkt == 4)
			{
				system("cls");
				cout << "Текущее краткое описание фильма: " << films[num_film].short_description;
			}
			cout << "\nКраткое описание фильма: ";
			getline(cin, films[num_film].short_description);
		} while (films[num_film].short_description == "");
	}
	else if (num_punkt == 5 || num_punkt == -5)	//Главные роли
	{
		do
		{
			if (num_punkt == 5)
			{
				system("cls");
				cout << "Текущие актеры в главной роли фильма: " << films[num_film].main_role;
			}
			cout << "\nГлавные роли фильма: ";	//куцое предложение!!!
			getline(cin, films[num_film].main_role);
		} while (films[num_film].main_role == "");
	}
	else if (num_punkt == 6 || num_punkt == -6)	//Режиссер(-ы)
	{
		do
		{
			if (num_punkt == 6)
			{
				system("cls");
				cout << "Текущие режиссер(-ы) фильма: " << films[num_film].rejisser;
			}
			cout << "\nРежиссер(-ы) фильма: ";
			getline(cin, films[num_film].rejisser);
		} while (films[num_film].rejisser == "");
	}
	else if (num_punkt == 7 || num_punkt == -7)	//время и стоимость сеансов
	{
		if (num_punkt == -7)
		{ 
			//время работы с 9 до 21;
			cout << "Самое позднее время для первого сеанса: ";
			cout << (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) / 60 << ":" << (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) % 60;
			//21*60
				//перерыв между сеансами для уборки 15 минут
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
						//все сеансы введены верно, необходимо присвоить это время сеансам
					}
				}
			}
			

			/*
			cout << "\n\nВведите время первого сеанса (пример: 12:40): ";
			bool time = false;
			string temp;
			getline(cin, temp);
			int minutes;
			int hours;
			//проверка на правильность ввода
			if (temp.length() == 4 || temp.length() == 5)	//первая проверка на правильность ввода времени
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
					if (isdigit(int(temp[0])) && isdigit(int(temp[o])) && isdigit(int(temp[k])) && isdigit(int(temp[k + 1])))			//проверка на принадлежность всех элементов к цифрам
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
							cout << "хорошее время!";
							time = true;
						}
					}
				}
				if (time)
				{
					cout << "Введите время второго сеанса: ";
					_getch();
				}
			}
			/*if (temp.length() == 4 || temp.length() == 5)	//первая проверка на правильность ввода времени
			{
				if (temp[1] == ':' || temp[2] == ':')	//вторая проверка на правильность ввода времени
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
			cout << "\n\nВведите время первого сеанса (пример: 12:40): ";
		}
		else if (num_seans == 2)
		{
			cout << "\n\nВведите время второго сеанса (пример: 12:40): ";
		}
		else if (num_seans == 3)
		{
			cout << "\n\nВведите время третьего сеанса (пример: 12:40): ";
		}
		getline(cin, temp);
		int minutes;
		int hours;
		//проверка на правильность ввода
		if (temp.length() == 4 || temp.length() == 5)	//первая проверка на правильность ввода времени
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
				if (isdigit(int(temp[0])) && isdigit(int(temp[o])) && isdigit(int(temp[k])) && isdigit(int(temp[k + 1])))			//проверка на принадлежность всех элементов к цифрам
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
							cout << "Время не удовлетворяет условию!";
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

	cout << "Первый сеанс: 8:00";

	cout << "\nВторой сеанс : " << ((21 * 60 - duration) - 2 * 15) / 60  << ":" << (((21 * 60 - duration) - (((21 * 60 - duration) - 2 * 15) / 60)) / 60);

	cout << "Третий сеанс: " << (21 * 60 - duration) / 60 << ":" << ((21 * 60 - ((21 * 60 - duration) / 60)) / 60);
	_getch();
	*/
}

void Cinema::InputName()
{
	//name = "";
	do
	{
		cout << "Введите название кинотеатра: ";
		getline(cin, name);
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{

		cout << "Введите ФИО кассира: ";
		getline(cin, full_name);
		//проверка на существование данного кассира в базе???
	} while (full_name == "");
	
	//присваивание кассиру
	return;
}

void Cinema::InputINN()
{
	do
	{
		system("cls");
		cout << "Введите ИНН кинотеатра: ";
		getline(cin, inn);
	} while (inn == "");
}

void Cinema::InputAdress()
{
	do
	{
		cout << "Введите адрес кинотеатра: ";
		getline(cin, adress);
	} while (adress == "");
}

void Cinema::InputRNM()
{
	do
	{
		cout << "Введите РНМ: ";
		getline(cin, rnm);
	} while (rnm == "");
}

void Cinema::NameOut()
{
	system("cls");
	cout << "Кинотеатр '" << name << "'\n\n";

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
	//cout << filmi[number_film].mesta[number];	//тест
	//cout << filmi[number_film].mesta[(number_d - 1) * 3 + (number_t - 1)];	//тест
	//_getch();
	return temp;
}