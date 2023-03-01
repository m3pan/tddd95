#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <iomanip>

double islandHopping(int nrIslands, std::vector<std::pair<float, float>> coordinates);


int findParent(int v, std::vector<int> &parent, std::vector<int> &rank) {
    if (v == parent[v])
        return v;
    return parent[v] = findParent(parent[v], parent, rank);
}

void unionSets(int a, int b, std::vector<int> &parent, std::vector<int> &rank)
{
    a = findParent(a, parent, rank);
    b = findParent(b, parent, rank);
    if (a != b) {

        // larger rank -> set as parent
        if (rank[a] > rank[b])
        {
            parent[b] = a;
            rank[a] += 1;
        } else {
            parent[a] = b;
            rank[b] += 1;
        }
        /*
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;*/
    }
}

int main(){
    int nrCases{};        // n
    std::cin >> nrCases;

    while(nrCases)
    {
        int nrIslands;
        std::cin >> nrIslands;
        std::vector<std::pair<float, float>> coordinates;

        for (int i = 0; i < nrIslands; i++)
        {
            // real-valued horizontal and vertical position of a bridge endpoint for the corresponding island.
            // Each coordinate is in the range [-1000, 1000] meters and has at most digits past the decimal point.
            std::pair<float, float> input{};
            std::cin >> input.first >> input.second;
            coordinates.push_back(input);
        }
        double result = islandHopping(nrIslands, coordinates);
        --nrCases;

        /*for (std::tuple<float, int, int> r : result)
        {
            resultValue += std::get<0>(r);
        }*/
        std::cout << std::setprecision(9) << result << "\n";
    }
    return 0;
}

double islandHopping(int nrIslands, std::vector<std::pair<float, float>> coordinates)
{
    std::vector<int> parent(nrIslands);
    std::vector<int> rank(nrIslands);       // hur djupt i vårt träd vi är


    // create all nodes
    for (int i = 0; i < nrIslands; i++)
    {
        parent[i] = i;
        rank[i] = 1;
    }

    // create all edges
    // sort all edges of the graph in non-decreasing order of the weights
    std::priority_queue<std::tuple<float, int, int>> edges;
    for (int i = 0; i < nrIslands; i++)
    {
        float x1 = coordinates[i].first;
        float y1 = coordinates[i].second;

        for (int j = i + 1; j < nrIslands; j++)
        {
            float x2 = coordinates[j].first;
            float y2 = coordinates[j].second;
            double distance = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            //double distance = pow(pow(x1-x2, 2) + pow(y1-y2, 2), 0.5);
            edges.push({-distance, i, j});
        }
    }
    // put each island in its own tree

    double cost = 0;
    std::vector<std::tuple<float, int, int>> result;

    int nrEdges = edges.size();

    for (int n = 0; n < nrEdges; n++)
    {
        std::tuple<float, int, int> top = edges.top();

        if (findParent(std::get<1>(top), parent, rank) != findParent(std::get<2>(top), parent, rank))
        {
            cost += - std::get<0>(top);   // weight
            result.push_back(top);
            unionSets(std::get<1>(top), std::get<2>(top), parent, rank);
        }
        edges.pop();
    }
    return cost;
}
