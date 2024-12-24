#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// 冒泡排序
void bubbleSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// 选择排序
void selectionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}
// 合并两个子数组
void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j)
    {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

// 归并排序
void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// 快速排序的分区函数
int partition(std::vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (arr[j] <= pivot)
        {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 快速排序
void quickSort(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 堆调整函数
void heapify(std::vector<int> &arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(std::vector<int> &arr)
{
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; --i)
    {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 生成测试序列
std::vector<int> generateSortedSequence(int n)
{
    std::vector<int> seq(n);
    for (int i = 0; i < n; ++i)
    {
        seq[i] = i;
    }
    return seq;
}

std::vector<int> generateReversedSequence(int n)
{
    std::vector<int> seq(n);
    for (int i = 0; i < n; ++i)
    {
        seq[i] = n - i - 1;
    }
    return seq;
}

std::vector<int> generateRandomSequence(int n)
{
    std::vector<int> seq(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);
    for (int i = 0; i < n; ++i)
    {
        seq[i] = dis(gen);
    }
    return seq;
}

// 测试排序算法性能
void testSortAlgorithms(const std::vector<int> &sortedSeq, const std::vector<int> &reversedSeq, const std::vector<int> &randomSeq)
{
    std::vector<std::string> algoNames = {
        "Bubble Sort", "Insertion Sort", "Selection Sort",
        "Merge Sort", "Quick Sort", "Heap Sort"};
    std::vector<void (*)(std::vector<int> &)> algorithms = {
        bubbleSort, insertionSort, selectionSort,
        [](std::vector<int> &arr)
        { mergeSort(arr, 0, arr.size() - 1); },
        [](std::vector<int> &arr)
        { quickSort(arr, 0, arr.size() - 1); },
        heapSort};

    for (size_t i = 0; i < algorithms.size(); ++i)
    {
        std::cout << algoNames[i] << ":\n";

        auto seq = sortedSeq;
        auto start = std::chrono::high_resolution_clock::now();
        algorithms[i](seq);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "  Sorted Sequence: " << duration << " microseconds\n";

        seq = reversedSeq;
        start = std::chrono::high_resolution_clock::now();
        algorithms[i](seq);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "  Reversed Sequence: " << duration << " microseconds\n";

        seq = randomSeq;
        start = std::chrono::high_resolution_clock::now();
        algorithms[i](seq);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "  Random Sequence: " << duration << " microseconds\n";

        std::cout << "\n";
    }
}

int main()
{
    int n = 10000;
    auto sortedSeq = generateSortedSequence(n);
    auto reversedSeq = generateReversedSequence(n);
    auto randomSeq = generateRandomSequence(n);

    testSortAlgorithms(sortedSeq, reversedSeq, randomSeq);

    return 0;
}