#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Cinema.h";
using namespace std;

class File_O
{

public:
	int error;
	int kol_vo_film;	//��������� � ���������?
	string path;

	void InputPath();		//���� ���� ��� �����
	void New();	//�������� ������ �����   ??????
	bool CheckPath();	//�������� �� ������������
	void Read(Cinema& cinema);
	bool CheckCompound();	//�������� �������������� �����
	void Write(Cinema cinema);	//������ ���� ������ � ����

	friend class Menu;
};

