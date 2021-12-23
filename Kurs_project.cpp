#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "Order.h"
#include "File_O.h"
#include <thread>
using namespace std;



bool loadingComplete;
void PrintLoading()
{
	int i = 0;
	do
	{
		std::cout << '.';
		std::this_thread::sleep_for(0.5s);
		i++;
		if (i == 3)
		{
			i = 0;
			cout << "\b \b\b \b\b \b";
			std::this_thread::sleep_for(0.5s);
		}
	} while (!loadingComplete);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Cinema cinema;
	Order order;
	Menu menu;
	File_O file_stream;
	bool f, n;
	order.cinema = menu.cinema = &cinema;
	string error = "\0";
	menu.cinema = &cinema;
	//ввод пути к БД
	do
	{
		system("cls");
		if (file_stream.path == "0" && error != "\0")
		{
			cout << error << "\n\n";
		}

		menu.File();
		menu.ChooseItem();
		
		/*
		if (menu.GetItem() == 1)	//файл с кинотеатром указан по default
		{
			file_stream.path = "kino_v_teatre.txt";
			if (file_stream.CheckCompound())		//проверка файла на внутренее форматирование
			{
				system("cls");
				cout << "Происходит считывание данных из файла. \n\nОжидайте...";
				thread t(PrintLoading);

				loadingComplete = false;
				file_stream.Read(cinema);
				loadingComplete = true;
				t.join();
				//cout << "Происходит считывание данных из файла. \n\nОжидайте...";
				//file_stream.Read(cinema);	//чтение фильмов в массивчик
			}
			else
			{
				system("cls");
				error = "Данные файла \"" + file_stream.path + "\" не удовлетворяют форматированию\n\0";
			}
		}
		else if (menu.GetItem() == 2)	//ввод своего имени файла с кинотеатром
		{
			file_stream.InputPath();
		}
		*/
		file_stream.path = "kino_v_teatre.txt";
		if (menu.GetItem() == 2)	//ввод своего имени файла с кинотеатром
		{
			file_stream.InputPath();
		}
		//происходит проверка где-то тут!
		if (file_stream.path != "0")
		{
			if (file_stream.CheckCompound())		//проверка файла на внутренее форматирование
			{
				system("cls");
				cout << "Происходит считывание данных из файла. \n\nОжидайте";
				thread t(PrintLoading);

				loadingComplete = false;
				file_stream.Read(cinema);
				loadingComplete = true;
				t.join();
				//cout << "Происходит считывание данных из файла. \n\nОжидайте...";
				//file_stream.Read(cinema);	//чтение фильмов в массивчик
			}
			else
			{
				error = "Данные файла \"" + file_stream.path + "\" не удовлетворяют форматированию\n\0";
				
			}
		}
		/*else if (menu.GetItem() == 3)
		{
			//вход в режим администратора
		}*/

	} while (menu.GetItem() == 0 || file_stream.path == "0" || !file_stream.CheckPath() || !file_stream.CheckCompound());

	f = true; 
	n = false;

	while (true)
	{
  		if (!menu.admin && f && menu.num_film == 0)
		{
			menu.Cashier();
			menu.ChooseItem();
			menu.Clear();
		}

 		if ((menu.GetItem() == 1 || menu.GetItem() <= 0 && !f || n) && !menu.admin)
		{
			n = true;
			cinema.NameOut();
			if (menu.num_film <= 0)
			{
				menu.FilmList();
				menu.ChooseFilm();
				order.film = menu.num_film;

				if (menu.num_film == 0)
					f = true;
				else if (menu.num_film == -1)
					f = false;
			}

			if (menu.num_film > 0)
			{
				f = false;

				if (menu.num_day <= 0)
				{
					menu.Description();	//ввод даты посещения
					menu.ChooseItem();
					menu.num_day = menu.GetItem();
					order.day = menu.num_day;

					if (menu.num_day == -1)
						menu.num_day = 0;
				}

				if (menu.num_day != 0 && menu.num_time == 0)
				{
					menu.Description();	//ввод времени посещения
					menu.ChooseItem();
					menu.num_time = menu.GetItem();
					order.time = menu.num_time;

					if (menu.num_time == -1)
						menu.num_time = 0;
				}

				if (menu.num_time != 0)
				{
					//вывод мест в кинотеатре
					if (order.ChoosePlace())
						menu.num_time = 0;
					else
						menu.Clear();
					//order.PrintInfo();

					//_getch();
				}

				//f = menu.GetItem() != 0;
			}
			
		}
		else if (menu.GetItem() == 2 && f || menu.admin)
		{
			//администратор
			//ввод пароля администратора


			// сделать выход из режима администратора
			menu.admin = true;
			menu.Admin();
			//menu.File();
			menu.ChooseItem();

			if (menu.GetItem() == 1)
			{
				file_stream.path = "kino_v_teatre.txt";
				file_stream.CheckPath();
			}
			else if (menu.GetItem() == 2)
			{
				file_stream.InputPath();
			}
			else if (menu.GetItem() == 3)
			{
				file_stream.New(cinema);
				//создание нового файла
			}
			else if (menu.GetItem() == 4)
			{
				menu.ChangeProkat();
				menu.ChooseItem();
				if (menu.GetItem() == 1)	//удаление фильма из проката
				{
					//вывод списка фильмов
					system("cls");
					cout << "Удаление фильма\n\n";
					menu.FilmList();
					//cout << "Введите номер фильма для удаления из проката: ";
					menu.items_number = cinema.films_number;
					menu.ChooseItem();
					cinema.DelFilm(menu.GetItem() - 1);
					system("cls");
					cout << "Фильм был успешно удален!";
					menu.FilmList();
					_getch();
					//нужно ли подтверждение удаления???

				}
				else if (menu.GetItem() == 2)	//редактирование информации о фильме в прокате
				{
					do
					{
						//вывод списка фильмов
						system("cls");
						cout << "Редактирование информации о фильме\n\n";
						menu.FilmList();
						cout << "Введите номер фильма для внесения изменений: ";
						menu.items_number = cinema.films_number;
						menu.ChooseItem();
						int num_film = menu.GetItem() - 1;
						cinema.ChangeFilm(0, num_film);

						menu.items_number = 6;
						menu.ChooseItem();
						if (menu.GetItem() == 1)	//изменение названия фильма
						{
							cinema.ChangeFilm(1, num_film);
						}
						if (menu.GetItem() == 2)	//изменение продолжительности фильма
						{
							cinema.ChangeFilm(2, num_film);
						}
						if (menu.GetItem() == 3)	//изменение возрастного ограничения фильма
						{
							cinema.ChangeFilm(3, num_film);
						}
						if (menu.GetItem() == 4)	//изменение краткого описания фильма
						{
							cinema.ChangeFilm(4, num_film);
						}
						if (menu.GetItem() == 5)	//изменение актерского состава фильма
						{
							cinema.ChangeFilm(5, num_film);
						}
						if (menu.GetItem() == 6)	//изменение режиссеров фильма
						{
							cinema.ChangeFilm(6, num_film);
						}

						file_stream.Write(cinema);
						//запись изменений в файл!!!
					} while (menu.GetItem() != '0');
				}
				else if (menu.GetItem() == 3)	//добавление нового фильма в прокат
				{
					
					system("cls");
					if (cinema.films_number < 8)
					{
						cinema.ChangeFilm(-1, cinema.films_number);		//ввод названия фильма
						cinema.ChangeFilm(-2, cinema.films_number);		//ввод продожительности фильма
						cinema.ChangeFilm(-3, cinema.films_number);		//ввод возрастного ограничения фильма
						cinema.ChangeFilm(-4, cinema.films_number);		//ввод краткого описания фильма
						cinema.ChangeFilm(-5, cinema.films_number);		//ввод актерского состава фильма
						cinema.ChangeFilm(-6, cinema.films_number);		//ввод режиссер фильма
						cinema.ChangeFilm(-7, cinema.films_number);		//ввод времени сеансов
						cout << "drop";
						_getch();
						//добавление зала и времени сеансов со стоимостью
						cinema.films_number++;
						file_stream.Write(cinema);
						
					}
					else
					{
						cout << "Количество фильмов в прокате достигло максимального количества";
						cout << "\n\nНажмите любую клавишу для возврата в меню";
						_getch();
					}

				}

				//добавление или удаление фильма
				//вывод списка фильмов
				//выбор
				//Редактирование информации о фильме
				//вывод списка фильмов
				//выбор фильма для редактирования информации о нем
				//вывод пунктов для редактирования
			}
			else if (menu.GetItem() == 5)
			{
				//Добавление или удаление промокода
				//вывод текущего списка промокодов
				//вывод действий над данными промокодамит
			}
			else if (menu.GetItem() == 6)
			{
				//Аннулирование билета
				//вывод списка фильмов
				//вывод даты времени
				//выбор места для аннулирования
			}
			else if (menu.GetItem() == 7)
			{
				system("cls");
				cout << "Выберите пункт для редактирования";
				cout << "\n\n1) Название\n2) Адрес\n3) Кассиры\n4) ИНН\n5) РНМ";
				menu.items_number = 5;
				menu.ChooseItem();
				system("cls");
				if (menu.GetItem() == 1)
				{
					cinema.ChangeName();
				}
				if (menu.GetItem() == 2)
				{
					cinema.ChangeAdress();
				}
				if (menu.GetItem() == 3)
				{
					cinema.ChangeCashier();
				}
				if (menu.GetItem() == 4)
				{
					cinema.ChangeInn();
				}
				if (menu.GetItem() == 5)
				{
					cinema.ChangeRnm();
				}
				//создание нового файла
			}
			else if (menu.GetItem() == 0)
			{
				menu.admin = false;
				f = true;
				//изменение 
			}

		}

	}

	

	/// 
	/// ДОБАВИТЬ ДЛЯ ВСЕХ РЕЖИМОВ ВОЗМОЖНОСТЬ СМЕНЫ ТЕКСТОВИКА С БАЗОЙ
	/// 
	/// 

	/*Menu.User_kassir();
	Menu.Input_number();
	do
	{
		if (Menu.menu_number == 1)
		{
			Menu.Spisok_kino(kinoteatr);	//Выбор фильма для посещения
			Menu.Input_number();
			Menu.num_film = Menu.menu_number;
			Menu.num_day = -1;
			if (Menu.menu_number != 0)	//переход к описанию фильма
			{
				Menu.num_time = -1;
				Menu.Opisanie(kinoteatr);	//ввод даты посещения
				Menu.Input_number();
				Menu.num_day = Menu.menu_number;	//день на покупку/бронь билета

				Menu.Opisanie(kinoteatr);	//ввод времени посещения
				Menu.Input_number();
				Menu.num_time = Menu.menu_number;

				Menu.Opisanie(kinoteatr);	//вывод мест в кинотеатре
				///
				///обработка введеного места
				///
				/// 
				_getch();
			}
		}
	} while (nem.menu_number != 0);*/
	
}
