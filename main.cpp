#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <functional>

using namespace std;
using namespace std::chrono;

const int N = 10000;

// Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j + 1] = arr[j--];
        arr[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[minIdx])
                minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

// Merge Sort
void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;

    while (i < (int)left.size() && j < (int)right.size())
        arr[k++] = (left[i] < right[j]) ? left[i++] : right[j++];
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSortHelper(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortHelper(arr, l, m);
    mergeSortHelper(arr, m + 1, r);
    merge(arr, l, m, r);
}

void mergeSort(vector<int>& arr) {
    mergeSortHelper(arr, 0, arr.size() - 1);
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low;
    for (int j = low; j < high; ++j)
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[high]);
    return i;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int>& arr) {
    quickSortHelper(arr, 0, arr.size() - 1);
}

// Heap Sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Обёртка для замера времени
double measureTime(function<void(vector<int>&)> sortFunc, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

// Печать результатов
void printResults(const string& name, double randT, double bestT, double worstT) {
    printf("%-20s | %10.3f ms | %10.3f ms | %10.3f ms\n", name.c_str(), randT, bestT, worstT);
}

int main() {
    // Инициализация случайного генератора
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 99999);

    // Исходные массивы
    vector<int> randomArr(N), bestCase(N), worstCase(N);
    for (int i = 0; i < N; ++i)
        randomArr[i] = dist(gen);

    bestCase = randomArr;
    sort(bestCase.begin(), bestCase.end());
    worstCase = bestCase;
    reverse(worstCase.begin(), worstCase.end());

    // Таблица
    cout << "Сравнение алгоритмов сортировки на " << N << " элементах:\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Сортировка          |   Случайный   |    Best case  |   Worst case  \n";
    cout << "--------------------|---------------|---------------|----------------\n";

    vector<pair<string, function<void(vector<int>&)>>> algorithms = {
        {"Bubble Sort", bubbleSort},
        {"Insertion Sort", insertionSort},
        {"Selection Sort", selectionSort},
        {"Merge Sort", mergeSort},
        {"Quick Sort", quickSort},
        {"Heap Sort", heapSort},
        {"std::sort", [](vector<int>& arr){ sort(arr.begin(), arr.end()); }},
        {"std::stable_sort", [](vector<int>& arr){ stable_sort(arr.begin(), arr.end()); }}
    };

    for (auto& [name, func] : algorithms) {
        double t1 = measureTime(func, randomArr);
        double t2 = measureTime(func, bestCase);
        double t3 = measureTime(func, worstCase);
        printResults(name, t1, t2, t3);
    }

    return 0;
}
