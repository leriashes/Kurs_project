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
            cout << "\n0 - ������� � ����\n\n������� ���� � ����� � ����������� � ����������: ";

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
    if (!(f1.is_open())) {
        cout << "���� �� ������";
        //�������� �����, ���������� ���� ������

    }
    else {
        cout << "���� ������!";
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


    //���������� ���������� �������� �� ������ ???

    getline(file, temp);

    //���������� ���������� � �������
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
    //cout << filmi[0].duration;        //����*/
   
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

    if ((i - 3) % 124 == 0)            //�������������� �����
    {
        kol_vo_film = (i - 4) / 123;
		result = true;
    }
    else               //�������������� �������, � ����� ������� ������
    {
        cout << "� ����� ������� ������";
    }

	return result;
}

