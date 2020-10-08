#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    // Напишите реализацию функции,
    // не копируя сортируемые элементы
    auto length = distance(range_begin, range_end);
    if (length < 2) {
        return;
    }
    vector<typename RandomIt::value_type> v(make_move_iterator(range_begin), make_move_iterator(range_end));
    auto first = range_begin + length / 3;
    auto second = range_begin + 2 * length / 3;

    MergeSort(range_begin, first);
    MergeSort(first, second);
    MergeSort(second, range_end);
    vector<typename RandomIt::value_type> temp;
    merge(make_move_iterator(range_begin), make_move_iterator(first), make_move_iterator(first),
          make_move_iterator(second), back_inserter(temp));
    merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()), make_move_iterator(second),
          make_move_iterator(range_end), range_begin);
}

void TestIntVector() {
    vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
    MergeSort(begin(numbers), end(numbers));
    ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestIntVector);
    return 0;
}

