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


struct Item {
    int value{};
    int weight{};
};


int getValue(const std::vector <Item>& items, const std::vector<int>& pickedItems) {
    int sum{};
    for (int i : pickedItems) {
        if (i == -1) {
            sum += 0;
        }
        sum += items[i].value;
    }
    return sum;
}


std::vector<int> knapsack(int currCapacity, const std::vector <Item>& items, unsigned long currItem, std::vector<std::vector<std::vector<int>>>& table) {
    /*
     * This recursive function determines the items to pick in order to obtain the maximum value for the knapsack.
     * I need to store the items selected in each of those sub-solutions as well, and then aggregate this at the end.
     * */

    // BASE CONDITIONS
    // Base condition: No more items or weight to consider
    if (currCapacity == 0 || currItem == 0) {
        return {};
    }

    // Base condition: If the value has already been computed and stored in the table we return it directly
    if (table[currItem][currCapacity] != std::vector<int>{-1}) {
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
    auto inclItems = knapsack(currCapacity - items[currItem].weight, items, currItem - 1, table);
    int inclVal = items[currItem].value + getValue(items, inclItems);

    auto exclItems = knapsack(currCapacity, items, currItem - 1, table);
    int exclVal = getValue(items, exclItems);

    if (inclVal > exclVal) {
        table[currItem][currCapacity] = inclItems;
        table[currItem][currCapacity].push_back(currItem);
    } else {
        table[currItem][currCapacity] = exclItems;
    }

    return table[currItem][currCapacity];
}


int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

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

        /* Create a 2-dimensional vector where an entry in row i, column j represents the maximum value that can be
         * obtained with items 1, 2, 3 … i, in a knapsack that can hold j weight units. */
        std::vector<std::vector<std::vector<int>>> table(nrItems, std::vector<std::vector<int>>(capacity + 1, std::vector<int>(1, -1)));

        std::vector <int> chosenItems = knapsack(capacity, items, nrItems - 1, table);

        // Terminal output
        std::cout << chosenItems.size() << "\n";
        for (int it : chosenItems) {
            if (it == -1) {continue;}
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
