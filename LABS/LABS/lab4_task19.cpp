/*--------------------------------------------------------------------------------------------------
	Задание: Имеется сеть автомобильных дорог. По  некоторым дорогам
	можно  проехать  только  в одном  направлении. Известна  длина
	каждой дороги, причем она может быть разной в  зависимости  от
	направления. С помощью алгоритма Дейкстры найти цикл минимальной
	длины из заданного города (9).

	Автор: Ковалев Владислав ПС-21
	Среда выполнение: Visual Studio 2022
--------------------------------------------------------------------------------------------------*/

#include "lab4.h"

#include <cstdlib>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <fstream>

struct Line
{
	Line(std::string endPoint, int length) : endPoint(endPoint), length(length) {}

	std::string endPoint;
	int length;

	bool operator==(const Line& other) const
	{
		return endPoint == other.endPoint && length == other.length;
	}

	bool operator<(const Line& other) const
	{
		return length < other.length;
	}
};

using Node = std::string;
using Graph = std::unordered_map<Node, std::vector<Line>>;

using Distances = std::unordered_map<Node, int>;
using Path = std::unordered_map<Node, Node>;
using Cycle = std::vector<Node>;

struct Result
{
	Result(int length, Cycle cycle) : length(length), cycle(cycle) {}

	int length;
	Cycle cycle;
};

static Result findShortestCycle(const Graph& graph, const Node& start)
{
	Distances distances;
	Path path;
	
	Cycle cycle;
	int shortestCycleLen = INT_MAX;

	for (const auto& node : graph)
	{
		distances[node.first] = INT_MAX;
	}
	distances[start] = 0;

	std::priority_queue<Line, std::vector<Line>> queue;
	queue.push(Line(start, 0));

	while (!queue.empty())
	{
		Line currLine = queue.top();
		queue.pop();

		if (currLine.length > distances[currLine.endPoint]) continue;

		for (const auto& edge : graph.at(currLine.endPoint))
		{
			int newDistance = currLine.length + edge.length;

			if (newDistance < distances[edge.endPoint])
			{
				distances[edge.endPoint] = newDistance;
				path[edge.endPoint] = currLine.endPoint;
				queue.push(Line(edge.endPoint, newDistance));
			}

			if (edge.endPoint == start && newDistance < shortestCycleLen)
			{
				shortestCycleLen = newDistance;

				cycle = { start };
				Node current = currLine.endPoint;
				while (current != start)
				{
					cycle.push_back(current);
					current = path[current];
				}
				cycle.push_back(start);
				std::reverse(cycle.begin(), cycle.end());
			}
		}
	}

	return Result(shortestCycleLen, cycle);
}

static void printToConsole(Result result)
{
	if (result.length == INT_MAX)
	{
		std::cout << "Цикл из заданного города не найден" << std::endl;
	}
	else
	{
		std::cout << "Минимальная длина цикла: " << result.length << std::endl;
		std::cout << "Путь: " << std::endl;
		for (size_t i = 0; i < result.cycle.size(); ++i)
		{
			std::cout << result.cycle[i] << (i == result.cycle.size() - 1 ? "" : "->");
		}
		std::cout << std::endl;
	}
}

static void printToFile(const std::string& inputName, Result result)
{
	std::string outFileName("cycle(" + inputName + ").txt");

	std::ofstream outFile(outFileName);
	if (outFile.is_open())
	{
		std::cout << "Данные сохранены в " << outFileName << std::endl;
		if (result.length == INT_MAX)
		{
			outFile << "Цикл из заданного города не найден" << std::endl;
			return;
		}
		outFile << "Минимальная длина цикла: " << result.length << std::endl;
		outFile << "Путь: " << std::endl;
		size_t cycleLen = result.cycle.size();
		for (size_t i = 0; i < cycleLen; ++i)
		{
			outFile << result.cycle[i] << (i == cycleLen - 1 ? "" : "->");
		}
	}
	else
	{
		std::cerr << "Не удалось открыть файл для записи" << std::endl;
	}

	outFile << std::endl;
	outFile.close();
}

int shortestGraphCycle()
{
	std::string inFileName;
	std::cout << "Введите имя входного файла" << std::endl;
	std::cin >> inFileName;

	std::ifstream file(inFileName);
	if (!file.is_open())
	{
		std::cerr << "Не удалось открыть файл" << std::endl;
		return EXIT_FAILURE;
	}

	Graph graph;
	Node from, to;
	int length;

	while (file >> from >> to >> length)
	{
		graph[from].push_back(Line(to, length));
		if (graph.find(to) == graph.end())
		{
			graph[to] = {};
		}
	}

	Node start;
	std::cout << "Укажите начальный город" << std::endl;
	std::cin >> start;

	if (graph.find(start) == graph.end())
	{
		std::cerr << "Указанного города не существует" << std::endl;
		return EXIT_FAILURE;
	}

	Result result = findShortestCycle(graph, start);

	printToConsole(result);
	printToFile(inFileName, result);

	return EXIT_SUCCESS;
}