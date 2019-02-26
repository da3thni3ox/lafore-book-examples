﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// fahren.cpp
// применение wcin и \n

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	int ftemp; // температура по Фаренгейту
	wcout << L"Введите температуру по Фаренгейту: ";
	wcin >> ftemp;
	int ctemp = (ftemp - 32) * 5 / 9;
	wcout << L"Температура no Цельсию равна " << ctemp << endl;

	return 0;
}