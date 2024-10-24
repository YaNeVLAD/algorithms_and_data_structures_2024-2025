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
	����� ����� ������� ������������� ������������������ ����� �� ����� �����.
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
#include <vector>
#include <conio.h>
#include <chrono>
#include <queue>
#include <cctype>

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
	int listIndex;
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
			std::cout << "������: ������ " << lineNumber << " �� �������������." << std::endl;
			return false;
		}
		prev = current;
	}

	for (char ch : line) {
		if (!std::isdigit(ch) && ch != ' ' && ch != '-')
		{
			std::cout << "������: ������ " << lineNumber << " �������� ���������� �������." << std::endl;
			return false;
		}
	}

	return true;
}

bool checkFile(std::ifstream& file) {
	std::string line;
	int lineNumber = 1;
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

void createListsFromFile(std::ifstream& inFile, std::vector<ListNode*>& lists)
{
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
}

void mergeLists(const std::vector<ListNode*>& lists, std::ofstream& outFile) {
	auto start = std::chrono::high_resolution_clock::now();

	std::priority_queue<HeapNode, std::vector<HeapNode>, std::greater<>> minHeap;

	for (int i = 0; i < lists.size(); ++i)
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

	std::cout << "����� ������ ���������: " << duration.count() << " �" << std::endl;
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

void showError(int code);

int linkedListsMerge()
{
	std::ifstream inputFile;
	std::ofstream outputFile;

	std::string inFileName;
	std::string outFileName;

	std::vector<ListNode*> lists;

	system("cls");

	std::cout << "������� �������� �������� � ��������� �����: ";
	std::cin >> inFileName >> outFileName;

	inputFile.open(inFileName);
	if (inputFile.is_open() == false)
	{
		showError(INPUT_FILE_OPEN_ERROR);

		return EXIT_FAILURE;
	}

	outputFile.open(outFileName);
	if (outputFile.is_open() == false)
	{
		showError(OUTPUT_FILE_OPEN_ERROR);

		return EXIT_FAILURE;
	}

	std::cout << "�������� �����..." << std::endl;

	if (checkFile(inputFile) == false)
	{
		showError(PROGRAM_ERROR);

		return EXIT_FAILURE;
	}
	inputFile.close();

	std::cout << "���� ������� ������ ��������." << std::endl;

	inputFile.open(inFileName);
	if (inputFile.is_open() == false)
	{
		showError(INPUT_FILE_OPEN_ERROR);

		return EXIT_FAILURE;
	}

	std::cout << std::endl << "���������..." << std::endl;

	createListsFromFile(inputFile, lists);
	if (lists.empty())
	{
		std::cout << "���� ����" << std::endl;

		return EXIT_FAILURE;
	}

	mergeLists(lists, outputFile);
	freeLists(lists);

	std::cout << "��������� ������� ��������� ������" << std::endl;

	inputFile.close();
	outputFile.close();

	system(("start " + std::string(outFileName)).c_str());

	return EXIT_SUCCESS;
}

void showError(int code)
{
	switch (code)
	{
	case PROGRAM_ERROR:
		std::cout << "����������� ��������� ����������� � �������" << std::endl;
		return;
	case INPUT_FILE_OPEN_ERROR:
		std::cout << "������� ���� �� ���������� ��� ��������� � ������ �����" << std::endl;
		return;
	case OUTPUT_FILE_OPEN_ERROR:
		std::cout << "�������� �������� � ��������� ��������� �����" << std::endl;
		return;
	default:
		std::cout << "������ � ����� ����� �� ����������" << std::endl;
		return;
	}
	std::cout << std::endl << "��������� ��������� ������ � �������" << std::endl;
}