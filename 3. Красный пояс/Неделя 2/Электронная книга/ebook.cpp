#include <iomanip>
#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

class ReadingManager {
    map<int, int> mUsers;
    map<int, set<int>> mPages;

public:
    void Read(const int &userNumber, const int &pageNumber) {
        if (mUsers.count(userNumber)) {
            int previousPage = mUsers.at(userNumber);
            mPages.at(previousPage).erase(userNumber);
            if (mPages.at(previousPage).empty()) {
                mPages.erase(previousPage);
            }
        }
        mUsers[userNumber] = pageNumber;
        mPages[pageNumber].insert(userNumber);
    }

    [[nodiscard]] double Cheer(const int &userNumber) const {
        if (!mUsers.count(userNumber)) {
            return 0;
        }
        if (mUsers.size() == 1) {
            return 1;
        }
        auto iteratorEnd = mPages.find(mUsers.at(userNumber));
        if (iteratorEnd == mPages.begin()) {
            return 0;
        }
        double totalUsers = mUsers.size();
        double findUsers = 0;
        for (auto i = mPages.begin(); i != iteratorEnd; i++) {
            findUsers += i->second.size();
        }
        return findUsers / (totalUsers - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ReadingManager manager;
    int query_count;
    cin >> query_count;
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;
        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    return 0;
}
