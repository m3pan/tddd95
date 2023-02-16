#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>


void birdOnAWire(int wireLength, int minimumDistance, int numberOfBirds, std::vector<int> birdPositions);

bool comparePositions(const int &lhs, const int &rhs)
{
    return lhs < rhs;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    int wireLength{};
    int minimumDistance{};
    int numberOfBirds{};
    std::string line;
    std::getline (std::cin, line, '\n');
    std::stringstream ss(line);
    ss >> wireLength;   // l
    ss >> minimumDistance;  // d
    ss >> numberOfBirds;    // n

    std::vector<int> birdPositions;
    for (int bird = 0; bird < numberOfBirds; bird++) {
        int position{};
        std::getline(std::cin, line, '\n');
        std::stringstream ss(line);
        ss >> position;
        birdPositions.push_back(position);
    }
    birdOnAWire(wireLength, minimumDistance, numberOfBirds, birdPositions);
    return 0;

}

void birdOnAWire(int wireLength, int minimumDistance, int numberOfBirds, std::vector<int> birdPositions)
{
    // Sort the array of bird positions in ascending order.
    std::sort(birdPositions.begin(), birdPositions.end(), comparePositions);

    // maximum number of additional birds that can sit on the wire.
    int maxBirds{};
    int distance{};

    // If the distance is greater than or equal to 2d, it means that there is enough space for at least one additional
    // bird between the two birds.
    if (numberOfBirds == 0)
    {
        if (wireLength - 12 > minimumDistance * 2)
        {
            maxBirds = (wireLength - 12) / minimumDistance + 1;
        } else {
            maxBirds = 0;
        }
        std::cout << maxBirds << std::endl;
        return;
    }

    for (int i = 0; i <= numberOfBirds; i++)
    {
        if (i == 0)
        {
            // first bird, adjacent to the spikes
            distance = birdPositions[i] - 6;
            if (distance >= minimumDistance)
            {
                maxBirds += (distance / minimumDistance);
            }
        } else if (i == numberOfBirds) {
            // last bird, adjacent to the spikes
            distance = (wireLength - birdPositions[i - 1]) - 6;
            if (distance >= minimumDistance)
            {
                maxBirds += (distance / minimumDistance);
            }
        } else {
            // all of the other birds
            distance = birdPositions[i] - birdPositions[i - 1];
            if (distance >= 2*minimumDistance)
            {
                maxBirds += (distance - minimumDistance) / minimumDistance; // todo: check so that it rounds down
            }
        }
    }
    std::cout << maxBirds << std::endl;
}
