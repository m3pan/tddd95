#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <list>
#include <numeric>
#include <random>
#include <set>

bool isKthBitSet(int n, int k)
{
    /* Given a number N and a bit number K, check if the Kth bit of N is set or not. */
    if (n & (1 << k))
        return true;
    else
        return false;
}


bool containsAllValuesUpToN(const std::set<int>& s, int n) {
    for (int i = 0; i <= n; ++i) {
        if (s.find(i) == s.end()) {
            return false;
        }
    }
    return true;
}


std::vector<int> markBitStrings(std::vector<bool> &nBitStrings, std::vector<int> &subclauses){
    std::vector<int> prune(nBitStrings.size()) ; // vector with 100 ints.
    std::iota (std::begin(prune), std::end(prune), 0); // Fill with 0, 1, ..., 2^N.
    for (int i = 0; i < subclauses.size(); i++) {
        // markera alla där det är "tvärtom"
        if (subclauses[i] != -1) {
            for(auto it = prune.begin(); it != prune.end();) {
                if (subclauses[i] == isKthBitSet(*it, i)) {
                    it = prune.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
    return prune;
}


bool solve(){
    int n, m;   // n:  the number of variables, m: the number of clauses
    std::cin >> n >> m;

    // Generera en vektor med 2^N element
    std::vector<bool> nBitStrings(pow(2,n), true);
    std::set<int> unsatisfiableBitStrings{};

    /* Then, m lines follow corresponding to each clause. Each clause is a disjunction of literals in the
     * form X or ~X for some, where ~X indicates the negation of the literal X. The “or” operator is denoted
     * by a ‘v’ character and is seperated from literals with a single space.
     * */
    std::string clause;
    getline(std::cin, clause);
    while(m){
        bool skip{};
        std::cout << m << "\n";
        getline(std::cin, clause);
        int pos{};
        std::string token;
        bool neg;
        int num;
        int index;
        char x;
        std::vector<int> subclauses(n, -1);
        while ((pos = clause.find(" v ")) != std::string::npos || clause.empty()) {
            // We have disjunctions
            token = clause.substr(0, pos);
            neg = token[0] == '~';
            if (neg)
                token = token.substr(token.length() - 2,2);
            std::istringstream iss{token};
            iss >> x >> index;
            // num = std::stoi(token.substr(1 + neg, token.length())) - 1;
            if (subclauses[index - 1] == -1) {
                subclauses[index - 1] = !neg;
            } else if (subclauses[index - 1] != !neg) {
                skip = true;
                break;
                subclauses[index - 1] = -1;
            }
            clause.erase(0, pos + 3);
        }
        if (skip){
            continue;
        }
        // We do not have disjunctions
        token = clause.substr(0, pos);
        neg = token[0] == '~';
        if (neg)
            token = token.substr(token.length() - 2,2);
        std::istringstream iss{token};
        iss >> x >> index;
        // num = std::stoi(token.substr(1 + neg, token.length())) - 1;
        if (subclauses[index - 1] == -1) {
            subclauses[index - 1] = !neg;
        } else if (subclauses[index - 1] != !neg) {
            subclauses[index - 1] = -1;
        }
        clause.erase(0, pos + 3);
        std::vector<int> delBitstrings = markBitStrings(nBitStrings, subclauses);
        for (const auto& elem : delBitstrings) {
            unsatisfiableBitStrings.insert(elem);
        }
        m--;
    }
    int nr = pow(2,n) - 1;
    if (containsAllValuesUpToN(unsatisfiableBitStrings, nr)) {
        return false;
    } else {
        return true;
    }
}

int main(){

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int testcases{};
    std::cin >> testcases;
    std::string dummy;
    getline(std::cin, dummy);
    for (int t{}; t < testcases; t++){
        if (solve())
            std::cout << "satisfiable\n";
        else
            std::cout << "unsatisfiable\n";
    }
    return 0;
}