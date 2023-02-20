#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>


void gettingGold(std::tuple<int,int> position, std::vector<std::vector <char>> (*maze));

bool checkAdjacent(char token, const std::string& direction, std::tuple<int,int> position, const std::vector<std::vector <char>> &maze);

int goldCount{};
int width{};
int height{};
std::vector<std::vector <char>> maze{};


int main() {
    std::tuple<int,int> startPosition{};
    std::cin >> width;
    std::cin >> height;


    // Clear input buffer, remove '\0' row in vector
    std::string readLine;
    std::getline (std::cin, readLine, '\n');

    for (int h = 0; h < height; h++) {
        readLine = "";
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
        maze.push_back(row);
    }
    gettingGold(startPosition, &maze);
    std::cout << goldCount << std::endl;

    return 0;
}

void gettingGold(std::tuple<int,int> position, std::vector<std::vector <char>> (*maze)) {
    int y = std::get<0>(position);
    int x = std::get<1>(position);
    char currentSquare = (*maze)[y][x];

    // Check to see if we can collect any gold
    if (currentSquare == 'G')
    {
        goldCount++;
    }

    // Mark the current square as visited
    (*maze)[y][x] = '#';

    // Checks if the player 'senses a draft' at the current position
    if (checkAdjacent('T', "all", position, *maze))
        // If the player "sense a draft" we should not proceed from the current square
        return;

    else {
        // Try to visit the adjacent squares

        if (checkAdjacent('#', "up", position, *maze))
            gettingGold({y-1, x}, maze);

        if (checkAdjacent('#', "down", position, *maze))
            gettingGold({y+1, x}, maze);

        if (checkAdjacent('#', "left", position, *maze))
            gettingGold({y, x-1}, maze);

        if (checkAdjacent('#', "right", position, *maze))
            gettingGold({y, x+1}, maze);

        return;
    }


}

bool checkAdjacent(char token, const std::string& direction, std::tuple<int,int> position, const std::vector<std::vector <char>> &maze)
{
    int y = std::get<0>(position);
    int x = std::get<1>(position);
    if (direction == "all")
    {
        if (maze[y-1][x] == token || maze[y+1][x] == token || maze[y][x-1] == token || maze[y][x+1] == token)
        {
            return true;
        } else {
            return false;
        }
    } else if (direction == "up")
    {
        if (maze[y-1][x] == token)
        {
            return false;
        } else {
            return true;
        }
    } else if (direction == "down")
    {
        if (maze[y+1][x] == token)
        {
            return false;
        } else {
            return true;
        }
    } else if (direction == "left")
    {
        if (maze[y][x-1] == token)
        {
            return false;
        } else {
            return true;
        }
    } else if (direction == "right")
    {
        if (maze[y][x+1] == token)
        {
            return false;
        } else {
            return true;
        }
    }
    return false;
}
