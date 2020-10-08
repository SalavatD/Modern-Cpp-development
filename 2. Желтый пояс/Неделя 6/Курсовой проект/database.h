#pragma once

#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include "date.h"

using namespace std;

using DatesVector = map<Date, vector<string>>;
using DatesSet = map<Date, set<string>>;

class Database {
    DatesVector mDatesVector;
    DatesSet mDatesSet;

public:
    void Add(const Date &date, const string &event);

    void Print(ostream &os) const;

    string Last(const Date &date) const;

    template<typename T>
    vector<string> FindIf(const T &predicate) const {
        vector<string> result;
        for (const auto &date : mDatesVector) {
            for (const auto &event : date.second) {
                if (predicate(date.first, event)) {
                    result.push_back(date.first.GetDate() + " " + event);
                }
            }
        }
        return result;
    }

    template<typename T>
    int RemoveIf(const T &predicate) {
        int result = 0;
        DatesVector remainingDatesVector;
        DatesSet remainingDatesSet;
        for (auto &date : mDatesVector) {
            size_t dateEventsCount = date.second.size();
            auto start = stable_partition(date.second.begin(), date.second.end(), [predicate, date](const auto &event) {
                return predicate(date.first, event);
            });
            if (start == date.second.end()) {
                result += dateEventsCount;
            } else {
                remainingDatesVector[date.first] = vector<string>(start, date.second.end());
                remainingDatesSet[date.first] = set<string>(start, date.second.end());
                result += dateEventsCount - remainingDatesVector.at(date.first).size();
            }
        }
        mDatesVector = remainingDatesVector;
        mDatesSet = remainingDatesSet;
        return result;
    }
};

ostream &operator<<(ostream &os, const DatesVector &datesVector);
