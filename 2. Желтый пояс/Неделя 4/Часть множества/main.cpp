#include <iostream>
#include <set>
#include <vector>

using namespace std;

template<typename T>
vector <T> FindGreaterElements(const set <T> &elements, const T &border) {
    auto it = begin(elements);
    while (it != end(elements) && *it <= border) {
        ++it;
    }
    return {it, end(elements)};
}
