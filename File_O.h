#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Menu.h";
#include "Kinoteatr.h";
using namespace std;

class File_O : public Menu, Kinoteatr
{
	
public:
	int error;
	int kol_vo_film;
	string path;
	

	void file_input();		//���� ���� ��� �����
	void file_new();	//�������� ������ �����
	int file_check(string path);	//�������� �� ������������
	void file_read(string path);
	int file_check_compound(string path);	//�������� �������������� �����
};

