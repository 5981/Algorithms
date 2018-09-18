#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>

// we calculate Fibonacci numbers using 3 different ways

// recursion
uint32_t Fibonacci(const uint32_t n) {
  if (n < 2) {
    return n;
  }
  return Fibonacci(n-1) + Fibonacci(n-2);
}

// recursion with memory
class Fib
{
public:
  Fib() {
    results_.push_back(0);
    results_.push_back(1);
  }
  uint32_t operator()(const uint32_t n) {
    if (n < 2) {
      return n;
    }
    if (n < results_.size()) {
      return results_[n];
    }
    return (*this)(n-2) + (*this)(n-1);
  }
private:
  std::vector<uint32_t> results_;
};

// expression
uint32_t F(const uint32_t n) {
  if (n < 2) {
    return n;
  }
  const double sqrt5 = std::sqrt(5);
  const double phi = (1 + sqrt5) / 2;
  return static_cast<uint32_t>(std::pow(phi, n)/sqrt5 + 0.5);
}

int main() {
  uint32_t n;
  std::cout << "Enter the ordinal number of the Fibonacci number\n";
  std::cin >> n;
  std::cout << Fibonacci(n) << std::endl;
  Fib fib;
  std::cout << fib(n) << std::endl;
  std::cout << F(n) << std::endl;
}
