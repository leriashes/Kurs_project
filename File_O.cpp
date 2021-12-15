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
            cout << "0 - ������� � ����\n\n������� ���� � ����� � ����������� � ����������: ";

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
*/

int File_O::File_check()
{
    ifstream f1;

    f1.open(path);
    if (!(f1.is_open())) {
        //cout << "���� �� ������"; //����
        return 2;
        //�������� �����, ���������� ���� ������

    }
    else {
        //cout << "���� ������!"; //����
        return 1;
    }

    /*ofstream fout(path); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ cppstudio.txt
    fout << "������ � ������� � �++"; // ������ ������ � ����
    fout.close(); // ��������� ����
    */
}



void File_O::File_read(Kinoteatr *kinoteatr)
{
    ifstream file(path);

    int numb = 0;
    int i = 0;
    int j = 0;
    string temp;

    //���������� ���������� � ����������
    getline(file, (*kinoteatr).name);    //������ �������� ����������
    getline(file, (*kinoteatr).adress);    //������ ������ ����������
    getline(file, (*kinoteatr).kassirs[0]);     //������ ��� ��������


    //���������� ���������� �������� �� ������ ???


    //���������� ���������� � �������
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
            //_getch();   //����
        }
        //getline(file, temp);
        i++;
    } while (i < (*kinoteatr).kol_vo_filmov);

    //cout << filmi[0].duration;        //����

}

int File_O::File_check_compound(int* kol_vo)        //�������� �������������� ���������� �����
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
    if ((i - 3) % 133 == 0)            //�������������� �����
    {
        *kol_vo = (i - 3) / 133;
        return 1;

    }
    else               //�������������� �������, � ����� ������� ������
    {
        cout << "� ����� ������� ������";
        return 2;
    }
}

