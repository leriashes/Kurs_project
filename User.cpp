#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "User.h"

bool User::admin = false;

bool User::GetAdmin()
{
	return admin;
}

bool User::SignIn()
{
	return true;
}

void User::AdminLogIn()
{
	admin = true;
	return;
}

void User::AdminLogOut()
{
	admin = false;
	return;
}

void User::Admin(Cinema &cinema, File_O &file_stream)
{
	Menu menu;
	menu.cinema = &cinema;
	AdminLogIn();

	if (admin)
	{
		//администратор
		//ввод пароля администратора

		// сделать выход из режима администратора
		admin = true;

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
					cinema.ChangeFilm(-8, cinema.films_number);		//ввод стоимости билета
					cinema.ChangeFilm(-9, cinema.films_number);		//ввод номера зала для показа фильма
					for (int y = 0; y < 9; y++)
					{
						cinema.NewHallCinema(cinema.films_number);
					}

					//cout << "drop";
					_getch();
					//добавление зала и времени сеансов со стоимостью
					cinema.films_number++;
					file_stream.Write(cinema);
					cout << "Все было успешно записано!";

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
			do
			{
				cinema.NameOut();
				cinema.ListPromo(0);
				cout << "1) Удалить промокод\n2) Изменить промокод\n3) Добавить промокод";
				menu.items_number = 3;
				menu.ChooseItem();

				if (menu.GetItem() == 1)	//удаление промокода
				{
					cinema.DelPromo();
					cinema.ListPromo(0);
				}
				if (menu.GetItem() == 2)	//редактирование промокода
				{
					cinema.RedPromo();
					cinema.ListPromo(0);
				}
				if (menu.GetItem() == 3)	//добавление нового промокода
				{
					cinema.NewPromo();
				}
				file_stream.Write(cinema);
			} while (menu.GetItem() != 0);	//???? изменить условие ????
			
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
				cinema.ChangeINN();
			}
			if (menu.GetItem() == 5)
			{
				cinema.ChangeRNM();
			}
			file_stream.Write(cinema);
			//создание нового файла
		}
		else if (menu.GetItem() == 0)
		{
			AdminLogOut();
			//menu.admin = false;
			//f = true;
			//изменение 
		}
	}

	return;
}