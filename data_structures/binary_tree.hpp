#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <cstddef>

#include "data_structure.hpp"

using namespace std;

template <typename T>
class BinaryTreeNode
{
public:
    BinaryTreeNode(const T &value, BinaryTreeNode<T> *parent = nullptr);

    T value;
    BinaryTreeNode<T> *left;
    BinaryTreeNode<T> *right;
    BinaryTreeNode<T> *parent;
};

template <typename T>
class BinaryTree : public DataStructure<T>
{
public:
    BinaryTree();

    T* to_array_preorder() const;
    void traceroute_recursive_preorder(BinaryTreeNode<T> *node, vector<T> &values) const;
    T* to_array_inorder() const;
    void traceroute_recursive_inorder(BinaryTreeNode<T> *node, vector<T> &values) const;
    T* to_array_postorder() const;
    void traceroute_recursive_postorder(BinaryTreeNode<T> *node, vector<T> &values) const;

    void add_node(T value);
    void remove_node(T value);

    void traceroute_node(T value) const;

    size_t size() const override { return sz; }
    bool is_empty() const override { return sz > 0 ? false : true; };
    bool contains(const T& value) const override { return contains(value, root); };

    T* to_array() const override { return to_array_inorder(); };

private:
    void add_node(T value, BinaryTreeNode<T> *parent);
    void traceroute_node(T value, BinaryTreeNode<T> *parent) const;
    bool contains(T value, BinaryTreeNode<T> *parent) const;

private:
    BinaryTreeNode<T> *root;
    BinaryTreeNode<T> *current;
    size_t sz;
};

// ----------

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T &value, BinaryTreeNode<T> *parent)
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
void BinaryTree<T>::traceroute_recursive_preorder(BinaryTreeNode<T> *node, vector<T>& values) const
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
void BinaryTree<T>::traceroute_recursive_inorder(BinaryTreeNode<T> *node, vector<T> &values) const
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
void BinaryTree<T>::traceroute_recursive_postorder(BinaryTreeNode<T> *node, vector<T> &values) const
{
    if (node != nullptr)
    {
        traceroute_recursive_postorder(node->left, values);
        traceroute_recursive_postorder(node->right, values);
        values.push_back(node->value);
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
void BinaryTree<T>::add_node(T value, BinaryTreeNode<T> *parent)
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
    else
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
void BinaryTree<T>::traceroute_node(T value) const
{
    traceroute_node(value, root);
}

template <typename T>
void BinaryTree<T>::traceroute_node(T value, BinaryTreeNode<T> *parent) const
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
bool BinaryTree<T>::contains(T value, BinaryTreeNode<T> *parent) const
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
