///////////////////////////
// Шрейбер М. БСБО-13-18 //
///////////////////////////

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <cctype>

using namespace std;

string slova[4][10] = {
{"ноль", "одиннадцать", "двенадцать", "тринадцать", "четырнадцать", "пятнадцать", "шестнадцать", "семнадцать", "восемнадцать", "девятнадцать"},
{"", "один", "два", "три", "четыре", "пять", "шесть", "семь", "восемь", "девять"},
{"", "десять", "двадцать", "тридцать", "сорок", "пятьдесят", "шестьдесят", "семьдесят", "восемьдесят", "девяносто"},
{"", "сто", "двести", "триста", "четыреста", "пятьсот", "шестьсот", "семьсот", "восемьсот", "девятьсот"}
};

void print(int res) {
	int i = 1;
	bool thous = false, milleon = false;
	string temp = "";

	if (res == 0) temp += slova[0][0];
	if (res < 0) {
		cout << "минус ";
		res *= -1;
	}
	while (res > 0) {
		if ((i == 4) && (!thous)) {
			temp = "тысяч " + temp;
			thous = true;
			i = 1;
		}
		else if ((i == 4) && (!milleon)) {
			temp = "миллионов " + temp;
			milleon = true;
			i = 1;
		}
		if ((res % 100 > 10) && (res % 100 < 20) && (i == 1)) {
			temp = slova[0][res % 10] + " " + temp;
			res /= 100;
			i++;
		}
		else {
			temp = slova[i][res % 10] + " " + temp;
			res /= 10;
		}
		i++;
	}
	cout << temp << endl;
}

string operations(string str) {
	int mult = str.find('*'); // проверяем, есть ли в строке умножение
	string number1 = "", number2 = ""; // числа, над которым будет производиться операция
	int n1_i = 1, n2_i = 1; // индексы чисел в строке, нужные при умножении
	int res, koef = 1; // результат операций и коэфицент (для учета отрицательных чисел)
	bool end = false;

	if (mult != -1) { // первым делом выполняем операции умножения, если такие еще остались
		while (!end) {
			if (mult - n1_i < 0) end = true;
			else if (!(isdigit(str[mult - n1_i]))) end = true;
			else {
				number1 = str[mult - n1_i] + number1;
				n1_i++;
			}
		}
		end = false;
		while (!end) {
			if (mult + n2_i > str.size()) end = true;
			else if (!(isdigit(str[mult + n2_i]))) end = true;
			else {
				number2 += str[mult + n2_i];
				n2_i++;
			}
		}
		res = stoi(number1) * stoi(number2);
		str = str.substr(0,mult - n1_i + 1) + to_string(res) + str.substr(mult + n2_i);
		return operations(str);
	}
	if (str[0] == '-') { // запоминаем "-", если первое число отрицательное
		str.erase(0, 1);
		koef = -1;
	}
	if ((str.find('+') != -1) || (str.find('-') != -1)) { // если есть операции сложения или вычитания, то выполняем их по порядку
		
		while (isdigit(str[0])) {
			number1 += str[0];
			str.erase(0, 1);
		}
		char oper = str[0];
		str.erase(0, 1);
		while (isdigit(str[0])) {
			number2 += str[0];
			str.erase(0, 1);
		}
		if (oper == '+') res = koef * stoi(number1) + stoi(number2);
		else res = koef * stoi(number1) - stoi(number2);
		str = to_string(res) + str;
		return operations(str);
	}
	if (koef == -1) str = "-" + str;
	return str;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int len = 20;
	int res;
	string str;
	char s;
	bool end = false;

	while (end != true) {
		cout << "------------------------------" << endl;
		cout << "| 1 - ввести выражение       |" << endl;
		cout << "| 0 - выход                  |" << endl;
		cout << "| Допустимые операции: + - * |" << endl;
		cout << "------------------------------" << endl;

		s = _getch();

		if (s == '1') {
			cout << "Введите выражение длинной не более " << len << " символов: ";
			cin >> str;
			while (str.size() > len) {
				cout << "Некорректный ввод, попробуйте еще раз: ";
				cin >> str;
			}
			system("cls");
			res = stoi(operations(str));
			cout << res << " ";
			print(res);
		}

		else if (s == '0') end = true;

		else system("cls");
		_getch();
	}

	return 0;
}