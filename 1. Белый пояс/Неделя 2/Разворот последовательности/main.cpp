void Reverse(vector<int>& v) {
  size_t n = v.size();
  for (size_t i = 0; i < n / 2; i++) {
    int temp = v[i];
    v[i] = v[n - 1 - i];
    v[n - 1 - i] = temp;
  }
}
