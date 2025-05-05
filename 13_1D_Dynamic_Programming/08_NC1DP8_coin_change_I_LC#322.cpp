/**
LC#322. NC1DP9. Coin Change I 
4 methods:
1. Recursion (Top Down)
2. Recursion + Memoization (Top Down Memo)
3. Bottom Up Approach
4. BFS where src = amount and dest = 0. BFS always gives the shortes path in unweighted graphs



**/

// Method 3. Bottom up DP approach
// Running time: O(amount+1) ~ O(n) where n = amount
// Auxiliary space: O(n+1) ~ O(n) due to the dp array
// Approach: Take amount = 6 and coins [1, 2, 5]. Draw the recursion tree. 

// Recurrence relation based on observation: 
// Base cases: f(0) = 0, f(n<0) = INT_MAX and f(c) = 1 + f(0) = 1 for all c in coins
// f(n) = 1 + min(f(n-c1), f(n-c2), ... f(n-cm-1)) where n = amount and m = coins.size()
// Build f from 1 to amount or n i.e n+1 space required

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // if(amount == 0) return 0; redundant case since dp[0] = 0
        vector<int> dp(amount+1, INT_MAX);
        dp[0] = 0;
        for(int i=1; i<=amount; i++) {
            int minVal = INT_MAX;
            for(int j=0; j<coins.size(); j++) {
                int currRem = i-coins[j];
                if(currRem>=0) {
                    minVal = min(minVal, dp[currRem]);
                }
            }
            if(minVal == INT_MAX) dp[i] = INT_MAX;
            else dp[i] = 1 + minVal;
        }
        return (dp[amount] == INT_MAX) ? -1 : dp[amount];
    }
};

// Method 3b. Compact Version of Bottom Up Approach
class Solution {
public:
    int coinChange(vector<int>& coins, int n) {
        vector<int> dp(n+1, INT_MAX);
        dp[0] = 0;
        for(int i=1; i<=n; i++) {
            for(int j=0; j<coins.size(); j++)
                if(i-coins[j]>=0 && dp[i-coins[j]]!=INT_MAX) 
                    dp[i] = min(dp[i], 1 + dp[i-coins[j]]);
        }
        return (dp[n] == INT_MAX) ? -1 : dp[n];
    }
};
    


// Method 1. Recursion without memoization
class Solution {
public:
    int rec(int n, vector<int> &coins) {
        if(n<0) return INT_MAX;
        else if(n==0) return 0;
        else {
            int minVal = INT_MAX;
            for(int i=0; i<coins.size(); i++) {
                minVal = min(minVal, rec(n-coins[i], coins));
            }
            return (minVal == INT_MAX) ? INT_MAX : 1 + minVal;
        }
    }

    int coinChange(vector<int>& coins, int amount) {
        if(amount==0) return amount;
        int ans = rec(amount, coins);
        return (ans==INT_MAX) ? -1 : ans;
    }
};
        
// Note: This is not a bottom up memoization unlike method 1 even when we know that dp[0] = 0 beforehand
// Method 2. Recursion with memoization (Top Down + Memo)
// Running time: O(n) where n = amount
// Auxiliary space: O(n+1) ~ O(n) due to the dp array

class Solution {
public:
    int rec(int n, vector<int> &coins, vector<int> &dp) {
        if(n<0) return INT_MAX;
        else if(n==0) return dp[0];
        else {
            if(dp[n] != -1) return dp[n];
            else {
                for(int i=0; i<coins.size(); i++) {
                    if(dp[n] == -1) dp[n] = INT_MAX;
                    int res = rec(n-coins[i], coins, dp);
                    if(res != INT_MAX)
                        dp[n] = min(dp[n], 1 + res);
                }
                return dp[n];
            } 
        }
    }

    int coinChange(vector<int>& coins, int n) {
        // Don't use INT_MAX here, -1 tells that dp[i] has not been visited earlier
        // While INT_MAX tells that dp[i] has been visited earlier but no solution exists
        vector<int> dp(n+1, -1); 
        dp[0] = 0;
        int ans = rec(n, coins, dp);
        return (ans==INT_MAX) ? -1 : ans;
    }
};

// Method 4: BFS where src = amount = n and dest = 0. BFS always gives the shortest path in unweighted graphs.
// for all n = (i-coins[j]) > 0 are the remaining nodes
// Running time: O(n) where n = amount
// Auxiliary space: O(n+1) ~ O(n) due to the visited array

class Solution {
    public:
        int coinChange(vector<int>& coins, int n) {
            if(n == 0) return 0; // This base case is important here since src = dest = 0
            queue<int> q;
            vector<int> visited(n+1, 0);
            q.push(n);
            visited[n] = 1;
            int dist = 1;
            while(!q.empty()) {
                int qSize = q.size();
                for(int i=0; i<qSize; i++) {
                    int u = q.front();
                    q.pop();
                    for(int j=0; j<coins.size(); j++) {
                        int v = u - coins[j];
                        if(v>0 && !visited[v]) {
                            q.push(v);
                            visited[v] = 1;
                        }
                        else if(v==0) return dist;
                    }
                }
                dist++;
            }
            return -1; // if code reaches here, then no path exists from src = n to dest = 0
        }
    };
    