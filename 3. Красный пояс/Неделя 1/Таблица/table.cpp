#include <vector>

using namespace std;

template<typename T>
class Table {
    size_t mRows;
    size_t mColumns;
    vector<vector<T>> mData;
public:
    Table(size_t rows, size_t columns) {
        Resize(rows, columns);
    }

    void Resize(size_t rows, size_t columns) {
        mRows = rows;
        mColumns = columns;
        mData.resize(rows);
        for (auto &c : mData) {
            c.resize(columns);
        }
    }

    [[nodiscard]] pair<size_t, size_t> Size() const {
        return make_pair(mRows * bool(mColumns), mColumns * bool(mRows));
    }

    vector<T> &operator[](const int index) {
        return mData[index];
    }

    const vector<T> &operator[](const int index) const {
        return mData[index];
    }
};