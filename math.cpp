#include "diffie_hellman.h"

//generate a prime number in range [0, p-2]
long long math::generateX(long long p) {
  if (!math::isPrime(p))
    throw runtime_error("p must be prime");
  
  long long res;
  do {
    res = rand() % (p-2);
  } while (!math::isPrime(res));
  return res;
}

//calculate: base^exp % mod
long long math::powModN(long long base, long long exp, long long mod) {
  if (mod <= 1)
    return 0;
  long long res = 1;
  base %= mod;
  while (exp > 0) {
    if (exp & 1) 
      res = (res*base) % mod;
    base = (base*base) % mod;
    exp >>= 1;
  }
  return res;
}
/*long long math::powModN(long long base, long long exp, long long mod) {
  if (mod == 1)
    return 0;
  long long c = 1;
  for (int x = 0; x < exp; x++)
    //c = (c*base) % mod;
    c = ((c % mod) * (base % mod)) % mod;
  return c;
}*/

//trivial test: O(sqrt(n))
bool math::isPrime(long long n) {
  if (n < 2 || !(n & 1))
    return false;
  if (n == 2)
    return true;
  
  long long sq = (long long)sqrt(n);
  
  for (int i = 3; i <= sq; i++) {
    if (!(i & 1))
      continue;
    if (!(n % i))
      return false;
  }
  return true;
}
