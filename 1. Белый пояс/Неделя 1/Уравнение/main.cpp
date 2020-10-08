#include <iostream>
#include <cmath>

using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;
    if (a != 0) {
        double d = pow(b, 2) - 4 * a * c;
        if (d == 0) {
            cout << -b / (2 * a) << endl;
        } else if (d > 0) {
            cout << (-b + sqrt(d)) / (2 * a) << ' ';
            cout << (-b - sqrt(d)) / (2 * a) << endl;
        }
    } else if (b != 0) {
        cout << -c / b << endl;
    }
    return 0;
}
