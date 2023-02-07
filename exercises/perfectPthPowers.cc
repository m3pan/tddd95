#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>


void determineP(int input);

int main() {

    std::string inputString;
    int integer;

    while(std::getline (std::cin, inputString, '\n'))
    {
        std::stringstream ss(inputString);
        ss >> integer;
        if (integer)
        {
            determineP(integer);
        } else {
            break;
        }
    }
    return 0;
}
void determineP(int input) {
    if (fabs(input) < 4) {
        std::cout << 1 << "\n";
        return;
    }
    double p{};
    int limit = ceil(sqrt(fabs(input)));

    for (long long int b = 2; b <= limit; b++) {
        if (input % b != 0) {
            continue;
        }
        p = (log(fabs(input)) / log(b));
        if (p > 1 && (p - floor(p) < 1e-11)) {
            if (input == fabs(input))
            {
                std::cout << p << "\n";
            } else {
                if (int(p) % 2 == 0) {
                    continue;
                }
                else {
                    std::cout << p << "\n";
                }
            }
            return;
        }
    }
    std::cout << 1 << "\n";
}