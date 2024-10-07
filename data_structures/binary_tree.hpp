#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <cstddef>
#include <algorithm>
#include <stdexcept>

#include "data_structure.h"

using namespace std;

template <typename T>
class BinaryTreeNode
{
public:
    BinaryTreeNode(const T& value, BinaryTreeNode<T>* parent = nullptr);

    T value;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;
    BinaryTreeNode<T>* parent;
};

template <typename T>
class BinaryTree : public DataStructure<T>
{
public:
    BinaryTree();

    T* to_array_preorder() const;
    void traceroute_recursive_preorder(BinaryTreeNode<T>* node, vector<T>& values) const;
    T* to_array_inorder() const;
    void traceroute_recursive_inorder(BinaryTreeNode<T>* node, vector<T>& values) const;
    T* to_array_postorder() const;
    void traceroute_recursive_postorder(BinaryTreeNode<T>* node, vector<T>& values) const;

    void traceroute_node(T value) const;

    void add_node(T value);
    void remove_node(T value);
    void clear();
    void clear(BinaryTreeNode<T>* node);

    void balance_by_inorder();
    void inorder_balance();
    void balance_recursive(T* data, int left, int right);

    size_t size() const override { return sz; }
    bool is_empty() const override { return sz > 0 ? false : true; };
    bool contains(const T& value) const override { return contains(value, root); };

    T* to_array() const override { return to_array_inorder(); };

private:
    void add_node(T value, BinaryTreeNode<T>* parent);
    void remove_node(T value, BinaryTreeNode<T>* current_node);
    void traceroute_node(T value, BinaryTreeNode<T>* parent) const;
    bool contains(T value, BinaryTreeNode<T>* parent) const;
    void clear_recursive(BinaryTreeNode<T>* node, vector<BinaryTreeNode<T>* >& nodes);

private:
    BinaryTreeNode<T>* root;
    BinaryTreeNode<T>* current;
    size_t sz;
};

// ----------

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T& value, BinaryTreeNode<T>* parent)
{
    this->parent = parent;
    this->value = value;
    left = nullptr;
    right = nullptr;
}

template <typename T>
BinaryTree<T>::BinaryTree()
{
    current = root = nullptr;
    sz = 0;
}

template <typename T>
T* BinaryTree<T>::to_array_preorder() const
{
    vector<T> values;
    traceroute_recursive_preorder(root, values);
    T* result = new T[sz];
    for (size_t i = 0; i < sz; ++i)
    {
        result[i] = values[i];
    }
    return result;
}

template <typename T>
void BinaryTree<T>::traceroute_recursive_preorder(BinaryTreeNode<T>* node, vector<T>& values) const
{
    if (node != nullptr)
    {
        values.push_back(node->value);
        traceroute_recursive_preorder(node->left, values);
        traceroute_recursive_preorder(node->right, values);
    }
}

template <typename T>
T* BinaryTree<T>::to_array_inorder() const
{
    vector<T> values;
    traceroute_recursive_inorder(root, values);
    T* result = new T[sz];
    for (size_t i = 0; i < sz; ++i)
    {
        result[i] = values[i];
    }
    return result;
}

template <typename T>
void BinaryTree<T>::traceroute_recursive_inorder(BinaryTreeNode<T>* node, vector<T>& values) const
{
    if (node != nullptr)
    {
        traceroute_recursive_inorder(node->left, values);
        values.push_back(node->value);
        traceroute_recursive_inorder(node->right, values);
    }
}

template <typename T>
T* BinaryTree<T>::to_array_postorder() const
{
    vector<T> values;
    traceroute_recursive_postorder(root, values);
    T* result = new T[sz];
    for (size_t i = 0; i < sz; ++i)
    {
        result[i] = values[i];
    }
    return result;
}

template <typename T>
void BinaryTree<T>::traceroute_recursive_postorder(BinaryTreeNode<T>* node, vector<T>& values) const
{
    if (node != nullptr)
    {
        traceroute_recursive_postorder(node->left, values);
        traceroute_recursive_postorder(node->right, values);
        values.push_back(node->value);
    }
}

template <typename T>
void BinaryTree<T>::traceroute_node(T value) const
{
    traceroute_node(value, root);
}

template <typename T>
void BinaryTree<T>::traceroute_node(T value, BinaryTreeNode<T>* parent) const
{
    if (parent == nullptr)
    {
        return;
    }
    // cout << parent->value << endl;
    if (value > parent->value)
    {
        traceroute_node(value, parent->right);
    }
    else if (value < parent->value)
    {
        traceroute_node(value, parent->left);
    }
    else
    {
        return;
    }
}

template <typename T>
void BinaryTree<T>::clear()
{
    clear(root);
    sz = 0;
    root = nullptr;
    current = root;
}
template <typename T>
void BinaryTree<T>::clear(BinaryTreeNode<T>* node)
{
    vector<BinaryTreeNode<T>*> nodes;
    clear_recursive(node, nodes);
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        delete nodes[i];
        sz--;
    }
    if (sz == 0)
    {
        root = nullptr;
    }
}
template <typename T>
void BinaryTree<T>::clear_recursive(BinaryTreeNode<T>* node, vector<BinaryTreeNode<T>*>& nodes)
{
    if (node != nullptr)
    {
        nodes.push_back(node);
        clear_recursive(node->left, nodes);
        clear_recursive(node->right, nodes);
    }
}

template <typename T>
void BinaryTree<T>::add_node(T value)
{
    if (root == nullptr)
    {
        root = new BinaryTreeNode<T>(value);
        sz += 1;
    }
    else
    {
        add_node(value, root);
    }
}
template <typename T>
void BinaryTree<T>::add_node(T value, BinaryTreeNode<T>* parent)
{
    if (value > parent->value)
    {
        if (parent->right == nullptr)
        {
            parent->right = new BinaryTreeNode<T>(value, parent);
            sz += 1;
        }
        else
        {
            add_node(value, parent->right);
        }
    }
    else if (value < parent->value)
    {
        if (parent->left == nullptr)
        {
            parent->left = new BinaryTreeNode<T>(value, parent);
            sz += 1;
        }
        else
        {
            add_node(value, parent->left);
        }
    }
}

template <typename T>
void BinaryTree<T>::remove_node(T value)
{
    remove_node(value, root);
}
template <typename T>
void BinaryTree<T>::remove_node(T value, BinaryTreeNode<T>* current_node)
{
    if (current_node != nullptr)
    {
        if (value > current_node->value)
        {
            remove_node(value, current_node->right);
        }
        else if (value < current_node->value)
        {
            remove_node(value, current_node->left);
        }
        else
        {
            // TODO clear_and_get_array(...) {...}

            // 1. Удаление всех узлов ниже current_node, включая сам узел current_node
            vector<T> values;
            traceroute_recursive_inorder(current_node, values);
            auto it = find(values.begin(), values.end(), current_node->value);
            if (it == values.end())
            {
                throw out_of_range("BinaryTree value not found.");
            }
            values.erase(it);

            // 2. delete pointers recursive
            clear(current_node);

            // 3. Вставка всех удалённых узлов, не считая current_node
            // for (auto& value : values)
            // {
            //     add_node(value);
            // }
        }
    }
}

template <typename T>
void BinaryTree<T>::balance_by_inorder()
{
    T* inorder_data = to_array_inorder();

    size_t size = sz;
    size_t middle = sz / 2;
    clear();

    add_node(inorder_data[middle]);
    int i;
    for (i = middle - 1; i >= 0; --i)
    {
        add_node(inorder_data[i]);
    }
    for (i = middle + 1; i < size; ++i)
    {
        add_node(inorder_data[i]);
    }

    delete[] inorder_data;
}

template <typename T>
void BinaryTree<T>::inorder_balance()
{
    T* inorder_data = to_array_inorder();

    size_t size = sz;

    clear();

    balance_recursive(inorder_data, 0, size - 1);

    delete[] inorder_data;
}
template <typename T>
void BinaryTree<T>::balance_recursive(T* data, int left, int right)
{
    if (left <= right)
    {
        int middle = left + (right - left) / 2;
        add_node(data[left]);

        balance_recursive(data, left, middle - 1);
        balance_recursive(data, middle + 1, right);

        add_node(data[right]);
    }
}

template <typename T>
bool BinaryTree<T>::contains(T value, BinaryTreeNode<T>* parent) const
{
    if (parent == nullptr)
    {
        return false;
    }
    if (value > parent->value)
    {
        return contains(value, parent->right);
    }
    else if (value < parent->value)
    {
        return contains(value, parent->left);
    }
    else
    {
        return true;
    }
}

#endif // BINARYTREE_H
