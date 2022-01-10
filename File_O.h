#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include "Cinema.h";
using namespace std;

class File_O
{

public:
	void ReadBron(Cinema& cinema);	//чтение файла с забронированными билетами
	void WriteBron(Cinema& cinema);	//запись в файл с забронированными билетами
	void WriteNewBron(Cinema& cinema);	//запись в файл из массива данного кинотеатра

	int error;
	int kol_vo_film;	//перенести в кинотеатр?
	string path;	//путь к файлу с кинотеатром
	string path_bron = "bronirovanie.txt";	//путь к файлу с забронированными билетами

	void InputPath();		//ввод пути для файла
	void New(Cinema& cinema);	//создание нового файла
	bool CheckPath();	//проверка на сущестование
	void Read(Cinema& cinema);	//чтение всех данных из файла кинотеатра
	bool CheckCompound();	//проверка форматирования файла
	void Write(Cinema& cinema);	//запись всех данных в файл
	void Clean(string path);		//очистка файла по пути path

	friend class Menu;
};

