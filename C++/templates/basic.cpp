#include <cstring>
#include <iostream>

template <typename T> T max(T a, T b) { return a > b ? a : b; }

// Explicit instantiation
template char max(char a, char b);

// Explicit specialization
template <> const char *max<const char *>(const char *a, const char *b) {
  return strcmp(a, b) > 0 ? a : b;
}

template <> float max(float a, float b) { return a > b ? a : b; }

// Template with a nontype template argument
// Array reference: this allows passing a row array to a function without
// needing to pass the size
template <typename T, int size> T sum(T (&arr)[size]) {
  T sum{};
  for (int i{0}; i < size; ++i)
    sum += arr[i];
  return sum;
}

int main() {
  const char *strB{"B"};
  const char *strA{"A"};
  // If no specialization where defined, this will return A as the max because
  // it will just compare addresses
  std::cout << max(strA, strB) << std::endl;

  int arr[]{1, 2, 3};
  std::cout << sum(arr) << std::endl;
  auto it{std::begin(arr)}; // Example of std function which uses this trick
  return 0;
}
