#pragma once

#include <iostream>

#define THRESHOLD 16

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
    while (last - first > THRESHOLD) {
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
    insertion_sort(first, last, comp);
}


template<typename T, typename Compare>
void sort(T* first, T* last, Compare comp) {
    if (first >= last-1)
        return;
    quick_sort(first, last-1, comp);
}