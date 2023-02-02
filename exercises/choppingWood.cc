#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>

// TODO: Change from copying to &references
void determineUColumn(int nrOfInputs, std::vector <int> vColumn, std::vector <int> degrees);

bool returnSmallest(const int &lhs, const int &rhs)
{
    return lhs < rhs;
}

int main() {
    int nrOfInputs;
    std::cin >> nrOfInputs;
    int integer;
    std::vector <int> vColumn(nrOfInputs);
    std::vector<int> degrees(nrOfInputs + 1);
    //std::priority_queue<int> degrees;

    // Read input data and count the node degrees
    for (int i = 0; i < nrOfInputs; i++)
    {
        std::cin >> integer;
        vColumn[i] = (integer);
        degrees[integer - 1] += 1;
    }
    determineUColumn(nrOfInputs, vColumn, degrees);
    return 0;
}

void determineUColumn(int nrOfInputs, std::vector <int> vColumn, std::vector <int> degrees) {
    std::vector<int> result;
    // A solution is not possible if the last input isn't the highest node
    if (vColumn[nrOfInputs - 1] != nrOfInputs + 1)
    {
        std::cout << "Error" << "\n";
        return;
    }
    // Initialization
    std::priority_queue<int> pq_degrees;

    // Decrease first element
    if (degrees[vColumn[0] - 1] != 0)
    {
        --degrees[vColumn[0] -1];
    }
    for (int i = 0; i < degrees.size(); i++)
    {
        // Add all zero elements to
        if (degrees[i] == 0)
        {
            pq_degrees.push((-i-1));
            degrees[i] = -43;
        }
    }

    if (!pq_degrees.empty()) {
        std::cout << (-1) * pq_degrees.top() << '\n';
        pq_degrees.pop();
    }
    for (int j = 1; j < nrOfInputs; j++)
    {
        if (!pq_degrees.empty()) {
            std::cout << (-1) * pq_degrees.top() << '\n';
            pq_degrees.pop();
        }
        if (degrees[vColumn[j] - 1])
        {
            --degrees[vColumn[j] - 1];
            if (degrees[vColumn[j] - 1] == 0)
            {
                pq_degrees.push(-vColumn[j]);
                degrees[vColumn[j] - 1] = -43;
            }
        }

    }
}
