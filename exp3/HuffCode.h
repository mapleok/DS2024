#ifndef HUFFCODE_H
#define HUFFCODE_H

#include "Bitmap.h"
#include <string>

// Huffman编码串类型
template <typename T>
class HuffCode
{
private:
    Bitmap codeBitmap;

public:
    HuffCode() : codeBitmap() {}

    // 设置编码串（增加对编码串有效性的检查，只接受包含 '0' 和 '1' 的字符串）
    void setCode(const std::string &code)
    {
        // 清空之前可能存在的编码位图
        for (Rank i = 0; i < codeBitmap.size(); ++i)
        {
            codeBitmap.clear(i);
        }

        // 示例逻辑，根据字符 '0' 和 '1' 设置位图
        for (size_t i = 0; i < code.length(); ++i)
        {
            if (code[i] == '1')
            {
                codeBitmap.set(i);
            }
            else if (code[i] == '0')
            {
                codeBitmap.clear(i);
            }
            else
            {
                // 如果遇到非法字符，抛出异常或进行其他错误处理，这里简单打印错误信息并返回
                std::cerr << "Invalid character in Huffman code: " << code[i] << std::endl;
                return;
            }
        }
    }

    // 获取编码串（将位图转换为字符串形式的编码串返回，返回类型改为std::string）
    std::string getCode()
    {
        return codeBitmap.bits2string(codeBitmap.size());
    }

    // 获取编码串的长度
    size_t getCodeLength()
    {
        return codeBitmap.size();
    }

    // 判断编码串是否为空
    bool isCodeEmpty()
    {
        return codeBitmap.size() == 0;
    }

    // 比较两个HuffCode对象的编码是否相等
    bool operator==(const HuffCode<T> &other) const
    {
        return codeBitmap == other.codeBitmap;
    }

    // 比较两个HuffCode对象的编码是否不相等
    bool operator!=(const HuffCode<T> &other) const
    {
        return !(*this == other);
    }

    // 为Bitmap类添加一个比较运算符重载，用于比较两个Bitmap对象是否相等
    friend bool operator==(const Bitmap &a, const Bitmap &b)
    {
        if (a.size() != b.size())
        {
            return false;
        }

        for (Rank i = 0; i < a.size(); ++i)
        {
            if (a.test(i) != b.test(i))
            {
                return false;
            }
        }

        return true;
    }
};

#endif