#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>;
#include <string>
#include "Film.h"
using namespace std;

class Cinema
{
public:
	int films_number;	//���������� ������� � �������

private:
	string name;	//�������� ����������
	string adress;	//����� ����������
	string cashiers[5];	//������� ����������		// ������� ����� �������� � ����������� � ���?

	string inn;		//������ ��� ����
	string rnm;		//������ ��� ����
	
	

	Film films[10];
	
public:
	void ChangeName();	//������� �������� ����������
	void ChangeAdress();	//������� ������ ����������
	void ChangeInn();		//��������� ��� ����������
	void ChangeRnm();		//��������� ��� ����������
	void ChangeCashier();	//��������� ��������
	void check_cash();

	void DelFilm(int num_film);
	void ChangeFilm(int num_punkt, int num_film);
	int CheckTime(int time, int num_seans, int duration);
	void TimeAuto(int duration);

	void InputName();	//���� �������� ����������
	void InputCashier();	//���� ��� �������
	void InputINN();		//���� ���
	void InputAdress();		//���� ������
	void InputRNM();		//���� ���

	string NewHall();	//��������� ���� (�������)

	void NameOut();	//����� �������� ����������

	friend class File_O;
	friend class Menu;
};

