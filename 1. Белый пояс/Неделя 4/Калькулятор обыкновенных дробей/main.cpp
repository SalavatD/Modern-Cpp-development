#include <iostream>
#include <sstream>
#include <exception>

using namespace std;

int GreatestCommonDivisor(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return GreatestCommonDivisor(b, a % b);
    }
}

class Rational {
public:
    Rational() {
        numerator = 0;
        denominator = 1;
    }

    Rational(int new_numerator, int new_denominator) {
        if (new_denominator == 0) {
            throw invalid_argument("");
        }
        const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
        numerator = new_numerator / gcd;
        denominator = new_denominator / gcd;
        if (denominator < 0) {
            denominator = -denominator;
            numerator = -numerator;
        }
    }

    int Numerator() const {
        return numerator;
    }

    int Denominator() const {
        return denominator;
    }

private:
    int numerator;
    int denominator;
};

bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.Numerator() == rhs.Numerator() &&
           lhs.Denominator() == rhs.Denominator();
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
    return {
            lhs.Numerator() * rhs.Numerator(),
            lhs.Denominator() * rhs.Denominator()
    };
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
    if (rhs.Numerator() == 0) {
        throw domain_error("");
    }
    return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}

istream &operator>>(istream &is, Rational &r) {
    int n, d;
    char c;

    if (is) {
        is >> n >> c >> d;
        if (is) {
            if (c == '/') {
                r = Rational(n, d);
            } else {
                is.setstate(ios_base::failbit);
            }
        }
    }

    return is;
}

ostream &operator<<(ostream &os, const Rational &r) {
    return os << r.Numerator() << '/' << r.Denominator();
}

int main() {
    Rational lhs;
    Rational rhs;
    char operation;
    try {
        cin >> lhs;
        cin.ignore(1);
        cin >> operation;
        cin.ignore(1);
        cin >> rhs;
    } catch (exception &e) {
        cout << "Invalid argument" << endl;
        return 0;
    }

    Rational result;
    try {
        switch (operation) {
            case '+': {
                result = lhs + rhs;
                break;
            }
            case '-': {
                result = lhs - rhs;
                break;
            }
            case '*': {
                result = lhs * rhs;
                break;
            }
            case '/': {
                result = lhs / rhs;
                break;
            }
            default: {
                cout << "Invalid operation" << endl;
            }
        }
    }
    catch (exception &e) {
        cout << "Division by zero" << endl;
        return 0;
    }

    cout << result << endl;
    return 0;
}
