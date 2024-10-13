/*--------------------------------------------------------------------------------------------------
	�������: � ����� ������ N ������������� ��  �����������  �������
	����� �����. ������������  �  �����������  ������  �  �������
	���������� N �������� ������� � ����� �� � ����� ������. (8)
   
	�����: ������� ��������� ��-21
	����� ����������: Visual Studio 2022
*//*------------------------------------------------------------------------------------------------
	� ����� n �����, � ������� ����� ������������� �� �����������.
	������ ����� ����� ���� ������, �� ����� � ��� ������ ������������� � ������� �����������.
	����� �� ������ ������ ������������ ������� ������.
	����� ����������� �������� ����� ������� ������������� ������������������ ����� ����� �����.
	��������:
	1) ���������� ������ ������ � ������
	2) ������� ����������� ������ ������� �� ���� �����
	3) ���������� ���
	4) � ������, � ������� �� ����� ���� ������ ��������� �� 1 ���
	5) ��������� �� ��������� (���� ��� ����� �� ��������)
--------------------------------------------------------------------------------------------------*/

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
	SHOW_FILE,
	SORT,
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
			case SHOW_FILE: break;
			case SORT: break;
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
	cout << "==== [���������� � ������� ����������� ����� � �����] ====" << std::endl;
	cout << "  1. ������� ������� ����" << std::endl;
	cout << "  2. ������� ������� ����" << std::endl;
	cout << "  3. �������� ������ � ����" << std::endl;
	cout << "  5. �������� ���������� �����" << std::endl;
	cout << "  7. ���������� �����" << std::endl;
	cout << "  8. �����" << std::endl;

	setCursorPosition(0, selectedOption);
	cout << "->";
}