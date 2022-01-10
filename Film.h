#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Film
{
private:
	string name;	//�������� ������
	string age;		//���������� �����������
	string duration;	//����������������� ������
	string rejisser;//���������
	string short_description;	//������� �������� ������
	string main_role;	//������� ����
	string number_zal;	//����� ���� ��� ������

	//??????????
	string price[9];	//��������� ������		//??????????
	string time[9];	//����� ������		//??????????
	string mesta[9];	//����� � ����		//??????????
	string rand[9];

	friend class File_O;
	friend class Menu;
	friend class Order;
	friend class Cinema;
};

