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


void File_O::ReadBron(Cinema& cinema) //���������� ������ �� ����� ������������
{
    bool result = false;
    ifstream f1;
    cinema.broni_number = 0;
    cinema.broni_zapis = 0;
    f1.open(path_bron);
    if (f1.is_open())
    {
        int i = 0;
        string str;
        string temp;
        while (!f1.eof())   //������ ���������� ����� � �����
        {
            getline(f1, str);
            i++;
        }

        
        f1.seekg(0, std::ios::beg);     //������� � ������ �����
        for (int u = 0; u < i; u++)
        {
            getline(f1, cinema.bron[u][0]);
            string rez[8];
            string sep = "|";   // ������ ��� ������ �����������
            size_t sep_size = sep.size();
            string original = cinema.bron[u][0];
            string tempura;
            int h = 1;
            while (true) 
            {
                tempura = original.substr(0, original.find(sep));
                if (tempura.size() != 0)   // ����� �������� ���. �������� ��� ����� �� ��������
                {
                    rez[h] = "";
                    rez[h] = tempura;
                    if (h == 7)
                    {
                        if ((rez[1] + "\0") == cinema.id_cinema)
                        {
                            for (int e = 1; e < 8; e++)
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
        f1.close();
        
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

    //����������� �������� ����
    std::ifstream    inFile(path_bron);
    std::ofstream    outFile(path_cop);

    
    outFile << inFile.rdbuf();
    outFile.close();
    inFile.close();
    remove(path_bron.c_str());
    

    ofstream outFiles(path_bron);
    ifstream f1;
    int num = 0;
    f1.open(path_cop);
    string str, write;
    
    while (!f1.eof())
    {
        getline(f1, str);
        if (str.size() > 5)
        {
            write = str;
            str.erase(5, str.size());
            if (str != cinema.id_cinema)
            {   
                string rez[8];
                string sep = "|";   // ������ ��� ������ �����������
                size_t sep_size = sep.size();
                string original = write;
                string tempura;
                int h = 1;
                while (true)
                {
                    tempura = original.substr(0, original.find(sep));
                    if (tempura.size() != 0)   // ����� �������� ���. �������� ��� ����� �� ��������
                    {
                        rez[h] = "";
                        rez[h] = tempura;
                        if (h == 7)
                        {
                            if (rez[6] == Time::RetDate(0, 1) || rez[6] == Time::RetDate(1, 1) || rez[6] == Time::RetDate(2, 1))
                            {
                                if (num != 0)
                                {
                                    outFiles << endl;
                                }
                                outFiles << write;
                                num++;
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
    std::ofstream f;                    //������� ����� 
    f.open(path_bron, std::ios::app);  // ��������� ���� ��� ������ � �����

    fstream file_s(path_bron);
    int size = 0;
    file_s.seekg(0, std::ios::end);
    size = file_s.tellg();
    if (size != 0)
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
            cout << "0 - ������� � ����\n\n������� ���� � ����� � ����������� � ����������: ";
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
        cout << "������� �������� ������ ����� (��� ����������): ";
        getline(cin, path);
    } while (path == "");
    path += ".txt";
    string sp;

    ifstream f1;
    f1.open(path);
    if (f1.is_open())   //�������� �� ������������� ������ ����� � ������
    {
        cout << "���� � ����� ��������� ��� ����������\n1) ������� ����� ����� � ������������� (" << sp + "_1.txt)" << "\n2) ������� ������� ������ ����� " << sp << ".txt";
        
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
            ofstream fout(path); //�������� ������� ������ ofstream ��� ������
            fout.close();   //�������� �����
        }
        f1.close();
    }
    else
    {
        system("cls");
        ofstream fout(path); //�������� ������� ������ ofstream ��� ������
        fout.close();   //�������� �����
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
        cout << "\n���� �� ������\n";
		_getch();

    }
    else 
	{
        f1.close();
        result = true;
    }

	return result;
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
    getline(file, temp);    //������ id ���������� (���� �������)
    if (temp[0] == 'i' && temp[1] == 'd' && temp[2] == ':')
    {
        for (int g = 0; g < temp.size(); g++)
        {
            if (g > 3)
            {
                cinema.id_cinema = cinema.id_cinema + temp[g];
            }
        }
        getline(file, cinema.name); //������ �������� ����������
    }
    else     //�������� id �����
    {
        cinema.id_cinema = cinema.NewID();
        cinema.name = temp;
    }
    getline(file, cinema.address);    //������ ������ ����������
    getline(file, cinema.cashiers[0]);     //������ ��� ��������
    string sep = ", ";   // ������ ��� ������ �����������
    size_t sep_size = sep.size();
    string original1 = cinema.cashiers[0];
    string tempura1;
    int h = 1;
    while (true) {
        tempura1 = original1.substr(0, original1.find(sep));
        if (tempura1.size() != 0)   
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
    
    getline(file, cinema.inn);     //������ ���
    getline(file, cinema.rnm);     //������ ���
    getline(file, cinema.promo[0][0]);     //������ ����������
    
    string tempura;
    string original = cinema.promo[0][0];
    
    h = 1;
    while (true) {
        tempura = original.substr(0, original.find(sep));
        if (tempura.size() != 0)   // ����� �������� ���. �������� ��� ����� �� ��������
        {
            cinema.promo[h][1] = "";
            if (tempura[tempura.size() - 2] == ' ')
            {
                cinema.promo[h][1] = tempura[tempura.size() - 1];       //������� ������
                cinema.promo[h][0] = tempura;   //��� ������, ���������� �������� �������
                cinema.promo[h][0].resize(cinema.promo[h][0].size() - 2);
            }
            else
            {
                cinema.promo[h][1] = cinema.promo[h][1] + tempura[tempura.size() - 2] + tempura[tempura.size() - 1];       //������� ������
                cinema.promo[h][0] = tempura;   //��� ������, ���������� �������� �������
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



    getline(file, cinema.otchet_vsego);     //������ ������� �� ������
    getline(file, cinema.otchet_today);     //������ ������� �� ����������� ����
    bool generate = false;
    string doub;
    for (i = 0; i < 10; i++)
    {
        doub = doub + cinema.otchet_today[i];
    }
    string today_d;
    today_d = Time::RetDate(0, 1);
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

    i = 0;
    int sdvig = 0;
    //���������� ���������� � �������
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
            if (j % 3 == 0)
            {
                getline(file, cinema.films[i].date[j / 3]);
            }
            
            if (j == 3)
            {
                if (old_date == Time::RetDate(0, 1))
                {
                    sdvig = 2;
                }
                else if (old_date == Time::RetDate(1, 1))
                {
                    sdvig = 1;
                }
                else if (old_date == Time::RetDate(2, 1))
                {
                    sdvig = 0;
                }
                else
                {
                    sdvig = 3;
                }
            }
            
            getline(file, cinema.films[i].price[j]);
            getline(file, cinema.films[i].time[j]);
            getline(file, cinema.films[i].rand[j]);

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
                for (int l = (3 - sdvig) * 3; l < 9; l++)
                {
                    cinema.films[i].mesta[l] = cinema.NewHall();

                }
            }
        }
        i++;
    } while (i < kol_vo_film);
	cinema.films_number = i;
    file.close();
    Write(cinema);
 
    return;
}

bool File_O::CheckCompound()        //�������� �������������� ���������� �����
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

    if (((i - 11) % 137 == 0) || ((i - 10) % 137 == 0))            //�������������� �����
    {
        kol_vo_film = (i - 11) / 137;
		result = true;
    }
	return result;
}

void File_O::Write(Cinema& cinema)
{
    string path_cop = path;
    path_cop.resize(path_cop.size() - 4);
    path_cop = path_cop + "_copy.txt\0";
    ifstream    inFile(path);
    ofstream    outFile(path_cop);
    outFile << inFile.rdbuf();
    inFile.close();
    outFile.close();

    Clean(path);   //�������� ���� ������ �� �����

    //������ � ����
    ofstream  f;
    f.open(path);
    if (f)
    {
        f << "id: " << cinema.id_cinema << endl;      //������ id �����
        f << cinema.name << endl;    //������ �������� ���������� � ����
        f << cinema.address << endl;  //������ ������ ���������� � ����

        for (int p = 1; p <= cinema.cashiers_number; p++)
        {
            f << cinema.cashiers[p];
            if (p != cinema.cashiers_number)
            {
                f << ", ";
            }
        }
        f << endl;
        f << cinema.inn << endl;     //������ ��� ���������� � ����
        f << cinema.rnm << endl;     //������ ��� ���������� � ����
        
        for (int o = 1; o <= cinema.promo_number; o++)
        {
            f << cinema.promo[o][0] << " " << cinema.promo[o][1];
            if (o != cinema.promo_number)
            {
                f << ", ";
            }
        }
        f << endl;
        f << cinema.otchet_vsego << endl;     //������ ������� �� ���� ������
        f << Time::RetDate(0, 1);
        f << ": " << cinema.otchet_today << endl;     //������ ������� �� ����������� ����
        f << Time::RetDate(2, 1) << endl;       //������ ������� ���� (����������� ������)

        for (int i = 0; i < cinema.films_number; i++)
        {
            f << endl;  //������ ������
            f << cinema.films[i].name << endl;   //������ �������� ������
            f << cinema.films[i].duration << endl;   //������ ������������ ������
            f << cinema.films[i].age << endl;    //������ ����������� �����������
            f << cinema.films[i].short_description << endl;  //������ ��������� ��������
            f << cinema.films[i].main_role << endl;  //������ ������� ������� ������
            f << cinema.films[i].rejisser << endl;   //������ ���������� ������
            f << cinema.films[i].number_zal << endl;   //������ ����� ����
            f << endl;  //������ ������

            for (int j = 0; j < 9; j++)
            {
                if (j % 3 == 0)
                {
                    f << Time::RetDate((j / 3), 1) << endl;
                }

                f << cinema.films[i].price[j] << endl;   //������ ��������� ������
                f << cinema.films[i].time[j] << endl;   //������ ������� ������
                f << cinema.films[i].rand[j] << endl;   //������ ����� (������) ���������

                for (int o = 0; o < 10; o++)
                {
                    for (int y = 0; y < 10; y++)
                    {
                        f << cinema.films[i].mesta[j][y + o * 10];
                    }
                    f << endl;  //������ ������
                }
                if (j != 8)
                {
                    f << endl;  //������ ������
                }
            }
        }
        f.close();
        const char* c = path_cop.c_str();
        remove(path_cop.c_str());
    }
    else
    {
        rename(path_cop.c_str(), path.c_str());
        cout << "�������� � ������� � ����";
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

