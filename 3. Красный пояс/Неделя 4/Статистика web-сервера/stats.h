#pragma once

#include "http_request.h"

#include <string_view>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Stats {
    map<string_view, int> mMethodStats;
    map<string_view, int> mUriStats;

public:
    array<string, 5> METHOD_CODES = {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
    array<string, 6> URI_CODES = {"/", "/order", "/product", "/basket", "/help", "unknown"};

    Stats();

    void AddMethod(string_view method);

    void AddUri(string_view uri);

    const map<string_view, int> &GetMethodStats() const;

    const map<string_view, int> &GetUriStats() const;
};

HttpRequest ParseRequest(string_view line);
