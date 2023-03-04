#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <sstream>
#include <algorithm>


struct minSpanTree{
    int minCost;
    std::vector<std::tuple<float, int, int>> minEdges;
};

minSpanTree minSpanningTree(int nrNodes, int nrEdges, std::priority_queue<std::tuple<int, int, int>> edges);


bool compareEdges(const std::tuple<float, int, int> &lhs, const std::tuple<float, int, int> &rhs)
{
    if (std::get<1>(lhs) < std::get<1>(rhs))
    {
        return lhs < rhs;
    } else if (std::get<1>(lhs) > std::get<1>(rhs))
    {
        return lhs > rhs;
    } else {
        // first node equal
        if (std::get<2>(lhs) < std::get<2>(rhs))
        {
            return lhs < rhs;
        } else if (std::get<2>(lhs) > std::get<2>(rhs))
        {
            return lhs > rhs;
        }
    }
    return lhs < rhs;
}

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
    }
}

int main(){
    std::string readLine{};

    while (std::getline(std::cin, readLine, '\n')) {
        if (readLine == "0 0") {
            break;
        }
        if (readLine.empty()) {
            std::getline(std::cin, readLine, '\n');
        }
        std::stringstream ss1{readLine};
        int nrNodes;    // n
        int nrEdges;    // m

        ss1 >> nrNodes >> nrEdges;

        std::priority_queue<std::tuple<int, int, int>> edges;

        for (int i = 0; i < nrEdges; i++)
        {
            int u, v, w;
            std::cin >> u >> v >> w;

            if (u > v)
            {
                std::swap(u,v);
            }
            std::tuple<int, int, int> edge = {-w, u, v};
            edges.push(edge);
        }
        minSpanTree result = minSpanningTree(nrNodes, nrEdges, edges);

        std::vector<std::tuple<float, int, int>> minEdges = result.minEdges;


        if (minEdges.size() != nrNodes - 1)
        {
            std::cout << "Impossible" << "\n";
        } else {
            // The edges should be output so that x < y and should be listed in the lexicographic order on
            // pairs of integers.
            std::cout << result.minCost << std::endl;

            // Sort all edges, first on [1] and then on [2]. Remember that the first entry is the weight with switched sign
            std::sort(minEdges.begin(), minEdges.end(), compareEdges);

            for (auto e : minEdges)
            {
                std::cout << std::get<1>(e) << " " << std::get<2>(e) << std::endl;
            }
        }
    }
    return 0;
}

minSpanTree minSpanningTree(int nrNodes, int nrEdges, std::priority_queue<std::tuple<int, int, int>> edges)
{
    std::vector<int> parent(nrNodes);
    std::vector<int> rank(nrNodes);

    // create all nodes
    for (int i = 0; i < nrNodes; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int cost = 0;
    std::vector<std::tuple<float, int, int>> result;

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
    return minSpanTree{cost, result};
}
