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
	

	void file_input();		//ввод пути для файла
	void file_new();	//создание нового файла
	int file_check(string path);	//проверка на сущестование
	void file_read(string path);
	int file_check_compound(string path);	//проверка форматирования файла
};

