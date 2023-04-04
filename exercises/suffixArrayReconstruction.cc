#include <iostream>

// Each suffix contains at most one ‘*’
// Each position contains exactly one character

std::string reconstruction(int const length, int const nrSuffixes){
    std::string word(length, '#');
    std::string suffix;

    for (int i = 0; i < nrSuffixes; i++){
        // suffixposition = i + 1, själva inputen som vi läser in, nu på cin för att det kunde vara snabbare?
        int suffixPos{};
        std::cin >> suffixPos;
        std::cin >> suffix;
        suffixPos--;

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

        }
        for (auto c : word) {
            if (c == '#') {
                word = "IMPOSSIBLE";
                break;
            }
    }
    return word;
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int nrTestCases{};
    std::cin >> nrTestCases;
    int length;
    int nrSuffixes;
    for (int i = 0; i < nrTestCases; ++i)
    {
        std::cin >> length >> nrSuffixes;

        //!? reconstruction(), to avoid unnecessary function calls

        std::string word(length, '#');
        std::string suffix;
        int suffixPos{};

        for (int i = 0; i < nrSuffixes; ++i){
            // suffixposition = i + 1, själva inputen som vi läser in, nu på cin för att det kunde vara snabbare?
            std::cin >> suffixPos >> suffix;
            --suffixPos;

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

        }
        for (auto c : word) {
            if (c == '#') {
                word = "IMPOSSIBLE";
                break;
            }
        }




        std::cout << word << "\n";
    }
    return 0;
}

