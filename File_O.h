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
	int kol_vo_film;	//перенести в кинотеатр?
	string path;

	void InputPath();		//ввод пути для файла
	void New();	//создание нового файла   ??????
	bool CheckPath();	//проверка на сущестование
	void Read(Cinema& cinema);
	bool CheckCompound();	//проверка форматирования файла
	void Write(Cinema cinema);	//запись всех данных в файл

	friend class Menu;
};

