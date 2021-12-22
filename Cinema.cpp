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

/*void start()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu nem;
	File_O file_stream;
	Kinoteatr kinoteatr;

	//Menu menu1("Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n", 2);
	//menu1.print();
	//menu1.input_number();

	do
	{
		//ввод пути к БД
		do
		{
			system("cls");
			nem.file_choice(2);
			nem.input_number();
			if (nem.menu_number == 1)	//файл с кинотеатром указан по default
			{
				file_stream.path = "kino_v_teatre.txt\0";
				if (file_stream.file_check_compound(file_stream.path) == 1)		//проверка файла на внутренее форматирование
				{
					file_stream.file_read(file_stream.path);	//чтение фильмов в массивчик
				}

				_getch();

			}
			else if (nem.menu_number == 2)	//ввод своего имени файла с кинотеатром
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
				//открытие меню со списком фильмов
			}
		}
		else if (nem.menu_number == 2)
		{
			//администратор
			//ввод пароля администратора
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
				//создание нового файла
			}

		}
	} while (nem.menu_number != 0);

	//std::cout << "Hello World!\n";
}*/
