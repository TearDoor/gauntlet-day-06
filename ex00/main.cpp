#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// O(log n) complexity
int binarySearch(const std::vector<int> &v, int target) {
  int lo = 0, hi = static_cast<int>(v.size());
  while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (target == v[mid]) {
      return mid;
    } else if (target < v[mid]) {
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }

  return -1;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cerr << "Usage: search <target> <numbers...>\n";
    return 1;
  }
  std::vector<int> numbers;
  for (int i = 2; i < argc; i++) {
    numbers.push_back(std::stoi(argv[i]));
  }

  std::sort(numbers.begin(), numbers.end());
  std::cout << "sorted asc:  ";
  for (int i : numbers)
    std::cout << i << ' ';
  std::cout << '\n';
  // descending view
  std::sort(numbers.begin(), numbers.end(), [](int a, int b) { return a > b; });
  std::cout << "sorted desc: ";
  for (int i : numbers)
    std::cout << i << ' ';
  std::sort(numbers.begin(), numbers.end());
  std::cout << '\n';

  int target = std::stoi(argv[1]);
  std::cout << "find " << target << " -> ";
  int index = binarySearch(numbers, target);
  if (index != -1) {
    std::cout << "index ";
  }
  std::cout << index << '\n';

  return 0;
}
