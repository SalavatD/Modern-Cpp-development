template<typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
    int range_length = range_end - range_begin;
    if (range_length < 2) {
        return;
    }

    vector<typename RandomIt::value_type> elements(range_begin, range_end);

    auto mid = elements.begin() + range_length / 2;

    MergeSort(elements.begin(), mid);
    MergeSort(mid, elements.end());

    merge(elements.begin(), mid, mid, elements.end(), range_begin);
}