#pragma once

#include <iostream>

#define DEFAULT_CAPACITY 16
#define CAPACITY_INCREASE 2

using namespace std;

template<typename T>
class DynamicArray {
private:
    T* buf_;
    int length_;
    int capacity_;

    void custom_move(T* new_el, T* old_el) {
        if (std::is_move_constructible_v<T>)
            new(new_el) T(std::move(*old_el));
        else {
            new (new_el) T(*old_el);
            (old_el)->~T();
        }
    }

    void capacity_check() {
        if (length_ == capacity_) {
            if (capacity_ > 0)
                capacity_ = capacity_ * CAPACITY_INCREASE;
            else
                capacity_ = DEFAULT_CAPACITY;
            T* buf = static_cast<T*>(malloc(capacity_ * sizeof(T)));

            for (int i = 0; i < length_; i++) {
                custom_move(buf + i, buf_ + i);
                buf_[i].~T();
            }

            free(buf_);
            buf_ = buf;
        }
    }

public:
    DynamicArray() : length_{ 0 }, capacity_{ DEFAULT_CAPACITY } {
        buf_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
    }

    DynamicArray(int capacity) : length_{ 0 }, capacity_{ capacity } {
        buf_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
    }

    ~DynamicArray() {
        if (buf_) {
            for (int i = 0; i < length_; i++)
                buf_[i].~T();
            free(buf_);
        }
    }

    DynamicArray(const DynamicArray& arr) : length_{ arr.length_ }, capacity_{ arr.capacity_ } {
        buf_ = static_cast<T*>(malloc(capacity_ * sizeof(T)));
        for (int i = 0; i < length_; ++i) {
            new (buf_ + i) T(arr.buf_[i]);
        }
    }

    DynamicArray(DynamicArray&& arr): buf_{ arr.buf_ }, length_{ arr.length_ }, capacity_{ arr.capacity_ } {
        arr.buf_ = nullptr;
        arr.length_ = 0;
        arr.capacity_ = 0;
    }

    DynamicArray& operator=(const DynamicArray& arr) {
        DynamicArray t(arr);

        std::swap(buf_, t.buf_);
        std::swap(length_, t.length_);
        std::swap(capacity_, t.capacity_);

        return *this;
    }

    DynamicArray& operator=(DynamicArray&& arr) {
        if (this != &arr) {
            this->~DynamicArray();
            new (this) DynamicArray(std::move(arr));
        }

        return *this;
    }

    int insert(const T& value) {
        capacity_check();

        new(buf_ + length_) T(value);
        length_++;

        return length_ - 1;
    }

    int insert(int index, const T& value) {
        capacity_check();

        for (int i = length_; i > index; i--) {
            custom_move(buf_ + i, buf_ + i - 1);
            buf_[i - 1].~T();
        }

        new (buf_ + index) T(value);
        length_++;

        return index;
    }

    void remove(int index) {
        if (index >= length_)
            return;

        buf_[index].~T();

        for (int i = index; i < length_ - 1; i++) {
            custom_move(buf_ + i, buf_ + i + 1);
            buf_[i + 1].~T();
        }

        length_--;
    }

    T& operator[](int index) {
        return buf_[index];
    }

    const T& operator[](int index) const {
        return buf_[index];
    }

    int size() const {
        return length_;
    }

    class Iterator {
    private:
        DynamicArray<T>& cnt_;
        int index_;
        bool rev_;

    public:
        Iterator(DynamicArray<T>& cnt, int index, bool rev) : cnt_{ cnt }, index_{ index }, rev_{ rev } {
        }

        const T& get() const {
            return cnt_.buf_[index_];
        }
        void set(const T& value) {
            cnt_.buf_[index_] = value;
        }
        void next() {
            if (rev_)
                index_--;
            else
                index_++;
        }
        bool hasNext() const {
            return ((rev_ && index_ > 0) || (!rev_ && (index_ + 1 < cnt_.length_)));
        }
    };

    class ConstIterator {
    private:
        const DynamicArray<T>& cnt_;
        int index_;
        bool rev_;

    public:
        ConstIterator(const DynamicArray<T>& cnt, int index, bool rev) : cnt_{ cnt }, index_{ index }, rev_{ rev } {
        }

        const T& get() const {
            return cnt_.buf_[index_];
        }
        void next() {
            if (rev_)
                index_--;
            else
                index_++;
        }
        bool hasNext() const {
            return ((rev_ && index_ > 0) || (!rev_ && (index_ + 1 < cnt_.length_)));
        }
    };

    Iterator iterator() {
        return Iterator(*this, 0, false);
    }

    Iterator reverseIterator() {
        return Iterator(*this, length_ - 1, true);
    }

    ConstIterator iterator() const {
        return Iterator(*this, 0, false);
    }

    ConstIterator reverseIterator() const {
        return Iterator(*this, length_ - 1, true);
    }
};