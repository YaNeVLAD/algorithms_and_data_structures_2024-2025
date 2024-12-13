//*& - �������� ��������� �� �����. ��� ����� �������� � ���� ������ ������� � �� ��������� ��� ���� ���������

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>

#include "lab1.h"
#include "lab2.h"
#include "lab3.h"
#include "lab4.h"

using namespace std;

enum MenuOptions {
	REVERSE_WORDS_IN_FILE,
	LINKED_LISTS_MERGE,
	FAMILY_TREE_SEARCH,
	SHORTEST_GRAPH_CYCLE,
	EXIT
};

enum ErrorCodes {
	PROGRAM_ERROR = 0,
	INPUT_FILE_OPEN_ERROR = 1,
	OUTPUT_FILE_OPEN_ERROR = 2,
};

enum KeyCodes {
	ENTER = 13,
	ARROW_UP = 72,
	ARROW_DOWN = 80,
	ARROW_LEFT = 75,
	ARROW_RIGHT = 77,
	SPECIAL_CODE = 224,
};

void showErrorMessage(int code);

void menu(int selectedOption);

int main()
{
	int selectedOption = 0;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Russian");

	while (true)
	{
		menu(selectedOption);
		int key = _getch();
		if (key == SPECIAL_CODE)
		{
			key = _getch();
			if (key == ARROW_UP || key == ARROW_RIGHT)
			{
				if (selectedOption > REVERSE_WORDS_IN_FILE)
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
			case REVERSE_WORDS_IN_FILE:
			{
				string inputFileName, outputFileName;

				cout << "������� ����� ������ ���� � �������� � ��������� �����" << endl;
				cin >> inputFileName >> outputFileName;

				ifstream inputFile(inputFileName);
				if (inputFile.is_open() == false)
				{
					showErrorMessage(INPUT_FILE_OPEN_ERROR);
					system("pause");
					break;
				}

				ofstream outputFile(outputFileName);
				if (outputFile.is_open() == false)
				{
					showErrorMessage(OUTPUT_FILE_OPEN_ERROR);
					system("pause");
					break;
				}

				if (reverseWordsInFile(inputFile, outputFile) == EXIT_FAILURE)
				{
					showErrorMessage(PROGRAM_ERROR);
					system("pause");
					break;
				}

				inputFile.close();
				outputFile.close();

				system(("start " + string(outputFileName)).c_str());

				system("pause");
				break;
			}
			case LINKED_LISTS_MERGE:
			{
				if (linkedListsMerge() == EXIT_FAILURE)
				{
					showErrorMessage(PROGRAM_ERROR);
					system("pause");
					break;
				}

				system("pause");
				break;
			}
			case FAMILY_TREE_SEARCH:
			{
				string inputFileName;
				wstring	firstName, secondName;

				cout << "������� ���� � �������� �����" << endl;
				cin >> inputFileName;

				wifstream inputFile(inputFileName);
				if (inputFile.is_open() == false)
				{
					showErrorMessage(INPUT_FILE_OPEN_ERROR);
					system("pause");
					break;
				}

				cout << "������� ��� ����� ��� ������ � ������� ������" << endl;
				wcin >> firstName >> secondName;

				if (familyTreeSearch(inputFile, firstName, secondName) == EXIT_FAILURE)
				{
					showErrorMessage(PROGRAM_ERROR);
					system("pause");
					break;
				}

				system("pause");
				break;
			}
			case SHORTEST_GRAPH_CYCLE:
			{
				if (shortestGraphCycle() == EXIT_FAILURE)
				{
					showErrorMessage(PROGRAM_ERROR);
					system("pause");
					break;
				}

				system("pause");
				break;
			}

			case EXIT:
				return EXIT_SUCCESS;
			}
		}
	}
}

void menu(int selectedOption)
{
	system("cls");
	cout << "==== [��������� � ��������� ������] ====" << endl;
	cout << (selectedOption == REVERSE_WORDS_IN_FILE ? "-> " : "   ") << "�.1 ��������� ���� � �����" << endl;
	cout << (selectedOption == LINKED_LISTS_MERGE ? "-> " : "   ") << "�.2 ������� ������� �������" << endl;
	cout << (selectedOption == FAMILY_TREE_SEARCH ? "-> " : "   ") << "�.3 ����������� ��������� ���� �������������" << endl;
	cout << (selectedOption == SHORTEST_GRAPH_CYCLE ? "-> " : "   ") << "�.4 ���������� ����� ����������� ����� �� �������" << endl;
	cout << (selectedOption == EXIT ? "-> " : "   ") << "�����" << endl;
}

void showErrorMessage(int code)
{
	switch (code)
	{
	case PROGRAM_ERROR:
		cout << "����������� ��������� ����������� � �������" << endl;
		return;
	case INPUT_FILE_OPEN_ERROR:
		cout << "������� ���� �� ���������� ��� ��������� � ������ �����" << endl;
		return;
	case OUTPUT_FILE_OPEN_ERROR:
		cout << "�������� �������� � ��������� ��������� �����" << endl;
		return;
	default:
		cout << "������ � ����� ����� �� ����������" << endl;
		return;
	}
	cout << endl << "��������� ��������� ������ � �������" << endl;
}