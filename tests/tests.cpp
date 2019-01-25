#include "../diffie_hellman.h"

#define STEP1 100
#define STEP2 1000
#define STEP3 10000
#define STEP4 100000
#define STEP5 1000000

int main() {
	srand(time(NULL));

#ifndef PRIME_GENERATION
	for (long long i = 0; i < STEP2; i++)
		if (math::isPrime(i))
			cout << "prime: " << i << endl;

	assert(math::powModN(2, 5, 13) == 6);
	assert(math::powModN(2, 5, 23) == 9);
	assert(math::powModN(3, 55, 17) == 11);
	assert(math::powModN(531, 79, 1001) == 587);
#else
	long long temp;
	for (int i = 0; i < 100; i++) {
		temp = math::generateX(9973);
		assert(math::isPrime(temp));
		cout << temp << endl;
	}
#endif		
	return 0;
}
