﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 07chapter_11exercise.cpp
// Вернуться к упражнению 7 главы 7 (работа с денежными строками) и дописать
// к имеющемуся классу money метод ldtoms, преобразующий число типа long double
// в денежную строку

// Задание к упражнению 7 главы 7:
// создать класс money, представляющий денежную сумму в долларах и центах;
// написать метод, принимающий денежную сумму в строковом виде и возвращающий
// эквивалентное ей число типа long double; написать программу для демонстрации
// работы этого метода

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <iomanip> // для манипуляторов setiosflags, setprecision
#include <sstream> // для стандартного класса wstringstream
using namespace std;

class money // класс, представляющий денежную сумму в долларах и центах
{
private:
	long double sum; // денежная сумма в долларах и центах
public:
	// метод преобразует денежную строку в число типа long double
	long double mstold(wchar_t []); // прототип
	// метод преобразует число типа long double (sum) в денежную строку и
	// возвращает эту строку через первый параметр
	void ldtoms(wchar_t []); // прототип
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

		// преобразуем строку с денежной суммой в числовое значение
		// типа long double
		res = ms.mstold(tms);

		// выводим результат на экран
		wcout << L"Число типа long double: " << setiosflags(ios::fixed)
			<< setprecision(2) << res << endl;

		// преобразуем полученное выше число типа long double обратно в
		// денежную строку
		ms.ldtoms(tms);

		// выводим результат на экран
		wcout << L"Денежная строка: " << tms << endl;

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

// метод преобразует число типа long double (поле sum класса money) в денежную строку
// и возвращает эту строку через первый параметр
void money::ldtoms(wchar_t str[])
{
	// В условиях упражнения в книге сказано, что при преобразовании числа в строку
	// можно использовать объект класса ostrstream "как рассматривалось ранее в этой главе".
	// На самом деле в главе 7, к которой идет это упражнение, и ранее Лафоре ничего
	// не писал об этом. Автор перепутал с 12-й главой, а конкретнее — см. стр.585 книги.

	// Итак, объект класса ostrstream можно здесь рассматривать как аналог стандартных
	// потоков ввода и вывода cin и cout. Для его использования нужно включить в программу
	// заголовочный файл <strstream>. Однако, нужно учитывать, что использование класса
	// ostrstream не одобряется, начиная со стандарта C++98.

	// Вместо класса ostrstream стандарт языка C++ рекомендует использовать ostringstream,
	// который требует включения в программу заголовочного файла <sstream>. Оба класса
	// (ostrstream и ostringstream) работают со строками-массивами типа char. Для широких
	// символов типа wchar_t можно использовать класс wostringstream, тоже требующий включения
	// в программу заголовочного файла <sstream>.

	// Вместо wostringstream я взял класс wstringstream, с объектом которого можно использовать
	// и вывод (оператор вставки), и ввод (оператор извлечения из потока).
	
	wchar_t ustring[80]; // временная строка
	wstringstream woss;  // создадим объект стандартного класса wstringstream
	
	// преобразуем число sum типа long double в строку, указав, что нужен неэкспоненциальный
	// вид числа и количество знаков после десятичной точки должно быть 2
	woss << setiosflags(ios::fixed) << setprecision(2) << sum;
	// загрузим полученную строку из потока во временную строку
	woss >> ustring;

	int i = 0, n = 0, j;       // индексы строк str и ustring соответственно
	int len = wcslen(ustring); // длина временной строки ustring
	wchar_t delim3 = L',';     // символ, разделяющий тройки разрядов (разделитель)
	
	str[i++] = L'$';  // первым в денежной строке идет символ доллара

	// выражение (len - 3) означает количество знаков числа
	// без десятичной точки и двух разрядов после точки

	if ((len - 3) % 3 == 2)      // если старших разрядов до разделителя два,
	{
		str[i++] = ustring[n++]; // то переписать два старших разряда
		str[i++] = ustring[n++];
		str[i++] = delim3;       // и вписать разделитель
	}
	else if ((len - 3) % 3 == 1) // иначе, если старший разряд до разделителя один,
	{
		str[i++] = ustring[n++]; // то переписать старший разряд
		str[i++] = delim3;       // и вписать разделитель
	}

	for (j = n; j < len - 3; j++) // переберем оставшиеся символы в цикле
	{
		str[i++] = ustring[j];    // перепишем очередной разряд
		// после каждой тройки разрядов вставляем разделитель, если
		// только это не последняя тройка разрядов
		if (((j - n + 1) % 3 == 0) && (j != len - 3 - 1))
			str[i++] = delim3;
	}

	str[i++] = ustring[j++]; // перепишем точку и два
	str[i++] = ustring[j++]; // разряда после точки (центы)
	str[i++] = ustring[j];
	str[i]   = L'\0';        // последним вписываем нулевой символ
}