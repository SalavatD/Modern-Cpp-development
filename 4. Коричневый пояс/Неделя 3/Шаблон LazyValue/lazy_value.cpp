#include "test_runner.h"

#include <functional>
#include <string>

using namespace std;

template<typename T>
class LazyValue {
public:
    explicit LazyValue(std::function<T()> init) : mInit(std::move(init)) {}

    bool HasValue() const {
        return mValue.has_value();
    }

    const T &Get() const {
        if (!mValue.has_value()) {
            mValue = mInit();
        }
        return mValue.value();
    }

private:
    std::function<T()> mInit;
    mutable std::optional<T> mValue;
};

void UseExample() {
    const string big_string = "Giant amounts of memory";

    LazyValue<string> lazy_string([&big_string] { return big_string; });

    ASSERT(!lazy_string.HasValue());
    ASSERT_EQUAL(lazy_string.Get(), big_string);
    ASSERT_EQUAL(lazy_string.Get(), big_string);
}

void TestInitializerIsntCalled() {
    bool called = false;

    {
        LazyValue<int> lazy_int([&called] {
            called = true;
            return 0;
        });
    }
    ASSERT(!called);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, UseExample);
    RUN_TEST(tr, TestInitializerIsntCalled);
    return 0;
}
