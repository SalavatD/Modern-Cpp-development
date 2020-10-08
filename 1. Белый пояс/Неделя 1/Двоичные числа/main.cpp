#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> binary;
    while (n > 0) {
        binary.push_back(n % 2);
        n /= 2;
    }
    for (auto i = binary.end() - 1; i >= binary.begin(); i--) {
        cout << *i;
    }
    cout << endl;
    return 0;
}
