//Задание: В файле заданы N упорядоченных по  возрастанию  списков
//целых чисел.Организовать  в  оперативной  памяти  с  помощью
//указателей N линейных списков и слить их в общий список. (8)
//Автор: Ковалев Владислав ПС-21
//Среда выполнения: Visual Studio 2022

#include "lab2.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>

#include <chrono>

using namespace std;

enum MenuOptions {
	CREATE_FILE = 1,
	SELECT_FILE,
	ADD_TO_FILE,
	ADD_TO_MEMORY,
	SHOW_FILE,
	SHOW_MEMORY,
	MERGE,
	EXIT
};

enum KeyCodes {
	ENTER = 13,
	ARROW_UP = 72,
	ARROW_DOWN = 80,
	ARROW_LEFT = 75,
	ARROW_RIGHT = 77,
	SPECIAL_CODE = 224,
};

void setCursorPosition(int x, int y);
void renderMenu(int selectedOption);
void updateMenuSelection(int previousOption, int currentOption);

int linkedListsMerge()
{
	int selectedOption = 1;
	int previousOption = 1;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");

	system("cls");
	renderMenu(selectedOption);

	while (true)
	{
		int key = _getch();
		if (key == SPECIAL_CODE)
		{
			key = _getch();
			if (key == ARROW_UP || key == ARROW_RIGHT)
			{
				if (selectedOption > CREATE_FILE)
				{
					previousOption = selectedOption;
					selectedOption--;
				}
				else
				{
					previousOption = selectedOption;
					selectedOption = EXIT;
				}
			}
			if (key == ARROW_DOWN || key == ARROW_LEFT)
			{
				if (selectedOption < EXIT)
				{
					previousOption = selectedOption;
					selectedOption++;
				}
				else
				{
					previousOption = selectedOption;
					selectedOption = CREATE_FILE;
				}
			}
		}
		if (key == ENTER) {
			switch (selectedOption)
			{
			case CREATE_FILE: break;
			case SELECT_FILE: break;
			case ADD_TO_FILE: break;
			case ADD_TO_MEMORY: break;
			case SHOW_FILE: break;
			case SHOW_MEMORY: break;
			case MERGE: break;
			case EXIT: return EXIT_SUCCESS; break;
			default:
				break;
			}
		}
		updateMenuSelection(previousOption, selectedOption);
	}

	return EXIT_SUCCESS;
}

void setCursorPosition(int x, int y)
{
	COORD coord{};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void updateMenuSelection(int previousOption, int currentOption)
{
	setCursorPosition(0, previousOption);
	cout << "  ";

	setCursorPosition(0, currentOption);
	cout << "->";
}

void renderMenu(int selectedOption)
{
	cout << "==== [Слияние связных списков из памяти и файла] ====" << std::endl;
	cout << "  1. Создать входной файл" << std::endl;
	cout << "  2. Указать входной файл" << std::endl;
	cout << "  3. Добавить список в файл" << std::endl;
	cout << "  4. Добавить список в оперативную память" << std::endl;
	cout << "  5. Показать содержимое файла" << std::endl;
	cout << "  6. Вывести списки из оперативной памяти" << std::endl;
	cout << "  7. Провести слияние списков" << std::endl;
	cout << "  8. Выход" << std::endl;

	setCursorPosition(0, selectedOption);
	cout << "->";
}