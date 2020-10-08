#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <algorithm>
#include <future>

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

struct Stats {
    map<string, int> word_frequences;

    void operator+=(const Stats &other) {
        for (const auto &[key, value] : other.word_frequences) {
            word_frequences[key] += value;
        }
    }
};

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, IteratorRange<vector<string>::iterator> &&words) {
    Stats stats;
    for (const auto &word : words) {
        if (key_words.find(word) != key_words.end()) {
            stats.word_frequences[word]++;
        }
    }
    return stats;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input) {
    // Реализуйте эту функцию
    vector<std::string> words;
    string word;
    while (input >> word) {
        words.push_back(move(word));
    }
    vector<future<Stats>> futures;
    for (auto &page : Paginate(words, words.size() / 16)) {
        futures.push_back(std::async(ExploreKeyWordsSingleThread, ref(key_words), page));
    }
    Stats stats;
    for (auto &future : futures) {
        stats += future.get();
    }
    return stats;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks",  2},
            {"sucks",  1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
}
