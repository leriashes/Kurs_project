#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Cinema.h";
using namespace std;

class File_O
{

public:
	void ReadBron(Cinema& cinema);

	int error;
	int kol_vo_film;	//��������� � ���������?
	string path;
	string path_bron = "bronirovanie.txt";

	void InputPath();		//���� ���� ��� �����
	void New(Cinema& cinema);	//�������� ������ �����   ??????
	bool CheckPath();	//�������� �� ������������
	void Read(Cinema& cinema);
	bool CheckCompound();	//�������� �������������� �����
	void Write(Cinema cinema);	//������ ���� ������ � ����
	void Clean();

	friend class Menu;
};

