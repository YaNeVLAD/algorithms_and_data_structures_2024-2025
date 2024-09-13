//Задание: Задан текстовый файл. Переносов слов нет. Создать файл, в котором каждое слово будет записано в обратном порядке
//Автор: Ковалев Владислав ПС-21
//Среда выполнения: Visual Studio 2022

//*& - передача указателя на адрес. Его можно изменить в ходе работы функции и он изменится для всей программы
#include "reverse_words_in_file.h"

#include <windows.h>
#include <iostream>
#include <fstream>

#include <chrono>

using namespace std;

const char SEPARATORS[] = {'\n', ' ', '/', '\\', ',', '.', ':', '&', '*', '^', '%', '$', '#', '@', '\'', '\"', '!', '?', '(', ')', '-', '+', '=', '_', ';', '№'};

bool isSeparator(char ch);
void reverseWord(string &word);
void processFile(ifstream &input, ofstream &output);
	
void showErrorMessage(int code);

int reverseWordsInFile(ifstream &inFile, ofstream &outFile)
{
	auto start = chrono::high_resolution_clock::now();

	processFile(inFile, outFile);

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	
	cout << "Время работы программы: " << duration.count() << " с" << endl;

	cout << "Программа успешно завершила работу" << endl;

	return EXIT_SUCCESS;
}

bool isSeparator(char ch)
{
	int i;
	int len = ARRAYSIZE(SEPARATORS);
	for (i = 0; i < len; i++)
	{
		if (ch == SEPARATORS[i])
		return true;
	}
	return false;

	//return isspace(ch) || ispunct(ch);
}

void reverseWord(string &word)
{
	//int len = word.length();
	//for (int i = 0; i < len / 2; ++i) {
	//	char temp = word[i];
	//	word[i] = word[len - i - 1];
	//	word[len - i - 1] = temp;
	//}

	reverse(word.begin(), word.end());
}

void processFile(ifstream &input, ofstream &output)
{
	char ch = 0;
	int i = 0;
	string word = "";

	while (input.get(ch))
	{
		if (isSeparator(ch))
		{
			if (word.empty() == false)
			{
				reverseWord(word);
				output << word;
				word.clear();	
			}
			output << ch;
		}
		else
		{
			word += ch;
		}
	}

	if (word.empty() == false) {
		reverseWord(word);
		output << word;
	}
}
