#pragma once

#include "AVLTree.hpp"
#include <string>
#include <vector>

template<typename T>
class TreePrinter
{
public:
	using TreeNode = AVLTree<T>::Node;

	static void PrintTree(AVLTree<T>& tree, int topMargin = 2, int leftMargin = 2)
	{
		TreeNode* root = tree.Root();
		if (root == nullptr) return;
		int rootTop = topMargin;
		std::vector<NodeInfo*> last;
		TreeNode* next = root;

		for (int level = 0; next != nullptr; ++level)
		{
			NodeInfo* item = new NodeInfo(next, std::to_string(next->key));
			if (level < last.size())
			{
				item->startPos = last[level]->endPos() + 1;
				last[level] = item;
			}
			else
			{
				item->startPos = leftMargin;
				last.push_back(item);
			}

			if (level > 0)
			{
				item->parent = last[level - 1];
				if (next == item->parent->node->left)
				{
					item->parent->left = item;
					item->setEndPos(std::max(item->endPos(), item->parent->startPos));
				}
				else
				{
					item->parent->right = item;
					item->startPos = std::max(item->startPos, item->parent->endPos());
				}
			}

			next = next->left ? next->left : next->right;
			for (; next == nullptr; item = item->parent)
			{
				print(item, rootTop + 2 * level);
				if (--level < 0) break;
				if (item == item->parent->left)
				{
					item->parent->startPos = item->endPos();
					next = item->parent->node->right;
				}
				else
				{
					if (item->parent->left == nullptr)
						item->parent->setEndPos(item->startPos);
					else
						item->parent->startPos += (item->startPos - item->parent->endPos()) / 2;
				}
			}
		}
		std::cout << "\033[" << rootTop + 2 * last.size() - 1;
	}

private:
	class NodeInfo
	{
	public:
		TreeNode* node;
		std::string text;
		size_t startPos;
		NodeInfo* parent;
		NodeInfo* left;
		NodeInfo* right;

		NodeInfo(TreeNode* n, const std::string& t)
			: node(n), text(t), startPos(0), parent(nullptr), left(nullptr), right(nullptr) {
		}

		size_t size() const { return text.length(); }

		size_t endPos() const { return startPos + size(); }

		void setEndPos(size_t endPos) { startPos = endPos - size(); }
	};

	static void print(const std::string& s, size_t top, size_t left, size_t right = -1)
	{
		std::cout << "\033[" << top << ";" << left << "H" << s;
	}

	static void printLink(size_t top, const std::string& start, const std::string& end, size_t startPos, size_t endPos)
	{
		print(start, top, startPos);
		print(" ", top, startPos + 1, endPos);
		print(end, top, endPos);
	}

	static void print(NodeInfo* item, size_t top)
	{
		print(item->text, top, item->startPos);
		if (item->left != nullptr)
			printLink(top + 1, "/", " ", item->left->startPos + item->left->size() / 2, item->startPos);
		if (item->right != nullptr)
			printLink(top + 1, " ", "\\", item->endPos() - 1, item->right->startPos + item->right->size() / 2);
	}
};
