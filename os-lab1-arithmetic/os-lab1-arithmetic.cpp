// os-lab1-arithmetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Calculate.h"


using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	float result;
	string input, notation;

	cout << "������� ��������� � ����� ����" << endl;
	cout << "input=";
	getline(cin, input);

	try {
		notation = postfix_note(input);
		result = Calculate(notation);
	}
	catch (...){
		cout << "������ ���������" << endl;
		system("PAUSE");
		return 1;
	}

	cout << "�������� �����: ";
	cout << notation;
	cout << endl;
	cout << "���������: " << result << endl;
	system("PAUSE");
}