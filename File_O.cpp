#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>;
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "File_O.h";
using namespace std;


void File_O::InputPath()
{
    do
    {
        do
        {
            cout << "\n0 - возврат в меню\n\nВведите путь к файлу с информацией о кинотеатре: ";

            cin >> path;
        } while (path == "");

        if (path == "0")
        {
            return;
        }

    } while (!CheckPath());
    _getch();
}

void File_O::New()
{
    cout << "Введите название нового файла (без расширения): ";
    string path;


    //проверка введеного имени файла на наличие "txt"

    if (CheckPath())   //проверка на существование такого файла в памяти
    {
        //файл с таким названием существует, создать копию и создать чистый файл или затереть текущий
        cout << "Файл с таким названием уже существует\n1) Создать копию файла и переименовать (" << path + "_1.txt)" << "\n2) Удалить текущую версию файла " << path;
        /*item_num = 2;
        input_number();
        if (menu_number == 1)
        {
            ifstream    inFile(path + ".txt");
            ofstream    outFile(path + "_1.txt");

            outFile << inFile.rdbuf();
            ofstream fout(path);
            fout.close();
        }
        else if (menu_number == 2)
        {
            ofstream fout(path); //создание объекта класса ofstream для записи
            fout.close();   //закрытие фалйа
        }*/
                
    }
    
    if (CheckPath() == 1)
    {
        //файл успешно создан, заполнение информации о кинотеатре
    }
    else
    {
        //файл не создан, изменение файла
    }

}

bool File_O::CheckPath()
{
	bool result = false;
    ifstream f1;

    f1.open(path);
    if (!(f1.is_open())) {
        cout << "Файл не найден";
        //создание файла, заполнение всех данных

    }
    else {
        cout << "Файл найден!";
        result = true;
    }

	return result;
    /*ofstream fout(path); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
    fout << "Работа с файлами в С++"; // запись строки в файл
    fout.close(); // закрываем файл
    */
}



void File_O::Read(Cinema& cinema)
{
    ifstream file(path);

    int numb = 0;
    int i = 0;
    int j = 0;
    string temp;

    //заполнение информации о кинотеатре
    getline(file, cinema.name);    //чтение названия кинотеатра
    getline(file, cinema.adress);    //чтение адреса кинотеатра

	//???? читаем только одного ?????
    getline(file, cinema.cashiers[0]);     //чтения ФИО кассиров


    //разложение количества кассиров на массив ???

    getline(file, temp);

    //заполнение информации о фильмах
    do
    {
        getline(file, cinema.films[i].name);
        getline(file, cinema.films[i].duration);
        getline(file, cinema.films[i].age);
        getline(file, cinema.films[i].short_description);
        getline(file, cinema.films[i].main_role);
        getline(file, cinema.films[i].rejisser);
        
        getline(file, temp);

        for (j = 0; j < 9; j++)
        {
            getline(file, (cinema.films[i].time[j]));
            getline(file, (cinema.films[i].price[j]));
            for (int k = 0; k < 10; k++)
            {
                getline(file, temp);
				cinema.films[i].mesta[j] = cinema.films[i].mesta[j] + temp;
            }
            getline(file, temp);
        }
        i++;
    } while (i < kol_vo_film);

	cinema.films_number = i;
    //cout << filmi[0].duration;        //тест*/
   
}

bool File_O::CheckCompound()        //проверка форматирования текстового файла
{
	bool result = false;
    char* str = new char[1024];
    int i = 0;
    ifstream base(path);
    while (!base.eof())
    {
        base.getline(str, 1024, '\n');
        i++;
    }
    base.close();
    delete[] str;

    if ((i - 3) % 124 == 0)            //форматирование верно
    {
        kol_vo_film = (i - 4) / 123;
		result = true;
    }
    else               //форматирование неверно, в файле имеются ошибки
    {
        cout << "В файле имеются ошибки";
    }

	return result;
}

