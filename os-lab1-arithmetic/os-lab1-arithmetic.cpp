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

	cout << "Введите выражение в общем виде" << endl;
	cout << "input=";
	getline(cin, input);

	try {
		notation = postfix_note(input);
		result = Calculate(notation);
	}
	catch (...){
		cout << "Ошибка выражения" << endl;
		system("PAUSE");
		return 1;
	}

	cout << "Польская форма: ";
	cout << notation;
	cout << endl;
	cout << "Результат: " << result << endl;
	system("PAUSE");
}