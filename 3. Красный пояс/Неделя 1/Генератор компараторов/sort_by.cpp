#include <iomanip>
#include <algorithm>
#include "airline_ticket.h"

using namespace std;

#define SORT_BY(field) ([](const AirlineTicket& lhs, const AirlineTicket& rhs) { return lhs.field < rhs.field; })

bool operator==(const Date &l, const Date &r) {
    return make_tuple(l.year, l.month, l.day) == make_tuple(r.year, r.month, r.day);
}

bool operator==(const Time &l, const Time &r) {
    return make_tuple(l.hours, l.minutes) == make_tuple(r.hours, r.minutes);
}

bool operator<(const Date &l, const Date &r) {
    return make_tuple(l.year, l.month, l.day) < make_tuple(r.year, r.month, r.day);
}

bool operator<(const Time &l, const Time &r) {
    return make_tuple(l.hours, l.minutes) < make_tuple(r.hours, r.minutes);
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
