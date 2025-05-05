// LC#746. NC1DP2. Min Cost Climbing Stairs
// Recurrence relation:
// given f(n) = 0 and f(n-1) = cost[n-1]; // Thus dp array has size of n+1 not n as f(n) = 0
// a.) f(n-(i+2)) = cost[n-(i+2)] + min(f(n-(i+1)), f(n-i)) where i varies from 0 to n-2
// or
// b.) f(i) = cost[i] + min(f(i+1), f(i+2)) where i varies from n-2 to 0
// Use top down approach diagram then use it to figure out the bottom up formula a.)
// Take cost = {1, 2, 3, 4} as an example

// Method 1a. Bottom up approach with DP array
// Running time = O(n) due to 0 to n-2 traversal of cost array
// Auxiliary space = O(n) due to the dp array

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp(n+1, -1);
        dp[n] = 0;
        dp[n-1] = cost[n-1];
        // Both are correct bottom up approaches
        // for(int i=0; i<=n-2; i++) { // Here i varies from 0 to n-2
        //     dp[n-(i+2)] = cost[n-(i+2)] + min(dp[n-(i+1)], dp[n-i]);
        // }
        for(int i=n-2; i>=0; i--) {     // Here i varies from n-2 to 0
            dp[i] = cost[i] + min(dp[i+1], dp[i+2]);
        }
        return min(dp[0], dp[1]);
    }
};

// Method 1b. Bottom up approach using two variables n1 and n2 i.e. space optimized
// Running time = O(n) due to 0 to n-2 traversal of cost array
// Auxiliary space = O(1) due to the variables n1 and n2

class Solution {
    public:
        int minCostClimbingStairs(vector<int>& cost) {
            int n = cost.size();
            int n1 = cost[n-1], n2 = 0;
            for(int i=n-2; i>=0; i--) {     // Here i varies from n-2 to 0
                int temp = cost[i] + min(n1, n2);
                n2 = n1;
                n1 = temp;
            }
            return min(n1, n2);
        }
    };
    