template<typename T>
T Sqr(T value);

template<typename T>
vector <T> Sqr(const vector <T> &value);

template<typename K, typename V>
map <K, V> Sqr(const map <K, V> &value);

template<typename K, typename V>
pair <K, V> Sqr(const pair <K, V> &value);

template<typename T>
T Sqr(T value) {
    return value * value;
}

template<typename T>
vector <T> Sqr(const vector <T> &value) {
    vector <T> result;
    for (const T &x : value) {
        result.push_back(Sqr(x));
    }

    return result;
}

template<typename K, typename V>
map <K, V> Sqr(const map <K, V> &value) {
    map <K, V> result;
    for (const auto &element : value) {
        result[element.first] = Sqr(element.second);
    }
    return result;
}

template<typename K, typename V>
pair <K, V> Sqr(const pair <K, V> &value) {
    return {Sqr(value.first), Sqr(value.second)};
}
