#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Cinema.h";
using namespace std;

class File_O
{

public:
	void ReadBron();

	int error;
	int kol_vo_film;	//перенести в кинотеатр?
	string path;
	string path_bron;

	void InputPath();		//ввод пути для файла
	void New(Cinema& cinema);	//создание нового файла   ??????
	bool CheckPath();	//проверка на сущестование
	void Read(Cinema& cinema);
	bool CheckCompound();	//проверка форматирования файла
	void Write(Cinema cinema);	//запись всех данных в файл
	void Clean();

	friend class Menu;
};

