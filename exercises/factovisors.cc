#include <iostream>
#include <map>
#include <cmath>

//!? Process finished with exit code 143 (interrupted by signal 15: SIGTERM)

/* Input
 * The input to your program consists of several lines, each containing two non-negative integers, n and m, both less
 * than 2^31.
 *
 * Output
 * For each input line, output a line stating whether or not m divides n!, in the format shown below.
*/

void primeFactorize(long n, std::map<long, long> &factors) {
    int maxVal = sqrt(n);
    long i = 2;
    while (i <= maxVal) {
        if (n%i == 0) {
            n /= i;
            maxVal = sqrt(n);
            ++factors[i];
        } else {
            ++i;
        }
    }
    ++factors[n];
}

bool dividesFactorial(long n, std::map<long, long> &factors) {
    /* For each prime factor, divide the factorial number by that prime factor until the result is not divisible
    * by that prime factor. Count the number of times you are able to divide by each prime factor. If the count
    * of divisions for each prime factor is greater than or equal to the count of appearances of that prime factor
    * in the specific integer's prime factorization, then the factorial is divisible by the specific integer.*/
    for (std::pair<long, long> f : factors) {
        long exp = 0;
        for (long j = f.first; j <= n; j = j*f.first) {
            exp += floor(n / j);
        }
        if (exp < f.second) {
            return false;
        }
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    long n{};
    long m{};

    while (std::cin >> n >> m) {

        /* Find the prime factorization of the specific integer & count the number of times each prime factor appears
         * in the prime factorization.
         *
         * primeFactors: < factor : nrOccurencies>
         * */

        if (m == 0) {
            std::cout << m << " does not divide " << n << "!\n";
            continue;
        }

        std::map<long, long> primeFactors{};
        primeFactorize(m, primeFactors);
        primeFactors.erase(1);

        /* Determine if the the factorial of n is divisible by m by division with the prime factors of m. */
        bool isDivisible = dividesFactorial(n, primeFactors);

        if (isDivisible)
            std::cout << m << " divides " << n << "!\n";
        else
            std::cout << m << " does not divide " << n << "!\n";
    }
    return 0;
}

