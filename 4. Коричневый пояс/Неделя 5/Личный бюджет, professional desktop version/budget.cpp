#include <iostream>
#include <ctime>
#include <vector>
#include <tuple>

using namespace std;

class Date {
    int mYear;
    int mMonth;
    int mDay;
public:
    friend istream &operator>>(istream &stream, Date &date);

    Date() : mYear(2000), mMonth(1), mDay(1) {}

    explicit Date(int year, int month, int day) : mYear(year), mMonth(month), mDay(day) {}

    bool operator<(const Date &other) const {
        return make_tuple(mYear, mMonth, mDay) < make_tuple(other.mYear, other.mMonth, other.mDay);
    }

    bool operator>(const Date &other) const {
        return make_tuple(mYear, mMonth, mDay) > make_tuple(other.mYear, other.mMonth, other.mDay);
    }

    bool operator==(const Date &other) const {
        return make_tuple(mYear, mMonth, mDay) == make_tuple(other.mYear, other.mMonth, other.mDay);
    }

    time_t AsTimestamp() const {
        std::tm t;
        t.tm_sec = 0;
        t.tm_min = 0;
        t.tm_hour = 0;
        t.tm_mday = mDay;
        t.tm_mon = mMonth - 1;
        t.tm_year = mYear - 1900;
        t.tm_isdst = 0;
        return mktime(&t);
    }
};

istream &operator>>(istream &stream, Date &date) {
    stream >> date.mYear;
    stream.ignore();
    stream >> date.mMonth;
    stream.ignore();
    return stream >> date.mDay;
}

uint32_t ComputeDaysDiff(const Date &date_to, const Date &date_from) {
    const time_t timestamp_to = date_to.AsTimestamp();
    const time_t timestamp_from = date_from.AsTimestamp();
    static const int SECONDS_IN_DAY = 86400;
    time_t t = timestamp_to - timestamp_from;
    return 1 + (t > 0 ? t : -t) / SECONDS_IN_DAY;
}

class BudgetManager {
    vector<pair<double, double>> mMoneyPerDays;
public:
    BudgetManager() : mMoneyPerDays(36600) {}

    void Earn(const pair<Date, Date> &range, double money) {
        double moneyPerDay = money / ComputeDaysDiff(range.first, range.second);
        size_t begin = ComputeDaysDiff(Date(), range.first);
        size_t end = ComputeDaysDiff(Date(), range.second);
        for (size_t i = begin; i <= end; i++) {
            mMoneyPerDays[i].first += moneyPerDay;
        }
    }

    double ComputeIncome(const pair<Date, Date> &range) const {
        double result = 0.0;
        size_t begin = ComputeDaysDiff(Date(), range.first);
        size_t end = ComputeDaysDiff(Date(), range.second);
        for (size_t i = begin; i <= end; i++) {
            result += mMoneyPerDays[i].first - mMoneyPerDays[i].second;
        }
        return result;
    }

    void PayTax(const pair<Date, Date> &range, int tax) {
        size_t begin = ComputeDaysDiff(Date(), range.first);
        size_t end = ComputeDaysDiff(Date(), range.second);
        for (size_t i = begin; i <= end; i++) {
            mMoneyPerDays[i].first *= (1 - tax * 0.01);
        }
    }

    void Spend(const pair<Date, Date> &range, double money) {
        double moneyPerDay = money / ComputeDaysDiff(range.first, range.second);
        size_t begin = ComputeDaysDiff(Date(), range.first);
        size_t end = ComputeDaysDiff(Date(), range.second);
        for (size_t i = begin; i <= end; i++) {
            mMoneyPerDays[i].second += moneyPerDay;
        }
    }
};


int main() {
    std::cout.precision(25);
    BudgetManager budgetManager;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        string query;
        pair<Date, Date> range;
        cin >> query >> range.first >> range.second;
        if (query == "Earn") {
            double money;
            cin >> money;
            budgetManager.Earn(range, money);
        } else if (query == "ComputeIncome") {
            cout << budgetManager.ComputeIncome(range) << endl;
        } else if (query == "PayTax") {
            int tax;
            cin >> tax;
            budgetManager.PayTax(range, tax);
        } else if (query == "Spend") {
            double money;
            cin >> money;
            budgetManager.Spend(range, money);
        }
    }
    return 0;
}
