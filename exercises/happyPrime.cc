#include <iostream>
#include <set>
#include <cmath>

/*
 * For each data set there is a single line of output. The single output line consists of the data set number, K,
 * followed by a single space followed by the candidate, m, followed by a single space, followed by YES or NO,
 * indicating whether m is a happy prime.
 *
 * happy number: https://www.youtube.com/watch?v=ljz85bxOYJ0
 * */

int sumOfSquares(int n) {
    // 19 => 1**2 + 9**2
    // 19 % 10 => 9
    // 19 / 10 => 1
    int result{};
    while(n) {
        int digit = pow(n % 10, 2);
        result += digit;
        n = n / 10;
    }
    return result;
}


bool isHappy(int n){
    /* Determines if a number is happy or not */
    std::set<int> visited{};
    while (!visited.count(n)){
        visited.insert(n);
        n = sumOfSquares(n);
        if (n == 1){
            return true;
        }
    }
    return false;
}

bool isPrime(int n) {
    bool isPrime{true};

    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        isPrime = false;
    }

    // loop to check if n is prime
    for (int i = 2; i <= n/2; ++i) {
        if (n % i == 0) {
            isPrime = false;
            break;
        }
    }
    return isPrime;
}


int main(){
    int nrInputs{};
    std::cin >> nrInputs;
    for (int i = 1; i <= nrInputs; i++) {
        int k, m;
        std::cin >> k >> m;
        if (isHappy(m) && isPrime(m))
        {
            std::cout << i << " " << m << " YES";
        } else {
            std::cout << i << " " << m << " NO";
        }
        if (i != nrInputs) {
            std::cout << "\n";
        }
    }
    return 0;
}


