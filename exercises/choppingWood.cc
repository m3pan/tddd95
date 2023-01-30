#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

// TODO: Change from copying to &references
std::vector<int> determineUColumn(std::vector <int> vColumn);

bool returnSmallest(const int &lhs, const int &rhs)
{
    return lhs < rhs;
}

int main() {
    int nrOfInputs;
    std::string nrString;
    std::getline (std::cin, nrString, '\n');
    std::stringstream ss(nrString);
    ss >> nrOfInputs;

    std::string line;
    int integer;
    std::vector <int> vColumn;

    for (int i = 0; i < nrOfInputs; i++)
    {
        std::getline (std::cin, line, '\n');
        std::istringstream iss_string(line);
        iss_string >> integer;
        vColumn.push_back(integer);
    }
    std::vector<int> result = determineUColumn(vColumn);


    return 0;
}

std::vector<int> determineUColumn(std::vector <int> vColumn) {
    // Count degree for all nodes
    std::vector<int> degrees(*max_element(vColumn.begin(), vColumn.end()));
    std::sort(vColumn.begin(), vColumn.end(), returnSmallest);
    for (int node : vColumn)
    {
        degrees[node - 1] += 1;
    }

    // TODO: pick lowest valued node with degree zero that has not been cut and cut it, update d accordingly


    std::vector<int> result{};


    return result;
}
