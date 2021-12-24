#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>;
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "File_O.h";
#include "windows.h"
using namespace std;


void File_O::InputPath()
{
    do
    {
        do
        {
			system("cls");
            cout << "0 - возврат в меню\n\nВведите путь к файлу с информацией о кинотеатре: ";
            cin >> path;
        } while (path == "");

        if (path == "0")
        {
            return;
        }

    } while (!CheckPath());
    //_getch();
}

void File_O::New(Cinema &cinema)
{
    cinema = *new Cinema();
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
    if (!(f1.is_open())) 
	{
        cout << "\nФайл не найден\n";
		_getch();
        //создание файла, заполнение всех данных

    }
    else 
	{
        //cout << "Файл найден!";
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
    getline(file, cinema.inn);     //чтение ИНН
    getline(file, cinema.rnm);     //чтение РНМ
    getline(file, cinema.promo[0][0]);     //чтение промокодов
    /*
    int kol_vo_promo = 0;
    int t = 1;
    int h = 0;
    for (int o = 0; o < (cinema.promo[0][0]).size(); o++)
    {
        if (cinema.promo[0][0][o] == ',')
        {
            kol_vo_promo++;
            t++;
            h = 0;
        }
        else
        {
            cinema.promo[t][0][h] += cinema.promo[0][0][o];
            h++;
        }
    }
    */

    string sep = ", ";   // строка или символ разделитель
    size_t sep_size = sep.size();
    string tempura;
    string original = cinema.promo[0][0];
    
    int h = 1;
    while (true) {
        tempura = original.substr(0, original.find(sep));
        if (tempura.size() != 0)   // можно добавить доп. проверку для строк из пробелов
        {
            cinema.promo[h][1] = "";
            if (tempura[tempura.size() - 2] == ' ')
            {
                cinema.promo[h][1] = tempura[tempura.size() - 1];       //процент скидки
                cinema.promo[h][0] = tempura;   //вся строка, необходимо обрезать процент
                cinema.promo[h][0].resize(cinema.promo[h][0].size() - 2);
            }
            else
            {
                cinema.promo[h][1] = cinema.promo[h][1] + tempura[tempura.size() - 2] + tempura[tempura.size() - 1];       //процент скидки
                cinema.promo[h][0] = tempura;   //вся строка, необходимо обрезать процент
                cinema.promo[h][0].resize(cinema.promo[h][0].size() - 3);
            }
            h++;
            cinema.promo_numbers++;
        }
        if (tempura.size() == original.size())
        {
            break;
        }
        else 
        {
            original = original.substr(tempura.size() + sep_size);
        }
    }



    getline(file, cinema.otchet_vsego);     //чтение выручки за период
    getline(file, cinema.otchet_today);     //чтение выручки за сегодняшний день


    int kolvo_cashiers = 0;
    //разложение количества кассиров на массив ???
    for (int y = 0; y < cinema.cashiers[0].length(); y++)
    {
        if (cinema.cashiers[0][y] == ',')
        {
            kolvo_cashiers++;
        }
    }
    int u = 0;
    int tre;
    for (int y = 1; y < kolvo_cashiers; y++)
    {
        for (; u < cinema.cashiers[0].length(); u++)
        {
            if (cinema.cashiers[0][u] != ',')
            {
                cinema.cashiers[y] = cinema.cashiers[y] + cinema.cashiers[0][u];
            }
            else
            {
                tre = u;
                u = 500;
            }
        }
        u = tre;
    }


    //заполнение информации о фильмах
    do
    {
        getline(file, temp);
        getline(file, cinema.films[i].name);
        getline(file, cinema.films[i].duration);
        getline(file, cinema.films[i].age);
        getline(file, cinema.films[i].short_description);
        getline(file, cinema.films[i].main_role);
        getline(file, cinema.films[i].rejisser);
        getline(file, cinema.films[i].number_zal);

        for (j = 0; j < 9; j++)
        {
            getline(file, temp);
            getline(file, cinema.films[i].price[j]);
            getline(file, cinema.films[i].time[j]);
            getline(file, cinema.films[i].rand[j]);
           
            for (int k = 0; k < 10; k++)
            {
                getline(file, temp);
                cinema.films[i].mesta[j] = cinema.films[i].mesta[j] + temp;
            }
            if (cinema.films[i].rand[j][0] == '0')
            {
                cinema.films[i].mesta[j] = cinema.NewHall();
                Sleep(100);
            }
        }
        i++;
    } while (i < kol_vo_film);
	cinema.films_number = i;

    Write(cinema);
 
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

    if ((i - 9) % 134 == 0)            //форматирование верно
    {
        kol_vo_film = (i - 9) / 134;
		result = true;

    }
	return result;
}

void File_O::Write(Cinema cinema)
{

    string path_cop = path;
    path_cop.resize(path_cop.size() - 4);
    path_cop = path_cop + "_copy.txt\0";

    //создание копии текущего файла
    ifstream    inFile(path);
    ofstream    outFile(path_cop);
    outFile << inFile.rdbuf();
    inFile.close();
    outFile.close();

    this->Clean();   //удаление всех данных из файла

    //запись в файл
    ofstream  f;
    f.open(path);
    if (f)
    {
        f << cinema.name << endl;    //запись названия кинотеатра в файл
        f << cinema.adress << endl;  //запись адреса кинотеатра в файл
        f << cinema.cashiers[0] << endl;    //запись кассиров

        f << cinema.inn << endl;     //запись ИНН кинотеатра в файл
        f << cinema.rnm << endl;     //запись РНМ кинотеатра в файл

        //f << cinema.promo[0][0] << endl;     //запись промокодов
        
        for (int o = 1; o <= cinema.promo_numbers; o++)
        {
            f << cinema.promo[o][0] << " " << cinema.promo[o][1];
            if (o != cinema.promo_numbers)
            {
                f << ", ";
            }
        }
        f << endl;
        f << cinema.otchet_vsego << endl;     //запись выручки за весь период
        f << cinema.otchet_today << endl;     //запись выручки за сегодняшний день

        for (int i = 0; i < cinema.films_number; i++)
        {
            f << endl;  //пустая строка
            f << cinema.films[i].name << endl;   //запись названия фильма
            f << cinema.films[i].duration << endl;   //запись длительность фильма
            f << cinema.films[i].age << endl;    //запись возрастного ограничения
            f << cinema.films[i].short_description << endl;  //запись короткого описания
            f << cinema.films[i].main_role << endl;  //запись главных актеров фильма
            f << cinema.films[i].rejisser << endl;   //запись режиссеров фильма
            f << cinema.films[i].number_zal << endl;   //запись номер зала
            f << endl;  //пустая строка

            for (int j = 0; j < 9; j++)
            {
                f << cinema.films[i].price[j] << endl;   //запись стоиомсти билета
                f << cinema.films[i].time[j] << endl;   //запись времени сеанса
                f << cinema.films[i].rand[j] << endl;   //запись точки (флажка) генерации

                for (int o = 0; o < 10; o++)
                {
                    for (int y = 0; y < 10; y++)
                    {
                        f << cinema.films[i].mesta[j][y + o * 10];
                    }
                    f << endl;  //пустая строка
                }
                if (j != 8)
                {
                    f << endl;  //пустая строка
                }
            }
        }
        f.close();
        const char* c = path_cop.c_str();
        //удалить копию файла
        remove(path_cop.c_str());
    }
    else
    {
        rename(path_cop.c_str(), path.c_str());
        cout << "Проблемы с записью в файл";
    }

}

void File_O::Clean()
{
    fstream ofs;
    ofs.open(path, ios::out | ios::trunc);
    ofs.close();
}

