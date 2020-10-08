#include <string>
#include <iostream>
#include <iomanip>
#include <map>
#include <set>

using namespace std;
// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
    friend bool operator<(const Date &, const Date &);

    friend istream &operator>>(istream &, Date &);

    friend ostream &operator<<(ostream &, const Date &);

public:
    Date() {
        day = 0;
        month = 0;
        year = 0;
    }

    Date(int year, int month, int day) {
        if (month < 1 || month > 12) {
            throw invalid_argument("Month value is invalid: " + to_string(month));
        }
        if (day < 1 || day > 31) {
            throw invalid_argument("Day value is invalid: " + to_string(day));
        }
        this->day = day;
        this->month = month;
        this->year = year;
    }

private:
    int year;
    int month;
    int day;
};

bool operator<(const Date &lhs, const Date &rhs) {
    return lhs.year * 365 + lhs.month * 31 + lhs.day <
           rhs.year * 365 + rhs.month * 31 + rhs.day;
}

istream &operator>>(istream &stream, Date &date) {
    string date_string;
    stream >> date_string;
    stringstream date_stream(date_string);
    int year;
    date_stream >> year;
    if (date_stream.peek() != '-') {
        throw invalid_argument("Wrong date format: " + date_string);
    }
    date_stream.ignore(1);
    if ((date_stream.peek() < '0' ||
         date_stream.peek() > '9') &&
         date_stream.peek() != '+' &&
         date_stream.peek() != '-') {
        throw invalid_argument("Wrong date format: " + date_string);
    }
    int month;
    date_stream >> month;
    if (date_stream.peek() != '-') {
        throw invalid_argument("Wrong date format: " + date_string);
    }
    date_stream.ignore(1);
    if ((date_stream.peek() < '0' ||
         date_stream.peek() > '9') &&
         date_stream.peek() != '+' &&
         date_stream.peek() != '-') {
        throw invalid_argument("Wrong date format: " + date_string);
    }
    int day;
    date_stream >> day;
    if (date_stream.peek() != EOF) {
        throw runtime_error("Wrong date format: " + date_string);
    }
    date = Date(year, month, day);
    return stream;
}

ostream &operator<<(ostream &stream, const Date &date) {
    stream << setfill('0');
    if (date.year < 0) {
        stream << '-' << setw(4) << -date.year;
    } else {
        stream << setw(4) << date.year;
    }
    stream << "-";
    stream << setw(2) << date.month;
    stream << "-";
    stream << setw(2) << date.day;
    return stream;
}

class Database {
public:
    void AddEvent(const Date &date, const string &event) {
        values[date].insert(event);
    }

    bool DeleteEvent(const Date &date, const string &event) {
        if (!values.empty()) {
            if (values[date].count(event) > 0) {
                values[date].erase(event);
                return true;
            }
        }

        return false;
    }

    int DeleteDate(const Date &date) {
        int counter = values[date].size();
        values.erase(date);
        return counter;
    }

    set<string> Find(const Date &date) const {
        if (values.find(date) != values.end()) {
            return values.at(date);
        } else {
            return {};
        }
    }

    void Print() const {
        for (const auto &i : values) {
            for (const auto &j : i.second) {
                cout << i.first << " " << j << endl;
            }
        }
    }

private:
    map<Date, set<string>> values;
};

ostream &operator<<(ostream &stream, const set<string> &set_of_string) {
    string separator;
    stringstream string_builder;
    for (const string &i : set_of_string) {
        string_builder << separator << i;
        separator = "\n";
    }
    stream << string_builder.str();
    return stream;
}

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        // Считайте команды с потока ввода и обработайте каждую
        stringstream command_stream(command);
        string command_code;
        command_stream >> command_code;
        if (command_code == "Add") {
            Date date;
            try {
                command_stream >> date;
                string event;
                command_stream >> event;
                db.AddEvent(date, event);
            }
            catch (exception &e) {
                cout << e.what() << endl;
                break;
            }
        } else if (command_code == "Del") {
            Date date;
            try {
                command_stream >> date;
                if (command_stream.peek() != ' ') {
                    cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
                } else {
                    string event;
                    command_stream >> event;
                    if (db.DeleteEvent(date, event)) {
                        cout << "Deleted successfully" << endl;
                    } else {
                        cout << "Event not found" << endl;
                    }
                }
            }
            catch (exception &e) {
                cout << e.what() << endl;
                break;
            }
        } else if (command_code == "Find") {
            Date date;
            try {
                command_stream >> date;
                cout << db.Find(date) << endl;
            }
            catch (exception &e) {
                cout << e.what() << endl;
                break;
            }
        } else if (command_code == "Print") {
            db.Print();
        } else if (!command.empty()) {
            cout << "Unknown command: " << command_code << endl;
        }
    }

    return 0;
}
