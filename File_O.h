#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Kinoteatr.h"
using namespace std;

class File_O
{

public:
	int error;	//����� ������
	string path;	//���� � ������� � ����������


	void File_input();		//���� ���� ��� �����
	void File_new();	//�������� ������ �����
	int File_check();	//�������� �� ������������
	void File_read(Kinoteatr *kinoteatr);
	int File_check_compound(int *kol_vo);	//�������� �������������� �����
	void File_write(Kinoteatr kinoteatr);	//������ ���� ������ � ����
};

