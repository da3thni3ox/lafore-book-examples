﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 09chapter_06exercise.cpp
// Имеется класс safearray из примера 333_arrover3.cpp главы 8, реализующий
// «безопасный» массив. В упражнении 9 главы 8 этот класс был модернизирован
// добавлением возможности определения верхней и нижней границы индекса массива
// в пределах массива с фиксированным размером в 100 элементов. Требуется
// сделать то же самое, только не изменяя оригинальный класс (как это делалось
// в упражнении 9 главы 8), а добавив новый класс с этой новой функциональностью,
// использовав возможности наследования.

// Пояснение к примеру 333_arrover3.cpp главы 8:
// демонстрация создания безопасного массива, проверяющего
// свои индексы при использовании
// (используется перегрузка операции индексации [])

////////////// Задание к упражнению 9 главы 8: ///////////////////////////////
// Дополнить класс safearray из примера 333_arrover3.cpp этой, 8-й, главы так,
// чтобы пользователь мог определять верхнюю и нижнюю границы индекса массива.
//
// Из-за того, что мы еще пока не проходили динамическое выделение памяти,
// данное упражнение следует выполнять на том же массиве с фиксированным
// размером в 100 элементов (индекс меняется от 0 до 99).
//
// Заданный пользователем размер индекса массива [lowerbound, upperbound] следует
// отобразить на реальный индекс [0, 99]. Квадратные скобки здесь означают,
// что указанные границы входят в индекс. Например, если пользователь задаст
// размер индекса массива [110, 145], то в реальном массиве эти номера элементов
// будут соответствовать номерам [0, 35].
//////////////////////////////////////////////////////////////////////////////

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;
// #include <process.h> // для функции exit не понадобился

const int LIMIT = 100; // размер массива

// оригинальный класс, реализующий «безопасный» массив
// (его программный код оставляем без изменений)
class safearray
{
private:
	int arr[LIMIT];
public:
	// обратите внимание, что функция возвращает ссылку!
	int& operator[] (int n)
	{
		if (n < 0 || n >= LIMIT)
			{ wcout << L"Ошибочный индекс!"; exit(1); }
		return arr[n];
	}
};

// новый класс, производный от оригинального класса safearray, реализующий
// возможность определения границ массива
class safehilo : public safearray
{
private:
	int lowerbound; // нижняя граница индекса массива
	int upperbound; // верхняя граница индекса массива
public:
	// конструктор с двумя аргументами
	safehilo(int low, int up) : lowerbound(low), upperbound(up)
	{
		// проверим заданные пользователем границы на ошибки
		if (lowerbound > upperbound)
			{ wcout << L"Ошибка! Верхняя граница индекса массива не может быть меньше нижней.\n"; exit(1); }
		if (upperbound - lowerbound >= LIMIT)
			{ wcout << L"Ошибка! В массиве не может быть больше " << LIMIT << L" элементов.\n"; exit(1); }
	}
	// обратите внимание, что функция возвращает ссылку!
	int& operator[] (int n)
	{
		if (n < lowerbound || n > upperbound)
			{ wcout << L"Ошибочный индекс!"; exit(1); }
		return safearray::operator[] (n - lowerbound);
		// выражение (n - lowerbound) отображает заданный пользователем индекс в реальный
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	int low, up; // для верхней и нижней границ индекса массива

	wcout << L"Введите нижнюю границу индекса массива : "; wcin >> low;
	wcout << L"Введите верхнюю границу индекса массива: "; wcin >> up;

	safehilo sa1(low, up);

	// задаем значения элементов
	for (int j = low; j <= up; j++)
		// используем функцию слева от знака присваивания (=)
		sa1[j] = j * 10;

	// показываем элементы
	for (int j = low; j <= up; j++)
	{
		// используем функцию справа от знака присваивания (=)
		int temp = sa1[j];
		wcout << L"Элемент " << j << L" равен " << temp << endl;
	}

	return 0;
}