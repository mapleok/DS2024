#include <iostream>
#include "vector.h"
using namespace std;
int main()
{
    Vector<int> vec; // 创建一个默认大小的 Vector

    // 测试插入
    vec.insert(0, 10);
    vec.insert(1, 20);
    vec.insert(2, 30);

    cout << "Vector size: " << vec.size() << endl; // 应该输出 3

    // 测试访问
    for (int i = 0; i < vec.size(); i++)
    {
        cout << "Element at index " << i << ": " << vec[i] << endl; // 应该输出 10, 20, 30
    }

    // 测试删除
    vec.remove(1);                                                  // 删除元素 20
    cout << "After removing index 1, size: " << vec.size() << endl; // 应该输出 2

    // 遍历并输出
    vec.traverse([](int &e)
                 { cout << e << " "; });
    cout << endl;

    return 0;
}

