#define _CRT_SECURE_NO_WARNINGS
#include "File_O.h";
#include <iostream>;
#include <conio.h>;
using namespace std;

void File_O::file_open(string path)
{
    system("cls");
    cout << "����� ��������������\n\n";

    ifstream f1;

    f1.open(path);
    if (!(f1.is_open())) {
        cout << "���� �� ������";
        //�������� �����, ���������� ���� ������
    }
    else {
        cout << "���� ������!";
    }

    /*ofstream fout(path); // ������ ������ ������ ofstream ��� ������ � ��������� ��� � ������ cppstudio.txt
    fout << "������ � ������� � �++"; // ������ ������ � ����
    fout.close(); // ��������� ����
    */

    _getch();
}
