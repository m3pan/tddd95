#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <iomanip>


/*
 * A modified version of Dijkstras algorithm
 */

double minSpanningTree(int nrNodes, int nrEdges, std::vector <std::vector <std::tuple<int, int, double>>> edges);

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



int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);


    // std::string readLine{};

    int nrIntersections{};      // n
    int nrCorridors{};          // m
    while (std::cin >> nrIntersections >> nrCorridors)
    {
        if (nrIntersections == 0 && nrCorridors == 0) break;

        std::vector <std::vector <std::tuple<int, int, double>>> dungeon(nrIntersections);

        for (int c = 0; c < nrCorridors; c++)
        {
            int x, y;
            double f;

            // An edge between x and y with a factor f
            std::cin >> x >> y >> f;

            if (x > y)
            {
                std::swap(x,y);
            }

            std::tuple<int, int, double> input{x, y, f};

            dungeon[x].push_back(input);
        }
        double fractionLeft = minSpanningTree(nrIntersections, nrCorridors, dungeon);

        std::cout << std::setprecision(3) << fractionLeft << '\n';

    }
}

double minSpanningTree(int nrNodes, int nrEdges, std::vector <std::vector <std::tuple<int, int, double>>> edges) {
    std::vector<int> parent(nrNodes);
    std::vector<int> rank(nrNodes);

    // Max fractions at each node
    std::vector<double> maxFrac(nrNodes, 0);

    // current fraction and current node
    std::priority_queue<std::pair<int, double>> unvisitedNodes;

    unvisitedNodes.push({1.0, 0});

    while (!unvisitedNodes.empty()) {
        std::pair<double, int> current = unvisitedNodes.top();
        unvisitedNodes.pop();
        int currentNode = current.first;
        double currentFraction = current.second;

        if (currentNode == nrNodes - 1) return currentFraction;

        // For each node, iterate over its neighbors

        for (auto &neigh : edges[currentNode]) {
            // If fraction will be bigger than found
            if (maxFrac[std::get<1>(neigh)] < currentFraction * std::get<2>(neigh)) {
                maxFrac[std::get<1>(neigh)] = currentFraction * std::get<2>(neigh);
                unvisitedNodes.push({currentFraction * std::get<2>(neigh), std::get<1>(neigh)});
            }
        }
    }
    return -1;
}