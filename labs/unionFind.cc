#include <iostream>
#include <sstream>
#include <vector>
#include <map>

/*
 * Implement a data structure to handle distinct sets. When the data structure is created, all elements are in their
 * own sets. Your implementation should at least support the following operations:
 * - union(int a, int b) - merge the sets containing the elements a and b
 * - boolean same(int a, int b) - test whether a and b are in the same set
 * Recommended time complexity: amortized O(log n) for both operations, where n is the total number of elements.
 * Warning: You are expected to produce a lot of output data for this problem. Make sure that you don't flush the
 * output buffer after each line, since this might make your otherwise correct solution too slow.
 * */


/*
struct element{
    int set{};
    int parent{};
};
*/

void join(int a, int b, std::map<int, int> & sets);
bool same(int a, int b, const std::map<int, int> & sets);

int main() {
    std::string inputString;
    int numberOfElements{};
    int numberOfOperations{};
    char operation{};
    int a{};
    int b{};
    std::vector <char> operations;
    //std::vector <element> lvalue;
    //std::vector <element> rvalue;

    std::getline (std::cin, inputString, '\n');

    if (inputString.empty()) {return 0;}
    std::stringstream ss1(inputString);
    ss1 >> numberOfElements; ss1 >> numberOfOperations;

    // Create a map for numberOfOperations
    std::map<int,int> sets;
    for (int i = 0; i < numberOfOperations; i++)
    {
        // Add our sets to the map
        sets.insert({i, i});
    }

    for (int i = 0; i < numberOfOperations; i++)
    {
        std::getline (std::cin, inputString, '\n');
        std::istringstream ss2(inputString);
        ss2 >> operation;
        ss2 >> a;
        ss2 >> b;

        if (operation == '?') {
            // boolean same(int a, int b) - test whether a and b are in the same set
            bool result = same(a, b, sets);
            if (result) {
                std::cout << "yes" << std::endl;
            } else {
                std::cout << "no" << std::endl;
            }

        } else {
            // union(int a, int b) - merge the sets containing the elements a and b
            join(a, b, sets);
        }
    }

    //unionFind(numberOfOperations,operations, lvalue, rvalue);

    return 0;
}

void join(int a, int b, std::map<int, int> & sets)
{
    sets[a] = b;
}

bool same(int a, int b, const std::map<int, int> & sets)
{
    int aRoot{};
    int bRoot{};
    int aParent = sets.find(a)->second;
    int bParent = sets.find(b)->second;
    if (aParent == bParent)
    {
        return true;
    }
    if (sets.find(a)->first == aParent)
    {
        aRoot = true;
    }
    if (sets.find(b)->first == bParent)
    {
        bRoot = true;
    }
    if (aRoot && bRoot && aRoot != bRoot)
    {
        return false;
    }
    if (not(aRoot))
    {
        return same(aParent, b, sets);
    }
    if (not(bRoot))
    {
        return same(a, bParent, sets);
    }
    // we won't get here?
    return false;
}

