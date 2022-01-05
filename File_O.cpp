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
        int i = 0;
        string str;
        string temp;
        while (!f1.eof())   //узнать количество строк в файле
        {
            getline(f1, str);
            i++;
        }

        bool reads;
        f1.seekg(0, std::ios::beg);     //переход в начало файла
        for (int u = 0; u < i; u++)
        {
            getline(f1, cinema.bron[u][0]);
            string rez[8];
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
                    if (h == 7)
                    {
                        if ((rez[1] + "\0") == cinema.id_cinema)
                        {
                            if (rez[6] == Time::RetDate(0, 1))
                            {
                                if (cinema.DeConvert_Time(rez[5]) + 30 > cinema.DeConvert_Time(Time::RetTime(0)))
                                {
                                    reads = true;
                                
                                }
                                else
                                {
                                    reads = false;
                                }
                            }
                            else
                            {
                                reads = true;
                            }
                            if (reads == true)
                            {
                                for (int e = 1; e < 8; e++)
                                {
                                    cinema.bron[cinema.broni_number][e] = rez[e];
                                }
                                cinema.broni_number++;
                            }
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
        f1.close();
        
        //cout << "Файл найден!";
        WriteBron(cinema);
        result = true;
    }

    return;
}


void File_O::WriteBron(Cinema& cinema)
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
    //Clean(path_bron);
    //std::ofstream fileStrm(path_bron, std::ios::out);

    /*fstream file;
    file.open(path_bron, ios::out);
    file << "";
    file.close();
    */

    if (remove(path_bron.c_str()) != 0)             // удаление файла file.txt
    {   
        //std::cout << "Ошибка удаления файла\n";
    }
    else
    {
        //std::cout << "Файл успешно удалён\n";
    }
    //_getch();

    ofstream outFiles(path_bron);
    ifstream f1;
    int num = 0;
    f1.open(path_cop);
    string str, write;
    bool writes;
    while (!f1.eof())
    {
        getline(f1, str);
        if (str.size() > 5)
        {
            write = str;
            //str.resize(str.size() - 5);
            str.erase(5, str.size());
            /*
            cout << str;
            _getch();
            */
            if (str != cinema.id_cinema)
            {   
                //проверка на дату сеанса
                string rez[8];
                //разбор брони на составляющие
                string sep = "|";   // строка или символ разделитель
                size_t sep_size = sep.size();
                string original = write;
                string tempura;
                int h = 1;
                while (true)
                {
                    tempura = original.substr(0, original.find(sep));
                    if (tempura.size() != 0)   // можно добавить доп. проверку для строк из пробелов
                    {
                        rez[h] = "";
                        rez[h] = tempura;
                        if (h == 7)
                        {
                            if (rez[6] == Time::RetDate(0, 1) || rez[6] == Time::RetDate(1, 1) || rez[6] == Time::RetDate(2, 1))
                            {
                                if (rez[6] == Time::RetDate(0, 1))
                                {
                                    if (cinema.DeConvert_Time(rez[5]) + 30 > cinema.DeConvert_Time(Time::RetTime(0)))       //проверка для 30-ти минутного аннулирования брони
                                    {

                                        cout << cinema.DeConvert_Time(rez[5]);
                                        cout << "\n\n";
                                        cout << cinema.DeConvert_Time(Time::RetTime(0));
                                        _getch();
                                        writes = true;
                                    }
                                    else
                                    {
                                        writes = false;
                                    }
                                }
                                else
                                {
                                    writes = true;
                                }
                                if (writes == true)
                                {
                                    //запись в новый файл
                                    if (num != 0)
                                    {
                                        outFiles << endl;
                                    }
                                    outFiles << write;
                                    num++;
                                }
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
        }
    }
    for (int d = 0; d < cinema.broni_number; d++)
    {
        if (cinema.bron[d][6] == Time::RetDate(0, 1) || cinema.bron[d][6] == Time::RetDate(1, 1) || cinema.bron[d][6] == Time::RetDate(2, 1))
        {
        }
        else
        {
            for (int h = 1; h < 8; h++)
            {
                cinema.bron[d][h] = cinema.bron[d + 1][h];
            }
            cinema.broni_number = cinema.broni_number - 1;
        }
    }

    if (cinema.broni_number != 0 && num != 0 && (cinema.broni_number - cinema.broni_number != 0))
    {
        if (num != 0)
        {
            outFiles << endl;
        }
    }
    outFiles.close();
    f1.close();
    cinema.broni_zapis = cinema.broni_number;
    WriteNewBron(cinema);
}

void File_O::WriteNewBron(Cinema& cinema)
{
    std::ofstream f;                    //создаем поток 
    f.open(path_bron, std::ios::app);  // открываем файл для записи в конец

    fstream file_s(path_bron);
    int size = 0;
    file_s.seekg(0, std::ios::end);
    size = file_s.tellg();
    /*
    cout << "SIZE:  " << size;
    _getch();
    */

    bool writes;
    if (size != 0 && cinema.broni_number != 0)
    {
        f << endl;
    }
    for (int y = (cinema.broni_number - cinema.broni_zapis); y < cinema.broni_number; y++)
    {
        
        for (int t = 1; t < 8; t++)
        {
            f << cinema.bron[y][t];
            if (t != 7)
            {
                f << "|";
            }
            //f << "    " << cinema.broni_number;
        }
        if (y < cinema.broni_number - 1)
        {
            f << endl;
        }
    }
    f.close();
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
            getline(cin, path);
            //cin >> path;
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
        getline(cin, path);
        //cin >> path;
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
        //cout << "Файл " << path << " создан!";
        ofstream fout(path); //создание объекта класса ofstream для записи
        fout.close();   //закрытие фалйа
        //_getch();
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
        f1.close();
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
    getline(file, temp);    //чтение id кинотеатра
    cinema.id_cinema = "";
    for (int g = 0; g < temp.size(); g++)
    {
        if (g > 3)
        {
            cinema.id_cinema = cinema.id_cinema + temp[g];
        }
    }
    getline(file, cinema.name); //чтение названия кинотеатра

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
    /*
    time_t t;
    std::time(&t);

    int da = localtime(&t)->tm_mday;
    int mo = localtime(&t)->tm_mon + 1;
    int yea = localtime(&t)->tm_year + 1900;
    */
    string doub;
    //cout << cinema.otchet_today.size();
    //_getch();
    for (i = 0; i < 10; i++)
    {
        doub = doub + cinema.otchet_today[i];
    }
    string today_d;
    today_d = Time::RetDate(0, 1);
    /*if (to_string(da).size() == 1)
    {
        today_d = "0";
    }
    today_d = today_d + to_string(da) + ".";
    if (to_string(mo).size() == 1)
    {
        today_d = today_d + "0";
    }
    today_d = today_d + to_string(mo) + "." + to_string(yea);
    */
    if (doub == today_d)
    {
        generate = false;
        cinema.otchet_today.erase(0, 12);
    }
    else
    {
        generate = true;
        cinema.otchet_today = "0";
    }
    string old_date;
    getline(file, old_date);

    //i = 0;
    int sdvig = 0;
    //заполнение информации о фильмах
    for (i = 0; i < kol_vo_film; i++)
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
            if (j % 3 == 0)
            {
                getline(file, cinema.films[i].date[j / 3]);
            }
            
            if (j == 3)
            {
                if (old_date == Time::RetDate(0, 1))
                {
                    sdvig = 2;
                    //cout << "2";
                }
                else if (old_date == Time::RetDate(1, 1))
                {
                    sdvig = 1;
                    //cout << "1";
                }
                else if (old_date == Time::RetDate(2, 1))
                {
                    sdvig = 0;
                    //cout << "0";
                }
                else
                {
                    sdvig = 3;
                    //cout << "3";
                    //cout << Time::RetDate(2, 1);
                }
            }
            
            getline(file, cinema.films[i].price[j]);
            getline(file, cinema.films[i].time[j]);
           
            //string mesta_sdvig;

            for (int k = 0; k < 10; k++)
            {
                getline(file, temp);
                cinema.films[i].mesta[j] = cinema.films[i].mesta[j] + temp;
            }
            if (j == 8)
            {
                int o;
                int d;
                for (d = 0, o = sdvig * 3; d < (3 - sdvig) * 3; d++, o++)
                {
                    cinema.films[i].mesta[d] = cinema.films[i].mesta[o];
                }


                /*if (sdvig == 1)
                {
                    //cout << cinema.films[i].mesta[0];
                    //cout << cinema.films[i].mesta[0];
                    //_getch();

                    cinema.films[i].mesta[0] = cinema.films[i].mesta[3];
                    cinema.films[i].mesta[1] = cinema.films[i].mesta[4];
                    cinema.films[i].mesta[2] = cinema.films[i].mesta[5];

                    cinema.films[i].mesta[3] = cinema.films[i].mesta[6];
                    cinema.films[i].mesta[4] = cinema.films[i].mesta[7];
                    cinema.films[i].mesta[5] = cinema.films[i].mesta[8];

                    /*
                    for (int k = 6; k < 9; k++)
                    {
                        cinema.films[i].mesta[k] = cinema.NewHall();
                    }
                    */
                    //}
                    /*
                    else if (sdvig == 2)
                    {
                        cinema.films[i].mesta[0] = cinema.films[i].mesta[6];
                        cinema.films[i].mesta[1] = cinema.films[i].mesta[7];
                        cinema.films[i].mesta[2] = cinema.films[i].mesta[8];
                        /*
                        for (int k = 3; k < 9; k++)
                        {
                            cinema.films[i].mesta[k] = cinema.NewHall();
                        }
                        */
                        //}

                        /*else if (sdvig == 3)
                        {
                            for (int k = 0; k < 9; k++)
                            {
                                //cout << cinema.films[i].mesta[k];

                                //cout << cinema.films[i].mesta[k];
                            }
                        }
                        */
                for (int l = (3 - sdvig) * 3; l < 9; l++)
                {
                    cinema.films[i].mesta[l] = cinema.NewHall();

                }
            }
        }
        //i++;
    }
    //} while (i < kol_vo_film);
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

    if ((i - 11) % 128 == 0)            //форматирование верно
    {
        kol_vo_film = (i - 11) / 128;
		result = true;
    }
	return result;
}

void File_O::Write(Cinema& cinema)
{
    /*
    time_t t;
    std::time(&t);

    int da = localtime(&t)->tm_mday;
    int mo = localtime(&t)->tm_mon + 1;
    int yea = localtime(&t)->tm_year + 1900;
    */
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
        f << Time::RetDate(0, 1);
        /*
        if (to_string(da).size() == 1)
        {
            f << "0" ;
        }
        f << to_string(da) << '.';
        if (to_string(mo).size() == 1)
        {
            f << "0";
        }
        f << to_string(mo) << '.' << to_string(yea) << ": " << cinema.otchet_today << endl;
        */
        f << ": " << cinema.otchet_today << endl;     //запись выручки за сегодняшний день
        f << Time::RetDate(2, 1) << endl;       //запись крайней даты (техническая запись)

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
                if (j % 3 == 0)
                {
                    f << Time::RetDate((j / 3), 1) << endl;
                    //cinema.films[i].date[j / 3] << endl;
                }

                f << cinema.films[i].price[j] << endl;   //запись стоиомсти билета
                f << cinema.films[i].time[j] << endl;   //запись времени сеанса

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

