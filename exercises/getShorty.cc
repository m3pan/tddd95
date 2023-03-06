#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <iomanip>


/*
 * A modified version of Dijkstra's algorithm
 *
 * Traverse through all nodes in a graph with the maximum resulting factor. Undirected graph, so remember to add all
 * edges in both directions to the graph container ("edges").
 */

double modifiedDijkstra(int nrNodes, std::vector <std::vector <std::tuple<int, int, double>>> edges);


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

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

            // Undirected graph => add the edges in both directions
            std::tuple<int, int, double> input1{x, y, f};
            std::tuple<int, int, double> input2{y, x, f};

            dungeon[x].push_back(input1);
            dungeon[y].push_back(input2);
        }
        double fractionLeft = modifiedDijkstra(nrIntersections, dungeon);

        std::cout << std::fixed << std::setprecision(4) << fractionLeft << '\n';

    }
}

double modifiedDijkstra(int nrNodes, std::vector <std::vector <std::tuple<int, int, double>>> edges) {

    // largest fractions at each node
    std::vector<double> maxFractions(nrNodes, 0);

    // pq that sorts by fraction
    std::priority_queue<std::pair<double, int>> unvisitedNodes;

    unvisitedNodes.push({1, 0});

    while (!unvisitedNodes.empty()) {
        std::pair<double, int> current = unvisitedNodes.top();
        unvisitedNodes.pop();
        int currentNode = current.second;
        double currentFraction = current.first;

        if (currentNode == nrNodes - 1)
        {
            // Exit always located in node n-1
            return currentFraction;
        }

        // For each node, iterate over its neighbors

        for (auto &neigh : edges[currentNode]) {
            // If fraction will be bigger than found
            if (maxFractions[std::get<1>(neigh)] < currentFraction * std::get<2>(neigh)) {
                maxFractions[std::get<1>(neigh)] = currentFraction * std::get<2>(neigh);
                unvisitedNodes.push({currentFraction * std::get<2>(neigh), std::get<1>(neigh)});
            }
        }
    }
    return 0;
}