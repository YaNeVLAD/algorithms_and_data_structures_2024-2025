#include "lab2.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>

#include <chrono>

using namespace std;

enum MenuOptions {
	CREATE_FILE,
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

void renderMenu(int selectedOption)
{
	system("cls");
	cout << "====================================";
	cout << (selectedOption == CREATE_FILE ? "-> " : "   ") << "1. Создать входной файл" << endl;
	cout << (selectedOption == SELECT_FILE ? "-> " : "   ") << "2. Указать входной файл" << endl;
	cout << (selectedOption == ADD_TO_FILE ? "-> " : "   ") << "3. Добавить список в файл" << endl;
	cout << (selectedOption == ADD_TO_MEMORY ? "-> " : "   ") << "4. Добавить список в оперативную память" << endl;
	cout << (selectedOption == SHOW_FILE ? "-> " : "   ") << "5. Показать содержимое файла" << endl;
	cout << (selectedOption == SHOW_MEMORY ? "-> " : "   ") << "6. Вывести списки из оперативной памяти" << endl;
	cout << (selectedOption == MERGE ? "-> " : "   ") << "7. Провести слияние списков" << endl;
	cout << (selectedOption == EXIT ? "-> " : "   ") << "8. Выход" << endl;
}

int linkedListsMerge()
{
	int selectedOption = 0;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");

	while (true)
	{
		renderMenu(selectedOption);

		int key = _getch();
		if (key == SPECIAL_CODE)
		{
			key = _getch();
			if (key == ARROW_UP || key == ARROW_RIGHT)
			{
				if (selectedOption > CREATE_FILE)
				{
					selectedOption--;
				}
				else
				{
					selectedOption = EXIT;
				}
			}
			if (key == ARROW_DOWN || key == ARROW_LEFT)
			{
				if (selectedOption < EXIT)
				{
					selectedOption++;
				}
				else
				{
					selectedOption = 0;
				}
			}
		}
		if (key == ENTER) {
			switch (selectedOption)
			{
			case 0: break;
			case 1: break;
			case 2: break;
			case 3: break;
			case 4: break;
			case 5: break;
			case 6: break;
			case 7: 
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_SUCCESS;
}