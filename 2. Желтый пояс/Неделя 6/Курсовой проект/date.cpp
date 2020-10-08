#include "date.h"

Date::Date() : mYear(0), mMonth(0), mDay(0) {}

Date::Date(const string &dateString) {
    stringstream dateStringStream(dateString);
    dateStringStream >> mYear;
    dateStringStream.ignore();
    dateStringStream >> mMonth;
    dateStringStream.ignore();
    dateStringStream >> mDay;
}

string Date::GetDate() const {
    stringstream dateStringStream;
    dateStringStream << setfill('0');
    dateStringStream << setw(4);
    if (mYear < 0) {
        dateStringStream << '-';
        dateStringStream << -mYear;
    } else {
        dateStringStream << mYear;
    }
    dateStringStream << '-';
    dateStringStream << setw(2);
    dateStringStream << mMonth;
    dateStringStream << '-';
    dateStringStream << setw(2);
    dateStringStream << mDay;
    return dateStringStream.str();
}

bool operator==(const Date &lhs, const Date &rhs) {
    return tie(lhs.mYear, lhs.mMonth, lhs.mDay) == tie(rhs.mYear, rhs.mMonth, rhs.mDay);
}

bool operator<(const Date &lhs, const Date &rhs) {
    return tie(lhs.mYear, lhs.mMonth, lhs.mDay) < tie(rhs.mYear, rhs.mMonth, rhs.mDay);
}

bool operator<=(const Date &lhs, const Date &rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date &lhs, const Date &rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Date &lhs, const Date &rhs) {
    return !(lhs < rhs);
}

bool operator!=(const Date &lhs, const Date &rhs) {
    return !(lhs == rhs);
}

ostream &operator<<(ostream &os, const Date &date) {
    os << setfill('0');
    os << setw(4);
    if (date.mYear < 0) {
        os << '-';
        os << -date.mYear;
    } else {
        os << date.mYear;
    }
    os << '-';
    os << setw(2);
    os << date.mMonth;
    os << '-';
    os << setw(2);
    os << date.mDay;
    return os;
}