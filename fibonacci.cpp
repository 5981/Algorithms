#include <stdint.h>
#include <iostream>
#include <vector>
#include <cmath>

// we calculate Fibonacci numbers using 3 different ways

// recursion
template<typename T>
T Fibonacci(const uint32_t n, const std::vector<T>& seed) {
  if (n < 2) {
    return seed[n];
  }
  return Fibonacci<T>(n-1, seed) + Fibonacci<T>(n-2, seed);
}

// recursion with memory
template<typename T>
class Fib {
public:
  Fib(const std::vector<T>& seed) {
    this->results_ = std::vector<T>(seed);
  }
  T operator()(const uint32_t n) {
    if (n < results_.size()) {
      return results_[n];
    }
    return (*this)(n-2) + (*this)(n-1);
  }
private:
  std::vector<T> results_;
};

// expression
template<typename T>
uint32_t F(const uint32_t n, const std::vector<T>& seed) {
  const double sqrt5 = std::sqrt(5);
  const double phi = (1 + sqrt5) / 2;
  const double psi = (1 - sqrt5) / 2;
  return std::round((seed[0]*phi-seed[1])/sqrt5 * std::pow(psi, n) -
                    (seed[0]*psi-seed[1])/sqrt5 * std::pow(phi, n));
}

int main() {
  uint32_t n;
  std::cout << "Enter the ordinal number of the Fibonacci number\n";
  std::cin >> n;

  // initialise Fibonacci sequence
  std::vector<uint32_t> seed(2);
  seed[0] = 3;
  seed[1] = 4;

  std::cout << Fibonacci<uint32_t>(n, seed) << std::endl;

  Fib<uint32_t> fib(seed);
  std::cout << fib(n) << std::endl;

  std::cout << F<uint32_t>(n, seed) << std::endl;
  
  return 0;
}
