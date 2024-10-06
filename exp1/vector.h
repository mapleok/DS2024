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
    void bubbleSort(Rank lo, Rank hi);
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);

public:
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
    Vector(Vector<T> const &V) { copyFrom(V._elem, 0, V._size); }
    Vector(Vector<T> const &V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }
    // 析构函数
    ~Vector() { delete[] _elem; }
    // 只读访问接口
    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    int disordered() const;
    Rank find(T const &e) const { return find(e, 0, _size); }
    Rank find(T const &e, Rank lo, Rank hi) const;
    Rank search(T const &e) const
    {
        return (0 > _size) ? -1 : search(e, 0, _size);
    }
    // 可写访问接口
    T &operator[](Rank r) const;
    Vector<T> &operator=(Vector<T> const &);
    T remove(Rank r);
    int remove(Rank lo, Rank hi);
    Rank insert(Rank r, T const &e);
    Rank insert(T const &e) { return insert(_size, e); }
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }
    void unsort(Rank lo, Rank hi);
    void unsort() { unsort(0, _size); }
    int deduplicate();
    int uniquify();

    // 遍历
    void traverse(void (*)(T &));
    template <typename VST>
    void traverse(VST &);
};
template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
        return;
    _capacity *= 2; // 扩展容量
    T *newElem = new T[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        newElem[i] = _elem[i];
    }
    delete[] _elem;
    _elem = newElem;
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const &e)
{
    expand();
    for (int i = _size; i > r; --i)
    {
        _elem[i] = _elem[i - 1]; // 移动元素
    }
    _elem[r] = e; // 插入新元素
    ++_size;
    return r;
}

template <typename T>
T &Vector<T>::operator[](Rank r) const
{
    return _elem[r]; // 返回元素
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r]; // 保存被删除的元素
    for (int i = r; i < _size - 1; ++i)
    {
        _elem[i] = _elem[i + 1]; // 移动元素
    }
    --_size; // 减少大小
    return e;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T &))
{
    for (int i = 0; i < _size; ++i)
    {
        visit(_elem[i]); // 调用访问函数
    }
}
