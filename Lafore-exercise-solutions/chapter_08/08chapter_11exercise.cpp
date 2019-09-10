﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 08chapter_11exercise.cpp
// преобразовать структуру sterling из упражнения 11 главы 5 в класс
// с указанными в задании данными и методами

// В старой английской системе денежные суммы представлялись фунтами стерлингов,
// шиллингами и пенсами (1 фунт = 20 шиллингов = 240 пенсов). Во второй половине
// XX века были введены десятичные фунты (1 фунт = 100 новых пенсов). Фунты в
// старой и новой системах равны друг другу.

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <iomanip> // для манипулятора setprecision
using namespace std;

class sterling // класс, представляющий денежную сумму в старой английской системе
{
private:
	long pounds;   // фунты (1 фунт = 20 шиллингов = 240 пенсов)
	int shillings; // шиллинги (1 шиллинг = 12 пенсов)
	int pences;    // пенсы
public:
	// конструктор без аргументов
	sterling() : pounds(0), shillings(0), pences(0)
		{ }
	// конструктор с одним аргументом
	// (для преобразования десятичных фунтов в денежную сумму в старой системе)
	sterling(double df)
	{
		// в этих формулах используется то обстоятельство, что при присвоении
		// целочисленной переменной вещественного значения дробная часть отбрасывается
		pounds = df;
		shillings = (df - pounds) * 20;
		// в случае пенсов необходимо округление до ближайшего целого (функция round),
		// а не отбрасывание дробной части
		pences = round(((df - pounds) * 20 - shillings) * 12);
	}
	// конструктор с тремя аргументами
	sterling(long ps, int s, int p) : pounds(ps), shillings(s), pences(p)
		{ }
	// метод для получения от пользователя денежной суммы в старой системе
	// в формате "£9.19.11"
	void getSterling()
	{
		// чтобы символ фунта отобразился в консоли, шрифт в консоли должен быть юникодным,
		// например, шрифт "Lucida Console" или "Consolas"

		wchar_t separator; // для точки, разделяющей фунты, шиллинги и пенсы
		wcout << L"Введите сумму (фунты, шиллинги и пенсы через точку): £";
		wcin >> pounds >> separator >> shillings >> separator >> pences;
	}
	// метод для вывода денежной суммы в старой системе на экран
	// в формате "£9.19.11"
	void putSterling() const
	{
		// чтобы символ фунта отобразился в консоли, шрифт в консоли должен быть юникодным,
		// например, шрифт "Lucida Console" или "Consolas"

		wcout << L"£" << pounds << L"." << shillings << L"." << pences;
	}
	// операция преобразования объекта класса (денежной суммы в старой системе)
	// в число типа double (денежную сумму в десятичных фунтах)
	operator double() const
	{
		// так как в этом арифметическом выражении используются вещественные числа
		// (по умолчанию это тип double), то результат выражения тоже будет приведен
		// к вещественному типу (double в данном случае)
		return (pounds + shillings / 20.0 + pences / 240.0);
	}
	// перегрузка операции сложения (+) для сложения двух объектов класса
	// (результат тоже будет объектом класса)
	sterling operator+ (sterling s) const
	{
		// 1) sterling(pounds, shillings, pences) — создание безымянного объекта класса
		// с помощью конструктора с тремя аргументами. Обозначим это выражение как s1

		// 2) double(s1) и double(s) — создание безымянных переменных типа double с
		// помощью операции преобразования объекта класса в число типа double,
		// определенной выше (сумма из старой системы преобразуется в десятичные фунты)

		// 3) sterling(double(s1) + double(s)) — создание безымянного объекта класса
		// с помощью конструктора с одним аргументом (из десятичных фунтов в сумму
		// в старой системе)

		return sterling(double(sterling(pounds, shillings, pences)) + double(s));
	}
	// перегрузка операции вычитания (-) для нахождения разности двух объектов класса
	// (результат тоже будет объектом класса)
	sterling operator- (sterling s) const
	{
		return sterling(double(sterling(pounds, shillings, pences)) - double(s));
	}
	// перегрузка операции умножения (*) для нахождения произведения объекта класса
	// и числа типа double (результатом будет объект класса)
	sterling operator* (double n) const
	{
		return sterling(double(sterling(pounds, shillings, pences)) * n);
	}
	// перегрузка операции деления (/) для нахождения частного от деления объекта
	// класса на другой объект класса (результатом будет число типа double)
	double operator/ (sterling s) const
	{
		return (double(sterling(pounds, shillings, pences)) / double(s));
	}
	// перегрузка операции деления (/) для нахождения частного от деления объекта
	// класса на число типа double (результатом будет объект класса)
	sterling operator/ (double n) const
	{
		return sterling(double(sterling(pounds, shillings, pences)) / n);
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	sterling s1, s2, s; // денежные суммы в старой английской системе
	double n;           // число типа double

	// запрашиваем у пользователя две денежные суммы в старой английской системе
	wcout << L"1. "; s1.getSterling();
	wcout << L"2. "; s2.getSterling(); wcout << endl;

	// покажем эти суммы в десятичных фунтах:
	wcout << L"1. В десятичных фунтах: " << fixed << setprecision(2) << double(s1) << endl;
	wcout << L"2. В десятичных фунтах: " << fixed << setprecision(2) << double(s2) << endl << endl;

	// ДЕМОНСТРАЦИЯ ПЕРЕГРУЖЕННЫХ ОПЕРАЦИЙ:

	// предположим, что денежные суммы s1 и s2 — выручка фирмы за первый и второй годы
	// ее существования, тогда выручка фирмы за 2 этих года составит s:
	s = s1 + s2;
	wcout << L"Результат сложения этих сумм: "; s.putSterling(); wcout << endl;

	// предположим, что s1 — денежная сумма на нашем расчетном счете, а s2 —
	// денежная сумма, перечисленная для оплаты счета поставщика, тогда у нас на
	// расчетном счете останется денежная сумма s:
	s = s1 - s2;
	wcout << L"Разность этих сумм: "; s.putSterling(); wcout << endl;

	// предположим, что s1 — денежная сумма вклада, который мы положили в банк, и
	// процентная ставка по вкладу согласно договора с банком составляет 5% за год,
	// тогда через год сумма нашего вклада вместе с процентами составит s:
	s = s1 * 1.05;
	wcout << L"Произведение первой суммы и числа 1,05: "; s.putSterling(); wcout << endl;

	// предположим, что s1 — денежная сумма, представляющая расходы на покупку грузовика,
	// а s2 — сумма ежегодной прибыли от его использования, определим тогда
	// число лет n, через которое грузовик окупится:
	n = s1 / s2;
	wcout << L"Частное от деления первой суммы на вторую: " << n << endl;

	// предположим, что s1 — денежная сумма, представляющая расходы на покупку грузовика,
	// и нам нужно узнать, сколько прибыли s необходимо получать ежегодно от использования
	// этого грузовика, чтобы он окупился за 3,5 года:
	s = s1 / 3.5;
	wcout << L"Частное от деления первой суммы на число 3,5: "; s.putSterling(); wcout << endl;

	return 0;
}