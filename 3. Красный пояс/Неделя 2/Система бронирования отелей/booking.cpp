#include <iostream>
#include <map>
#include <set>
#include <queue>

using namespace std;

struct Booking {
    long long mTime;
    string mHotelName;
    int mClientId;
    int mRoomCount;
};

class BookingManager {
    static const long long SECONDS_IN_DAY = 86400;

    map<string, set<int>> mClients;
    map<string, int> mRooms;
    queue<Booking> mBookings;

public:
    void Book(const long long &time, const string &hotelName, const int &clientId, const int &roomCount) {
        while (mBookings.front().mTime <= (time - SECONDS_IN_DAY) && !mBookings.empty()) {
            mClients.at(mBookings.front().mHotelName).erase(mBookings.front().mClientId);
            mRooms.at(mBookings.front().mHotelName) -= mBookings.front().mRoomCount;
            mBookings.pop();
        }
        mBookings.push({time, hotelName, clientId, roomCount});
        mClients[hotelName].insert(clientId);
        mRooms[hotelName] += roomCount;
    }

    [[nodiscard]] int Clients(const string &hotelName) const {
        try {
            return mClients.at(hotelName).size();
        } catch (const out_of_range &outOfRange) {
            return 0;
        }
    }

    [[nodiscard]] int Rooms(const string &hotelName) const {
        try {
            return mRooms.at(hotelName);
        } catch (const out_of_range &outOfRange) {
            return 0;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    BookingManager manager;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string commandCode;
        cin >> commandCode;
        if (commandCode == "BOOK") {
            long long time;
            string hotelName;
            int clientId;
            int roomCount;
            cin >> time >> hotelName >> clientId >> roomCount;
            manager.Book(time, hotelName, clientId, roomCount);
        } else {
            string hotelName;
            cin >> hotelName;
            if (commandCode == "CLIENTS") {
                cout << manager.Clients(hotelName) << '\n';
            } else if (commandCode == "ROOMS") {
                cout << manager.Rooms(hotelName) << '\n';
            }
        }
    }
    return 0;
}
