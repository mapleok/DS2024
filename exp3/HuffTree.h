#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "BinTree.h"

// Huffman树节点结构体，包含频率信息
template <typename T>
struct HuffNode : public BinNode<T>
{
    int frequency;

    HuffNode(const T &d, int f) : BinNode<T>(d), frequency(f) {}
};

// Huffman树类
template <typename T>
class HuffTree : public BinTree<T>
{
public:
    // 构建Huffman树的函数（这里假设已经有了节点频率信息的数组等，具体构建逻辑需根据实际情况完善）
    void buildHuffmanTree()
    {
        // 示例构建逻辑，这里只是简单示意，实际需要根据节点频率等信息构建真正的HuffTree
        // 假设已经有了一些节点，将它们插入到二叉树中（这里的插入逻辑也需要进一步完善）
        T sampleData = T();
        int sampleFrequency = 0;
        HuffNode<T> *node = new HuffNode<T>(sampleData, sampleFrequency);
        this->insert(node);
    }

    // 获取根节点的函数，通过调用基类的保护成员函数来实现
    BinNode<T> *getRoot() const
    {
        return this->BinTree<T>::getRoot();
    }
};

#endif