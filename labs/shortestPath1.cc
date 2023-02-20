#include <iostream>
#include <sstream>
#include <vector>

/* Implement Dijkstras algorithm to find the shortest path from one node to all other nodes in a graph with
 * non-negative edge weights.
 *
 * Kattis only asks for the shortest distance while your solution should be able to construct the actual shortest paths.
 *
 * Suggested API:
 * distance/parent[] shortest_path(graph G, node start)
 * */

/* 4 3 4 0
0 1 2
1 2 2
3 0 2
0
1
2
3
2 1 1 0
0 1 100
1
0 0 0 0 */

std::vector<int> shortestPath(std::vector<std::vector<int>>edges, int startingNode);


int main() {
    std::cout << "Hello, World!" << std::endl;

    int nrNodes{};          // n
    int nrEdges{};          // m
    int nrQueries{};        // q
    int startingNode{};     // s

    std::string readLine{};

    while (std::getline(std::cin, readLine, '\n')) {
        if (readLine == "0 0 0 0") break;
        std::stringstream ss1{readLine};
        ss1 >> nrNodes;
        ss1 >> nrEdges;
        ss1 >> nrQueries;
        ss1 >> startingNode;
        std::vector<std::vector<int>> edges{};
        std::vector<int> result{};
        for (int m = 0; m < nrEdges; m++)
        {
            std::vector<int> edgeVec{};
            std::getline(std::cin, readLine, '\n');
            std::stringstream ss2{readLine};
            for (int i = 0; i < 3; i++)
            {
                int input{};
                ss2 >> input;
                edgeVec.push_back(input);
            }
            edges.push_back(edgeVec);
        }

        std::vector<std::vector<int>> queries{};
        for (int q = 0; q < nrQueries; q++)
        {
            std::vector<int> queriesVec{};
            std::getline(std::cin, readLine, '\n');
            std::stringstream ss3{readLine};
            for (int j = 0; j < 3; j++)
            {
                int input{};
                ss3 >> input;
                queriesVec.push_back(input);
            }
            //queries.push_back(queriesVec);
            result  = shortestPath(edges, startingNode);
        }

    }
    return 0;
}