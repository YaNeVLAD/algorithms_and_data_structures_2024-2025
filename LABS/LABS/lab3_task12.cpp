/*
�������: ������� ������, ������ �������� �������������
����������  ����.  �������  ������  �������  ������  ������� �
�������  ����������������  ��������.  �����������  �����  ����
�������  (��������,  �  �  �).  ��������,  �����  �� ���������
�������� ����� �����:
   1) � ������ �;
   2) � ������ �;
   3) � � � ����� ���������� ������ ������ � (9).

�����: ������� ��������� ��-21
����� ����������: Visual Studio 2022
*/

#include "lab3.h"

#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>

struct TreeNode
{
	std::string name;
	TreeNode* parent;
	std::vector<std::unique_ptr<TreeNode>> children;

	TreeNode(std::string name) : name(name), parent(nullptr) {}
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

static std::vector<const TreeNode*> GetPathToRoot(const TreeNode* node)
{
	std::vector<const TreeNode*> path;
	while (node)
	{
		path.push_back(node);
		node = node->parent;
	}
	return path;
}

static const TreeNode* FindCommonAncestor(const TreeNode* first, const TreeNode* second) 
{
	std::unordered_set<const TreeNode*> firstAncestors;

	while (first) 
	{
		firstAncestors.insert(first);
		first = first->parent;
	}

	while (second) 
	{
		if (firstAncestors.contains(second)) 
		{
			return second;
		}
		second = second->parent;
	}

	return nullptr;
}

static int GetElementDepth(const std::string& line)
{
	return std::count(line.begin(), line.end(), '-');
}

static NodePtr CreateTree(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("�� ������� ������� ���� " + filename);
	}

	NodePtr root = nullptr;
	std::stack<std::pair<int, TreeNode*>> stack;

	std::string line;
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
			stack.push({ depth, root.get() });
		}
		else
		{
			while (!stack.empty() && stack.top().first >= depth)
			{
				stack.pop();
			}

			TreeNode* parent = stack.top().second;

			parent->children.push_back(std::move(newNode));

			parent->children.back()->parent = parent;

			stack.push({ depth, parent->children.back().get() });
		}
	}

	return root;
}

static TreeNode* FindNode(const std::string& name, TreeNode* node)
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

int familyTreeSearch(const std::string& fileName, const std::string& firstName, const std::string& secondName)
{
	try
	{
		NodePtr root = CreateTree(fileName);

		TreeNode* first = FindNode(firstName, root.get());
		TreeNode* second = FindNode(secondName, root.get());

		if (!first || !second)
		{
			std::cout << "�� ������� ����� ����� �����" << std::endl;
			return EXIT_FAILURE;
		}

		if (IsAncestor(first, second))
		{
			std::cout << first->name << " ������ " << second->name << std::endl;
		}
		else if (IsAncestor(second, first))
		{
			std::cout << second->name << " ������ " << first->name << std::endl;
		}
		else
		{
			const TreeNode* commonAncestor = FindCommonAncestor(first, second);
			if (commonAncestor)
			{
				std::cout << commonAncestor->name << " - ����� ������ " << first->name << " � " << second->name << std::endl;
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