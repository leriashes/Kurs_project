#include "Cinema.h"
#include "conio.h"
#include "File_O.h"
#include "Time.h"
#include "Menu.h"

void Cinema::ChangeName()
{
	cout << "Текущее название кинотеатра: " << name << "";
	InputName();
	return;
}

void Cinema::ChangeAdress()
{
	cout << "Текущий адес кинотеатра: " << address << "";
	InputAdress();
	return;
}

void Cinema::ChangeINN()
{
	cout << "Текущий ИНН: " << inn;
	InputINN();
	return;
}

void Cinema::ChangeRNM()
{
	cout << "Текущий РНМ: " << rnm;
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
		cout << "\n\n0) Назад\n\n1) Добавить кассира\n2) Удалить кассира\n";
		menu.ChooseItem();
		func = menu.GetItem();
	} while (func < 0 || func > promo_number);
	
	if (func == 1)
	{
		if (cashiers_number >= 5)
		{
			cout << "Удалите одного из кассиров прежде, чем добавлять нового.";
		}
		else
		{
			cashiers_number++;
			do
			{
				NameOut();
				cout << "Введите данные нового кассира: ";
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
			cout << "Введите порядковый номер кассира для удаления: ";
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
			cout << "Ни один кассир не найден";
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
	ListPromo(1);		//вывод всех промокодов
	cout << "Номер промокода для удаления: ";
	//функция возврата в меню
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
	ListPromo(1);		//вывод всех промокодов
	cout << "Номер промокода для редактирования: ";
	//функция возврата в меню
	Menu menu(promo_number);

	do
	{
		menu.ChooseItem();
		num = menu.GetItem();
	} while (num < 0 || num > promo_number);

	if (num != 0)
	{
		NameOut();
		cout << "Промокод: \"" << promo[num][0] << " (" << promo[num][1] << "%)";
		cout << "\n\n1) Название\n2) Номинал";
		int func;
		do
		{
			func = _getch();
		} while (func != '1' && func != '2');
		string temp = "";
		if (func == '1')
		{
			string old = "Текущее название промокода \"" + promo[num][0] + "\"\n\n";

			promo[num][0] = NewPromoName(old);
		}
		else if (func == '2')
		{
			string old = "Текущий номинал промокода \"" + promo[num][0] + "\" (" + promo[num][1] + "%)\n\n";
			promo[num][1] = NewPromoValue(old);
		}
	}
}

void Cinema::NewPromo()
{
	if (promo_number >= 9)
	{
		system("cls");
		cout << "Количество промокодов максимально. Удалите любой промокод прежде, чем добавлять новый";
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
		NameOut();
		cout << "1) Название\n2) Продолжительность\n3) Возрастное ограничение\n4) Краткое описание\n5) Главные роли\n6) Режиссер";
		cout << "\n\nВведите номер пункт для внесения изменений: ";
	}
	else if (num_punkt == 1 || num_punkt == -1)	//название фильма
	{
		do
		{
			if (num_punkt == 1)
			{
				NameOut();
				cout << "Текущее название фильма: " << films[num_film].name << "\n";
			}
			cout << "Название фильма: ";
			getline(cin, films[num_film].name);
		} while (films[num_film].name == "");
	}
	else if (num_punkt == 2 || num_punkt == -2)	//продожительность фильма
	{
		do
		{
			if (num_punkt == 2)
			{
				NameOut();
				cout << "Текущая продолжительность фильма: " << films[num_film].duration << " мин.";
			}
			string temp;
			cout << "\nПродолжительность фильма (мин.): ";
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
				NameOut();
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
				NameOut();
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
				NameOut();
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
				NameOut();
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
			cout << "\nСамое позднее время для первого сеанса: ";
			cout << (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) / 60 << ":" << (21 * 60 - 2 * 15 - 3 * (atoi(films[num_film].duration.c_str()))) % 60;
			//21*60
				//перерыв между сеансами для уборки 15 минут
			int first_time, second_time, third_time;
			int m, h;
			
			//TimeAuto(atoi(films[num_film].duration.c_str()));

			first_time = CheckTime(8 * 60, 1, atoi(films[num_film].duration.c_str()));	//
			if (first_time != 0)
			{
				h = (first_time + 15 + (atoi(films[num_film].duration.c_str()))) / 60;
				m = (first_time + 15 + (atoi(films[num_film].duration.c_str()))) % 60;
				cout << "\nСамое раннее время для второго сеанса: " << h << ":" << m << "\n";

				h = (21 * 60 - 15 - 2 * (atoi(films[num_film].duration.c_str()))) / 60;
				m = (21 * 60 - 15 - 2 * (atoi(films[num_film].duration.c_str()))) % 60;
				cout << "\nСамое позднее время для второго сеанса: " << h << ":" << m << "\n";

				second_time = CheckTime(first_time, 2, atoi(films[num_film].duration.c_str()));	//
				if (second_time != 0)
				{
					h = (second_time + 15 + (atoi(films[num_film].duration.c_str()))) / 60;
					m = (second_time + 15 + (atoi(films[num_film].duration.c_str()))) % 60;
					cout << "\nСамое раннее время для третьего сеанса: " << h << ":" << m << "\n";

					h = (21 * 60 - (atoi(films[num_film].duration.c_str()))) / 60;
					m = (21 * 60 - (atoi(films[num_film].duration.c_str()))) % 60;
					cout << "\nСамое позднее время для третьего сеанса: " << h << ":" << m << "\n";

					third_time = CheckTime(second_time, 3, atoi(films[num_film].duration.c_str()));	//
					if (third_time != 0)
					{
						films[num_film].time[0] = films[num_film].time[3] = films[num_film].time[6] = Convert_Time(first_time);
						films[num_film].time[1] = films[num_film].time[4] = films[num_film].time[7] = Convert_Time(second_time);
						films[num_film].time[2] = films[num_film].time[5] = films[num_film].time[8] = Convert_Time(third_time);
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
	else if (num_punkt == 8 || num_punkt == -8)	//стоимость сеансов
	{
		PriceInput(num_film, 0);
		PriceInput(num_film, 1);
		PriceInput(num_film, 2);
	}
	else if (num_punkt == 9 || num_punkt == -9)	//зал сеанса
	{
		NameOut();
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

		cout << "Доступные залы: ";
		for (int y = 0; y < 9; y++)
		{
			if (zals[y] > 0)
			{
				cout << zals[y] << "   ";
			}
		}
		
		bool zall =  false;
		int num;
		cout << "\n\nВведите номер зала: ";
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
			cout << "\n\nВведите время первого сеанса (пример: 12:40): ";
			//TimeAuto(duration);
		}
		else if (num_seans == 2)
		{
			cout << "\nВведите время второго сеанса (пример: 12:40): ";
		}
		else if (num_seans == 3)
		{
			cout << "\nВведите время третьего сеанса (пример: 12:40): ";
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
							cout << "Время не удовлетворяет условию!";
						}
					}
					else
					{
						cout << "Время не удовлетворяет условию!";
					}
				}
				else
				{
					cout << "Неверное формтирование. Повторите попытку";
				}
			}
			else
			{
				cout << "Неверное формтирование. Повторите попытку";
			}
		}
		else
		{
			cout << "Неверное формтирование. Повторите попытку";
		}
	} while (true);
}

void Cinema::TimeAuto(int duration)
{

	if (8 * 60 + duration <= 14 * 60)
	{
		if (14 * 60 + 2 * duration + 2 * 15 <= 21 * 60)
		{
			cout << "\n\n\nАвтоматическое проставление времени сеансов: ";
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
	
	//_getch();
	return;
}

string Cinema::Convert_Time(int time)
{
	int temp;
	string ret;
	//конвертация в часы и минуты с помощью деления, добавления знака :
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
		cout << "\n\nВведите название кинотеатра: ";
		getline(cin, name);
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{
		cout << "\n\nВведите ФИО кассира: ";
		getline(cin, full_name);
		//проверка на существование данного кассира в базе???
	} while (full_name == "");

	return;
}

void Cinema::InputINN()
{
	do
	{
		cout << "\n\nВведите ИНН кинотеатра: ";
		getline(cin, inn);
	} while (inn == "");

	return;
}

void Cinema::InputAdress()
{
	do
	{
		cout << "\n\nВведите адрес кинотеатра: ";
		getline(cin, address);
	} while (address == "");

	return;
}

void Cinema::InputRNM()
{
	do
	{
		cout << "\n\nВведите РНМ: ";
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
		cout << "Введите стоимость билета для сеанса в " << films[num_film].time[num] << ": ";
		getline(cin, temp);	//Проверка на правильность ввода ???? заменить на ввод int
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
		cout << "Кинотеатр '" << name << "'\n\n";
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