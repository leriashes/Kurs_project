#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
#include "Film.h"
using namespace std;

class Cinema
{
private:
	string name;	//�������� ����������
	string adress;	//����� ����������
	string cashiers[5];	//������� ����������		// ������� ����� �������� � ����������� � ���?

	string inn;		//������ ��� ����
	string rnm;		//������ ��� ����
	
	int films_number;	//���������� ������� � �������

	Film films[10];
	

	void InputName();	//���� �������� ����������
	void InputCashier();	//���� ��� �������

};

