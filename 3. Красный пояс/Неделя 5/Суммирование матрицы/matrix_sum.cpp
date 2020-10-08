#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>

using namespace std;

template<typename Iterator>
class IteratorRange {
    Iterator mBegin;
    Iterator mEnd;

public:
    IteratorRange<Iterator>(Iterator begin, Iterator end) : mBegin(begin), mEnd(end) {}

    auto begin() const {
        return mBegin;
    }

    auto end() const {
        return mEnd;
    }

    size_t size() const {
        return distance(mBegin, mEnd);
    }
};

template<typename Iterator>
IteratorRange<Iterator> make_range(Iterator begin, Iterator end) {
    return IteratorRange<Iterator>(begin, end);
}

template<typename Iterator>
class Paginator {
    vector<IteratorRange<Iterator>> mPages;

public:
    Paginator<Iterator>(Iterator begin, Iterator end, size_t page_size) {
        if (distance(begin, end)) {
            if (page_size >= distance(begin, end)) {
                mPages.push_back(make_range(begin, end));
            } else {
                Iterator left;
                Iterator right = begin;
                while (right != end) {
                    left = right;
                    right += min(page_size, size_t(distance(right, end)));
                    mPages.push_back(make_range(left, right));
                }
            }
        }
    }

    auto begin() const {
        return mPages.begin();
    }

    auto end() const {
        return mPages.end();
    }

    size_t size() const {
        return mPages.size();
    }
};

template<typename C>
auto Paginate(C &c, size_t page_size) {
    return Paginator(begin(c), end(c), page_size);
}

int64_t CalculateMatrixSum(const vector<vector<int>> &matrix) {
    // Реализуйте эту функцию
    size_t pageSize = 1125;

    Paginator<vector<vector<int>>::const_iterator> paginator(begin(matrix), end(matrix), pageSize);

    vector<future<int64_t>> futures;
    vector<int64_t> partialSums;

    futures.reserve(paginator.size());
    partialSums.reserve(paginator.size());

    for (const auto &i : paginator) {
        futures.push_back(async([i]() {
            int64_t result = 0;
            for (const auto &j : i) {
                result += accumulate(j.begin(), j.end(), 0LL);
            }
            return result;
        }));
    }

    for (auto &i : futures) {
        partialSums.push_back(i.get());
    }

    return accumulate(partialSums.begin(), partialSums.end(), 0LL);
}

void TestCalculateMatrixSum() {
    const vector<vector<int>> matrix = {
            {1,  2,  3,  4},
            {5,  6,  7,  8},
            {9,  10, 11, 12},
            {13, 14, 15, 16}
    };
    ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestCalculateMatrixSum);
}
