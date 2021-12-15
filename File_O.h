#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Kinoteatr.h"
using namespace std;

class File_O
{

public:
	int error;	//номер ошибки
	string path;	//файл с данными о кинотеатре


	void File_input();		//ввод пути для файла
	void File_new();	//создание нового файла
	int File_check();	//проверка на сущестование
	void File_read(Kinoteatr *kinoteatr);
	int File_check_compound(int *kol_vo);	//проверка форматирования файла
	void File_write(Kinoteatr kinoteatr);	//запись всех данных в файл
};

