#include "test_runner.h"

#include <cstddef>  // нужно для nullptr_t

using namespace std;

// Реализуйте шаблон класса UniquePtr
template<typename T>
class UniquePtr {
    T *mPointer;
public:
    UniquePtr() : mPointer(nullptr) {}

    UniquePtr(T *ptr) : mPointer(ptr) {}

    UniquePtr(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) : mPointer(other.Release()) {}

    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr &operator=(nullptr_t) {
        Reset(nullptr);
        return *this;
    }

    UniquePtr &operator=(UniquePtr &&other) {
        Reset(nullptr);
        mPointer = other.Release();
        return *this;
    }

    ~UniquePtr() {
        delete mPointer;
    }

    T &operator*() const {
        return *Get();
    }

    T *operator->() const {
        return Get();
    }

    T *Release() {
        T *pointer = mPointer;
        mPointer = nullptr;
        return pointer;
    }

    void Reset(T *ptr) {
        delete mPointer;
        mPointer = ptr;
    }

    void Swap(UniquePtr &other) {
        swap(mPointer, other.mPointer);
    }

    T *Get() const {
        return mPointer;
    }
};

struct Item {
    static int counter;
    int value;

    Item(int v = 0) : value(v) {
        ++counter;
    }

    Item(const Item &other) : value(other.value) {
        ++counter;
    }

    ~Item() {
        --counter;
    }
};

int Item::counter = 0;


void TestLifetime() {
    Item::counter = 0;
    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        ptr.Reset(new Item);
        ASSERT_EQUAL(Item::counter, 1);
    }
    ASSERT_EQUAL(Item::counter, 0);

    {
        UniquePtr<Item> ptr(new Item);
        ASSERT_EQUAL(Item::counter, 1);

        auto rawPtr = ptr.Release();
        ASSERT_EQUAL(Item::counter, 1);

        delete rawPtr;
        ASSERT_EQUAL(Item::counter, 0);
    }
    ASSERT_EQUAL(Item::counter, 0);
}

void TestGetters() {
    UniquePtr<Item> ptr(new Item(42));
    ASSERT_EQUAL(ptr.Get()->value, 42);
    ASSERT_EQUAL((*ptr).value, 42);
    ASSERT_EQUAL(ptr->value, 42);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestLifetime);
    RUN_TEST(tr, TestGetters);
}
