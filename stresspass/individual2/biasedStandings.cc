#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>


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


int biasedStandings(int nrTeams, std::vector<std::pair<std::string, int>> &teams)
{
    std::vector<int> parent(nrTeams);
    std::vector<int> rank(nrTeams);       // hur djupt i vårt träd vi är

    // create all nodes
    for (int i = 0; i < nrTeams; i++)
    {
        parent[i] = 1;
        rank[i] = 1;
    }

    // create all edges
    // sort all edges of the graph in non-decreasing order of the weights
    std::priority_queue<std::tuple<int, int, int>> edges;   // {badness, name, to}
    for (int i = 0; i < nrTeams; i++)
    {
        int preferredPos = teams[i].second;

        for (int pos = i + 1; pos < nrTeams; pos++)
        {
            int badness = abs(preferredPos - pos);
            edges.push({-badness, i, pos});
        }
    }

    // put each team in its own tree
    double cost = 0;
    std::vector<std::tuple<int, int, int>> result;

    int nrEdges = edges.size();

    for (int n = 0; n < nrEdges; n++)
    {
        std::tuple<int, int, int> top = edges.top();

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

int main()
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(NULL);

    int nrTestCases;
    std::cin >> nrTestCases;

    int nrTeams{};  // N <= 100 000

    for (int n = 0; n < nrTestCases; n++)
    {
        std::string blankLine{};
        std::getline(std::cin, blankLine, '\n');
        std::cin >> nrTeams;
        std::vector<std::pair<std::string, int>> teams;
        for (int t = 0; t < nrTeams; t++)
        {
            std::string teamName{};
            int prefPlace{};
            std::cin >> teamName >> prefPlace;
            teams.push_back({teamName, prefPlace});     // emplace_back?
        }

        int result = biasedStandings(nrTeams, teams);
        std::cout << result << '\n';
    }
    return 0;
}