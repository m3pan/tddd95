#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>
#include <set>
#include <iomanip>
#include <algorithm>

#define M_PI   3.14159265358979323846264338327950288
/*
 * Exercise 13
 * A straight-forward non-recursive solution that works by counting the number of ways zeros can appear in each position.
 *
 * https://stackoverflow.com/questions/11891984/count-the-number-of-occurrences-of-0s-in-integers-from-1-to-n
 * */
//
unsigned int solve(long long n){
    unsigned long result{0};
    unsigned int i{1};     // exponential

    while(true) {
        unsigned int a, b, c;
        // quotient
        b = (unsigned int) n / i;
        // remainder
        c = n % i; /* Likely uses the result of the division. */

        // quotient
        a = (unsigned int) b / 10;
        // remainder
        b = b % 10;

        if (a == 0){
            return result;
        }
        if (b == 0) {
            result += (a - 1) * i + c + 1;
        } else {
            result += a * i;
        }
        i *= 10;
    }
}


int main(){
    long m{};
    long n{};
    unsigned long mZeros{};
    while(true){
        std::cin >> m >> n;
        if (m < 0) break;
        if (m == 0) {
            std::cout << solve(n) + 1 << "\n";
        } else {
            std::cout << solve(n) - solve(m-1)  << "\n";
        }
    }

}