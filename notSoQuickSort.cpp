#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

template <typename RandomAccessIterator, typename Less>
void notSoQuickSort(const RandomAccessIterator begin, const RandomAccessIterator end, Less less);

void printVector(std::vector<int>& v, std::ostream& outputStream = std::cout);

bool more(int a, int b) {
  return a > b;
}

int main() {
  srand(42);
  
  int length = 10;
  std::vector<int> v(length);
  for (int i = 0; i < length; ++i) {
    v[i] = rand() % 5981;
  }

  printVector(v);

  notSoQuickSort(v.begin(), v.end(), more);

  printVector(v);

  return 0;
}


template <typename RandomAccessIterator, typename Less>
void notSoQuickSort(const RandomAccessIterator begin, const RandomAccessIterator end, Less less) {
  for (RandomAccessIterator it = begin; it < end; ++it) {
    if (less(*it, *begin)) {
      std::swap(*it, *begin);
    }
  }
  if (begin + 1 == end) {
    return;
  }
  notSoQuickSort(begin + 1, end, less);
}

void printVector(std::vector<int>& v, std::ostream& outputStream) {
  for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    outputStream << *it;
    if (it < v.end() - 1) {
      outputStream << " ";
    } else {
      outputStream << "\n";
    }
  }
}
