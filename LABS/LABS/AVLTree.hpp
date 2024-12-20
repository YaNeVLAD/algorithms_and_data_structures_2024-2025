#pragma once

#include <vector>
#include <iostream>

template<typename T>
class AVLTree {
public:
    struct Node
    {
        T key;
        size_t height;
        Node* left;
        Node* right;

        Node(T value) : key(value), height(1), left(nullptr), right(nullptr) {}
    };
    using node_ptr = Node*;

    AVLTree() {}

    void Insert(T key)
    {
        m_root = InsertR(m_root, key);
    }

    void Insert(const std::vector<T>& keys)
    {
        for (const auto& key : keys)
        {
            m_root = InsertR(m_root, key);
        }
    }

    void Replace(T oldKey, T newKey)
    {
        m_root = RemoveR(m_root, oldKey);
        m_root = InsertR(m_root, newKey);
    }

    void Remove(T key)
    {
        m_root = RemoveR(m_root, key);
    }

    void Clear()
    {
        ClearR(m_root);
        m_root = nullptr;
    }

    node_ptr Root() { return m_root; }

private:
    node_ptr m_root = nullptr;

    size_t Height(node_ptr node) const
    {
        return node ? node->height : 0;
    }

    size_t MaxHeight(node_ptr node) const
    {
        return std::max(Height(node->left), Height(node->right)) + 1;
    }

    int Balance(node_ptr node) const
    {
        return node ? (Height(node->left) - Height(node->right)) : 0;
    }

    node_ptr RotateRight(node_ptr y)
    {
        node_ptr x = y->left;
        node_ptr T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = MaxHeight(y);
        x->height = MaxHeight(x);

        return x;
    }

    node_ptr RotateLeft(node_ptr x)
    {
        node_ptr y = x->right;
        node_ptr T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = MaxHeight(x);
        y->height = MaxHeight(y);

        return y;
    }

    node_ptr BalanceTree(node_ptr node)
    {
        node->height = MaxHeight(node);
        int balance = Balance(node);

        if (balance > 1 && Balance(node->left) >= 0)
            return RotateRight(node);

        if (balance > 1 && Balance(node->left) < 0)
        {
            node->left = RotateLeft(node->left);
            return RotateRight(node);
        }

        if (balance < -1 && Balance(node->right) <= 0)
            return RotateLeft(node);

        if (balance < -1 && Balance(node->right) > 0)
        {
            node->right = RotateRight(node->right);
            return RotateLeft(node);
        }

        return node;
    }

    node_ptr InsertR(node_ptr node, T key)
    {
        if (node == nullptr)
            return new Node(key);

        if (key < node->key)
        {
            node->left = InsertR(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = InsertR(node->right, key);
        }
        else
        {
            return node;
        }

        return BalanceTree(node);
    }

    node_ptr MinValueNode(node_ptr node)
    {
        node_ptr current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    node_ptr RemoveR(node_ptr node, T key)
    {
        if (node == nullptr)
            return node;

        if (key < node->key)
        {
            node->left = RemoveR(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = RemoveR(node->right, key);
        }
        else
        {
            if (node->left == nullptr || node->right == nullptr)
            {
                node_ptr temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }

            node_ptr temp = MinValueNode(node->right);
            node->key = temp->key;
            node->right = RemoveR(node->right, temp->key);
        }

        node->height = MaxHeight(node);
        return BalanceTree(node);
    }

    void ClearR(node_ptr node)
    {
        if (node == nullptr) return;

        ClearR(node->left);
        ClearR(node->right);
        delete node;
    }
};