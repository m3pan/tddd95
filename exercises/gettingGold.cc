#include <iostream>
#include <vector>
#include <sstream>

void gettingGold(std::tuple<int,int> startPosition, std::vector<std::vector <char>> map);

int main() {
    std::cout << "Hello, World!" << std::endl;
    int width{};
    int height{};
    std::tuple<int,int> startPosition{};
    std::cin >> width;
    std::cin >> height;

    std::vector<std::vector <char>> map{};

    // Clear input buffer, remove '\0' row in vector
    std::string readLine;
    std::getline (std::cin, readLine, '\n');

    for (int h = 0; h < height; h++) {
        std::string readLine;
        std::getline (std::cin, readLine, '\n');
        std::stringstream ss1(readLine);
        std::vector <char> row{};

        for (int w = 0; w < width; w++)
        {
            char input{};
            ss1 >> input;
            if (input == 'P')
            {
                startPosition = {h,w};
            }
            row.push_back(input);
        }
        map.push_back(row);
    }
    gettingGold(startPosition, map);
    return 0;
}

void gettingGold(std::tuple<int,int> startPosition, std::vector<std::vector <char>> map)
{
    // woho
}