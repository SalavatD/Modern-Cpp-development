#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int range_length;
    cin >> range_length;

    vector<int> permutation(range_length);
    iota(permutation.rbegin(), permutation.rend(), 1);

    do {
        for (int num : permutation) {
            cout << num << ' ';
        }
        cout << endl;
    } while (prev_permutation(permutation.begin(), permutation.end()));

    return 0;
}
