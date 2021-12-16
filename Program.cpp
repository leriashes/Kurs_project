#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Program.h"
#include "Menu.h"
#include "File_O.h"
#include "Cinema.h"
using namespace std;

void Program::Start(Cinema cinema)
{
	 

	Menu menu;
	File_O file_stream;
	
	menu.cinema = &cinema;

	//���� ���� � ��
	do
	{
		system("cls");
		menu.File();
		menu.ChooseItem();
		if (menu.GetItem() == 1)	//���� � ����������� ������ �� default
		{
			file_stream.path = "kino_v_teatre.txt";
			if (file_stream.CheckCompound())		//�������� ����� �� ��������� ��������������
			{
				file_stream.Read(cinema);	//������ ������� � ���������
			}
		}
		else if (menu.GetItem() == 2)	//���� ������ ����� ����� � �����������
		{
			file_stream.InputPath();
		}

	} while (menu.GetItem() != 0 && !file_stream.CheckPath());

	if (menu.GetItem() != 0)
	{
		do
		{

			if (!menu.admin)
			{
				menu.Cashier();
				menu.ChooseItem();
			}

			//���������� � ����� �������
			if (menu.GetItem() == 1 && !menu.admin)
			{
				cinema.NameOut();
				menu.FilmList();
				_getch();
			}
			else if (menu.GetItem() == 2 || menu.admin)
			{
				//�������������
				//���� ������ ��������������


				// ������� ����� �� ������ ��������������
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
					//�������� ������ �����
				}
				else if (menu.GetItem() == 4)
				{
					//�������� ������ �����
				}
				else if (menu.GetItem() == 5)
				{
					//�������� ������ �����
				}
				else if (menu.GetItem() == 6)
				{
					//�������� ������ �����
				}
				else if (menu.GetItem() == 7)
				{
					//�������� ������ �����
				}
				else if (menu.GetItem() == 8)
				{
					//�������� ������ �����
				}
				else if (menu.GetItem() == 0)
				{
					menu.admin = false;
					//��������� 
				}

			}
		} while (menu.GetItem() != 0);
	}
}
