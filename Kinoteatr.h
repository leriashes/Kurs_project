#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
using namespace std;

class Kinoteatr
{
public:
	string name;	//�������� ����������
	string adress;	//����� ����������
	string kassirs[5];	//������� ����������
	string inn;		//������ ��� ����
	string rnm;		//������ ��� ����

	int kol_vo_filmov;	//���������� ������� � �������

	struct film
	{
		string name;	//�������� ������
		string age;		//���������� ����������
		string duration;	//����������������� ������
		string rejisser;//���������
		string short_description;	//������� �������� ������
		string main_role;	//������� ����
		string price[9];	//��������� ������
		string time[9];	//����� ������
		string mesta[9];	//����� � ����
		string rand[9];
	};
	film filmi[10];


	void New_name();	//���� �������� ����������
	void New_kassir();	//���� ��� �������
	string New_zal(int number_film, int number);		//��������� ������������� ����
};

