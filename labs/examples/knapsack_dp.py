# https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/


def knapsack(wt, val, W, n):
    # base conditions
    if n == 0 or W == 0:
        return 0

    # If the place in the table is filled, return it
    if t[n][W] != -1:
        return t[n][W]

    # choice diagram code
    if wt[n - 1] <= W:
        # Update table
        t[n][W] = max(
            val[n - 1] + knapsack(
                wt, val, W - wt[n - 1], n - 1),
            knapsack(wt, val, W, n - 1))
        return t[n][W]
    elif wt[n - 1] > W:
        # Set value in table
        t[n][W] = knapsack(wt, val, W, n - 1)
        return t[n][W]


if __name__ == '__main__':
    profit = [60, 100, 120]
    weight = [10, 20, 30]
    W = 50
    n = len(profit)

    # We initialize the matrix with -1 at first.
    t = [[-1 for i in range(W + 1)] for j in range(n + 1)]
    print(knapsack(weight, profit, W, n))
