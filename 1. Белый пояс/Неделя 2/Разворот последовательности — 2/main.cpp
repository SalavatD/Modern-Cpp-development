vector<int> Reversed(const vector<int> &input) {
    vector<int> result;
    for (size_t i = input.size() - 1; i >= 0; i--) {
        result.push_back(input[i]);
    }
    return result;
}
