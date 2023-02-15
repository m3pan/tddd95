#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <bitset> // for std::cout
#include <unordered_map>

void uxuhulVoting(int votingPriests, int currPriest, const std::vector<std::vector <int>>& preferences);

// std::unordered_map<int,int>states = {{0b000, 1}, {0b001, 2}, {0b010, 3}, {0b011, 4},
                                                // {0b100, 5}, {0b101, 6}, {0b110, 7}, {0b111, 8}};
std::unordered_map<int,int>states = {{1,0b000}, {2,0b001}, {3,0b010}, {4,0b011},
                                     {5, 0b100}, {6,0b101}, {7,0b110}, {8,0b111}};

std::unordered_map<int, int>oddPriests = {{2, 0b001}, {3, 0b010}, {5, 0b100}};

std::unordered_map<int, int>evenPriests = {{1, 0b000}, {4, 0b011}, {6, 0b101}, {7, 0b110}};

int countStoneFlips(int firstStone, int secondStone){
    int n = firstStone ^ secondStone;
    int flips = 0;
    while (n) {
        n = n & (n - 1);    // clear the least significant bit set
        flips++;
    }
    return flips;
}


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
        int currPriest{};
        uxuhulVoting(votingPriests, currPriest, preferences);
    }
    return 0;
}

void uxuhulVoting(int votingPriests, int currPriest, const std::vector<std::vector <int>>& preferences) {

    // Börja med äldsta prästen, vi vet vilka 4 alternativ den har att välja på.
    // Den översätter de fyra inputs till output beroende på egna preferenser. map!!
    // Skicka de fyra rankningarna till äldre som rankar om baserat på översättningen. Då tar den ett beslut baserat på översättning

    std::map<int, int> comprehensiveMap{};


    int remainingPriests = votingPriests - currPriest;
    std::vector<int> possiblePref{}; // our output
    std::map<int, int> preferredOutputs{};  // {input : output}
    for (int priest = votingPriests; priest > 0; priest--) {
        // determine what states the priest could get
        std::unordered_map<int, int> inputStates;
        std::unordered_map<int, int> outputStates;

        if (priest == 1) {
            // The first is a special case
            // possibleStates = {{001, 2}, {010, 3}, {100, 5}}; // todo: add outputStates
            inputStates = {{1, 0b000}};
            outputStates = {{2, 0b001},
                            {3, 0b010},
                            {5, 0b100}};
        } else if (priest % 2 == 0) {
            // Even priest, odd input
            // possibleStates = {{000, 1}, {011, 4}, {101, 6}, {110, 7}};
            inputStates = {{2, 0b001},
                           {3, 0b010},
                           {5, 0b100},
                           {8, 0b111}};
            outputStates = {{1, 0b000},
                            {4, 0b011},
                            {6, 0b101},
                            {7, 0b110}};
        } else {
            // Odd priest, even input
            // possibleStates = {{001, 2}, {010, 3}, {100, 5}, {111, 8}};
            inputStates = {{1, 0b000},
                           {4, 0b011},
                           {6, 0b101},
                           {7, 0b110}};
            outputStates = {{2, 0b001},
                            {3, 0b010},
                            {5, 0b100},
                            {8, 0b111}};
        }
        std::unordered_map<int, int>::iterator inputIt;
        for (inputIt = inputStates.begin(); inputIt != inputStates.end(); inputIt++) {
            // For each input state, determine what output is desirable and store it in a map
            std::unordered_map<int, int>::iterator outputIt;
            // Determine possible outputs for each input, {score : output}. The map is sorted based on score
            std::map<int, int> possibleOutputs{};
            for (outputIt = outputStates.begin(); outputIt != inputStates.end(); outputIt++) {
                if (countStoneFlips(inputIt->second, outputIt->second) == 1) {
                    possibleOutputs.insert({preferences[priest-1][outputIt->first], outputIt->first});
                    // bestäm outputIt->second värde och lägg i en lista
                    // std::cout << preferences[priest-1][outputIt->first] << std::endl;
                    // Skapa en map från inputIt till outputIt
                }
            }
            // The most desirable output
            int chosenOutput = possibleOutputs.find((possibleOutputs.begin())->first)->second;
            preferredOutputs.insert({inputIt->first, chosenOutput});
        }
        if (priest == votingPriests)
        {
            comprehensiveMap = preferredOutputs;
            continue;
        } else {
            std::map<int, int> comprehensiveMap2{};
            // let comprehensiveMap be like {olderInput: olderOutput} and connect it with preferredOutputs {newInput : newOutput}
            for (const auto& pairA : preferredOutputs) {
                int keyA = pairA.first;
                int valueA = pairA.second;

                // check if the key exists in map B
                auto it = comprehensiveMap.find(valueA);
                if (it != comprehensiveMap.end()) {
                    int valueB = it->second;
                    comprehensiveMap2[keyA] = valueB;
                }
            }
            comprehensiveMap = comprehensiveMap2;
        }
    }
    // titta på den resulterande mapen
    auto it = comprehensiveMap.find(1);
    if (it != comprehensiveMap.end()) {
        std::cout << std::bitset<3> (states.find(it->second)->second) << std::endl;
    }
}

        /*
            std::cout << it->first    // string (key)
                      << ':'
                      << it->second   // string's value
                      << std::endl;
            // inputStates = {{2, 001}, {3, 010}, {5, 100}};
            // inputStates = {{1, 000}, {4, 011}, {6, 101}, {7, 110}};
*/
    /*

        // sort the states based on how valuable they are
        for (int pref = 1; pref <= 8; pref++)
        {
            if(inputStates.count(preferences[priest][pref]))
            {
                possiblePref.push_back(preferences[priest][pref]);
            }
        }

        std::unordered_map<std::bitset<3>,int>::iterator it;

        for (it = possibleStates.begin(); it != possibleStates.end(); it++)
        {
            std::cout << it->first    // string (key)
                      << ':'
                      << it->second   // string's value
                      << std::endl;
                                  inputStates = {{2, 001}, {3, 010}, {5, 100}};
                                              inputStates = {{1, 000}, {4, 011}, {6, 101}, {7, 110}};


        }*/
