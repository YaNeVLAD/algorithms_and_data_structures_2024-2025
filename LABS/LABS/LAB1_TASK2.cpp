//Задание: Задан текстовый файл. Переносов слов нет. Создать файл, в котором каждое слово будет записано в обратном порядке
//Автор: Ковалев Владислав ПС-21
//Среда выполнения: Visual Studio 2022

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

const int ARGUMENTS_COUNT_ERROR = 1;
const int INPUT_FILE_OPEN_ERROR = 2;
const int OUTPUT_FILE_OPEN_ERROR = 3;

void reverseWord(char* word);
void processFile(std::ifstream& input, std::ofstream& output);

void showErrorMessage(int code);

int main(int argc, char* argv[])
{
	std::ifstream inFile;
	std::ofstream outFile;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");

	if (argc <= 2)
	{
		showErrorMessage(ARGUMENTS_COUNT_ERROR);
		return EXIT_FAILURE;
	}

	inFile.open(argv[1]);
	if (inFile.is_open() == false)
	{
		showErrorMessage(INPUT_FILE_OPEN_ERROR);
		return EXIT_FAILURE;
	}

	outFile.open(argv[2]);
	if (outFile.is_open() == false)
	{
		showErrorMessage(OUTPUT_FILE_OPEN_ERROR);
		return EXIT_FAILURE;
	}

	processFile(inFile, outFile);

	inFile.close();
	outFile.close();

	system(("start " + std::string(argv[2])).c_str());

	cout << "Программа успешно завершила работу" << endl;
	return EXIT_SUCCESS;
}

void reverseWord(char* word)
{
	int len = strlen(word);
	for (int i = 0; i < len / 2; ++i) {
		char temp = word[i];
		word[i] = word[len - i - 1];
		word[len - i - 1] = temp;
	}
}

void processFile(std::ifstream& input, std::ofstream& output)
{
	char ch = 0;
	int i = 0;
	char word[255]{};

	while (input.get(ch))
	{
		if (ch == ' ' || ch == '\n')
		{
			if (i > 0)
			{
				word[i] = '\0';
				reverseWord(word);
				output << word;
				i = 0;
			}
			output << ch;
		}
		else
		{
			if (i < 255)
			{
				word[i++] = ch;
			}
		}
	}

	if (i > 0) {
		word[i] = '\0';
		reverseWord(word);
		output << word;
	}
}

void showErrorMessage(int code)
{
	switch (code)
	{
	case ARGUMENTS_COUNT_ERROR:
		cout << "Передано недостаточное количество параметров" << endl;
		cout << "После названия программы через пробел должен быть указан путь входного файла" << endl;
		cout << "После него через пробел должен быть указан путь выходного файла" << endl;
		break;
	case INPUT_FILE_OPEN_ERROR:
		cout << "Входной файл не существует или находится в другом месте" << endl;
		break;
	case OUTPUT_FILE_OPEN_ERROR:
		cout << "Возникли проблемы с созданием выходного файла" << endl;
		break;
	default:
		cout << "Ошибки с таким кодом не существует" << endl;
		return;
	}
	cout << endl << "Программа завершила работу с ошибкой" << endl;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
