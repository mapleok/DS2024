#ifndef BINTREE_H
#define BINTREE_H

#include <iostream>

// 二叉树节点结构体
template <typename T>
struct BinNode
{
    T data;
    BinNode<T> *left;
    BinNode<T> *right;

    BinNode(const T &d) : data(d), left(nullptr), right(nullptr) {}
};

// 二叉树类
template <typename T>
class BinTree
{
protected:
    BinNode<T> *root;

public:
    BinTree() : root(nullptr) {}

    // 插入节点（简单示例，这里假设插入到合适位置，可根据具体需求完善插入逻辑）
    void insert(const T &data)
    {
        if (root == nullptr)
        {
            root = new BinNode<T>(data);
        }
        else
        {
            // 这里可以实现更复杂的插入逻辑，比如按照某种顺序插入到合适的子树位置
            // 暂时简单地插入到左子树（仅为示例）
            if (root->left == nullptr)
            {
                root->left = new BinNode<T>(data);
            }
            else
            {
                std::cerr << "Insertion not properly implemented. Tree may become unbalanced." << std::endl;
            }
        }
    }

    // 其他可能的操作函数，如遍历等，这里暂未详细实现

    ~BinTree()
    {
        // 释放二叉树节点内存的函数（这里简单示意，可根据具体需求完善）
        clear(root);
    }

protected:
    void clear(BinNode<T> *node)
    {
        if (node != nullptr)
        {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // 添加获取根节点的保护成员函数
    BinNode<T> *getRoot() const
    {
        return root;
    }
};

#endif