#include <algorithm>
#include <utility>
#include <string>

template<typename RandomIt>
pair <RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, char prefix) {
    auto left = lower_bound(range_begin, range_end, string(1, prefix));
    char next_prefix = static_cast<char>(prefix + 1);
    auto right = lower_bound(range_begin, range_end, string(1, next_prefix));
    return {left, right};
}
