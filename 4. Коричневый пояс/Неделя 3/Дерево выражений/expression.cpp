#include "Common.h"
#include "test_runner.h"

#include <sstream>

using namespace std;

string Print(const Expression *e) {
    if (!e) {
        return "Null expression provided";
    }
    stringstream output;
    output << e->ToString() << " = " << e->Evaluate();
    return output.str();
}

namespace Expr {
    class Value : public Expression {
        int mValue;
    public:
        explicit Value(int value) : mValue(value) {}

        int Evaluate() const override {
            return mValue;
        }

        string ToString() const override {
            return to_string(mValue);
        }
    };

    class Sum : public Expression {
        unique_ptr<Expression> mLeft;
        unique_ptr<Expression> mRight;
    public:
        Sum(unique_ptr<Expression> left, unique_ptr<Expression> right) : mLeft(move(left)), mRight(move(right)) {}

        int Evaluate() const override {
            return mLeft->Evaluate() + mRight->Evaluate();
        }

        string ToString() const override {
            return "(" + mLeft->ToString() + ")+(" + mRight->ToString() + ")";
        }
    };

    class Product : public Expression {
        unique_ptr<Expression> mLeft;
        unique_ptr<Expression> mRight;
    public:
        Product(unique_ptr<Expression> left, unique_ptr<Expression> right) : mLeft(move(left)), mRight(move(right)) {}

        int Evaluate() const override {
            return mLeft->Evaluate() * mRight->Evaluate();
        }

        string ToString() const override {
            return "(" + mLeft->ToString() + ")*(" + mRight->ToString() + ")";
        }
    };
}

ExpressionPtr Value(int value) {
    return make_unique<Expr::Value>(Expr::Value(value));
}

ExpressionPtr Sum(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<Expr::Sum>(Expr::Sum(move(left), move(right)));
}

ExpressionPtr Product(ExpressionPtr left, ExpressionPtr right) {
    return make_unique<Expr::Product>(Expr::Product(move(left), move(right)));
}

void Test() {
    ExpressionPtr e1 = Product(Value(2), Sum(Value(3), Value(4)));
    ASSERT_EQUAL(Print(e1.get()), "(2)*((3)+(4)) = 14");

    ExpressionPtr e2 = Sum(move(e1), Value(5));
    ASSERT_EQUAL(Print(e2.get()), "((2)*((3)+(4)))+(5) = 19");

    ASSERT_EQUAL(Print(e1.get()), "Null expression provided");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, Test);
    return 0;
}