class SortedStrings {
    vector<string> data;
public:
    void AddString(const string &s) {
        data.push_back(s);
    }

    vector<string> GetSortedStrings() {
        sort(begin(data), end(data));
        return data;
    }
};
