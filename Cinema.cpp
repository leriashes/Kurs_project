#include "Cinema.h"
#include "conio.h"

void Cinema::InputName()
{
	name = "";
	do
	{
		cout << "������� �������� ����������: ";
		cin >> name;
		cout << "\n";
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{
		cout << "������� ��� �������: ";
		cin >> full_name;
		cout << "\n";
		//�������� �� ������������� ������� ������� � ����???
	} while (full_name == "");
	
	//������������ �������
	return;
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
	return (temp);
}

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
