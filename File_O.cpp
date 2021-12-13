#define _CRT_SECURE_NO_WARNINGS
#include "File_O.h";
#include <iostream>;
#include <conio.h>;
using namespace std;

void File_O::file_open(string path)
{
    system("cls");
    cout << "Режим администратора\n\n";

    ifstream f1;

    f1.open(path);
    if (!(f1.is_open())) {
        cout << "Файл не найден";
        //создание файла, заполнение всех данных
    }
    else {
        cout << "Файл найден!";
    }

    /*ofstream fout(path); // создаём объект класса ofstream для записи и связываем его с файлом cppstudio.txt
    fout << "Работа с файлами в С++"; // запись строки в файл
    fout.close(); // закрываем файл
    */

    _getch();
}
