#include "database.h"

void Database::Add(const Date &date, const string &event) {
    if (mDatesSet[date].insert(event).second) {
        mDatesVector[date].push_back(event);
    }
}

void Database::Print(ostream &os) const {
    os << mDatesVector;
}

string Database::Last(const Date &date) const {
    auto last = mDatesVector.upper_bound(date);
    if (last == mDatesVector.begin()) {
        return "No entries";
    } else {
        last = prev(last);
        return last->first.GetDate() + " " + last->second.back();
    }
}

ostream &operator<<(ostream &os, const DatesVector &datesVector) {
    for (const auto &date : datesVector) {
        for (const auto &event : date.second) {
            os << date.first.GetDate() << " " << event << endl;
        }
    }
    return os;
}
