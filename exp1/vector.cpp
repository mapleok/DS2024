#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
class Vector
{
protected:
    Rank _size;
    int _capacity;
    T *_elem;
    void copyFrom(T const *A, Rank lo, Rank hi);
    void expand();
    void shrink();
    bool bubble(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);

public:
    void bubbleSort(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v)
            ;
    }
    Vector(T const *A, Rank n)
    {
        copyFrom(A, 0, n);
    }
    Vector(T const *A, Rank lo, Rank hi)
    {
        copyFrom(A, lo, hi);
    }
    Vector(Vector<T> const &V)
    {
        copyFrom(V._elem, 0, V._size);
    }
    Vector(Vector<T> const &V, Rank lo, Rank hi)
    {
        copyFrom(V._elem, lo, hi);
    }
    ~Vector() { delete[] _elem; }

    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    Rank find(T const &e) const { return find(e, 0, _size); }
    Rank find(T const &e, Rank lo, Rank hi) const;

    T &operator[](Rank r) const;
    Vector<T> &operator=(Vector<T> const &);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    Rank insert(Rank r, T const &e);
    Rank insert(T const &e) { return insert(_size, e); }
    void unsort(Rank lo, Rank hi);
    void unsort() { unsort(0, _size); }
    int uniquify();

    Vector<T> rangeSearch(double m1, double m2) const; // 查找函数
    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
};

// 复制构造函数
template <typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
}

// 赋值操作符
template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> const &V)
{
    if (_elem)
    {
        delete[] _elem;
    }
    copyFrom(V._elem, 0, V.size());
    return *this;
}

// 扩容
template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
        return;
    if (_capacity < DEFAULT_CAPACITY)
        _capacity = DEFAULT_CAPACITY;
    T *oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

// 缩容
template <typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1)
        return;
    if (_size << 2 > _capacity)
        return;
    T *oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++)
    {
        _elem[i] = oldElem[i];
    }
    delete[] oldElem;
}

// 直接引用元素
template <typename T>
T &Vector<T>::operator[](Rank r) const
{
    return _elem[r];
}

// 置乱算法
template <typename T>
void permute(Vector<T> &V)
{
    for (int i = V.size(); i > 0; i--)
        swap(V[i - 1], V[rand() % i]);
}
// 区间置乱算法
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T *V = _elem + lo;
    for (Rank i = hi - lo; i > 0; i--)
        std::swap(V[i - 1], V[rand() % i]);
}

// 顺序查找
template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
    while ((lo < hi--) && (e != _elem[hi]))
        ;
    return hi;
}
// 插入
template <typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
    expand();
    for (int i = _size; i > r; --i)
    {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
Vector<T> Vector<T>::rangeSearch(double m1, double m2) const
{
    Vector<T> result;
    for (Rank i = 0; i < _size; i++)
    {
        double modulus = _elem[i].modulus();
        if (modulus >= m1 && modulus < m2)
        {
            result.insert(result.size(), _elem[i]); // 将符合条件的元素插入结果向量
        }
    }
    return result; // 返回查找结果
}

// 区间删除
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
        return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    _size = lo;
    shrink();
    return hi - lo;
}

// 单个元素删除
template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

// 遍历
template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; ++i)
    {
        visit(_elem[i]);
    }
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST &visit)
{
    for (int i = 0; i < _size; i++)
    {
        visit(_elem[i]);
    }
}

// 唯一化
template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < _size)
    {
        if (_elem[i] != _elem[j])
        {
            _elem[++i] = _elem[j];
        }
    }
    _size = ++i;
    shrink();
    return j - i;
}

// 气泡排序
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true;
    for (Rank i = lo; i < hi - 1; i++)
    {
        if (_elem[i] > _elem[i + 1])
        {
            swap(_elem[i], _elem[i + 1]);
            sorted = false;
        }
    }
    return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--))
        ;
}

// 归并排序
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
    if (hi - lo <= 1)
        return;
    Rank mi = lo + (hi - lo) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}


// 归并操作
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    T *B = new T[mi - lo];
    for (Rank i = 0; i < mi - lo; i++)
    {
        B[i] = _elem[lo + i];
    }

    Rank i = 0, j = mi, k = lo;
    while (i < mi - lo && j < hi)
    {
        if (B[i] <= _elem[j])
        {
            _elem[k++] = B[i++];
        }
        else
        {
            _elem[k++] = _elem[j++];
        }
    }
    while (i < mi - lo)
    {
        _elem[k++] = B[i++];
    }
    delete[] B;
}

// 复数类
class Complex
{
public:
    double real, imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double modulus() const
    {
        return sqrt(real * real + imag * imag);
    }

    bool operator<(const Complex &other) const
    {
        return modulus() < other.modulus() || (modulus() == other.modulus() && real < other.real);
    }

    bool operator!=(const Complex &other) const
    {
        return real != other.real || imag != other.imag;
    }

    friend ostream &operator<<(ostream &os, const Complex &c)
    {
        os << "(" << c.real << ", " << c.imag << "i)";
        return os;
    }
};

// 打印复数的函数
void print(const Complex &c)
{
    cout << c << " ";
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // 随机数种子

    // 创建无序向量
    Vector<int> vec;
    for (int i = 0; i < 10; ++i)
    {
        vec.insert(i, rand() % 10); // 插入随机数
    }

    std::cout << "Original Vector: ";
    vec.traverse(print);
    std::cout << std::endl;

    // 置乱
    vec.unsort();
    std::cout << "Shuffled Vector: ";
    vec.traverse(print);
    std::cout << std::endl;

    // 查找
    int toFind = 5;
    Rank index = vec.find(toFind);
    std::cout << "Find " << toFind << " at index: " << index << std::endl;

    // 插入
    vec.insert(3, 20);
    std::cout << "After Insertion: ";
    vec.traverse(print);
    std::cout << std::endl;

    // 删除
    vec.remove(2);
    std::cout << "After Deletion: ";
    vec.traverse(print);
    std::cout << std::endl;

    // 唯一化
    vec.uniquify();
    std::cout << "After Uniquification: ";
    vec.traverse(print);
    std::cout << std::endl;

    // 测试不同的排序算法

    clock_t start, end;

    // 冒泡排序
    start = clock();
    vec.bubbleSort(0, vec.size());
    end = clock();
    std::cout << "Bubble Sort Time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds." << std::endl;

    // 归并排序
    start = clock();
    vec.mergeSort(0, vec.size());
    end = clock();
    std::cout << "Merge Sort Time: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " seconds." << std::endl;

    Vector<Complex> result = vec.rangeSearch(1, 5);
    cout << "Range Search Result [1, 5): ";
    result.traverse(print);
    cout << endl;
    return 0;
}
