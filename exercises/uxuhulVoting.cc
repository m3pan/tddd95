#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <bitset> // for std::cout
#include <unordered_map>

void uxuhulVoting(std::vector<std::vector<int>> preferences);

int countStoneFlips(int firstStone, int secondStone){
    int n = firstStone ^ secondStone;
    int flips = 0;
    while (n) {
        n = n & (n - 1);    // clear the least significant bit set
        flips++;
    }
    return flips;
}
// change to zero-indexed
std::unordered_map<int, int> states = {{0b000, 0}, {0b001, 1}, {0b010, 2}, {0b011, 3}, {0b100, 4}, {0b101, 5}, {0b110, 6}, {0b111, 7}};
std::unordered_map<int, std::string> convertStates = {{0, "NNN"}, {1, "NNY"}, {2, "NYN"}, {3, "NYY"}, {4, "YNN"}, {5, "YNY"}, {6, "YYN"}, {7, "YYY"}};

int main() {
    int votingRounds{};
    std::string nr_st;
    std::getline (std::cin, nr_st, '\n');
    std::stringstream ss(nr_st);
    ss >> votingRounds;

    for (int round = 1; round <= votingRounds; round++){
        int votingPriests{};
        std::getline (std::cin, nr_st, '\n');
        std::stringstream ss(nr_st);
        ss >> votingPriests;

        std::vector <std::vector <int>> preferences;

        for (int priest = 1; priest <= votingPriests; priest++)
        {
            std::string line;
            std::getline(std::cin, line, '\n');
            std::istringstream iss(line);
            int input{};
            std::vector <int> singleRow;
            for (int vote = 1; vote <= 8; vote++)
            {
                iss >> input;
                singleRow.push_back(input);
            }
            preferences.push_back(singleRow);
        }
        uxuhulVoting(preferences);
    }
    return 0;
}

void uxuhulVoting(std::vector<std::vector<int>> preferences) {
    // Börja med äldsta prästen, vi vet vilka 4 alternativ den har att välja på.
    // Den översätter de fyra inputs till output beroende på egna preferenser. map!!
    // Skicka de fyra rankningarna till äldre som rankar om baserat på översättningen. Då tar den ett beslut baserat på översättning

    std::map<int, int> comprehensiveMap{};

    //!! Let the last priest make its choices
    // Determine what states the priest could get

    std::vector<int> inputStates;
    std::vector<int> outputStates;
    int votingPriests = preferences.size();
    if (votingPriests % 2 == 1) {
        // Odd priest, odd input
        inputStates = {0b011, 0b110, 0b101, 0b000};
        outputStates = {0b001, 0b010, 0b100, 0b111};
    } else {
        // Even priest, even input
        inputStates = {0b001, 0b010, 0b100, 0b111};
        outputStates = {0b011, 0b110, 0b101, 0b000};
    }

    //todo: remove iterators, change to vectors
    for (int inputStone : inputStates) {
        int pref{1000};
        // For each input state, determine what output is desirable and store it in a map
        std::unordered_map<int, int>::iterator outputIt;
        // Determine possible outputs for each input, {score : output}. The map is sorted based on score
        //std::map<int, int> possibleOutputs{};
        for (int outputStone : outputStates) {
            if (countStoneFlips(inputStone, outputStone) == 1 && preferences.back()[states[outputStone]] < pref) {
                // Enters the most preferable output for each input
                pref = preferences.back()[states[outputStone]];
                comprehensiveMap[inputStone] = outputStone;
            }
        }
    }
    --votingPriests;    // här är det rätt

    // Let the rest of the priests make their choices
    // todo: dubbelkolla for-loop index

    // Set inputStates and outputStates

    for (int i = preferences.size()-2; i >= 0; --i) {
        if (votingPriests % 2) {
            // possibleStates = {{001, 2}, {010, 3}, {100, 5}, {111, 8}};
            inputStates = {0b011, 0b110, 0b101, 0b000}; ;
            outputStates = {0b001, 0b010, 0b100, 0b111};
        } else {
            // Even priest, odd input
            // possibleStates = {{000, 1}, {011, 4}, {101, 6}, {110, 7}};
            inputStates = {0b001, 0b010, 0b100, 0b111};
            outputStates = {0b011, 0b110, 0b101, 0b000}; ;
        }
        // Determine the optimal choice for all the following priests
        std::unordered_map<int, int> comprehensiveMap2;
        std::unordered_map<int, int>::iterator inputIt;
        for (int inputStone : inputStates) {
            int pref{1000};
            for (int outputStone : outputStates) {
                if (countStoneFlips(inputStone, outputStone) == 1 && preferences[i][states[comprehensiveMap[outputStone]]] < pref) {
                    //std::cout << "preferences: " << preferences[i][states[comprehensiveMap[outputStone]]] << std::endl;
                    pref = preferences[i][states[comprehensiveMap[outputStone]]];
                    comprehensiveMap2[inputStone] = outputStone;
                }
            }
        }


        for (std::pair<int,int> c : comprehensiveMap2) {
            comprehensiveMap[c.first] = comprehensiveMap[c.second];
        }
        // titta på den resulterande mapen
        /*auto it = comprehensiveMap.find(1);
        if (it != comprehensiveMap.end()) {
            std::cout << std::bitset<3>(states.find(it->second)->second) << std::endl;
        }*/

        --votingPriests;
    }
    std::cout << convertStates[comprehensiveMap[0b000]] << "\n";
    //std::cout << std::bitset<3>(comprehensiveMap[0b000]) << "\n";
}

