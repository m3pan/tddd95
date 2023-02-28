#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <queue>
#include <cmath>

void islandHopping(int nrIslands, std::vector<std::pair<float, float>> coordinates);



std::vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            std::swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}
/*
struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

*/

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
        islandHopping(nrIslands, coordinates);
        --nrCases;
    }
    return 0;
}

void islandHopping(int nrIslands, std::vector<std::pair<float, float>> coordinates)
{
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

            float distance = pow(pow(x1-x2, 2) + pow(y1-y2, 2), 0.5);
            edges.push({distance, i, j});
        }
    }

    // put each island in its own tree
    /*
    int n;
    std::vector<Edge> edges;

    int cost = 0;
    std::vector<Edge> result;
    parent.resize(n);
    rank.resize(n);
    for (int i = 0; i < n; i++)
    {
        make_set(i);
    }

    std::sort(edges.begin(), edges.end());

    for (Edge e : edges) {
        if (find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            result.push_back(e);
            union_sets(e.u, e.v);
        }
    }
     */
}
