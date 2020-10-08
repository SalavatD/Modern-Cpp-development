#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <unordered_set>

using namespace std;

template<class T>
class ObjectPool {
    unordered_multiset<T *> mAllocatedObjects;
    queue<T *> mDeallocatedObjects;

public:
    T *Allocate() {
        T *object;
        if (mDeallocatedObjects.empty()) {
            object = new T;
        } else {
            object = mDeallocatedObjects.front();
            mDeallocatedObjects.pop();
        }
        mAllocatedObjects.insert(object);
        return object;
    }

    T *TryAllocate() {
        if (mDeallocatedObjects.empty()) {
            return nullptr;
        } else {
            return Allocate();
        }
    }

    void Deallocate(T *object) {
        auto iterator = mAllocatedObjects.find(object);
        if (iterator == mAllocatedObjects.end()) {
            throw invalid_argument("");
        }
        mDeallocatedObjects.push(*iterator);
        mAllocatedObjects.erase(iterator);
    }

    ~ObjectPool() {
        for (auto &object  : mAllocatedObjects) {
            delete object;
        }
        while (!mDeallocatedObjects.empty()) {
            delete mDeallocatedObjects.front();
            mDeallocatedObjects.pop();
        }
    }
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
