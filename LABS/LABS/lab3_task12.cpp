/*--------------------------------------------------------------------------------------------------
Задание: Имеется дерево, корень которого соответствует
основателю  рода.  Сыновья  каждой  вершины  задают  сыновей и
дочерей  соответствующего  человека.  Указываются  имена  двух
человек  (например,  А  и  В).  Сообщить,  какая  из следующих
ситуаций имеет место:
   1) А предок В;
   2) В предок А;
   3) А и В имеют ближайшего общего предка С (9).

Автор: Ковалев Владислав ПС-21
Среда выполнение: Visual Studio 2022
--------------------------------------------------------------------------------------------------*/

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING

#include "lab3.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <locale>
#include <codecvt>

struct TreeNode
{
	std::wstring name;
	TreeNode* parent;
	std::vector<std::unique_ptr<TreeNode>> children;

	TreeNode(std::wstring name) : name(name), parent(nullptr) {}
};

typedef std::unique_ptr<TreeNode> NodePtr;

static bool IsAncestor(const TreeNode* ancestor, const TreeNode* descendant)
{
	while (descendant)
	{
		if (descendant == ancestor)
		{
			return true;
		}
		descendant = descendant->parent;
	}
	return false;
}

static int GetDepth(const TreeNode* node)
{
	int depth = 0;
	while (node)
	{
		depth++;
		node = node->parent;
	}
	return depth;
}

static const TreeNode* FindCommonAncestor(const TreeNode* first, const TreeNode* second) 
{
	int firstDepth = GetDepth(first);
	int secondDepth = GetDepth(second);

	while (firstDepth > secondDepth) 
	{
		first = first->parent;
		firstDepth--;
	}

	while (secondDepth > firstDepth) 
	{
		second = second->parent;
		secondDepth--;
	}

	while (first && second)
	{
		if (first == second)
		{
			return first;
		}

		first = first->parent;
		second = second->parent;
	}

	return nullptr;
}

static int GetElementDepth(const std::wstring& line)
{
	return std::count(line.begin(), line.end(), L'-');
}

static NodePtr CreateTree(std::wifstream& file)
{
	file.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
	if (!file.is_open())
	{
		throw std::runtime_error("Не удалось открыть файл ");
	}

	NodePtr root = nullptr;
	std::vector<std::pair<int, TreeNode*>> stack;

	std::wstring line;
	while (std::getline(file, line))
	{
		int depth = GetElementDepth(line);
		line.erase(0, depth);

		if (line.empty())
		{
			continue;
		}

		NodePtr newNode = std::make_unique<TreeNode>(line);

		if (!root)
		{
			root = std::move(newNode);
			stack.push_back({ depth, root.get() });
		}
		else
		{
			while (!stack.empty() && stack.back().first >= depth)
			{
				stack.pop_back();
			}

			TreeNode* parent = stack.back().second;

			parent->children.push_back(std::move(newNode));

			parent->children.back()->parent = parent;

			stack.push_back({ depth, parent->children.back().get() });
		}
	}

	return root;
}

static TreeNode* FindNode(const std::wstring& name, TreeNode* node)
{
	if (!node)
	{
		return nullptr;
	}

	if (node->name == name)
	{
		return node;
	}

	for (const auto& child : node->children)
	{
		TreeNode* result = FindNode(name, child.get());
		if (result)
		{
			return result;
		}
	}

	return nullptr;
}

int familyTreeSearch(std::wifstream& input, const std::wstring& firstName, const std::wstring& secondName)
{
	try
	{
		NodePtr root = CreateTree(input);

		TreeNode* first = FindNode(firstName, root.get());
		TreeNode* second = FindNode(secondName, root.get());

		if (!first)
		{
			std::wcout << L"Не удалось найти человека с именем " << firstName << std::endl;
			return EXIT_FAILURE;
		}

		if (!second)
		{
			std::wcout << L"Не удалось найти человека с именем " << secondName << std::endl;
			return EXIT_FAILURE;
		}

		if (IsAncestor(first, second))
		{
			std::wcout << first->name << L" предок " << second->name << std::endl;
		}
		else if (IsAncestor(second, first))
		{
			std::wcout << second->name << L" предок " << first->name << std::endl;
		}
		else
		{
			const TreeNode* commonAncestor = FindCommonAncestor(first, second);
			if (commonAncestor)
			{
				std::wcout << commonAncestor->name << L" - общий предок " << first->name << L" и " << second->name << std::endl;
			}
		}
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}