#include <iterator>
#include <set>

set<int>::const_iterator FindNearestElement(const set<int> &numbers, int border) {
    const auto first_not_less = numbers.lower_bound(border);

    if (first_not_less == numbers.begin()) {
        return first_not_less;
    }

    const auto last_less = prev(first_not_less);
    if (first_not_less == numbers.end()) {
        return last_less;
    }

    const bool is_left = (border - *last_less <= *first_not_less - border);
    return is_left ? last_less : first_not_less;
}
