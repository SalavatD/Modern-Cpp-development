#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Deque {
    vector<T> mDequeFront;
    vector<T> mDequeBack;

public:
    bool Empty() const {
        return mDequeFront.empty() && mDequeBack.empty();
    }

    const size_t Size() const {
        return mDequeFront.size() + mDequeBack.size();
    }

    T &At(const size_t index) {
        if (index > Size()) {
            throw out_of_range("");
        }
        return operator[](index);
    }

    const T &At(const size_t index) const {
        if (index > Size()) {
            throw out_of_range("");
        }
        return operator[](index);
    }

    T &Front() {
        if (mDequeFront.empty()) {
            return mDequeBack[0];
        }
        return mDequeFront.back();
    }

    const T &Front() const {
        if (mDequeFront.empty()) {
            return mDequeBack[0];
        }
        return mDequeFront.back();
    }

    T &Back() {
        if (mDequeBack.empty()) {
            return mDequeFront[0];
        }
        return mDequeBack.back();
    }

    const T &Back() const {
        if (mDequeBack.empty()) {
            return mDequeFront[0];
        }
        return mDequeBack.back();
    }

    void PushBack(const T &value) {
        return mDequeBack.push_back(value);
    }

    void PushFront(const T &value) {
        return mDequeFront.push_back(value);
    }

    T &operator[](const size_t index) {
        if (index < mDequeFront.size()) {
            return mDequeFront[mDequeFront.size() - index - 1];
        } else {
            return mDequeBack[index - mDequeFront.size()];
        }
    }

    const T &operator[](const size_t index) const {
        if (index < mDequeFront.size()) {
            return mDequeFront[mDequeFront.size() - index - 1];
        } else {
            return mDequeBack[index - mDequeFront.size()];
        }
    }
};
