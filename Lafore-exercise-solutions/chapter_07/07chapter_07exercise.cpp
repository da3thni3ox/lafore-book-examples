﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 07chapter_07exercise.cpp
// Создать класс money, представляющий денежную сумму в долларах и центах;
// написать метод, принимающий денежную сумму в строковом виде и возвращающий
// эквивалентное ей число типа long double; написать программу для демонстрации
// работы этого метода

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <iomanip> // для манипуляторов setiosflags, setprecision
using namespace std;

class money // класс, представляющий денежную сумму в долларах и центах
{
private:
	long double sum; // денежная сумма в долларах и центах
public:
	long double mstold(wchar_t []); // прототип функции
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	money ms;        // денежная сумма (объект класса money)
	wchar_t tms[80]; // для строки с денежной суммой
	long double res; // для числового значения типа long double
	wchar_t ans;     // для ответа пользователя о продолжении ввода (д/н)

	do {
		// запрашиваем у пользователя строку с денежной суммой
		wcout << L"Введите денежную сумму (пример: '$1,234,567.99'):\n";
		wcin >> tms;

		// преобразовываем строку с денежной суммой в числовое значение
		// типа long double
		res = ms.mstold(tms);

		// выводим результат на экран
		wcout << L"Число типа long double: " << setiosflags(ios::fixed)
			<< setprecision(2) << res << endl;

		wcout << L"Продолжить (д/н)? "; wcin >> ans;
	} while (ans != L'н');

	return 0;
}

// метод преобразует заданную строку в число типа long double и возвращает это число;
// предполагается, что заданная строка представляет денежную сумму,
// например, "$1,234,567,890,123.99";
// mstold расшифровывается как "money string to long double"
long double money::mstold(wchar_t str[])
{
	wchar_t temp[80]; // временная строка
	int j = 0;        // индекс для временной строки (массива символов)
	// обрабатываем денежную строку-параметр как массив символов
	for (int i = 0; i < wcslen(str); i++)
	{
		wchar_t ch = str[i]; // возьмем очередной символ из массива (строки)

		if ((ch >= L'0') && (ch <= L'9')) // если он является цифрой,
			temp[j++] = ch;               // то добавить его к временной строке,
		else if (ch == L'.')              // иначе, если он является точкой,
			temp[j++] = ch;               // то тоже добавить к временной строке,
		                                  // остальные символы игнорировать
	}
	temp[j] = L'\0'; // завершаем временную строку нулевым символом

	wchar_t *stop;
	// преобразуем временную строку в числовое значение типа long double
	sum = wcstold(temp, &stop);

	// В книге Лафоре рекомендует использовать библиотечную функцию _atold для
	// преобразования строки в виде массива типа char в число типа long double.
	// Однако, нужно учитывать, что Лафоре пользовался при написании книги
	// средой Microsoft Visual C++ версии 6.0, вышедшей в 1998 году.
	// На сегодня (2019 год) в среде Visual Studio Community 2017 библиотечная функция
	// _atold отсутствует.
	
	// Есть функция atof, принимающая в качестве аргумента массив типа char, но
	// она возвращает число типа double, а не long double.

	// Еще есть функция _atoldbl, которая принимает вторым аргументом массив типа
	// char и возвращает в первом аргументе значение типа указатель на _LDOUBLE.

	// Еще есть функция strtold, которая принимает первым аргументом массив типа
	// char и возвращает число типа long double. Ее аналогом для широких символов
	// является функция wcstold.

	// Для преобразования массива типа wchar_t (широких символов) я нашел и
	// применил (см. выше) библиотечную функцию wcstold. Эта функция принимает
	// массив типа wchar_t первым аргументом и возвращает соответствующее число
	// типа long double. Второй параметр обязателен, но для наших целей НЕ
	// ИМЕЕТ ЗНАЧЕНИЯ (в нем возвращается адрес первого символа в строке
	// такого, что не может являться частью числа). Для понимания второго
	// параметра нужно понимание указателей, которые будут разбираться позже,
	// в девятой главе книги.

	// Ну и ВАЖНО понимать, что тип long double поддерживался как 80-битное представление
	// числа с плавающей запятой только в старых версиях Microsoft Visual C++.
	// В последних версиях, в том числе и в Visual Studio Community 2017, тип
	// long double хоть и поддерживается и отличается компилятором от типа double,
	// однако, на деле является таким же 64-битным представлением числа с плавающей
	// запятой, как и double. Эти типы в указанной среде разработки идентичны и
	// значения таких типов занимают по 8 байт (64 бита) каждое.

	// Размер 8 байт (64 бита) позволяет оперировать числами длиной в 15-16 значимых
	// десятичных разрядов (включая разряды после десятичной точки). То есть, к примеру,
	// получив на вход строку "$123,456,789,012,345.62" наш метод mstold вернет
	// число типа long double = 123456789012345.63
	// Из этого примера видно, что в последнем, 17-м разряде, вместо цифры "2" стоит
	// цифра "3". То есть ручаться можно только за точность первых 15-16 разрядов.

	return sum; // возвращаем полученное значение
}