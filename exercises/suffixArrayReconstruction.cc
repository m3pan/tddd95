#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <unordered_map>
#include <map>

// Each suffix contains at most one ‘*’
// Each position contains exactly one character

std::string reconstruction(std::vector<std::string> &input, int const length){
    std::string word(length, '#');
    for (int suffixPos = 0; suffixPos < input.size(); suffixPos++){
        // suffixposition = i + 1, själva inputen
        std::string suffix = input[suffixPos];

        for (int j = 0; j < suffix.length(); ++j) {
            // iterate over each character in the suffix
                if (suffix[j] == '*') {
                    // hoppa över placeholders
                    j = length - suffix.length() + 1;
                    continue;
                }
                if (word[suffixPos + j] != '#')
                {
                    if (word[suffixPos + j] != suffix[j]){
                        word = "IMPOSSIBLE";
                        break;
                    }
                }
            word[suffixPos + j] = suffix[j];
        }

        for (auto c : word) {
            if (c == '#') {
                word = "IMPOSSIBLE";
                break;
            }
        }
    }
    return word;
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    int nrTestCases{};
    std::cin >> nrTestCases;
    for (int i = 0; i < nrTestCases; i++)
    {
        int length;
        std::cin >> length;
        int suffixes;
        std::cin >> suffixes;
        std::vector<std::string> input(suffixes, "");
        std::map<int, char> word;
        for (int j = 0; j < suffixes; j++)
        {
            int position{};
            std::cin >> position;
            std::string suffix;
            std::cin >> suffix;
            input[position - 1] = suffix; // zero indexing
        }
        std::string result = reconstruction(input, length);
        std::cout << result << "\n";
    }
    return 0;
}

