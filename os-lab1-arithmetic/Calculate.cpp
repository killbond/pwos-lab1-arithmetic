#include "stdafx.h"
#include "Calculate.h"

using namespace std;

string postfix_note(string exp){

	Stack<char> opStack(256);
	ostringstream result;

	map <char, int> op;
	op['*'] = 3;
	op['/'] = 3;
	op['+'] = 2;
	op['-'] = 2;
	op['('] = 1;
	op['='] = 0;

	char buff;
	float number = 0;
	string::size_type numberSize;

	replace(exp.begin(), exp.end(), '.', ',');
	for (int i = 0; i < exp.length(); i++) {
		buff = exp[i];

		if (' ' == buff) {
			continue;
		}

		if (op.count(buff)) {

			if ((!opStack.IsEmpty()) && (op[buff] <= op[opStack.Peek()]) && (buff != '(')) {
				while ((!opStack.IsEmpty()) && (op[buff] <= op[opStack.Peek()])) {
					result << opStack.Pop() << ' ';
				}
			}

			opStack.Push(buff);
			continue;
		}

		if (isdigit(buff) || '.' == buff || '.' == buff) {
			number = stof(exp.substr(i), &numberSize);
			result << to_string(number) << ' ';
			i += numberSize - 1;
			continue;
		}

		if (buff == ')') {

			while ((!opStack.IsEmpty()) && (opStack.Peek() != '(')) {
				result << opStack.Pop() << ' ';
			}

			if (opStack.IsEmpty()) {
				throw "не правильно расставлены скобки";
			}

			opStack.Pop();
			continue;
		}
		throw "недопустимый символ";
	}

	while (!opStack.IsEmpty()){
		if (opStack.Peek() == '(')
			throw "не правильно расставлены скобки";
		result << opStack.Pop() << ' ';
	}

	if (result.rdbuf()->in_avail())
		throw "нет данных";

	return result.str();
}

double Calculate(string exp)
{
	if (exp.empty())
		throw "нет данных";

	char buff;
	float leftOperand;
	float rightOperand;
	float parsedNumber;
	string::size_type parsedSize;
	Stack<float> trackStack(256);

	map<char, float> val;

	replace(exp.begin(), exp.end(), '.', ',');
	for (int i = 0; i < exp.length(); i++){
		buff = exp[i];

		if (' ' == buff) {
			continue;
		}

		if (exp[exp.length() - 1] == '=')
			val[exp[0]] = 0;

		if (isdigit(buff) || '.' == buff || '.' == buff){
			parsedNumber = stof(exp.substr(i), &parsedSize);
			trackStack.Push(parsedNumber);
			i += parsedSize - 1;
			continue;
		}

		if (trackStack.IsEmpty())
			throw "нет совпадения с числом операндов";

		rightOperand = trackStack.Pop();
		if (trackStack.IsEmpty())
			throw "нет совпадения с числом операндов";

		leftOperand = trackStack.Pop();

		switch (buff){
			case '+':{ trackStack.Push(leftOperand + rightOperand); break; }
			case '-':{ trackStack.Push(leftOperand - rightOperand); break; }
			case '*':{ trackStack.Push(leftOperand * rightOperand); break; }
			case '/':{ trackStack.Push(leftOperand / rightOperand); break; }
			default:break;
		}
	}

	float result = trackStack.Pop();
	if (!trackStack.IsEmpty())
		throw "Стек переполнен";

	return result;
}