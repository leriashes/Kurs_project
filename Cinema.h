#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Film.h"
#include <thread>
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
	string otchet_vsego;	//����� ������� �� ���� ������
	string otchet_today;	//����� ������� �� ����������� ����
	string promo[10][2];	//���������
	int promo_numbers = 0;
	int casshiers_numbers = 0;
	

	Film films[10];
	
public:
	void ChangeName();	//������� �������� ����������
	void ChangeAdress();	//������� ������ ����������
	void ChangeINN();		//��������� ��� ����������
	void ChangeRNM();		//��������� ��� ����������

	void ChangeCashier();	//��������� ��������
	void ListCashier(int k);	//����� ��������

	/// 
	/// ��������� � ����� USER
	/// 
	void ListPromo(int k);	//����� ������ ����������
	void DelPromo();		//�������� ���������
	void RedPromo();		//�������������� ���������� � ���������
	void NewPromo();		//���������� ������ ���������
	string NewPromoName(string message);
	string NewPromoValue(string message);

	void DelFilm(int num_film);
	void ChangeFilm(int num_punkt, int num_film);
	int CheckTime(int time, int num_seans, int duration);
	void TimeAuto(int duration);
	string Convert_Time(int time);

	void InputName();	//���� �������� ����������
	void InputCashier();	//���� ��� �������
	void InputINN();		//���� ���
	void InputAdress();		//���� ������
	void InputRNM();		//���� ���
	void NewHallCinema(int number_film);	//��������� ������������� ���� ��� ������ ������	
	void PriceInput(int num_film, int num);

	string NewHall();	//��������� ���� (�������)

	void NameOut();	//����� �������� ����������

	friend class File_O;
	friend class Menu;
	friend class Order;
};

