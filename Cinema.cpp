#include "Cinema.h"
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <string>
#include <windows.h>
#include "Menu.h"
#include "File_O.h"
#include "Kinoteatr.h"
#include <conio.h>
using namespace std;

/*void start()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu nem;
	File_O file_stream;
	Kinoteatr kinoteatr;

	//Menu menu1("��� ��������� ������ ������� ������� '1'.\n��� ����� � ����� �������������� ������� '2'.\n��� ������ ������� 'esc'.\n\n", 2);
	//menu1.print();
	//menu1.input_number();

	do
	{
		//���� ���� � ��
		do
		{
			system("cls");
			nem.file_choice(2);
			nem.input_number();
			if (nem.menu_number == 1)	//���� � ����������� ������ �� default
			{
				file_stream.path = "kino_v_teatre.txt\0";
				if (file_stream.file_check_compound(file_stream.path) == 1)		//�������� ����� �� ��������� ��������������
				{
					file_stream.file_read(file_stream.path);	//������ ������� � ���������
				}

				_getch();

			}
			else if (nem.menu_number == 2)	//���� ������ ����� ����� � �����������
			{
				file_stream.file_input();
			}
		} while (file_stream.file_check(file_stream.path) != 1);
		nem.start_menu();
		nem.input_number();

		if (nem.menu_number == 1)
		{
			nem.user_kassir();
			if (nem.menu_number == 1)
			{
				//�������� ���� �� ������� �������
			}
		}
		else if (nem.menu_number == 2)
		{
			//�������������
			//���� ������ ��������������
			nem.file_choice(1);
			nem.input_number();

			if (nem.menu_number == 1)
			{
				file_stream.path = "kino_v_teatre.txt\0";
				file_stream.file_check(file_stream.path);
			}
			else if (nem.menu_number == 2)
			{
				file_stream.file_input();

			}
			else if (nem.menu_number == 3)
			{
				//�������� ������ �����
			}

		}
	} while (nem.menu_number != 0);

	//std::cout << "Hello World!\n";
}*/
