#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template<typename Object>
class PriorityCollection {
public:
    using Id = size_t;
    using Priority = size_t;

    PriorityCollection() : mNextId_(0) {}

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
    Id Add(Object object) {
        Id id = mNextId_++;
        mPriorityToId_.insert(make_pair(0, id));
        mIdToPriority_[id] = 0;
        mIdToObject_[id] = move(object);
        return id;
    }

    // Добавить все элементы диапазона [range_begin, range_end)
    // с помощью перемещения, записав выданные им идентификаторы
    // в диапазон [ids_begin, ...)
    template<typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin) {
        for (auto i = range_begin; i != range_end; i++, ids_begin++) {
            *ids_begin = Add(move(*i));
        }
    }

    // Определить, принадлежит ли идентификатор какому-либо
    // хранящемуся в контейнере объекту
    bool IsValid(Id id) const {
        try {
            mIdToObject_.at(id);
            return true;
        } catch (out_of_range &outOfRange) {
            return false;
        }
    }

    // Получить объект по идентификатору
    const Object &Get(Id id) const {
        return mIdToObject_.at(id);
    }

    // Увеличить приоритет объекта на 1
    void Promote(Id id) {
        mPriorityToId_.erase(make_pair(mIdToPriority_.at(id)++, id));
        mPriorityToId_.insert(make_pair(mIdToPriority_.at(id), id));
    }

    // Получить объект с максимальным приоритетом и его приоритет
    pair<const Object &, int> GetMax() const {
        Id id = prev(mPriorityToId_.end())->second;
        return {mIdToObject_.at(id), mIdToPriority_.at(id)};
    }

    // Аналогично GetMax, но удаляет элемент из контейнера
    pair<Object, int> PopMax() {
        Id id = prev(mPriorityToId_.end())->second;
        pair<Object, size_t> result(move(mIdToObject_.at(id)), mIdToPriority_.at(id));
        mPriorityToId_.erase(make_pair(mIdToPriority_.at(id)++, id));
        mIdToPriority_.erase(id);
        mIdToObject_.erase(id);
        return result;
    }

private:
    // Приватные поля и методы
    Id mNextId_;

    set<pair<Priority, Id>> mPriorityToId_;

    map<Id, Priority> mIdToPriority_;
    map<Id, Object> mIdToObject_;
};


class StringNonCopyable : public string {
public:
    using string::string;  // Позволяет использовать конструкторы строки
    StringNonCopyable(const StringNonCopyable &) = delete;

    StringNonCopyable(StringNonCopyable &&) = default;

    StringNonCopyable &operator=(const StringNonCopyable &) = delete;

    StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy() {
    PriorityCollection<StringNonCopyable> strings;
    const auto white_id = strings.Add("white");
    const auto yellow_id = strings.Add("yellow");
    const auto red_id = strings.Add("red");

    strings.Promote(yellow_id);
    for (int i = 0; i < 2; ++i) {
        strings.Promote(red_id);
    }
    strings.Promote(yellow_id);
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "red");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "yellow");
        ASSERT_EQUAL(item.second, 2);
    }
    {
        const auto item = strings.PopMax();
        ASSERT_EQUAL(item.first, "white");
        ASSERT_EQUAL(item.second, 0);
    }
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestNoCopy);
    return 0;
}
