#include "node.h"

DateComparisonNode::DateComparisonNode(const Comparison &comparison, const Date &date) : mComparison(comparison),
                                                                                         mDate(date) {}

EventComparisonNode::EventComparisonNode(const Comparison &comparison, const string &event) : mComparison(comparison),
                                                                                              mEvent(event) {}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation &logicalOperation,
                                           const shared_ptr<Node> &leftNode,
                                           const shared_ptr<Node> &rightNode) : mLogicalOperation(logicalOperation),
                                                                                mLeftNode(leftNode),
                                                                                mRightNode(rightNode) {}

bool EmptyNode::Evaluate(const Date &date, const string &event) {
    return true;
}

bool DateComparisonNode::Evaluate(const Date &date, const string &event) {
    switch (mComparison) {
        case Comparison::Less:
            return date < mDate;
        case Comparison::LessOrEqual:
            return date <= mDate;
        case Comparison::Greater:
            return date > mDate;
        case Comparison::GreaterOrEqual:
            return date >= mDate;
        case Comparison::Equal:
            return date == mDate;
        case Comparison::NotEqual:
            return date != mDate;
    }
}

bool EventComparisonNode::Evaluate(const Date &date, const string &event) {
    switch (mComparison) {
        case Comparison::Less:
            return event < mEvent;
        case Comparison::LessOrEqual:
            return event <= mEvent;
        case Comparison::Greater:
            return event > mEvent;
        case Comparison::GreaterOrEqual:
            return event >= mEvent;
        case Comparison::Equal:
            return event == mEvent;
        case Comparison::NotEqual:
            return event != mEvent;
    }
}

bool LogicalOperationNode::Evaluate(const Date &date, const string &event) {
    switch (mLogicalOperation) {
        case LogicalOperation::Or:
            return mLeftNode->Evaluate(date, event) ||
                   mRightNode->Evaluate(date, event);
        case LogicalOperation::And:
            return mLeftNode->Evaluate(date, event) &&
                   mRightNode->Evaluate(date, event);
        default:
            return false;
    }
}
