#include "Kinoteatr.h"

void Kinoteatr::new_name()
{
	do
	{
		cout << "������� �������� ����������:";
		cin >> name;
	} while (name == "");
}

void Kinoteatr::new_kassir()
{
	string FIO;
	
	do
	{
		cout << "������� ��� �������: ";
		cin >> FIO;
		//�������� �� ������������� ������� ������� � ����???
	} while (FIO == "");
	

}
