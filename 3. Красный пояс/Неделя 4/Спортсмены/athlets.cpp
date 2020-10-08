#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int MAX_PLAYERS = 100'000;
    int n;
    cin >> n;
    list<int> players;
    vector<list<int>::iterator> playersPositions(MAX_PLAYERS + 1, players.end());
    for (int i = 0; i < n; i++) {
        int playerNumber, nextPlayerNumber;
        cin >> playerNumber >> nextPlayerNumber;
        playersPositions[playerNumber] = players.insert(playersPositions[nextPlayerNumber], playerNumber);
    }
    for (const auto &player : players) {
        cout << player << '\n';
    }
    return 0;
}
