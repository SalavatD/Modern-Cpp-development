#include <map>
#include <string>

string FindNameByYear(const map<int, string> &names, int year) {
    string name;
    for (const auto &item : names) {
        if (item.first <= year) {
            name = item.second;
        } else {
            break;
        }
    }
    return name;
}

class Person {
    map<int, string> firstNames;
    map<int, string> lastNames;

public:
    void ChangeFirstName(int year, const string &first_name) {
        firstNames[year] = first_name;
    }

    void ChangeLastName(int year, const string &last_name) {
        lastNames[year] = last_name;
    }

    string GetFullName(int year) {
        const string first_name = FindNameByYear(firstNames, year);
        const string last_name = FindNameByYear(lastNames, year);
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        } else if (first_name.empty()) {
            return last_name + " with unknown first name";
        } else if (last_name.empty()) {
            return first_name + " with unknown last name";
        } else {
            return first_name + " " + last_name;
        }
    }
};
