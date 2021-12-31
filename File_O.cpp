#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdio>
#include "File_O.h"
#include "Menu.h"
#include "windows.h"
using namespace std;


void File_O::ReadBron(Cinema& cinema) //считывание данных из файла бронирования
{
    bool result = false;
    ifstream f1;
    cinema.broni_number = 0;
    cinema.broni_zapis = 0;

    f1.open(path_bron);
    if (!(f1.is_open()))
    {
        //создать файл
        /*cout << "\nФайл не найден\n";
        _getch();
        */
        //создание файла, заполнение всех данных

    }
    else
    {
        //считывание данных о бронировании в массив или в строку

        string str;
        string temp;
        int i = 0;
        while (!f1.eof())   //узнать количество строк в файле
        {

            getline(f1, str);
            i++;
        }

        
        f1.seekg(0, std::ios::beg);     //переход в начало файла
        for (int u = 0; u < i; u++)
        {
            getline(f1, cinema.bron[u][0]);
            string rez[7];
            //разбор брони на составляющие
            string sep = "|";   // строка или символ разделитель
            size_t sep_size = sep.size();
            string original = cinema.bron[u][0];
            string tempura;
            int h = 1;
            while (true) 
            {
                tempura = original.substr(0, original.find(sep));
                if (tempura.size() != 0)   // можно добавить доп. проверку для строк из пробелов
                {
                    rez[h] = "";
                    rez[h] = tempura;
                    if (h == 6)
                    {
                        if ((rez[1] + "\0") == cinema.id_cinema)
                        {
                            for (int e = 0; e < 7; e++)
                            {
                                cinema.bron[cinema.broni_number][e] = rez[e];
                            }
                            cinema.broni_number++;
                        }
                    }
                    h++;
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
        }

        //cout << "Файл найден!";
        result = true;
    }

    return;
}


void File_O::WriteBron(Cinema cinema)
{
    string path_cop = path_bron;
    path_cop.resize(path_cop.size() - 4);
    path_cop = path_cop + "_copy.txt\0";

    //скопировать исходный файл
    std::ifstream    inFile(path_bron);
    std::ofstream    outFile(path_cop);

    
    outFile << inFile.rdbuf();
    outFile.close();
    inFile.close();
    Clean(path_bron);

    ofstream    outFile(path_cop);
    ifstream f1;
    cinema.broni_number = 0;
    cinema.broni_zapis = 0;

    f1.open(path_cop);
    string str;
    while (!f1.eof())
    {
        getline(f1, str);
        str.resize(str.size() - 5);
        if (str != cinema.id_cinema)
        {   //запись в новый файл

        }
        //обрезать номера 

    }

    
    
    

    //открыть копию файла, начать его прочитывать и копировать в файл, если номер фильма не совпадает с текущим открытым файлом

    std::ofstream f;                    //создаем поток 
    f.open(path_bron, std::ios::app);  // открываем файл для записи в конец
    for (int y = 0; y < cinema.broni_number; y++)
    {
        f << endl;
        for (int t = 1; t < 7; t++)
        {
            f << cinema.bron[y][t];
            if (t != 6)
            {
                f << "|";
            }
        }
        //f << cinema.broni_number;
    }
    //cinema.broni_number = 0;
    f.close();
}

void File_O::WriteNewBron(Cinema& cinema)
{
    std::ofstream f;                    //создаем поток 
    f.open(path_bron, std::ios::app);  // открываем файл для записи в конец
    for (int y = (cinema.broni_number - cinema.broni_zapis); y < cinema.broni_number; y++)
    {
        f << endl;
        for (int t = 1; t < 8; t++)
        {
            f << cinema.bron[y][t];
            if (t != 7)
            {
                f << "|";
            }
        }
    }
    cinema.broni_zapis = 0;
}

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

    return;
}

void File_O::New(Cinema &cinema)
{
    Menu menu;
    Cinema co;
    cinema = co;

    do
    {
        system("cls");
        cout << "Введите название нового файла (без расширения): ";
        cin >> path;
    } while (path == "");
    path += ".txt";
    string sp;
    //проверка введеного имени файла на наличие "txt"

    ifstream f1;
    f1.open(path);
    if (f1.is_open())   //проверка на существование такого файла в памяти
    {
        //файл с таким названием существует, создать копию и создать чистый файл или затереть текущий
        cout << "Файл с таким названием уже существует\n1) Создать копию файла и переименовать (" << sp + "_1.txt)" << "\n2) Удалить текущую версию файла " << sp << ".txt";
        
        menu.items_number = 2;
        menu.ChooseItem();
        if (menu.GetItem() == 1)
        {
            ifstream inFile(sp + ".txt");
            ofstream outFile(sp + "_1.txt");

            outFile << inFile.rdbuf();
            ofstream fout(path);
            fout.close();
        }
        else if (menu.GetItem() == 2)
        {
            ofstream fout(path); //создание объекта класса ofstream для записи
            fout.close();   //закрытие фалйа
        }
        f1.close();
    }
    else
    {
        system("cls");
        cout << "Файл " << path << " создан!";
        ofstream fout(path); //создание объекта класса ofstream для записи
        fout.close();   //закрытие фалйа
        _getch();
    }

    return;
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
    cinema.cashiers_number = 0;
    cinema.promo_number = 0;
    getline(file, temp);    //чтение id кинотеатра (если имеется)
    if (temp[0] == 'i' && temp[1] == 'd' && temp[2] == ':')
    {
        for (int g = 0; g < temp.size(); g++)
        {
            if (g > 3)
            {
                cinema.id_cinema = cinema.id_cinema + temp[g];
            }
        }
        getline(file, cinema.name); //чтение названия кинотеатра
    }
    else     //создание id файла
    {
        cinema.name = temp;
        string str = "";
        for (int i = 0; i < 5; ++i)
        {
            str += to_string(rand() % 10);
        }
        cinema.id_cinema = str;
    }

    //заполнение информации о кинотеатре
        
    getline(file, cinema.address);    //чтение адреса кинотеатра

	//???? читаем только одного ?????
    getline(file, cinema.cashiers[0]);     //чтения ФИО кассиров
    string sep = ", ";   // строка или символ разделитель
    size_t sep_size = sep.size();
    string original1 = cinema.cashiers[0];
    string tempura1;
    int h = 1;
    while (true) {
        tempura1 = original1.substr(0, original1.find(sep));
        if (tempura1.size() != 0)   // можно добавить доп. проверку для строк из пробелов
        {
            cinema.cashiers[h] = "";
            cinema.cashiers[h] = tempura1;
            cinema.cashiers_number++;
            h++;
        }
        if (tempura1.size() == original1.size())
        {
            break;
        }
        else
        {
            original1 = original1.substr(tempura1.size() + sep_size);
        }
    }


    getline(file, cinema.inn);     //чтение ИНН
    getline(file, cinema.rnm);     //чтение РНМ
    getline(file, cinema.promo[0][0]);     //чтение промокодов
    
    string tempura;
    string original = cinema.promo[0][0];
    
    h = 1;
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
            cinema.promo_number++;
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
    bool generate = false;
    time_t t;
    std::time(&t);

    int da = localtime(&t)->tm_mday;
    int mo = localtime(&t)->tm_mon + 1;
    int yea = localtime(&t)->tm_year + 1900;
    string doub;
    //cout << cinema.otchet_today.size();
    //_getch();
    for (i = 0; i < 10; i++)
    {
        doub = doub + cinema.otchet_today[i];
    }
    if (doub == (to_string(da) + '.' + to_string(mo) + '.' + to_string(yea)))
    {
        generate = false;
        cinema.otchet_today.erase(0, 12);
    }
    else
    {
        generate = true;
        cinema.otchet_today = "0";
    }
    i = 0;
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
            if (cinema.films[i].rand[j][0] == '0' && generate == true)
            {
                cinema.films[i].mesta[j] = cinema.NewHall();
                Sleep(100);
            }
        }
        i++;
    } while (i < kol_vo_film);
	cinema.films_number = i;
    file.close();
    Write(cinema);
 
    return;
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

    if (((i - 10) % 134 == 0) || ((i - 9) % 134 == 0))            //форматирование верно
    {
        kol_vo_film = (i - 10) / 134;
		result = true;
    }
    base.close();
	return result;
}

void File_O::Write(Cinema cinema)
{

    time_t t;
    std::time(&t);

    int da = localtime(&t)->tm_mday;
    int mo = localtime(&t)->tm_mon + 1;
    int yea = localtime(&t)->tm_year + 1900;

    string path_cop = path;
    path_cop.resize(path_cop.size() - 4);
    path_cop = path_cop + "_copy.txt\0";

    //создание копии текущего файла
    ifstream    inFile(path);
    ofstream    outFile(path_cop);
    outFile << inFile.rdbuf();
    inFile.close();
    outFile.close();

    Clean(path);   //удаление всех данных из файла

    //запись в файл
    ofstream  f;
    f.open(path);
    if (f)
    {
        f << "id: " << cinema.id_cinema << endl;      //запись id файла
        f << cinema.name << endl;    //запись названия кинотеатра в файл
        f << cinema.address << endl;  //запись адреса кинотеатра в файл
        //f << cinema.cashiers[0] << endl;    //запись кассиров

        for (int p = 1; p <= cinema.cashiers_number; p++)
        {
            f << cinema.cashiers[p];
            if (p != cinema.cashiers_number)
            {
                f << ", ";
            }
        }
        f << endl;
        f << cinema.inn << endl;     //запись ИНН кинотеатра в файл
        f << cinema.rnm << endl;     //запись РНМ кинотеатра в файл

        //f << cinema.promo[0][0] << endl;     //запись промокодов
        
        for (int o = 1; o <= cinema.promo_number; o++)
        {
            f << cinema.promo[o][0] << " " << cinema.promo[o][1];
            if (o != cinema.promo_number)
            {
                f << ", ";
            }
        }
        f << endl;
        f << cinema.otchet_vsego << endl;     //запись выручки за весь период
        /// <summary>
        /// ПЕРЕДЕЛАТЬ ЗАПИСЬ ЕЖЕДНЕВНОГО ОТЧЕТА
        /// </summary>
        /// <param name="cinema"></param>
        f << to_string(da) << '.' << to_string(mo) << '.' << to_string(yea) << ": " << cinema.otchet_today << endl;     //запись выручки за сегодняшний день

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

    return;
}

void File_O::Clean(string pat)
{
    fstream ofs;
    ofs.open(pat, ios::out | ios::trunc);
    ofs.close();

    return;
}

