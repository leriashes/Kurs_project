#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
using namespace std;

class File_O
{
	
public:
	int error;
	int kol_vo_film;
	string path;
	

	void Input();		//���� ���� ��� �����
	void New();	//�������� ������ �����   ??????
	int Check(string path);	//�������� �� ������������
	void Read(string path);
	int CheckCompound(string path);	//�������� �������������� �����
};

