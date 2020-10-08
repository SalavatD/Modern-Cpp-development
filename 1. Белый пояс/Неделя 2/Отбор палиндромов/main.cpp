bool IsPalindrom(const string& s) {
  for (size_t i = 0; i < s.size() / 2; ++i) {
    if (s[i] != s[s.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

vector<string> PalindromFilter(vector<string> words, int min_length) {
  vector<string> result;
  for (const auto& word : words) {
    if (word.size() >= min_length && IsPalindrom(word)) {
      result.push_back(word);
    }
  }
  return result;
}
