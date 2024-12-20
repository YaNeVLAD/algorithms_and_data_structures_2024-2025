/*--------------------------------------------------------------------------------------------------
	Задание: В файле задана  строка  из  целых  чисел  через  пробел.
	Реализовать следующие функции :
	1) построение АВЛ - дерева;
	2) добавление нового элемента с перестроением дерева;
	3) изменение значения заданного элемента с перестроением дерева;
	4) выдачу на экран АВЛ - дерева(10).

	Автор: Ковалев Владислав ПС-21
	Среда выполнение: Visual Studio 2022
--------------------------------------------------------------------------------------------------*/

#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "AVLTree.hpp"
#include "TreePrinter.hpp"

static void ShowMenu()
{
	std::cout << "\nМеню:\n";
	std::cout << "1. Ввести числа из строки\n";
	std::cout << "2. Ввести числа из файла\n";
	std::cout << "3. Сгенерировать случайное дерево\n";
	std::cout << "4. Вывести дерево\n";
	std::cout << "5. Удалить элемент\n";
	std::cout << "6. Вставить элемент\n";
	std::cout << "7. Заменить элемент\n";
	std::cout << "8. Очистить дерево\n";
	std::cout << "9. Выход\n";
	std::cout << "Выберите действие: ";
}

static void InsertFromString(AVLTree<int>& tree)
{
	std::string input;
	std::cout << "Введите числа через пробел: ";
	std::getline(std::cin, input);

	std::istringstream iss(input);
	int num;
	while (iss >> num)
	{
		tree.Insert(num);
	}
}

static void InsertFromFile(AVLTree<int>& tree)
{
	std::string filename;
	std::cout << "Введите имя файла: ";
	std::cin >> filename;
	std::cin.ignore();

	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Ошибка открытия файла!" << std::endl;
		return;
	}

	int num;
	while (file >> num)
	{
		tree.Insert(num);
	}
}

static void RemoveElement(AVLTree<int>& tree)
{
	int num;
	std::cout << "Введите число для удаления: ";
	std::cin >> num;
	tree.Remove(num);
}

static void HandleReplace(AVLTree<int>& tree)
{
	int oldNum, newNum;
	std::cout << "Введите число для замены: ";
	std::cin >> oldNum;
	std::cout << "Введите новое число: ";
	std::cin >> newNum;
	tree.Replace(oldNum, newNum);
}

static void InsertElement(AVLTree<int>& tree)
{
	int num;
	std::cout << "Введите число для вставки: ";
	std::cin >> num;
	tree.Insert(num);
}

static void GenerateRandomTree(AVLTree<int>& tree)
{
	size_t max;
	std::vector<int> vec;
	std::cout << "Введите количество элементов ";
	std::cin >> max;

	vec.resize(max);
	for (size_t i = 0; i < max; ++i)
	{
		vec[i] = i + 1;
	}
	
	std::random_device rd;
	std::mt19937_64 g(rd());

	std::shuffle(vec.begin(), vec.end(), g);

	tree.Insert(vec);
}

int avlTree() {
	AVLTree<int> tree;
	int choice;

	while (true) {
		system("cls");
		ShowMenu();
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Неверный выбор! Попробуйте снова.\n";
			system("pause");
			continue;
		}

		std::cin.ignore();

		switch (choice)
		{
		case 1:
			InsertFromString(tree);
			break;
		case 2:
			InsertFromFile(tree);
			break;
		case 3:
			GenerateRandomTree(tree);
			break;
		case 4:
			system("cls");
			TreePrinter<int>::PrintTree(tree, 5, 15);
			system("pause");
			break;
		case 5:
			RemoveElement(tree);
			break;
		case 6:
			InsertElement(tree);
			break;
		case 7:
			HandleReplace(tree);
			break;
		case 8:
			tree.Clear();
			break;
		case 9:
			std::cout << "Выход...\n";
			tree.Clear();
			return EXIT_SUCCESS;

		default:
			std::cout << "Неверный выбор! Попробуйте снова.\n";
			break;
		}
	}
	tree.Clear();
	return EXIT_SUCCESS;
}