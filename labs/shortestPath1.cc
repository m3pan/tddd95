/*
 * Madeleine Nilsson
 * madni264
 * Solves the Single source shortest path (non-negative weights) using Dijkstras Algorithm. Given a
 * startingNode it returns the shortest distance and predecessors to all nodes in the graph.
 *
 * The algorithm iterates over all edges and checks if it gives a new shortest distance to a node from our starting
 * node. It stores a queue
 *
 * */





#include <iostream>
#include <sstream>
#include <vector>
#include <utility>  //  std::pair
#include <set>

/* Implement Dijkstras algorithm to find the shortest path from one node to all other nodes in a graph with
 * non-negative edge weights.
 *
 * Kattis only asks for the shortest distance while your solution should be able to construct the actual shortest paths.
 *
 * Suggested API:
 * distance/parent[] shortest_path(graph G, node start)
 * Är vår graf sparse?
 * */

struct distancePredecessors{
    std::vector<int> distance;
    std::vector<int> predecessors;
};

int inf = 10000000;

distancePredecessors shortestPath(std::vector<std::vector<std::pair<int, int>>> adjacent, int startingNode,
                                  std::vector<int> & distance, std::vector<int> & predecessors);

int main() {

    int nrNodes{};          // n
    int nrEdges{};          // m
    int nrQueries{};        // q
    int startingNode{};     // s

    std::string readLine{};

    while (std::getline(std::cin, readLine, '\n')) {
        if (readLine == "")
        {
            std::getline(std::cin, readLine, '\n');
            if (readLine == "0 0 0 0")
            {
                break;
            }
            else {
                std::cout << "\n";
            }
        }

        std::stringstream ss1{readLine};
        ss1 >> nrNodes;
        ss1 >> nrEdges;
        ss1 >> nrQueries;
        ss1 >> startingNode;
        std::vector<std::vector<std::pair<int, int>>> adjacent(nrNodes);
        std::vector<int> result{};
        // std::vector<std::pair<int, int>> edgeVec{};
        int u{};
        for (int m = 0; m < nrEdges; m++)
        {
            std::getline(std::cin, readLine, '\n');
            std::stringstream ss2{readLine};
            int cmp{};
            ss2 >> cmp;

            // Read input line consisting of [u v w] = [startNode endNode weight]
            u = cmp;
            int v{};
            int w{};
            ss2 >> v;
            ss2 >> w;
            std::pair<int, int> edge{v, w};
            adjacent[u].push_back(edge);
        }
        std::vector<int> distance{};
        std::vector<int> predecessors{};
        distancePredecessors returnValues{};
        returnValues  = shortestPath(adjacent, startingNode, distance, predecessors);

        int q1{};
        for (int q = 0; q < nrQueries; q++)
        {
            std::cin >> q1;
            if (returnValues.distance[q1] == inf)
            {
                std::cout << "Impossible" << "\n";
            } else {
                std::cout << returnValues.distance[q1] << std::endl;
            }
        }

    }
    return 0;
}

distancePredecessors shortestPath(std::vector<std::vector<std::pair<int, int>>> adjacent, int startingNode,
                              std::vector<int> & distance, std::vector<int> & predecessors)
{
    /*
     * std::vector<int> distance : for each vertex v, we store the current shortest path from s to v
     *
     * std::vector<int> predecessors : for each vertex v != s, p[v] is the penultimate vertex in the shortest path
     * from s to v
     * */

    // Number of nodes:
    int nrNodes = adjacent.size();

    distance.assign(nrNodes, inf);
    predecessors.assign(nrNodes, -1);

    // A boolean array u[] which stores for each vertex v whether it's marked
    // std::vector<bool> markedVertices(nrNodes, false);

    distance[startingNode] = 0;

    std::set<std::pair<int, int>> queue;
    queue.insert({0, startingNode});

    while (!queue.empty())
    {
        int currNode = queue.begin()->second;
        queue.erase(queue.begin());

        for (auto edge : adjacent[currNode]) {
            // iterate over edges in the edge vector
            int to = edge.first;
            int weight = edge.second;

            if (distance[currNode] + weight < distance[to]) {
                // if we've found a new shortest path with out edge
                queue.erase({distance[to], to});
                distance[to] = distance[currNode] + weight;
                // store the parent node
                predecessors[to] = currNode;
                queue.insert({distance[to], to});
            }
        }
    }
    return distancePredecessors{distance, predecessors};
}

