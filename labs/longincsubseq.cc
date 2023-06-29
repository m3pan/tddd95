/**
 * Author: Madeleine Nilsson (madni264)
 * Date: 29 july 2023
 *
 * Calculates the length of the Longest Increasing Subsequence (LIS) in the given subsequence using the dynamic
 * programming approach. The program uses the concept of a dynamic programming table to store the lengths of the LIS
 * ending at each element.
 *
 * Time Complexity: O(n^2)
 *   - The algorithm iterates through each element of the given sequence, resulting in an outer loop of O(n).
 *   - For each element, it checks all the previous elements to find the longest increasing subsequence, resulting in
 *   an inner loop of O(n). Therefore, the time complexity of the program is O(n^2).
 *
 * Space Complexity: O(n)
 *   - The algorithm uses two additional vectors: `LISelements` and `DPtable`, each of size n, to store results.
 */

#include <iostream>
#include <vector>
#include <algorithm>

unsigned long LIS(std::vector<int>& givenSequence, std::vector<unsigned long>& DPtable) {

    std::vector<int> LISelements{};

    // Initialize the LIS vector with the first element of the array
    LISelements.push_back(givenSequence[0]);

    // Set the LIS length for the first element as 1
    DPtable[0] = 1;

    // Iterate through the array elements
    for (int i = 1; i < givenSequence.size(); i++) {
        // If the current element is greater than the last element of the LIS
        if (givenSequence[i] > LISelements.back()) {
            // Extend the LIS by appending the current element and update the DP table
            LISelements.push_back(givenSequence[i]);
            DPtable[i] = LISelements.size();
        } else {
            /* If the current element is not greater, find the position to insert it in the LIS.
             * Then, Update the LIS length at the current position*/
            auto pos = lower_bound(LISelements.begin(), LISelements.end(), givenSequence[i]);
            DPtable[i] = pos - LISelements.begin() + 1;
            // Replace the existing element at that position with the current element
            *pos = givenSequence[i];
        }
    }

    return LISelements.size();
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n{};

    while (std::cin >> n) {

        std::vector<unsigned long> DPtable(n, 0);
        std::vector<int> givenSequence(n, 0);

        // Terminal input
        for (int i = 0; i < n; i++) {
            std::cin >> givenSequence[i];
        }

        // Calculate the length of the LIS
        unsigned long lengthLIS = LIS(givenSequence, DPtable);
        std::cout << lengthLIS << std::endl;

        /* Traverse the array in reverse order to reconstruct the LIS. Update the upperbound to ensure the next
         * element to ensure the next element is smaller*/
        double upperbound = 1e10;
        std::vector<int> LISindices; // Vector to store the indices of the LIS elements
        for (int i = n - 1; i >= 0; i--) {
            // If the LIS length at the current position matches the remaining length and the element is smaller
            if (DPtable[i] == lengthLIS && givenSequence[i] < upperbound) {
                // Store index for terminal output
                LISindices.push_back(i);
                upperbound = givenSequence[i];
                lengthLIS--;
            }
        }

        // Terminal output
        for (int i = (int)LISindices.size() - 1; i >= 0; i--) {
            std::cout << LISindices[i] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}