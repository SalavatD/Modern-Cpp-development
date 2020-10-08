#pragma once

#include <cstdlib>

template<typename T>
class SimpleVector {
    T *mBegin;
    T *mEnd;
    size_t mSize;
    size_t mCapacity;

public:
    SimpleVector();

    explicit SimpleVector(size_t size);

    ~SimpleVector();

    T &operator[](size_t index);

    const T &operator[](size_t index) const;

    T *begin();

    const T *begin() const;

    T *end();

    const T *end() const;

    [[nodiscard]] size_t Size() const;

    [[nodiscard]] size_t Capacity() const;

    void PushBack(const T &value);
};

template<typename T>
SimpleVector<T>::SimpleVector() : mBegin(nullptr), mEnd(nullptr), mSize(0), mCapacity(0) {}

template<typename T>
SimpleVector<T>::SimpleVector(size_t size) {
    mBegin = new T[size];
    mEnd = mBegin + size;
    mSize = size;
    mCapacity = size;
}

template<typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] mBegin;
}

template<typename T>
T &SimpleVector<T>::operator[](size_t index) {
    return mBegin[index];
}

template<typename T>
const T &SimpleVector<T>::operator[](size_t index) const {
    return mBegin[index];
}

template<typename T>
T *SimpleVector<T>::begin() {
    return mBegin;
}

template<typename T>
const T *SimpleVector<T>::begin() const {
    return mBegin;
}

template<typename T>
T *SimpleVector<T>::end() {
    return mEnd;
}

template<typename T>
const T *SimpleVector<T>::end() const {
    return mEnd;
}

template<typename T>
size_t SimpleVector<T>::Size() const {
    return mSize;
}

template<typename T>
size_t SimpleVector<T>::Capacity() const {
    return mCapacity;
}

template<typename T>
void SimpleVector<T>::PushBack(const T &value) {
    if (mCapacity == mSize) {
        size_t newCapacity = mCapacity * 2;
        auto *newBegin = new T[newCapacity];
        for (size_t i = 0; i < mSize; ++i) {
            newBegin[i] = mBegin[i];
        }
        delete[] mBegin;
        mBegin = newBegin;
        mEnd = mBegin + mSize;
        mCapacity = newCapacity;
    }
    *mEnd = value;
    mSize++;
    mEnd++;
}
