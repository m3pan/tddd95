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
        if (readLine == "0 0 0 0") break;
        std::stringstream ss1{readLine};
        ss1 >> nrNodes;
        ss1 >> nrEdges;
        ss1 >> nrQueries;
        ss1 >> startingNode;
        std::vector<std::vector<std::pair<int, int>>> adjacent{};
        std::vector<int> result{};
        for (int m = 0; m < nrEdges; m++)
        {
            std::vector<int> edgeVec{};
            std::getline(std::cin, readLine, '\n');
            std::stringstream ss2{readLine};

            // Read input line consisting of [u v w] = [startNode endNode weight]
            int u{};
            int v{};
            int w{};
            ss2 >> u;
            ss2 >> v;
            ss2 >> w;
            std::pair<int, int> edge{v, w};

            adjacent[edgeVec[0]].push_back(edge);   // todo: kolla varför det blir fel här
        }
        std::vector<int> distance{};
        std::vector<int> predecessors{};
        distancePredecessors returnValue{};
        returnValue  = shortestPath(adjacent, startingNode, distance, predecessors);

        // no need to store queries, just print returnvalues

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
        int v = queue.begin()->second;
        queue.erase(queue.begin());

        for (auto edge : adjacent[v]) {
            int to = edge.first;
            int len = edge.second;

            if (distance[v] + len < distance[to]) {
                queue.erase({distance[to], to});
                distance[to] = distance[v] + len;
                predecessors[to] = v;
                queue.insert({distance[to], to});
            }
        }
    }
    return distancePredecessors{distance, predecessors};

}

