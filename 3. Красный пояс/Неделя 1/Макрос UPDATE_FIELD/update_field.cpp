#include <iomanip>
#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

#define UPDATE_FIELD(ticket, field, values) { \
    auto it = values.find(#field);            \
    if (it != values.end()) {                 \
        istringstream is(it->second);         \
        is >> ticket.field;                   \
    }                                         \
}

bool operator==(const Date &l, const Date &r) {
    return make_tuple(l.year, l.month, l.day) == make_tuple(r.year, r.month, r.day);
}

bool operator==(const Time &l, const Time &r) {
    return make_tuple(l.hours, l.minutes) == make_tuple(r.hours, r.minutes);
}

istream &operator>>(istream &is, Date &date) {
    is >> date.year;
    is.ignore() >> date.month;
    is.ignore() >> date.day;
    return is;
}

istream &operator>>(istream &is, Time &time) {
    is >> time.hours;
    is.ignore() >> time.minutes;
    return is;
}

ostream &operator<<(ostream &os, const Date &date) {
    os << setfill('0');
    os << setw(4) << date.year;
    os << '.';
    os << setw(2) << date.month;
    os << '.';
    os << setw(2) << date.day;
    return os;
}

ostream &operator<<(ostream &os, const Time &time) {
    os << setfill('0');
    os << setw(2) << time.hours;
    os << ':';
    os << setw(2) << time.minutes;
    return os;
}
