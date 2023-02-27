#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>

std::vector<std::vector<std::pair<int, int>>> graph{};

int main(){
    int nrCities{};     // n
    int nrRoads{};      // m

    std::string readLine{};

    while (std::getline(std::cin, readLine, '\n')) {
        if (readLine == "") {
            std::getline(std::cin, readLine, '\n');
            if (readLine == "0 0 0 0") {
                break;
            } else {
                std::cout << "\n\n";
            }
        }
        std::stringstream ss1{readLine};
        ss1 >> nrCities;
        ss1 >> nrRoads;
        std::vector<int> fuelPrice(nrCities);
        std::getline(std::cin, readLine, '\n');
        std::stringstream ss2{readLine};
        for (int n = 0; n < nrCities; n++)
        {
            ss2 >> fuelPrice[n];
        }
        for (int i = 0; i < nrRoads; ++i){
            int u, v, d;
            std::cin >> u >> v >> d;
            graph[u].push_back({d, v});
            graph[v].push_back({d, u});
        }
        int nrQueries;
        std::cin >> nrQueries;

        for (int q = 0; q < nrQueries; q++)
        {
            // For each query, output the price of the cheapest trip from s to e using a car with the given capacity,
            // or “impossible” if there is no way of getting from s to e with the given car.
            int startingCity, goalCity, fuelCapacity;
            std::cin >> startingCity >> goalCity >> fuelCapacity;
        }

    }
}