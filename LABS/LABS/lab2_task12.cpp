/*--------------------------------------------------------------------------------------------------
	Задание: В файле заданы N упорядоченных по  возрастанию  списков
	целых чисел. Организовать  в  оперативной  памяти  с  помощью
	указателей N линейных списков и слить их в общий список. (8)

	Автор: Ковалев Владислав ПС-21
	Среда выполнения: Visual Studio 2022
*//*------------------------------------------------------------------------------------------------
	В файле n строк, в которых числа отсортированы по возрастанию.
	Длинна строк может быть разной, но чиста в них всегда отсортированы в порядке возрастания.
	Нужно из каждой строки организовать связный список.
	Далее нужно вывести упорядоченную последовательность чисел из всего файла.
	Алгоритм:
	1) сравниваем каждую строку с каждой
	2) находим минимальный первый элемент из всех строк
	3) записываем его
	4) в строке, в который мы нашли этот символ смещаемся на 1 шаг
	5) повторять до победного (пока все числа не кончатся)
--------------------------------------------------------------------------------------------------*/

#include "lab2.h"

enum MenuOptions
{
	SELECT_FILE = 1,
	SHOW_FILE,
	SORT,
	EXIT
};

enum KeyCodes
{
	ENTER = 13,
	ARROW_UP = 72,
	ARROW_DOWN = 80,
	ARROW_LEFT = 75,
	ARROW_RIGHT = 77,
	SPECIAL_CODE = 224,
};

enum ErrorCodes
{
	PROGRAM_ERROR,
	INPUT_FILE_OPEN_ERROR,
	OUTPUT_FILE_OPEN_ERROR,
};

struct ListNode {
	int value;
	ListNode* next;

	ListNode(int val) : value(val), next(nullptr) {}
};

struct HeapNode {
	int value;
	size_t listIndex;
	ListNode* node;

	bool operator>(const HeapNode& other) const
	{
		return value > other.value;
	}
};

void append(ListNode*& head, int value) {
	if (!head)
	{
		head = new ListNode(value);
	}
	else
	{
		ListNode* temp = head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new ListNode(value);
	}
}

bool isSortedAndNumeric(const std::string& line, size_t lineNumber) {
	std::istringstream iss(line);
	int prev = MININT;
	int current;

	while (iss >> current)
	{
		if (current < prev)
		{
			std::cout << "Ошибка: Строка " << lineNumber << " не отсортирована." << std::endl;
			return false;
		}
		prev = current;
	}

	for (char ch : line) {
		if (!std::isdigit(ch) && ch != ' ' && ch != '-')
		{
			std::cout << "Ошибка: Строка " << lineNumber << " содержит нечисловые символы." << std::endl;
			return false;
		}
	}

	return true;
}

bool checkFile(std::ifstream& file) {
	std::string line;
	size_t lineNumber = 1;
	bool allCorrect = true;

	while (std::getline(file, line) && allCorrect)
		if (isSortedAndNumeric(line, lineNumber))
		{
			++lineNumber;
		}
		else
		{
			allCorrect = false;
		}

	return allCorrect;
}

std::vector<ListNode*> createListsFromFile(std::ifstream& inFile) {
	std::vector<ListNode*> lists;

	std::string line;
	while (std::getline(inFile, line))
	{
		ListNode* head = nullptr;
		std::stringstream iss(line);
		int number;

		while (iss >> number)
		{
			append(head, number);
		}

		lists.push_back(head);
	}

	return lists;
}

void mergeLists(const std::vector<ListNode*>& lists, std::ofstream& outFile) {
	auto start = std::chrono::high_resolution_clock::now();

	std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<>> minHeap;

	for (size_t i = 0; i < lists.size(); ++i)
	{
		if (lists[i])
		{
			minHeap.push({ lists[i]->value, i, lists[i] });
		}
	}

	while (!minHeap.empty())
	{
		HeapNode top = minHeap.top();
		minHeap.pop();

		outFile << top.value << " ";

		if (top.node->next)
		{
			minHeap.push({ top.node->next->value, top.listIndex, top.node->next });
		}
	}

	outFile << std::endl;

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;

	std::cout << "Время работы программы: " << duration.count() << " с" << std::endl;
}

void freeLists(const std::vector<ListNode*>& lists) {
	for (ListNode* head : lists)
	{
		while (head)
		{
			ListNode* temp = head;
			head = head->next;
			delete temp;
		}
	}
}

void setCursorPosition(int x, int y);
void renderMenu(int selectedOption);
void showError(int code);
void updateMenuSelection(int previousOption, int currentOption);
void exitOption(int selectedOption);

int linkedListsMerge()
{
	int selectedOption = 1;
	int previousOption = 1;

	std::ifstream inputFile;
	std::ofstream outputFile;

	std::string inFileName = "";
	std::string outFileName = "";

	std::vector<ListNode*> lists;

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
				if (selectedOption > SELECT_FILE)
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
					selectedOption = SELECT_FILE;
				}
			}
		}
		if (key == ENTER) {
			switch (selectedOption)
			{
			case SELECT_FILE:
				system("cls");
				std::cout << "Введите название входного и выходного файла: ";
				std::cin >> inFileName >> outFileName;

				std::cout << std::endl << "Операция прошла успешно" << std::endl;
				exitOption(selectedOption);

				break;
			case SHOW_FILE:
				if (inFileName != "")
				{
					system(("start " + std::string(inFileName)).c_str());
				}
				else
				{
					system("cls");
					std::cout << "Файл не выбран." << std::endl;
					exitOption(selectedOption);
				}

				break;
			case SORT:
				system("cls");

				inputFile.open(inFileName);
				if (inputFile.is_open() == false)
				{
					showError(INPUT_FILE_OPEN_ERROR);
					exitOption(selectedOption);

					break;
				}

				std::cout << "Проверка файла..." << std::endl;
				if (checkFile(inputFile) == false)
				{
					exitOption(selectedOption);

					break;
				}
				std::cout << "Файл успешно прошёл проверку." << std::endl;

				std::cout << std::endl << "Сортируем..." << std::endl;
				lists = createListsFromFile(inputFile);
				if (lists.empty())
				{
					std::cout << "Файл не выбран." << std::endl;
					exitOption(selectedOption);

					break;
				}

				mergeLists(lists, outputFile);
				freeLists(lists);

				inputFile.close();
				outputFile.close();

				std::cout << "Программа успешно завершила работу" << std::endl;

				system(("start " + std::string(outFileName)).c_str());

				exitOption(selectedOption);

				break;
			case EXIT:
				inputFile.close();
				outputFile.close();

				return EXIT_SUCCESS;
			}
		}
		updateMenuSelection(previousOption, selectedOption);
	}
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
	std::cout << "  ";

	setCursorPosition(0, currentOption);
	std::cout << "->";
}

void renderMenu(int selectedOption)
{
	std::cout << "==== [Вывод всех чисел в файле в порядке возрастания] ====" << std::endl;
	std::cout << "  1. Указать входной и выходной файлы" << std::endl;
	std::cout << "  2. Показать содержимое входного файла" << std::endl;
	std::cout << "  3. Сортировка файла" << std::endl;
	std::cout << "  4. Выход" << std::endl;

	setCursorPosition(0, selectedOption);
	std::cout << "->";
}

void exitOption(int selectedOption)
{
	system("pause");
	system("cls");
	renderMenu(selectedOption);
}

void showError(int code)
{
	switch (code)
	{
	case PROGRAM_ERROR:
		std::cout << "Выполняемая программа завершилась с ошибкой" << std::endl;
		return;
	case INPUT_FILE_OPEN_ERROR:
		std::cout << "Входной файл не существует или находится в другом месте" << std::endl;
		return;
	case OUTPUT_FILE_OPEN_ERROR:
		std::cout << "Возникли проблемы с созданием выходного файла" << std::endl;
		return;
	default:
		std::cout << "Ошибки с таким кодом не существует" << std::endl;
		return;
	}
	std::cout << std::endl << "Программа завершила работу с ошибкой" << std::endl;
}