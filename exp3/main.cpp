#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>
#include "BinTree.h"
#include "HuffTree.h"
#include "HuffCode.h"
#include "Bitmap.h"

// 统计字符频率的函数
std::unordered_map<char, int> countFrequencies(const std::string &text)
{
    std::unordered_map<char, int> frequencies;
    for (char c : text)
    {
        // 只统计字母（不分大小写），将所有字母转换为 lowercase 进行统计
        if (isalpha(c))
        {
            char lowerC = tolower(c);
            frequencies[lowerC]++;
        }
    }
    return frequencies;
}

// 构建Huffman树的函数
template <typename T>
HuffTree<T> buildHuffmanTree(const std::unordered_map<T, int> &frequencies)
{
    // 使用优先队列来辅助构建Huffman树，按照频率从小到大排序
    std::priority_queue<HuffNode<T> *, std::vector<HuffNode<T> *>,
                        std::function<bool(HuffNode<T> *, HuffNode<T> *)>>
        pq(
            [](HuffNode<T> *a, HuffNode<T> *b)
            {
                return a->frequency > b->frequency;
            });

    // 将每个字符及其频率作为节点插入到优先队列中
    for (const auto &pair : frequencies)
    {
        HuffNode<T> *node = new HuffNode<T>(pair.first, pair.second);
        pq.push(node);
    }

    // 不断从优先队列中取出两个频率最小的节点，合并成一个新节点并插入队列
    while (pq.size() > 1)
    {
        HuffNode<T> *left = pq.top();
        pq.pop();
        HuffNode<T> *right = pq.top();
        pq.pop();

        HuffNode<T> *parent = new HuffNode<T>(T(), left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    // 最后队列中剩下的就是Huffman树的根节点
    HuffTree<T> huffTree;
    huffTree = HuffTree<T>(pq.top());
    pq.pop();

    return huffTree;
}

// 为Huffman树的每个节点生成编码的函数
template <typename T>
void generateHuffmanCodes(const HuffTree<T> &huffTree,
                          std::unordered_map<T, HuffCode<T>> &huffmanCodes,
                          HuffCode<T> initialCode)
{
    if (huffTree.getRoot() == nullptr)
    {
        return;
    }

    // 递归遍历Huffman树，为每个叶子节点生成编码
    std::function<void(BinNode<T> *, HuffCode<T>)> traverse = [&](BinNode<T> *node, HuffCode<T> code)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->left == nullptr && node->right == nullptr)
        {
            // 叶子节点，保存其编码
            huffmanCodes[node->data] = code;
        }

        // 向左子树遍历，编码添加 '0'
        HuffCode<T> leftCode = code;
        std::string tempCode = code.getCode();
        tempCode += "0";
        leftCode.setCode(tempCode);
        traverse(node->left, leftCode);

        // 向右转树遍历，编码添加 '1'
        HuffCode<T> rightCode = code;
        std::string tempCode2 = code.getCode();
        tempCode2 += "1";
        rightCode.setCode(tempCode2);
        traverse(node->right, rightCode);
    };

    traverse(huffTree.getRoot(), initialCode);
}

int main()
{
    // 读取马丁路德金演讲原文《I have a dream》
    std::ifstream file("I_have_a_dream.txt");
    if (!file.is_open())
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    std::string text;
    std::string line;
    while (std::getline(file, line))
    {
        text += line;
    }
    file.close();

    // 统计26个字母（不分大小写）的频率
    std::unordered_map<char, int> frequencies = countFrequencies(text);

    // 构建Huffman树
    HuffTree<char> huffTree = buildHuffmanTree(frequencies);

    // 为Huffman树的每个节点生成编码
    std::unordered_map<char, HuffCode<char>> huffmanCodes;
    HuffCode<char> initialCode;
    generateHuffmanCodes(huffTree, huffmanCodes, initialCode);

    // 对单词 "dream" 进行编码
    std::string wordToEncode = "dream";
    std::string encodedWord;
    for (char c : wordToEncode)
    {
        encodedWord += huffmanCodes[c].getCode();
    }

    std::cout << "Encoded word 'dream': " << encodedWord << std::endl;

    return 0;
}