#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 假设Rank是某种整数类型的别名，这里简单定义为unsigned int，如果在实际中有更具体的定义可替换
typedef unsigned int Rank;

class Bitmap
{
private:
    unsigned char *M;
    Rank N;   // 位图空间M[]实际分配的字节数，每个字节可表示8个比特
    Rank _sz; // 位图中当前有效的比特位数

protected:
    void init(Rank n)
    {
        // 计算所需字节数，向上取整保证能容纳所有比特
        N = (n + 7) / 8;
        M = new unsigned char[N];
        // 初始化为全0
        memset(M, 0, N);
        _sz = 0;
    }

public:
    Bitmap(Rank n = 8)
    {
        init(n);
    } // 按指定容量创建位图（为测试暂时选用较小的默认值）

    Bitmap(char *file, Rank n = 8)
    { // 按指定或默认规模，从指定文件中读取位图
        init(n);
        FILE *fp = fopen(file, "r");
        if (fp == NULL)
        {
            perror("Error opening file for reading bitmap");
            exit(EXIT_FAILURE);
        }
        // 读取位图数据到内存
        fread(M, sizeof(char), N, fp);
        fclose(fp);

        // 计算有效比特位数
        _sz = 0;
        for (Rank k = 0; k < n; ++k)
        {
            if (this->test(k))
            {
                ++_sz;
            }
        }
    }

    ~Bitmap()
    {
        // 释放位图占用的内存空间
        delete[] M;
        M = NULL;
        _sz = 0;
    } // 析构时释放位图空间

    Rank size() const
    {
        return _sz;
    }

    void set(Rank k)
    {
        // 确保位图空间足够容纳要设置的比特位
        expand(k);

        // 设置指定比特位为1
        M[k >> 3] |= (0x80 >> (k & 0x07));

        // 有效比特位数增加
        if (!this->test(k))
        {
            ++_sz;
        }
    }

    void clear(Rank k)
    {
        // 确保位图空间足够容纳要清除的比特位
        expand(k);

        // 清除指定比特位为0
        M[k >> 3] &= ~(0x80 >> (k & 0x07));

        // 有效比特位数减少
        if (this->test(k))
        {
            --_sz;
        }
    }

    bool test(Rank k) const
    {
        // 确保位图空间足够容纳要测试的比特位
        expand(k);

        // 测试指定比特位是否为1
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }

    void dump(char *file) // 将位图整体导出至指定的文件，以便对此后的新位图批量初始化
    {
        FILE *fp = fopen(file, "w");
        if (fp == NULL)
        {
            perror("Error opening file for writing bitmap");
            exit(EXIT_FAILURE);
        }
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }

    char *bits2string(Rank n)
    { // 将前n 位转换为字符串——
        // 确保位图空间足够容纳要转换的比特位
        expand(n - 1);

        char *s = new char[n + 1];
        s[n] = '\0'; // 字符串末尾添加结束符

        // 逐个比特位转换为字符 '0' 或 '1'
        for (Rank i = 0; i < n; ++i)
        {
            s[i] = this->test(i) ? '1' : '0';
        }

        return s; // 返回生成的字符串，由调用者负责释放内存
    }

    void expand(Rank k)
    { // 若被访问的Bitmap[k]已出界，则需扩容
        if (k < 8 * N)
        {
            return; // 仍在界内，无需扩容
        }

        Rank oldN = N;
        unsigned char *oldM = M;

        // 采用加倍扩容策略
        init(2 * k);

        // 将原数据复制到新空间
        memcpy(M, oldM, oldN);

        // 释放原内存空间
        delete[] oldM;
    }
};

#endif