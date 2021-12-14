#define _CRT_SECURE_NO_WARNINGS
#include "File_O.h";
#include <conio.h>;
#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <cstring>
#include <cstdio>


void File_O::file_input()
{
    do
    {
        do
        {
            cout << "0 - ������� � ����\n\n������� ���� � ����� � ����������� � ����������: ";

            cin >> path;
        } while (path == "");
        if (path == "0")
        {
            return;
        }
    } while (file_check(path) != 1);
    _getch();
}

void File_O::file_new()
{
    cout << "������� �������� ������ ����� (��� ����������): ";
    string path;


    //�������� ��������� ����� ����� �� ������� "txt"

    if (file_check(path) == 1)   //�������� �� ������������� ������ ����� � ������
    {
        //���� � ����� ��������� ����������, ������� ����� � ������� ������ ���� ��� �������� �������
        cout << "���� � ����� ��������� ��� ����������\n1) ������� ����� ����� � ������������� (" << path + "_1.txt)" << "\n2) ������� ������� ������ ����� " << path;
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
            ofstream fout(path); //�������� ������� ������ ofstream ��� ������
            fout.close();   //�������� �����
        }
                
    }
    
    if (file_check(path) == 1)
    {
        //���� ������� ������, ���������� ���������� � ����������
    }
    else
    {
        //���� �� ������, ��������� �����
    }

}

int File_O::file_check(string path)
{
    ifstream f1;

    f1.open(path);
    if (!(f1.is_open())) {
        cout << "���� �� ������";
        return 2;
        //�������� �����, ���������� ���� ������

    }
    else {
        cout << "���� ������!";
        return 1;
    }

    /*ofstream fout(path); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ cppstudio.txt
    fout << "������ � ������� � �++"; // ������ ������ � ����
    fout.close(); // ��������� ����
    */
}



void File_O::file_read(string path)
{
    ifstream file(path);

    int numb = 0;
    int i = 0;
    int j = 0;
    string temp;

    //���������� ���������� � ����������
    getline(file, name);    //������ �������� ����������
    getline(file, adress);    //������ ������ ����������
    getline(file, kassirs[0]);     //������ ��� ��������


    //���������� ���������� �������� �� ������ ???

    getline(file, temp);

    //���������� ���������� � �������
    do
    {
        getline(file, filmi[i].name);
        getline(file, filmi[i].duration);
        getline(file, filmi[i].age);
        getline(file, filmi[i].short_description);
        getline(file, filmi[i].main_role);
        getline(file, filmi[i].rejisser);
        
        getline(file, temp);

        for (j = 0; j < 9; j++)
        {
            getline(file, (filmi[i].time[j]));
            getline(file, (filmi[i].price[j]));
            for (int k = 0; k < 10; k++)
            {
                getline(file, temp);
                filmi[i].mesta[j] = filmi[i].mesta[j] + temp;
            }
            getline(file, temp);
        }
        getline(file, temp);
        i++;
    } while (i < kol_vo_filmov);

    //cout << filmi[0].duration;        //����
   
}

int File_O::file_check_compound(string path)        //�������� �������������� ���������� �����
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
    if ((i - 3) % 124 == 0)            //�������������� �����
    {
        kol_vo_filmov = (i - 4) / 123;
        return 1;
 
    }
    else               //�������������� �������, � ����� ������� ������
    {
        cout << "� ����� ������� ������";
        return 2;
    }
}

