#include <iostream>
#include <random>
#include <vector>

bool isPrime(size_t a) {
  if(a <= 2 && a != 0) {
    return true;
  }
  for(size_t i = 2; i <= std::sqrt(a); i++) {
    if(a % i == 0)
      return false;
  }
  return true;
}

size_t gcd(size_t a, size_t b) {
  if(b > a) {
    std::swap(a, b);
  }
  while(b != 0) {
    size_t tmp = a;
    a = b;
    b = tmp % b;
  }
  return a;
}

std::vector<long long int> dioph(long long a, long long b, long long c) {
  long long int result_x = 0;
  long long int result_y = 0;
  long long int result_error_status = 0;
  int reversed = 0;
  auto a_p = (unsigned long long)(a < 0 ? a * -1 : a);
  auto b_p = (unsigned long long)(b < 0 ? b * -1 : b);
  unsigned long long d = gcd(a_p, b_p);
  if(d == 0) {  // a and b == 0
    if(c != 0)
      result_error_status = 1;
  } else if(c % (long long)d != 0) {  // no result available
    result_error_status = 2;
  } else {
    if(a < b) {
      long long p = a;
      a = b;
      b = p;
      reversed = 1;
    }
    long long x = 1;
    long long y = 0;
    if(b != 0) {
      long long div_result;
      long long div_rest = 1;
      long long x_temp = 0;
      long long y_temp = 1;
      while(div_rest != 0) {  // extended euklides algorithm
        div_result = a / b;
        div_rest = a % b;
        a = b;
        b = div_rest;

        long long helper_x_temp = x_temp;
        long long helper_y_temp = y_temp;
        x_temp = x - div_result * x_temp;
        y_temp = y - div_result * y_temp;
        x = helper_x_temp;
        y = helper_y_temp;
      }
    }
    if(reversed == 1) {
      result_x = y;
      result_y = x;
    } else {
      result_x = x;
      result_y = y;
    }
    long long s = c / d;
    result_x *= s;
    result_y *= s;
  }
  return {result_x, result_y, result_error_status};
}

using keysPair = std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t >>;

keysPair genRsa(size_t p, size_t q) {
  if(!isPrime(p)) {
    throw std::runtime_error("P is not a prime");
  }
  if(!isPrime(q)) {
    throw std::runtime_error("Q is not a prime");
  }
  size_t n = p * q;
  size_t phi_n = (p-1) * (q-1);
  std::mt19937_64 rand{std::random_device{}()};
  std::uniform_int_distribution<size_t> dist(2, phi_n - 1);
  size_t e;
  do {
    e = dist(rand);
  } while(gcd(e, phi_n) != 1);
  auto res = dioph(phi_n, e, 1);
  while(res.at(1) < 0) {
    res.at(1) += phi_n;
  }
  return {{n, res.at(1)}, {n, e}};
}

size_t crackRsa(keysPair first_pair, std::pair<size_t, size_t> public_key) {
  size_t kphi = first_pair.first.second * first_pair.second.second - 1;
  size_t t = kphi;
  while(t % 2 == 0) {
    t /= 2;
  }
  size_t a = 2;
  size_t p;
  bool found = false;
  while(a < 100) {
    size_t k = t;
    while(k < kphi) {
      size_t x = 1;
      for(int i = 0; i < k; i++) {
        x *= a;
        x %= first_pair.first.first;
      }
      if(x != t && x != (first_pair.first.first - 1) && (x * x) % first_pair.first.first == 1) {
        p = gcd(x - 1, first_pair.first.first);
        found = true;
        break;
      }
      k *= 2;
    }
    if(found)
      break;
    a += 2;
  }
  size_t q = first_pair.first.first / p;
  std::cout << "p = " << p << ", q = " << q << std::endl;
  size_t phi_n = (p - 1) * (q - 1);
  auto res = dioph(phi_n, public_key.second, 1);
  while(res.at(1) < 0) {
    res.at(1) += phi_n;
  }

  return res.at(1);
}

int main() {
  size_t q = 197;
  size_t p =  4337;
  auto res1 = genRsa(p, q);
  std::cout << "First keys pair\n";
  std::cout << "public: (" << res1.first.first << ", " << res1.first.second << ")" << std::endl;
  std::cout << "private: (" << res1.second.first << ", " << res1.second.second << ")" << std::endl;

  auto res2 = genRsa(p, q);
  std::cout << "Second keys pair\n";
  std::cout << "public: (" << res2.first.first << ", " << res2.first.second << ")" << std::endl;
  std::cout << "private: (" << res2.second.first << ", " << res2.second.second << ")" << std::endl;

  size_t cr = crackRsa(res1, res2.first);
  std::cout << "Cracked private key: " << cr << std::endl;
}