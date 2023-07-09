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
#include <sstream>
#include <vector>
#include <cstdio>


//std::vector<double> fenwickTree(5000000,0);
double* fenwickTree;
int N, Q;


/**
 * Calculates the index of the parent element in the Fenwick tree for the given index i. It performs a bitwise
 * AND operation between i and i + 1 to calculate the index.
 *
 * @param i The index for which to calculate the parent index.
 */

int g(int i) {
    //int nextIndex = i & (i + 1);
    return i & (i + 1); // Equivalent to i - (i & -i)
}


/**
 * Computes the index of the next element after i in the Fenwick tree that has the same parent.
 * It performs a bitwise OR operation between i and i + 1 to efficiently calculate this index.
 *
 * @param i The index for which to calculate the next element in the Fenwick tree that has the same parent
 * */

int h(int i) {
    //int nextIndex = i | (i + 1);
    return i | (i + 1); // Equivalent to i + (i & -i)
}


/**
 * Increases the value at the specified index index in the Fenwick tree by the given delta.
 *
 * @param index The index at which the value in the Fenwick tree will be increased.
 * @param delta The value to be added to the existing value at the specified index.
 * */

void add(int index, double delta) {
    for(; index< N; index|=(index+1)){
        fenwickTree[index] = fenwickTree[index] + delta;
    }
}

/* for(; index< N; index|=(index+1)){
        fenwicktree[index] = fenwicktree[index] + delta;
    }
 *
 * */

/**
 * Computes the sum of the numbers up to, but not including, the element at index end in the Fenwick tree.
 *
 * @param end The index of the last element (not inclusive) up to which the sum will be calculated.
 * @return The sum of the numbers up to index end in the Fenwick tree.
 * */

double sum(int end) {
    double res = 0;
    /*
    while (end >= 0) {
        res += fenwickTree[end];
        end = (end & (end + 1)) - 1;
    }*/
    for(;end > 0; end &= end-1){
        res += fenwickTree[end-1];
    }

    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    std::cin >> N >> Q;
    N = N+1;

    fenwickTree = new double[N]();

    //fenwickTree.assign(0, N);
    //fenwickTree.resize(N);

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