#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include <conio.h>
#include "Menu.h"
#include "File_O.h"
#include "Cinema.h"
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu menu;
	File_O file_stream;
	Cinema cinema;

	//Menu menu1("��� ��������� ������ ������� ������� '1'.\n��� ����� � ����� �������������� ������� '2'.\n��� ������ ������� 'esc'.\n\n", 2);
	//menu1.print();
	//menu1.input_number();

	do
	{
		//���� ���� � ��
		do
		{
			system("cls");
			menu.ChooseFile(2);
			menu.ChooseItem();
			if (menu.GetItem() == 1)	//���� � ����������� ������ �� default
			{
				file_stream.path = "kino_v_teatre.txt";
				if (file_stream.CheckCompound(file_stream.path) == 1)		//�������� ����� �� ��������� ��������������
				{
					file_stream.Read(file_stream.path);	//������ ������� � ���������
				}

				_getch();

			}
			else if (menu.GetItem() == 2)	//���� ������ ����� ����� � �����������
			{
				file_stream.Input();
			}

		} while (file_stream.Check(file_stream.path) != 1);
		menu.Start();
		menu.ChooseItem();

		if (menu.GetItem() == 1)
		{
			menu.Cashier();
			if (menu.GetItem() == 1)
			{
				//�������� ���� �� ������� �������
			}
		}
		else if (menu.GetItem() == 2)
		{
			//�������������
			//���� ������ ��������������
			menu.ChooseFile(1);
			menu.ChooseItem();

			if (menu.GetItem() == 1)
			{
				file_stream.path = "kino_v_teatre.txt";
				file_stream.Check(file_stream.path);
			}
			else if (menu.GetItem() == 2)
			{
				file_stream.Input();

			}
			else if (menu.GetItem() == 3)
			{
				//�������� ������ �����
			}

		}
	} while (menu.GetItem() != 0);

	//std::cout << "Hello World!\n";
}
