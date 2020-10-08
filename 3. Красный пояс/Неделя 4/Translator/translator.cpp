#include "test_runner.h"
#include <deque>
#include <map>

using namespace std;

class Translator {
    map<string_view, string_view> forward;
    map<string_view, string_view> backward;
    deque<string> data;

    string_view GetClonedView(string_view s) {
        for (const auto *map_ptr : {&forward, &backward}) {
            const auto it = map_ptr->find(s);
            if (it != map_ptr->end()) {
                return it->first;
            }
        }
        return data.emplace_back(s);
    }

    static string_view Translate(const map<string_view, string_view> &dict, string_view s) {
        if (const auto it = dict.find(s); it != dict.end()) {
            return it->second;
        } else {
            return {};
        }
    }

public:
    void Add(string_view source, string_view target) {
        const string_view source_view = GetClonedView(source);
        const string_view target_view = GetClonedView(target);
        forward[source_view] = target_view;
        backward[target_view] = source_view;
    }

    string_view TranslateForward(string_view source) const {
        return Translate(forward, source);
    }

    string_view TranslateBackward(string_view target) const {
        return Translate(backward, target);
    }
};


void TestSimple() {
    Translator translator;
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));

    ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
    ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
    ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSimple);
    return 0;
}
