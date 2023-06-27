#include <iostream>
#include <sstream>
#include <vector>

/*
 * Implement a function that computes what to pack in a capacity limited knapsack to maximize the total value of all
 * the items packed. Each item has an integer value and an integer weight. The total weight of all items packed must
 * be less than or equal to the capacity (which is a real number).
 *
 * Suggested API:
 * int[] knapsack(capacity, value/weight[])
 * The returned vector contains the indices of the chosen items.
 * Recommended time complexity: O(n·capacity).
 * */

//!? we’re assuming that there are no massless, valuable items
// todo: change so that the table stores a std::vector of the picked items


struct Item {
    int value{};
    int weight{};
};

int getValue(const std::vector <Item>& items, const std::vector<int>& pickedItems) {
    int sum{};
    for (int i : pickedItems) {
        sum += items[i].value;
    }
    return sum;
}

std::vector<int> knapsack(int currCapacity, const std::vector <Item>& items, unsigned long currItem, std::vector <std::vector <std::vector<int>>>& table);

int main() {
    int capacity{};
    unsigned long nrItems{};
    std::string line{};
    std::cout << "hello" << std::endl;

    while (std::cin >> capacity >> nrItems){
        std::vector<Item> items{};
        int value{};
        int weight{};
        for (int i{}; i < nrItems; ++i) {
            std::cin >> value >> weight;
            Item temp{value, weight};
            items.push_back(temp);
        }
        std::cout << "no" << std::endl;

        /* For each test case, output a line containing the number of items chosen, followed by a line containing
         * the indices of the chosen items (the first item has index, the second index, and so on). The indices can
         * be given in any order.*/

        // The entry point to solve the 0-1 Knapsack problem using dynamic programming. The function initializes
        // std::vector <int> chosenItems = knapsack(capacity, items);
        /* Create a 2-dimensional vector where an entry in row i, column j represents the maximum value that can be
         * * obtained with items 1, 2, 3 … i, in a knapsack that can hold j weight units. */
        nrItems = items.size();

        std::vector<std::vector<std::vector<int>>> table(nrItems, std::vector<std::vector<int>>(capacity + 1, {-1}));
        std::vector<int> pickedItems{};
        pickedItems = knapsack(capacity, items, nrItems - 1, table);
        //std::cout << maxValue << std::endl;
        for (int it : pickedItems){
            std::cout << it << std::endl;
        }
    }
    return 0;
}

std::vector<int> knapsack(int currCapacity, const std::vector <Item>& items, unsigned long currItem, std::vector <std::vector <std::vector<int>>>& table) {
    /*
     * This recursive function determines the items to pick in order to obtain the maximum value for the knapsack.
     * */

    // BASE CONDITIONS
    // Base condition: No more items or weight to consider
    if (currCapacity == 0 || currItem == 0) {
        return {};
    }

    // Base condition: If the value has already been computed and stored in the table we return it directly
    if (table[currItem][currCapacity] != std::vector<int>({-1})) {
        return table[currItem][currCapacity];
    }

    // RECURSIVE CONDITIONS
    // Recursive case: Checks if the weight of the nth item is more than the knapsack's currCapacity and should be ignored
    if (items[currItem].weight > currCapacity) {
        table[currItem][currCapacity] = knapsack(currCapacity, items, currItem - 1, table);
        return table[currItem][currCapacity];
    }

    // Recursive case: Store the maximum value by either including or excluding the current item
    // Including the item:
    int inclVal = items[currItem].value + getValue(items, knapsack(currCapacity - items[currItem].weight, items, currItem -1, table));
    int exclVal = getValue(items, knapsack(currCapacity, items, currItem - 1, table));
    // int inclVal = items[currItem].value + knapsack(currCapacity - items[currItem].weight, items, currItem -1, table, pickedItems);
    //int exclVal = knapsack(currCapacity, items, currItem - 1, table, pickedItems);

    if (inclVal > exclVal) {
        // add element to vector in table
        table[currItem][currCapacity].push_back((int)currItem);
    }
    return table[currItem][currCapacity];
}
