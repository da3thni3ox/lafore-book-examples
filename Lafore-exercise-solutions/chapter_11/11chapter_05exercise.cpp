﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 11chapter_05exercise.cpp
// Дана программа из упражнения 8 главы 8, в которой перегружены пять арифметических
// операторов для объектов класса bMoney, представляющего денежную строку. Требуется
// добавить еще два оператора вида long double * bMoney и long double / bMoney,
// которые не были перегружены в исходном упражнении из-за того, что еще не была
// пройдена тема дружественных функций. Также требуется добавить в main тестирование
// этих двух новых операторов.

////// Задание к упражнению 8 главы 8: /////////////////////////////////////////
// Модифицировать класс bMoney из упражнения 12 главы 7, включив в него арифметические
// операции с помощью перегрузки стандартных операций. 1) сложение двух объектов класса;
// 2) разность двух объектов класса; 3) умножение объекта класса на число типа long double;
// 4) деление объекта класса на другой объект класса; 5) деление объекта класса на число
// типа long double.
//
// Программа main должна запрашивать у пользователя две денежные строки и вещественное число.
// Затем программа должна выполнить пять перегруженных операций и показать их результаты.
// Всё это должно происходить в цикле, чтобы пользователь мог задать разные исходные данные.
//
// Дополнительное условие: не включать в класс операций преобразования bMoney в long double
// или long double в bMoney. Проверить, что попытка применения в программе выражений вида
// (bMoney * bMoney) или вида (bMoney + число) приведет к ошибке компиляции. (При необходимости
// использования конструктора с одним параметром рекомендуется использовать его со служебным
// словом explicit).
//
// При отсутствии операций преобразования не будут работать выражения вида (long double * bMoney)
// или вида (long double / bMoney), проверить это.
////////////////////////////////////////////////////////////////////////////////

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <iomanip> // для манипуляторов setiosflags, setprecision
#include <sstream> // для стандартного класса wstringstream
using namespace std;

class bMoney // класс, представляющий денежную сумму в долларах и центах
{
private:
	long double sum; // денежная сумма в долларах и центах
public:
	bMoney() // конструктор без параметров
		{ sum = 0.0L; }
	// конструктор с одним параметром (преобразование из long double в bMoney)
	// (с помощью служебного слова explicit делаем возможным использование
	// конструктора только в виде конструктора, а не для неявных преобразований)
	explicit bMoney(long double n) : sum(n)
		{ }
	bMoney(const wchar_t s[]) // конструктор с одним параметром (денежная строка)
		{ mstold(s); }
	// метод преобразует денежную строку в число типа long double
	long double mstold(const wchar_t []); // прототип
	// метод преобразует число типа long double (sum) в денежную строку и
	// возвращает эту строку через первый параметр
	void ldtoms(wchar_t []); // прототип
	// метод для получения денежной строки от пользователя с клавиатуры
	// и сохранения ее в поле sum класса
	void getmoney()
	{
		wchar_t tms[80]; // для строки с денежной суммой
		wcout << L"Введите денежную сумму (пример: '$1,234,567.99'):\n";
		wcin >> tms; // получаем денежную строку
		mstold(tms); // преобразуем денежную строку в long double и сохраняем в sum
	}
	// метод для вывода поля sum класса на экран в виде денежной строки
	void putmoney()
	{
		wchar_t tms[80]; // для строки с денежной суммой
		ldtoms(tms);     // преобразуем поле sum класса (long double) в денежную строку
		wcout << tms;    // выводим денежную строку на экран
	}
	// операция сложения двух объектов класса
	bMoney operator+ (bMoney m) const
		// используем конструктор с одним параметром для преобразования long double в bMoney
		{ return bMoney(sum + m.sum); }
	// операция нахождения разности двух объектов класса
	bMoney operator- (bMoney m) const
		{ return bMoney(sum - m.sum); }
	// операция нахождения произведения объекта класса и числа типа long double
	bMoney operator* (long double n) const
		{ return bMoney(sum * n); }
	// операция нахождения частного от деления объекта класса на другой объект класса
	long double operator/ (bMoney m) const
		{ return sum / m.sum; }
	// операция нахождения частного от деления объекта класса на число типа long double
	bMoney operator/ (long double n) const
		{ return bMoney(sum / n); }
	// дружественный для класса bMoney оператор для обработки выражений вида long double * bMoney
	friend bMoney operator* (long double, bMoney); // прототип
	// дружественный для класса bMoney оператор для обработки выражений вида long double / bMoney
	friend long double operator/ (long double, bMoney); // прототип
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	wchar_t ans;         // для ответа пользователя о продолжении ввода (д/н)
	bMoney m1, m2, mres; // для двух денежных сумм и результата операций
	long double n, res;  // для вещественного числа и результата операций

	// работаем в цикле, чтобы можно было выполнить операции для разных исходных данных
	do {
		
		// запрашиваем у пользователя исходные данные
		wcout << L"1. "; m1.getmoney();
		wcout << L"2. "; m2.getmoney();
		wcout << L"3. Введите вещественное число: "; wcin >> n; wcout << endl;

		// выполняем пять перегруженных операций и выводим результаты на экран
		mres = m1 + m2; wcout << L"1. m1 + m2 = "; mres.putmoney(); wcout << endl;
		mres = m1 - m2; wcout << L"2. m1 - m2 = "; mres.putmoney(); wcout << endl;
		mres = m1 * n;  wcout << L"3. m1 * n  = "; mres.putmoney(); wcout << endl;
		res  = m1 / m2; wcout << L"4. m1 / m2 = " << res << endl;
		mres = m1 / n;  wcout << L"5. m1 / n  = "; mres.putmoney(); wcout << endl;

		// на описанные ниже две закомментированные операции компилятор должен выдавать ошибку
		// (они не имеют смысла в рамках концепции класса bMoney, представляющего денежную сумму)

		// нет смысла в произведении денежных сумм:
		// например, если 5 м * 20 м = 100 кв.м., где 100 кв.м. — это площадь прямоугольника,
		// то 5 руб. * 20 руб. = 100 кв.руб. — нет сущностей, измеряющихся в квадратных рублях!
		// mres = m1 * m2; // Операция умножения с такими типами операндов не определена в классе bMoney.
		                   // Конечно, можно ее определить, но нам этого не нужно.
		                   // Также можно определить операцию преобразования bMoney в long double,
		                   // но нам этого тоже не нужно.

		// нет смысла в сложении денежной суммы (к примеру, стоимости деталей) и числа (деталей)
		// mres = m1 + n; // Операция сложения с такими типами операндов не определена в классе bMoney.
		                  // Если убрать служебное слово explicit из заголовка конструктора с одним
		                  // параметром, то данное выражение будет работать, но нам этого не нужно.

		// на описанные ниже две закомментированные операции компилятор уже не выдает ошибку,
		// так как были написаны соответствующие перегружающие дружественные операции

		// это просто перемена сомножителей в работающей выше операции mres = m1 * n;
		// она бы работала без написания отдельной дружественной операции, если б были определены
		// операции преобразования bMoney <-> long double, но по условиям задания операции
		// преобразования должны быть отключены
		mres = n * m1;  wcout << L"6. n * m1  = "; mres.putmoney(); wcout << endl;

		// Непонятно, какой смысл у этой операции (какой смысл в делении, к примеру, количества
		// деталей на некую денежную сумму?). Будем считать, что подразумевается, что n — это
		// тоже денежная сумма, только в виде вещественного числа, а не объекта класса bMoney.
		// Тогда отдельная для этой операции дружественная функция должна делать то же, что и
		// перегруженная операция bMoney / bMoney = long double.
		res = n / m1;   wcout << L"7. n / m1 = " << res << endl << endl;

		wcout << L"Попробовать с другими исходными данными (д/н)? "; wcin >> ans; wcout << endl;
	} while (ans != L'н');

	return 0;
}

// дружественный для класса bMoney оператор для обработки выражений вида long double * bMoney
bMoney operator* (long double n, bMoney m)
	{ return bMoney(n * m.sum); }

// дружественный для класса bMoney оператор для обработки выражений вида long double / bMoney
long double operator/ (long double n, bMoney m)
	{ return n / m.sum; }

// метод преобразует заданную строку в число типа long double и возвращает это число;
// предполагается, что заданная строка представляет денежную сумму,
// например, "$1,234,567,890,123.99";
// mstold расшифровывается как "money string to long double"
long double bMoney::mstold(const wchar_t str[])
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

// метод преобразует число типа long double (поле sum класса bMoney) в денежную строку
// и возвращает эту строку через первый параметр
void bMoney::ldtoms(wchar_t str[])
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

	if (len > 6) // если в числе требуются разделители
	{
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