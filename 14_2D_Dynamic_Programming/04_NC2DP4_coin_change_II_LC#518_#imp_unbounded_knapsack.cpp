// LC#518. Coin Change II
// Example of Unbounded Knapsack (not 0/1 Knapsack)

// 1. Rec without memo
// Time complexity: O(2^max(n,a/m)) or O(2^N) where N = max(n, amount/minimumCoinValue)
// Space complexity: O(max(n,a/m))
// Where n is the number of coins, a is the given amount and m is the minimum value among all the coins.

class Solution {
    int rec(int i, vector<int> &coins, int amount) {
        if(amount < 0) return 0;
        if(amount == 0) return 1;
        if(i==coins.size()) return 0;
        return rec(i+1, coins, amount) + rec(i, coins, amount-coins[i]);
    }
public:
    int change(int amount, vector<int>& coins) {
        sort(coins.begin(), coins.end());
        return rec(0, coins, amount);
    }
};

// 2. Rec with memo
// O(n*amount) where n = coins.size()
// O(n*amount) due to the 2D DP array

class Solution {
    int rec(int i, vector<int> &coins, int amount, vector<vector<int>> &dp) {
        if(amount < 0) return 0;
        if(amount == 0) return dp[i][amount] = 1;
        if(i==coins.size()) return dp[i][amount] = 0;
        if(dp[i][amount] != -1) return dp[i][amount];
        return dp[i][amount] = rec(i+1, coins, amount, dp) + rec(i, coins, amount-coins[i], dp);
    }
public:
    int change(int amount, vector<int>& coins) {
        sort(coins.begin(), coins.end());
        vector<vector<int>> dp(coins.size()+1, vector<int>(amount+1, -1));
        return rec(0, coins, amount, dp);
    }
};

// 3. Bottom up DP
// O(n*amount) where n = coins.size()
// O(n*amount) due to the 2D DP array

class Solution {
    public:
        int change(int amount, vector<int>& coins) {
            int n = coins.size();
            sort(coins.begin(), coins.end());
            
            // using uint instead of int as we are only adding values here, and signed int gets overflowed
            vector<vector<uint>> dp(n+1, vector<uint>(amount+1, 0)); 
            // Base case 1: if coins array is empty and amount > 0 we have 0 ways to make the amount
            for(int j=0; j<=amount; j++) dp[n][j] = 0;  
            // Base case 2: if amount == 0 we have one way to make the amount not pick any coins even if coins array is empty
            for(int i=0; i<=n; i++) dp[i][0] = 1;       // overrides dp[n][0] from 0 to 1
            
            // Now we build from bottom(i==n-1), left(j==0) to up(i==0) and right(j==amount) hence return dp[0][amount];
            // here for(int j=amount; j>=0; j--) {      // incorrect as we build from left to right
            for(int i=n-1; i>=0; i--) {                 // correct as we build from down to up
                for(int j=0; j<=amount; j++) {
                    dp[i][j] = dp[i+1][j];
                    if(j>=coins[i]) dp[i][j] += dp[i][j-coins[i]];
                }
            }
            return dp[0][amount];
        }
    };
    

// Worse recursion than above as its not unbounded knapsack 
// O(n^(amount/minVal)) where n = coins.size()
// 

class Solution {
    public:
        void rec(int n, vector<int> &coins, set<vector<int>> &st, vector<int> &path) {
            if(n<=0) {
                if(n==0) {
                    sort(path.begin(), path.end());
                    // for(auto i: path) cout<<i<<" "; cout<<endl;
                    st.insert(path);
                }
                return;
            }
            else {
                for(int i=0; i<coins.size(); i++) {
                    int currAmount = n - coins[i];
                    if(currAmount>=0) {
                        path.push_back(coins[i]);
                        rec(currAmount, coins, st, path);
                        path.pop_back(); // Backtrack
                    }
                }
            }
        }
        int change(int n, vector<int>& coins) {
            set<vector<int>> st; // Don't use unordered_set<vector<int>> st;
            vector<int> path; 
            rec(n, coins, st, path);
            return st.size();
        }
    };