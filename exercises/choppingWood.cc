#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

// TODO: Change from copying to &references
std::vector<int> determineUColumn(int nrOfInputs, std::vector <int> vColumn);

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
    std::vector<int> result = determineUColumn(nrOfInputs, vColumn);
    if (result.empty())
    {
        std::cout << "Error" << "\n";
    } else {
        for (int r : result){
            std::cout << r << std::endl;
        }
    }
    return 0;
}

std::vector<int> determineUColumn(int nrOfInputs, std::vector <int> vColumn) {
    std::vector<int> result;
    // Count degree for all nodes
    if (vColumn[nrOfInputs - 1] != nrOfInputs + 1)
    {
        return result;
    }
    std::vector<int> degrees(nrOfInputs);
    //std::priority_queue<int> degrees;

    std::vector<int> vColumnSorted(nrOfInputs);
    std::copy(vColumn.begin(), vColumn.end(), vColumnSorted.begin());
    std::sort(vColumnSorted.begin(), vColumnSorted.end(), returnSmallest);

    for (int node : vColumnSorted)
    {
        degrees[node - 1] += 1;
    }

    // Pick lowest valued node with degree zero that has not been cut and cut it, update d accordingly
    long index = 0;
    for (int i = 0; i < nrOfInputs; i++)
    {
        // todo: use range based for loop instead
        // todo: change so that the 'last element' is N+1
        auto itr = std::find( degrees.begin(), degrees.end(), 0 );
        if (itr != degrees.cend()) {
            index = std::distance(degrees.begin(), itr);
            degrees[index] = -1;
            if (degrees[vColumn[i] - 1]) {--degrees[vColumn[i] - 1];}
            result.push_back(index + 1);
        }
    }
    return result;
}
