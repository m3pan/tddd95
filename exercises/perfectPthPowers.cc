#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

// m^k = n
// primtalsfaktorisera och kolla om man kan skriva talet som multipel av ett och samma tal ?
// generera en sekvens av tal genom att ändra m och k tills du kommer upp i, eller över n?
// Sätt b = floor(sqrt(x)) & kör en approach genom att gå nedåt

void determineP(int input);

int main() {

    std::string inputString;
    int integer;

    while(std::getline (std::cin, inputString, '\n')) //!! never stops with terminal input
    {
        std::stringstream ss(inputString);
        ss >> integer;
        determineP(integer);
    }

    return 0;
}
void determineP(int input)
{
    if (input < 2)
    {
        return;
    }
    if (input < 4)
    {
        std::cout << 1 << "\n";
        return;
    } /*
    double squareroot = sqrt(input);
    if (squareroot == floor(squareroot))
    {
        std::cout << 2;
        return;
    }*/
    double k{};
    for (int m = 2; m <= input/2; ++m) {
        k = (log(input) / log(m));
        if (k == floor(k))
        {
            std::cout << k << "\n";
            return;
        }
    }
    std::cout << 1 << "\n";
    return;


    // Find prime factors
    /*
    std::priority_queue<int> primeFactors{};
    int divideInput{input};
    while (input % 2 == 0)
    {
        primeFactors.push(-2);
        input = input/2;
    }

    // n must be odd at this point. So we can skip
    // one element (Note i = i +2)
    for (int i = 3; i <= sqrt(divideInput); i = i + 2)
    {
        // While i divides n, print i and divide n
        while (divideInput % i == 0)
        {
            primeFactors.push(-divideInput);
            divideInput = divideInput/i;
        }
    }

    // This condition is to handle the case when n
    // is a prime number greater than 2
    if (divideInput > 2)
        primeFactors.push(-divideInput);

    int primeFactor{};
    int pMax{};
    // Begin by determining the largest possible p från log av minsta primtalsgrej
    while (!primeFactors.empty())
    {
        primeFactor = primeFactors.top();
        primeFactors.pop();
        pMax = log2(input) / log2(primeFactor);
        for (int b = 2; p != 0; p--)
        {

        }


    }

    // int pMax = std::floor(log2(input));
    std::cout << pMax << "\n";
    for (int p = pMax; p != 0; p--)
    {
    }*/


}
