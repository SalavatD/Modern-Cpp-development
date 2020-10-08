#pragma once

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
    int mYear;
    int mMonth;
    int mDay;

    friend bool operator==(const Date &, const Date &);

    friend bool operator<(const Date &, const Date &);

    friend bool operator<=(const Date &, const Date &);

    friend bool operator>(const Date &, const Date &);

    friend bool operator>=(const Date &, const Date &);

    friend bool operator!=(const Date &, const Date &);

    friend ostream &operator<<(ostream &os, const Date &date);

public:
    Date();

    Date(const string &dateString);

    string GetDate() const;
};
