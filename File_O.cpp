#define _CRT_SECURE_NO_WARNINGS
#include "File_O.h";
#include <conio.h>;
#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <cstring>
#include <cstdio>


void File_O::File_input()
{
    do
    {
        do
        {
            cout << "0 - возврат в меню\n\nВведите путь к файлу с информацией о кинотеатре: ";

            cin >> path;
        } while (path == "");
        if (path == "0")
        {
            return;
        }
    } while (File_check() != 1);
    _getch();
}

/*
void File_O::file_new()
{
    cout << "Введите название нового файла (без расширения): ";
    string path;


    //проверка введеного имени файла на наличие "txt"

    if (file_check(path) == 1)   //проверка на существование такого файла в памяти
    {
        //файл с таким названием существует, создать копию и создать чистый файл или затереть текущий
        cout << "Файл с таким названием уже существует\n1) Создать копию файла и переименовать (" << path + "_1.txt)" << "\n2) Удалить текущую версию файла " << path;
        item_num = 2;
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
        }

    }

    if (file_check(path) == 1)
    {
        //файл успешно создан, заполнение информации о кинотеатре
    }
    else
    {
        //файл не создан, изменение файла
    }
}
*/

int File_O::File_check()
{
    ifstream f1;

    f1.open(path);
    if (!(f1.is_open())) {
        //cout << "Файл не найден"; //тест
        return 2;
        //создание файла, заполнение всех данных

    }
    else {
        //cout << "Файл найден!"; //тест
        return 1;
    }

    /*ofstream fout(path); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
    fout << "Работа с файлами в С++"; // запись строки в файл
    fout.close(); // закрываем файл
    */
}



void File_O::File_read(Kinoteatr *kinoteatr)
{
    ifstream file(path);

    int numb = 0;
    int i = 0;
    int j = 0;
    string temp;

    //заполнение информации о кинотеатре
    getline(file, (*kinoteatr).name);    //чтение названия кинотеатра
    getline(file, (*kinoteatr).adress);    //чтение адреса кинотеатра
    getline(file, (*kinoteatr).kassirs[0]);     //чтения ФИО кассиров


    //разложение количества кассиров на массив ???


    //заполнение информации о фильмах
    do
    {
        getline(file, temp);
        getline(file, (*kinoteatr).filmi[i].name);
        getline(file, (*kinoteatr).filmi[i].duration);
        getline(file, (*kinoteatr).filmi[i].age);
        getline(file, (*kinoteatr).filmi[i].short_description);
        getline(file, (*kinoteatr).filmi[i].main_role);
        getline(file, (*kinoteatr).filmi[i].rejisser);
        
        

        for (j = 0; j < 9; j++)
        {
            getline(file, temp);
            getline(file, ((*kinoteatr).filmi[i].price[j]));
            getline(file, ((*kinoteatr).filmi[i].time[j]));
            getline(file, (*kinoteatr).filmi[i].rand[j]);
            //(*kinoteatr).filmi[i].rand[j] = (*kinoteatr).filmi[i].rand[j][0] + "\0";
            
            for (int k = 0; k < 10; k++)
            {
                getline(file, temp);
                (*kinoteatr).filmi[i].mesta[j] = (*kinoteatr).filmi[i].mesta[j] + temp;
            }
            if (kinoteatr->filmi[i].rand[j][0] == '0')
            {
                (*kinoteatr).filmi[i].mesta[j] = kinoteatr->New_zal(i, j);
            }
            //_getch();   //тест
        }
        //getline(file, temp);
        i++;
    } while (i < (*kinoteatr).kol_vo_filmov);

    //cout << filmi[0].duration;        //тест

}

int File_O::File_check_compound(int* kol_vo)        //проверка форматирования текстового файла
{
    char* str = new char[1024];
    int i = 0;
    ifstream base(path);
    while (!base.eof())
    {
        base.getline(str, 1024, '\n');
        i++;
    }
    base.close();
    delete str;
    if ((i - 3) % 133 == 0)            //форматирование верно
    {
        *kol_vo = (i - 3) / 133;
        return 1;

    }
    else               //форматирование неверно, в файле имеются ошибки
    {
        cout << "В файле имеются ошибки";
        return 2;
    }
}

