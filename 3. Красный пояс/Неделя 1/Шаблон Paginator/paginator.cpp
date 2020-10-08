#include <vector>

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
