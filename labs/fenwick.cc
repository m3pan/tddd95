/*
 * Author: Madeleine Nilsson, madni264
 *
 * Problem description: A size of an array and a set of queries to perform on the array is given. The queries can be
 * of two types: add queries and sum queries. Your task is to process these queries efficiently using a Fenwick tree
 * and output the results of the sum queries.
 *
 * Time complexity: O(log n) for both operations, where n is the number of elements in the array.
 * Memory-complexity: O(N), since we store a Fenwick tree that has the same number of nodes as the array has elements.
 * */

#include <iostream>
#include <vector>

double* fenwickTree;
int N, Q;


/**
 * Increases the value at the specified index index in the Fenwick tree by the given delta.
 *
 * @param index The index at which the value in the Fenwick tree will be increased.
 * @param delta The value to be added to the existing value at the specified index.
 * */

void add(int index, double delta) {
    while (index < N) {
        fenwickTree[index] += delta;
        // Calculate the index of the next element in the Fenwick tree with the same parent
        index |= (index + 1);
    }
}

/**
 * Computes the sum of the numbers up to, but not including, the element at index end in the Fenwick tree.
 *
 * @param end The index of the last element (not inclusive) up to which the sum will be calculated.
 * @return The sum of the numbers up to index end in the Fenwick tree.
 * */

long long sum(int end) {
    /* Using long long allows for more efficient memory usage and better compatibility with the underlying bitwise
     * operations used in the Fenwick tree implementation. */
    long long res = 0;
    while (end > 0) {
        res += fenwickTree[end - 1];
        // Calculate the index of the parent of the current index in the Fenwick tree
        end = end & (end - 1);
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> Q;
    // One-based indexing
    N = N+1;

    // Initialize the Fenwick tree with zeros
    fenwickTree = new double[N]();

    std::cout << std::fixed;
    std::cout.precision(0);

    for (long long j = 0; j < Q; ++j) {
        char queryType;
        std::cin >> queryType;

        if (queryType == '+') {
            // Add query, begin by reading the index and delta
            int i;
            double delta;
            std::cin >> i >> delta;
            // Update the Fenwick tree by adding delta to the elements with index i and its descendants
            add(i, delta);
        } else if (queryType == '?') {
            // Sum query, begin by reading the index
            int i;
            std::cin >> i;
            // Calculate and print the sum
            std::cout << sum(i) << '\n';
        } else {
            std::cerr << "Error: Invalid query. Please enter a valid query.\n";
        }
    }

    return 0;
}