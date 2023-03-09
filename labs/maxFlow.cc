#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>


int INF = 100000;

int bfs(int nrNodes, int nrEdges, int startNode, int endNode, std::vector <std::vector <int>> &dungeon,
        std::vector<std::vector<std::pair<int, int>*>> &capacityMatrix, std::vector<int>& parent) {
    /* Has augmenting path, return bool */

    // Reset all parents
    std::fill(parent.begin(), parent.end(), -1);
    parent[startNode] = -2;
    std::queue<std::pair<int, int>> q;
    q.push({startNode, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : dungeon[cur]) {
            if (parent[next] == -1 && capacityMatrix[cur][next]) {
                parent[next] = cur;
                int new_flow = std::min(flow, (*capacityMatrix[cur][next]).first);
                if (next == endNode)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxFlow(int nrNodes, int nrEdges, int startNode, int endNode, std::vector <std::vector <int>> &dungeon,
            std::vector<std::vector<std::pair<int, int>*>> &capacityMatrix) {
    /* The function maxFlow will return the value of the maximal flow. During the algorithm, the matrix capacity
     * will actually store the residual capacity of the network. The value of the flow in each edge will actually
     * not be stored, but it is easy to extend the implementation - by using an additional matrix - to also store
     * the flow and return it.
     * */

    int flow = 0;
    std::vector<int> parent(nrNodes);
    int new_flow;

    while (new_flow = bfs(nrNodes, nrEdges, startNode, endNode, dungeon, capacityMatrix, parent)) {
        flow += new_flow;
        int cur = endNode;
        while (cur != startNode) {
            int prev = parent[cur];
            (*capacityMatrix[prev][cur]).first -= new_flow;
             (*capacityMatrix[cur][prev]).second += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    int nrNodes, nrEdges, startNode, endNode;       // n, m, s, t

    std::cin >> nrNodes >> nrEdges >> startNode >> endNode;

    /* We use two containers for the graph:
     * @ dungeon: all edges but no capacities. The first index is the fromNode. We have duplicates of the nodes since
     * the graph is undirected.
     *
     * @ capacity: a matrix that stores {capacity, remainingCapacity} between all nodes.
     * */
    std::vector <std::vector <int>> dungeon(nrNodes, std::vector<int>());
    std::vector<std::vector<std::pair<int, int> *>> capacityMatrix(nrNodes, std::vector<std::pair<int, int> *>(nrNodes));

    int from, to, c;

    for (int i = 0; i < nrEdges; ++i) {
        std::cin >> from >> to >> c;

        dungeon[from].push_back(to);
        dungeon[to].push_back(from);

        // Add a pointer to a capacity pair to the capacityMatris
        // std::pair<int, int> capacityPair = std::make_pair(c, 0);
        // std::pair<int, int> *capPtr = &capacityPair;

        // std::auto_ptr<std::pair<int, int>> x(new std::make_pair(c, 0))
        capacityMatrix[from][to] = new std::pair<int, int> (std::make_pair(c, 0));
        capacityMatrix[to][from] = new std::pair<int, int> (std::make_pair(c, 0));
    }

    int result = maxFlow(nrNodes, nrEdges, startNode, endNode, dungeon, capacityMatrix);
    std::cout << result << std::endl;

    return 0;
}