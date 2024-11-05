#include <bits/stdc++.h>
using namespace std;

class KnapSack
{
public:
    // Memoization approach
    int solveMemoization(vector<int> &weight, vector<int> &value, int index, int capacity, vector<vector<int>> &dp)
    {
        if (index == 0)
        {
            if (weight[0] <= capacity)
                return value[0];
            else
                return 0;
        }

        if (dp[index][capacity] != -1)
            return dp[index][capacity];

        int include = 0;
        if (weight[index] <= capacity)
            include = value[index] + solveMemoization(weight, value, index - 1, capacity - weight[index], dp);

        int exclude = 0 + solveMemoization(weight, value, index - 1, capacity, dp);

        dp[index][capacity] = max(include, exclude);
        return dp[index][capacity];
    }

    // Tabulation approach
    int solveTabulation(vector<int> &weight, vector<int> &value, int n, int capacity)
    {
        vector<vector<int>> dp(n, vector<int>(capacity + 1, 0));

        // Base-case
        for (int w = weight[0]; w <= capacity; w++)
        {
            if (weight[0] <= capacity)
                dp[0][w] = value[0];
            else
                dp[0][w] = 0;
        }

        for (int index = 1; index < n; index++)
        {
            for (int w = 0; w <= capacity; w++)
            {
                int include = 0;
                if (weight[index] <= w)
                    include = value[index] + dp[index - 1][w - weight[index]];

                int exclude = 0 + dp[index - 1][w];

                dp[index][w] = max(include, exclude);
            }
        }

        return dp[n - 1][capacity];
    }

    // Space-optimized approach
    int spaceOptimised(vector<int> &weight, vector<int> &value, int n, int capacity)
    {
        vector<int> prev(capacity + 1, 0);
        vector<int> curr(capacity + 1, 0);

        // Base-case
        for (int w = weight[0]; w <= capacity; w++)
        {
            if (weight[0] <= capacity)
                prev[w] = value[0];
            else
                prev[w] = 0;
        }

        for (int index = 1; index < n; index++)
        {
            for (int w = 0; w <= capacity; w++)
            {
                int include = 0;
                if (weight[index] <= w)
                    include = value[index] + prev[w - weight[index]];

                int exclude = 0 + prev[w];

                curr[w] = max(include, exclude);
            }

            prev = curr;
        }

        return prev[capacity];
    }

    // Wrapper function for Memoization
    int knapSackMemoization(vector<int> &weight, vector<int> &value, int capacity)
    {
        int n = weight.size();
        vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));
        return solveMemoization(weight, value, n - 1, capacity, dp);
    }

    // Wrapper function for Tabulation
    int knapSackTabulation(vector<int> &weight, vector<int> &value, int capacity)
    {
        int n = weight.size();
        return solveTabulation(weight, value, n, capacity);
    }

    // Wrapper function for Space-Optimized
    int knapSackSpaceOptimised(vector<int> &weight, vector<int> &value, int capacity)
    {
        int n = weight.size();
        return spaceOptimised(weight, value, n, capacity);
    }
};

int main()
{
    int n, capacity;
    cout << "Enter the number of items: ";
    cin >> n;

    vector<int> weight(n), value(n);

    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; i++)
        cin >> weight[i];

    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; i++)
        cin >> value[i];

    cout << "Enter the capacity of the knapsack: ";
    cin >> capacity;

    KnapSack ks;

    cout << "Maximum profit (Memoization): " << ks.knapSackMemoization(weight, value, capacity) << endl;
    cout << "Maximum profit (Tabulation): " << ks.knapSackTabulation(weight, value, capacity) << endl;
    cout << "Maximum profit (Space Optimized): " << ks.knapSackSpaceOptimised(weight, value, capacity) << endl;

    return 0;
}
