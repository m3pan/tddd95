#include <iostream>
#include <vector>
#include <fstream> // file stream
#include <sstream>

int main() {

    // split input by '\r' and blank space into a nested list
    std::ifstream ifs{"../exercises/input/help.txt"};       // cwd: TDDD95/cmake-build-debug/
    std::string line{};
    std::vector <std::vector<std::string>> lines{};
    std::string word{};

    while (getline(ifs, line, '\r'))
    {
        std::istringstream iss_string(line);
        std::vector <std::string> lineVec{};

        while (iss_string >> word) lineVec.push_back(word);

        lines.push_back(lineVec);
    }

    int nr = std::stoi(lines[0][0]);
    lines.erase(lines.begin(), lines.begin() + 1);


    return 0;
}
