#include "stats.h"

Stats::Stats() {
    for (const auto &item: METHOD_CODES) {
        mMethodStats[item] = 0;
    }
    for (const auto &item: URI_CODES) {
        mUriStats[item] = 0;
    }
}

void Stats::AddMethod(string_view method) {
    auto it = find(begin(METHOD_CODES), end(METHOD_CODES), method);
    if (it == end(METHOD_CODES)) {
        mMethodStats["UNKNOWN"]++;
    } else {
        mMethodStats[*it]++;
    }
}

void Stats::AddUri(string_view uri) {
    auto it = find(begin(URI_CODES), end(URI_CODES), uri);
    if (it == end(URI_CODES)) {
        mUriStats["unknown"]++;
    } else {
        mUriStats[*it]++;
    }
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return mMethodStats;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return mUriStats;
}

HttpRequest ParseRequest(string_view line) {
    std::array<std::string_view, 3> requestData;
    line.remove_prefix(line.find_first_not_of(' '));
    for (auto i = 0; i < 3; i++) {
        auto find = line.find(' ');
        requestData[i] = line.substr(0, find);
        line.remove_prefix(find + 1);
    }
    return HttpRequest{requestData[0], requestData[1], requestData[2]};
}
