#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int result = -2;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == 'f') {
            if (result == -2) {
                result++;
            } else if (result == -1) {
                result = i;
            }
        }
    }
    cout << result << endl;
    return 0;
}
