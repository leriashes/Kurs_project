#include "Cinema.h"

void Cinema::InputName()
{
	name = "";
	do
	{
		cout << "������� �������� ����������: ";
		cin >> name;
		cout << "\n";
	} while (name == "");
}

void Cinema::InputCashier()
{
	string full_name = "";
	
	do
	{
		cout << "������� ��� �������: ";
		cin >> full_name;
		cout << "\n";
		//�������� �� ������������� ������� ������� � ����???
	} while (full_name == "");
	
	//������������ �������
}
