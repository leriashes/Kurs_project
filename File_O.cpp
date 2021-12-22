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
            cout << "0 - ������� � ����\n\n������� ���� � ����� � ����������� � ����������: ";
            cin >> path;
        } while (path == "");

        if (path == "0\0")
        {
            return;
        }

    } while (!CheckPath());
    //_getch();
}

void File_O::New(Cinema &cinema)
{
    cinema = *new Cinema();
    cout << "������� �������� ������ ����� (��� ����������): ";
    string path;

    //�������� ��������� ����� ����� �� ������� "txt"

    if (CheckPath())   //�������� �� ������������� ������ ����� � ������
    {
        //���� � ����� ��������� ����������, ������� ����� � ������� ������ ���� ��� �������� �������
        cout << "���� � ����� ��������� ��� ����������\n1) ������� ����� ����� � ������������� (" << path + "_1.txt)" << "\n2) ������� ������� ������ ����� " << path;
        
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
            ofstream fout(path); //�������� ������� ������ ofstream ��� ������
            fout.close();   //�������� �����
        }*/
                
    }
    
    if (CheckPath() == 1)
    {
        
        //���� ������� ������, ���������� ���������� � ����������
    }
    else
    {
        //���� �� ������, ��������� �����
    }
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
        //�������� �����, ���������� ���� ������

    }
    else 
	{
        //cout << "���� ������!";
        result = true;
    }

	return result;
    /*ofstream fout(path); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ cppstudio.txt
    fout << "������ � ������� � �++"; // ������ ������ � ����
    fout.close(); // ��������� ����
    */
}



void File_O::Read(Cinema& cinema)
{
    ifstream file(path);

    int numb = 0;
    int i = 0;
    int j = 0;
    string temp;

    //���������� ���������� � ����������
    getline(file, cinema.name);    //������ �������� ����������
    getline(file, cinema.adress);    //������ ������ ����������

	//???? ������ ������ ������ ?????
    getline(file, cinema.cashiers[0]);     //������ ��� ��������
    getline(file, cinema.inn);     //������ ���
    getline(file, cinema.rnm);     //������ ���
    


    int kolvo_cashiers = 0;
    //���������� ���������� �������� �� ������ ???
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

    if ((i - 6) % 133 == 0)            //�������������� �����
    {
        kol_vo_film = (i - 6) / 133;
		result = true;

    }
	return result;
}

void File_O::Write(Cinema cinema)
{

    string path_cop = path;
    path_cop.resize(path_cop.size() - 4);
    path_cop = path_cop + "_copy.txt\0";

    //�������� ����� �������� �����
    ifstream    inFile(path);
    ofstream    outFile(path_cop);
    outFile << inFile.rdbuf();
    inFile.close();
    outFile.close();

    this->Clean();   //�������� ���� ������ �� �����

    //������ � ����
    ofstream  f;
    f.open(path);
    if (f)
    {
        f << cinema.name << endl;    //������ �������� ���������� � ����
        f << cinema.adress << endl;  //������ ������ ���������� � ����
        f << cinema.cashiers[0] << endl;    //������ ��������

        f << cinema.inn << endl;     //������ ��� ���������� � ����
        f << cinema.rnm << endl;     //������ ��� ���������� � ����

        for (int i = 0; i < cinema.films_number; i++)
        {
            f << endl;  //������ ������
            f << cinema.films[i].name << endl;   //������ �������� ������
            f << cinema.films[i].duration << endl;   //������ ������������ ������
            f << cinema.films[i].age << endl;    //������ ����������� �����������
            f << cinema.films[i].short_description << endl;  //������ ��������� ��������
            f << cinema.films[i].main_role << endl;  //������ ������� ������� ������
            f << cinema.films[i].rejisser << endl;   //������ ���������� ������
            f << endl;  //������ ������
            for (int j = 0; j < 9; j++)
            {
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
        //������� ����� �����
        remove(path_cop.c_str());
    }
    else
    {
        rename(path_cop.c_str(), path.c_str());
        cout << "�������� � ������� � ����";
    }

}

void File_O::Clean()
{
    fstream ofs;
    ofs.open(path, ios::out | ios::trunc);
    ofs.close();
}

