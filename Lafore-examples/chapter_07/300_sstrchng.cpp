﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// sstrchng.cpp
// изменение частей строки с помощью стандартного класса string

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <string> // для стандартного класса string в языке C++
using namespace std;

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	wstring s1(L"Все хорошо, прекрасная маркиза.");
	wstring s2(L"принцесса");
	wstring s3(L"Приветствую, ");

	// метод erase удаляет часть строки s1, начиная с символа с индексом 0,
	// 12 — это количество удаляемых символов
	s1.erase(0, 12);            // убираем "Все хорошо, "

	// теперь s1 = "прекрасная маркиза."
	
	// метод replace заменяет часть строки s1, начиная с символа с индексом 11,
	// 7 — максимальное число символов в строке s1, которое должно быть заменено,
	// s2 — подстрока, которой должны быть заменены 7 (или меньше) символов из строки s1
	s1.replace(11, 7, s2);      // заменяем "маркиза" на "принцесса"
	
	// теперь s1 = "прекрасная принцесса."

	// метод insert вставляет подстроку s3 в строку s1 перед символом с индексом 0,
	// то есть в начало строки s1
	s1.insert(0, s3);           // вставляем "Приветствую, "

	// теперь s1 = "Приветствую, прекрасная принцесса."
	
	// метод size возвращает длину строки в символах,
	// индекс s1.size() - 1 указывает на последний символ в строке, так как
	// нумерация символов начинается с нуля,
	// второй параметр, равный 1, как уже указывалось выше, это количество удаляемых символов
	s1.erase(s1.size() - 1, 1); // убираем '.'

	// теперь s1 = "Приветствую, прекрасная принцесса"
	
	// метод append добавляет 3 символа (первый параметр), указанных во втором параметре,
	// в конец строки s1
	s1.append(3, L'!');         // добавляем '!!!'

	// теперь s1 = "Приветствую, прекрасная принцесса!!!"
	
	int x = s1.find(L' ');      // ищем первый пробел
	while (x < s1.size())       // продолжать цикл, пока пробелы находятся
	{
		// двойные кавычки при задании подстроки L"/" в методе replace
		// обязательны, так как третий параметр метода может принимать только строки, а не символы
		s1.replace(x, 1, L"/"); // заменяем пробел на '/'
		x = s1.find(L' ');      // ищем следующий пробел
	}

	wcout << L"s1 = \"" << s1 << L"\"" << endl;

	return 0;
}