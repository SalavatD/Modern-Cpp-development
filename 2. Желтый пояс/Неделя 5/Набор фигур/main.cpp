#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <cmath>

#define PI 3.14

using namespace std;

class Figure {
public:
    Figure(const string &name) : mName(name) {}

    virtual const string Name() const = 0;

    virtual const double Perimeter() const = 0;

    virtual const double Area() const = 0;

    const string mName;
};

class Triangle : public Figure {
    const double mPerimeter;
    const double mArea;

public:
    Triangle(int &a, int &b, int &c) :
            Figure("TRIANGLE"),
            mPerimeter(a + b + c),
            mArea(sqrt(mPerimeter / 2 * (mPerimeter / 2 - a) * (mPerimeter / 2 - b) * (mPerimeter / 2 - c))) {}

    const double Perimeter() const override {
        return mPerimeter;
    }

    const double Area() const override {
        return mArea;
    }

    const string Name() const override {
        return mName;
    }
};

class Rect : public Figure {
    const double mPerimeter;
    const double mArea;

public:
    Rect(int &a, int &b) : Figure("RECT"), mPerimeter(2 * (a + b)), mArea(a * b) {}

    const double Perimeter() const override {
        return mPerimeter;
    }

    const double Area() const override {
        return mArea;
    }

    const string Name() const override {
        return mName;
    }
};

class Circle : public Figure {
    const double mPerimeter;
    const double mArea;

public:
    Circle(int &r) : Figure("CIRCLE"), mPerimeter(2 * PI * r), mArea(PI * r * r) {}

    const double Perimeter() const override {
        return mPerimeter;
    }

    const double Area() const override {
        return mArea;
    }

    const string Name() const override {
        return mName;
    }
};

shared_ptr<Figure> CreateFigure(istringstream &is) {
    shared_ptr<Figure> figure;

    string figureName;
    is >> figureName;
    if (figureName == "RECT") {
        int a, b;
        is >> a >> b;
        figure = make_shared<Rect>(a, b);
        return figure;
    }
    if (figureName == "TRIANGLE") {
        int a, b, c;
        is >> a >> b >> c;
        figure = make_shared<Triangle>(a, b, c);
        return figure;
    }
    if (figureName == "CIRCLE") {
        int r;
        is >> r;
        figure = make_shared<Circle>(r);
        return figure;
    }
    throw std::invalid_argument("");
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            // Пропускаем "лишние" ведущие пробелы.
            // Подробнее об std::ws можно узнать здесь:
            // https://en.cppreference.com/w/cpp/io/manip/ws
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto &current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}