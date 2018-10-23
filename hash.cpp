#include <iostream>
#include <algorithm>
#include <random>

const int INFTY = 1e9;
const long long PRIME = 4294967311;
std::default_random_engine generator;
std::uniform_int_distribution<long long> distribution(1, PRIME / 4);


class Hash {
private:
  long long paramA, paramB, paramC;
  int size;
public:
  void set(const long long ParamA,
		   const long long ParamB,
		   const long long ParamC,
		   const int Size) {
    paramA = ParamA;
    paramB = ParamB;
    paramC = ParamC;
    size = Size;
  }
  void random(const int Size) {
    set(distribution(generator), distribution(generator), distribution(generator), Size);
  }
  int operator()(const double a, const double b) const {
    return ( (paramA * static_cast<int>(INFTY * a) +
			  paramB * static_cast<int>(INFTY * b) +
			  paramC) % PRIME ) % size;
  }
};

int main() {
  Hash hash;
  hash.random(100);

  std::cout << hash(0,0) << std::endl;
  // 07
  std::cout << hash(0.42,0.43) << std::endl;
  // 46
  std::cout << hash(0.4200000001,0.4299999999) << std::endl;
  // 97
  std::cout << hash(0.3141592654,0.2718281828) << std::endl;
  // 43
  
  return 0;
}
