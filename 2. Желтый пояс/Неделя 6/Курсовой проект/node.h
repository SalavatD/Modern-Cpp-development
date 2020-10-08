#pragma once

#include <memory>
#include "date.h"

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(const Date &date, const string &event) = 0;
};

class EmptyNode : public Node {
public:
    bool Evaluate(const Date &date, const string &event) override;
};

class DateComparisonNode : public Node {
    Comparison mComparison;
    Date mDate;

public:
    DateComparisonNode(const Comparison &comparison, const Date &date);

    bool Evaluate(const Date &date, const string &event) override;
};

class EventComparisonNode : public Node {
    Comparison mComparison;
    string mEvent;

public:
    EventComparisonNode(const Comparison &comparison, const string &event);

    bool Evaluate(const Date &date, const string &event) override;
};

class LogicalOperationNode : public Node {
    LogicalOperation mLogicalOperation;
    shared_ptr<Node> mLeftNode;
    shared_ptr<Node> mRightNode;

public:
    LogicalOperationNode(const LogicalOperation &logicalOperation,
                         const shared_ptr<Node> &leftNode,
                         const shared_ptr<Node> &rightNode);

    bool Evaluate(const Date &date, const string &event) override;
};
