#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <locale.h>
#include <windows.h>
#include "Menu.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu menu1("Для просмотра списка фильмов нажмите '1'.\nДля входа в режим администратора нажмите '2'.\nДля выхода нажмите 'esc'.\n\n", 2);

	menu1.print();
	menu1.input_number();
    std::cout << "Hello World!\n";
}
