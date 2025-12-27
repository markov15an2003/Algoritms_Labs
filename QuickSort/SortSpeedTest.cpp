// SortSpeedTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Windows.h>
#include <ctime>

using namespace std;

template<typename T>
void swap(T* a, T* b) {
    T t = std::move(*a);
    *a = std::move(*b);
    *b = std::move(t);
}

template<typename T, typename Compare>
T* median_select(T* first, T* last, Compare comp) {
    T* mid = first + (last - first) / 2;

    if (comp(*first, *mid)) {
        if (comp(*mid, *last))
            return mid;
        if (comp(*first, *last))
            return last;
        return first;
    }
    else {
        if (comp(*first, *last))
            return first;
        if (comp(*mid, *last))
            return last;
        return mid;
    }
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp) {
    T* pivot = median_select(first, last, comp);

    T val = *pivot;

    swap(first, pivot);

    T* left = first;
    T* right = last + 1;

    while (true) {
        do {
            ++left;
        } while (left < last && comp(*left, val));

        do {
            --right;
        } while (right > first && comp(val, *right));

        if (left >= right) {
            break;
        }

        swap(left, right);
    }

    swap(first, right);
    return right;
}

template<typename T, typename Compare>
void insertion_sort(T* first, T* last, Compare comp) {
    for (int i = 1; i < last - first + 1; i++)
    {
        T key = std::move(*(first + i));
        int j = i - 1;
        while (j >= 0 && comp(key, *(first + j)))
        {
            *(first + j + 1) = std::move(*(first + j));
            j--;
        }
        *(first + j + 1) = std::move(key);
    }
}

template<typename T, typename Compare>
void quick_sort(T* first, T* last, Compare comp) {
    while (last - first > 0) {
        T* pivot = partition(first, last, comp);

        if (pivot - first < last - pivot) {
            quick_sort(first, pivot - 1, comp);
            first = pivot + 1;
        }
        else {
            quick_sort(pivot + 1, last, comp);
            last = pivot - 1;
        }
    }
}

int main()
{
    srand(time(0));
    LARGE_INTEGER f, start, end;
    QueryPerformanceFrequency(&f);
    int* arr1, * arr2;
    double time1, time2;
    for (int i = 0; i < 100; i++) {
        arr1 = new int[i + 1];
        arr2 = new int[i + 1];
        cout << i + 1 << ';';
        time1 = 0;
        time2 = 0;
        for (int t = 0; t < 5; t++) {
            for (int j = 0; j < i + 1; j++) {
                arr1[j] = rand() % 10000;
                arr2[j] = arr1[j];
            }
            QueryPerformanceCounter(&start);
            quick_sort(arr1, arr1 + i, [](int a, int b) { return a < b; });
            QueryPerformanceCounter(&end);
            time1 += (double)(end.QuadPart - start.QuadPart) * 1000.0 / f.QuadPart;
            QueryPerformanceCounter(&start);
            insertion_sort(arr2, arr2 + i, [](int a, int b) { return a < b; });
            QueryPerformanceCounter(&end);
            time2 += (double)(end.QuadPart - start.QuadPart) * 1000.0 / f.QuadPart;
        }
        cout << time1 / 5 << ';' << time2 / 5 << '\n';
        delete []arr1;
        delete []arr2;
    }
    return 0;
}
