#include <iostream>
#include <string>

using namespace std;

int main() {
    string a, b, c;
    cin >> a >> b >> c;

    if (a <= b && a <= c) {
        cout << a << endl;
        return 0;
    }
    if (b <= a && b <= c) {
        cout << b << endl;
        return 0;
    }
    cout << c << endl;
    return 0;
}
