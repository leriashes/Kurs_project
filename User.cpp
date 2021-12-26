#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "User.h"

bool User::admin = false;
string User::password = "Kino12345";
string User::parol = "";

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

	while (true)
	{
		system("cls");
		printf("������� ������: ");

		parol = "";
		//���� ������
		char symbol;
		do
		{
			symbol = _getch();
			if (symbol != 13 && symbol != 8)
			{
				cout << "*";
				parol += symbol;
			}

			//���� ������ ������� backspace
			if (symbol == 8)
			{
				if (parol.length() > 0)
				{
					cout << "\b \b";
					parol.pop_back();
				}
			}

		} while (symbol != 13);

		//code(parol);

		//�������� ������������ ������
		//���� ������ ����� �������
		if (password != parol)
		{
			Menu menu;
			do
			{
				system("cls");
				cout << "�������� ������!\n��� �������� � ���� ������� '0'.\n��� ���������� ����� ������ ������� '1'.\n��� ������ ������� 'esc'.";

				
				menu.items_number = 1;
				menu.ChooseItem();

				if (menu.GetItem() == 0)
					return;

			} while (menu.GetItem() == -1);

		}
		//���� ������ ����� �����
		else
		{
			admin = true;
			break;
		}
	}
	
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

	while (admin)
	{
		//�������������
		//���� ������ ��������������

		// ������� ����� �� ������ ��������������
		admin = true;

		menu.Admin(file_stream);
		//menu.File();
		menu.ChooseItem();

		if (menu.GetItem() == 1)
		{
			file_stream.path = "kino_v_teatre.txt";

			if (file_stream.CheckPath() && file_stream.CheckCompound())		//�������� ����� �� ��������� ��������������
			{
				system("cls");
				cout << "��� ���������� ������ �� �����. \n\n��������";
				thread t(Time::PrintLoading);

				Time::loadingComplete = false;
				file_stream.Read(cinema);
				Time::loadingComplete = true;
				t.join();
			}
			/*
			else
			{
				error = "���� \"" + file_stream.path + "\" �� ������������� �������� ��������������.\n";
			}*/
		}
		else if (menu.GetItem() == 2)
		{
			file_stream.InputPath();
			if (file_stream.CheckPath() && file_stream.CheckCompound())		//�������� ����� �� ��������� ��������������
			{
				system("cls");
				cout << "��� ���������� ������ �� �����. \n\n��������";
				thread t(Time::PrintLoading);

				Time::loadingComplete = false;
				file_stream.Read(cinema);
				Time::loadingComplete = true;
				t.join();
			}
			/*
			else
			{
				error = "���� \"" + file_stream.path + "\" �� ������������� �������� ��������������.\n";
			}*/
		}
		else if (menu.GetItem() == 3)
		{
			file_stream.New(cinema);
			//�������� ������ �����
		}
		else if (menu.GetItem() == 4)
		{
			while (true)
			{
				menu.ChangeProkat();
				menu.ChooseItem();
				if (menu.GetItem() == 1)	//�������� ������ �� �������
				{
					//����� ������ �������
					do
					{
						system("cls");
						cout << "�������� ������\n\n";
						menu.FilmList();
						menu.ChooseItem();
					} while (menu.GetItem() < 0);

					if (menu.GetItem() != 0)
					{
						cinema.DelFilm(menu.GetItem() - 1);
						system("cls");
						cout << "����� ��� ������� ������!";
						file_stream.Write(cinema);
						_getch();
						//����� �� ������������� ��������???
					}

				}
				else if (menu.GetItem() == 2)	//�������������� ���������� � ������ � �������
				{
					int num_film = -1;
					do
					{
						do
						{
							//����� ������ �������
							system("cls");
							cout << "�������������� ���������� � ������\n\n";
							menu.FilmList();
							menu.ChooseItem();
						} while (menu.GetItem() < 0);

						num_film = 0;
						if (menu.GetItem() > 0)
						{
							num_film = menu.GetItem() - 1;

							while (true)
							{
								cinema.ChangeFilm(0, num_film);
								menu.items_number = 6;
								menu.ChooseItem();
								if (menu.GetItem() > 0 && menu.GetItem() < 7)
								{
									cinema.ChangeFilm(menu.GetItem(), num_film);
									file_stream.Write(cinema);
								}
								else if (menu.GetItem() == 0)
								{
									num_film = -1;
									break;
								}
							}
						}
							
					} while (menu.GetItem() < 0 || num_film < 0);
				}
				else if (menu.GetItem() == 3)	//���������� ������ ������ � ������
				{
					if (cinema.films_number < 9)
					{
						cinema.NameOut();
						cinema.ChangeFilm(-1, cinema.films_number);		//���� �������� ������
						cinema.ChangeFilm(-2, cinema.films_number);		//���� ���������������� ������
						cinema.ChangeFilm(-3, cinema.films_number);		//���� ����������� ����������� ������
						cinema.ChangeFilm(-4, cinema.films_number);		//���� �������� �������� ������
						cinema.ChangeFilm(-5, cinema.films_number);		//���� ���������� ������� ������
						cinema.ChangeFilm(-6, cinema.films_number);		//���� �������� ������
						cinema.ChangeFilm(-7, cinema.films_number);		//���� ������� �������
						cinema.ChangeFilm(-8, cinema.films_number);		//���� ��������� ������
						cinema.ChangeFilm(-9, cinema.films_number);		//���� ������ ���� ��� ������ ������

						cinema.NameOut();
						cout << "��� ������ ������ � ����. \n\n��������";
						thread t(Time::PrintLoading);
						Time::loadingComplete = false;
						for (int y = 0; y < 9; y++)
						{
							cinema.NewHallCinema(cinema.films_number);
						}
						Time::loadingComplete = true;
						t.join();

						//cout << "drop";
						//���������� ���� � ������� ������� �� ����������
						cinema.films_number++;
						file_stream.Write(cinema);
						cinema.NameOut();
						cout << "\n������ ������� ��������!";
						_getch();

					}
					else
					{
						cout << "���������� ������� � ������� �������� ������������� ����������";
						cout << "\n\n������� ����� ������� ��� �������� � ����";
						_getch();
					}

				}
				else if (menu.GetItem() == 0)
					break;

				//���������� ��� �������� ������
				//����� ������ �������
				//�����
				//�������������� ���������� � ������
				//����� ������ �������
				//����� ������ ��� �������������� ���������� � ���
				//����� ������� ��� ��������������
			}
		}
		else if (menu.GetItem() == 5)
		{
			do
			{
				cinema.NameOut();
				cinema.ListPromo(0);
				cout << "1) ������� ��������\n2) �������� ��������\n3) �������� ��������";
				menu.items_number = 3;
				menu.ChooseItem();

				if (menu.GetItem() == 1)	//�������� ���������
				{
					cinema.DelPromo();
				}
				else if (menu.GetItem() == 2)	//�������������� ���������
				{
					cinema.RedPromo();
				}
				else if (menu.GetItem() == 3)	//���������� ������ ���������
				{
					cinema.NewPromo();
				}
				file_stream.Write(cinema);
			} while (menu.GetItem() != 0);	//???? �������� ������� ????
			
		}
		else if (menu.GetItem() == 6)
		{
			//������������� ������
			//����� ������ �������
			//����� ���� �������
			//����� ����� ��� �������������
		}
		else if (menu.GetItem() == 7)
		{
			while (true)
			{
				cinema.NameOut();
				cout << "�������� ����� ��� ��������������";
				cout << "\n\n1) ��������\n2) �����\n3) �������\n4) ���\n5) ���";
				menu.items_number = 5;
				menu.ChooseItem();
				cinema.NameOut();
				if (menu.GetItem() == 0)
					break;
				else
				{
					if (menu.GetItem() == 1)
					{
						cinema.ChangeName();
					}
					else if (menu.GetItem() == 2)
					{
						cinema.ChangeAdress();
					}
					else if (menu.GetItem() == 3)
					{
						cinema.ChangeCashier();
					}
					else if (menu.GetItem() == 4)
					{
						cinema.ChangeINN();
					}
					else if (menu.GetItem() == 5)
					{
						cinema.ChangeRNM();
					}
					file_stream.Write(cinema);
				}
			}
		}
		else if (menu.GetItem() == 0)
		{
			AdminLogOut();
		}
	}

	return;
}