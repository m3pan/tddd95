#include <iostream>
#include <sstream>
#include <vector>

std::vector <int> cover(float A, float B, std::vector <std::vector <double> > lines);

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::string AB_st;
    float A, B;

    while(std::getline (std::cin, AB_st, '\n')) //!! never stops with terminal input
    {
        std::stringstream ss1(AB_st);
        ss1 >> A; ss1 >> B;

        int n;
        std::string n_st;
        std::getline (std::cin, n_st, '\n');
        std::stringstream ss2(n_st);
        ss2 >> n;

        std::string line;
        double number;
        std::vector <std::vector <double> > lines;

        for (int i = 0; i < n; i++)
        {
            std::getline (std::cin, line, '\n');
            std::istringstream iss_string(line);
            std::vector <double> lineVec;

            while (iss_string >> number) lineVec.push_back(number);
            lines.push_back(lineVec);
        }

        std::vector <int> result = cover(A, B, lines);



    }
    return 0;
}

std::vector <int> cover(float A, float B, std::vector <std::vector <double> > lines)
{
    std::sort(lines.begin(), lines.end(), [](auto const& lhs, auto const& rhs) {
        return lhs[0] < rhs[0];
    });

    for (auto & line : lines)
    {
        std::cout << line[0] << std::endl;
    }

    std::vector <int> result;
    return result;
}