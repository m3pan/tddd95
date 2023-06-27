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

struct Item {
    int value{};
    int weight{};
};

int knapsackRecursive(int currCapacity, const std::vector <Item>& items, unsigned long currItem, std::vector <std::vector <int>>& table);

int knapsack(int capacity, const std::vector <Item>& items);

int main() {
    int capacity{};
    int nrItems{};

    while (std::cin >> capacity >> nrItems){
        std::vector<Item> items{};
        int value{};
        int weight{};
        for (int i{}; i < nrItems; ++i) {
            std::cin >> value >> weight;
            Item temp{value, weight};
            items.push_back(temp);
        }

        /* For each test case, output a line containing the number of items chosen, followed by a line containing
         * the indices of the chosen items (the first item has index, the second index, and so on). The indices can
         * be given in any order.*/

        // std::vector <int> chosenItems = knapsack(capacity, items);
        int maxValue = knapsack(capacity, items);
        std::cout << maxValue << std::endl;
    }
    return 0;
}

int knapsack(int capacity, const std::vector <Item>& items)
{
    /*
     * The entry point to solve the 0-1 Knapsack problem using dynamic programming. The function initializes
     *
     * Parameters:
     *
     * Return value:
     * Returns the value inside the table, i.e. the maximum value the knapsack can hold
     * */
    unsigned long nrItems = items.size();
    // todo: move this code snippet to main function
    // todo: change so that the table stores a std::vector of the picked items

    /* Create a 2-dimensional vector where an entry in row i, column j represents the maximum value that can be
     * obtained with items 1, 2, 3 … i, in a knapsack that can hold j weight units. */
    std::vector <std::vector <int>> table( nrItems, std::vector<int> (capacity + 1, -1));

    /* Now, we want to begin populating our table. As with all dynamic programming solutions, at each step, we
     * will make use of our solutions to previous sub-problems. */

    return knapsackRecursive(capacity, items, nrItems - 1, table);
}

int knapsackRecursive(int currCapacity, const std::vector <Item>& items, unsigned long currItem, std::vector <std::vector <int>>& table) {
    /*
     * This recursive function determines the items to pick in order to obtain the maximum value for the knapsack.
     * */

    // BASE CONDITIONS
    // Base condition: No more items or weight to consider
    if (currCapacity == 0 || currItem == 0) {
        return 0;
    }

    // Base condition: If the value has already been computed and stored in the table we return it directly
    if (table[currItem][currCapacity] != -1) {
        return table[currItem][currCapacity];
    }

    // RECURSIVE CONDITIONS
    // Recursive case: Checks if the weight of the nth item is more than the knapsack's currCapacity and should be ignored
    if (items[currItem].weight > currCapacity) {
        table[currItem][currCapacity] = knapsackRecursive(currCapacity, items, currItem - 1, table);
        return table[currItem][currCapacity];
    }

    // Recursive case: Store the maximum value by either including or excluding the current item

    // Including the item:
    int inclVal = items[currItem].value + knapsackRecursive(currCapacity - items[currItem].weight, items, currItem -1, table);
    int exclVal = knapsackRecursive(currCapacity, items, currItem - 1, table);

    if (inclVal > exclVal) {
        // add element to vector in table
        table[currItem][currCapacity] = inclVal;
    } else {
        table[currItem][currCapacity] = exclVal;
    }
    return table[currItem][currCapacity];
}
