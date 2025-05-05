// LC#309. NC2DP3. Best Time to Buy and Sell Stock with Cooldown


// Rec without memo
// O(2^n)
// O(n) due to the recursion stack

class Solution {
    int rec(int i, vector<int> &prices, int prevBuyPrice) {
        if(i>=prices.size()) return 0; // since i+2 used
        if(prevBuyPrice==-1) {  // condition for either not buy or buy
            return max(rec(i+1, prices, -1), rec(i+1, prices, prices[i]));
        }
        else {  // condition for either not sell or sell
            return max(rec(i+1, prices, prevBuyPrice), (prices[i] - prevBuyPrice) + rec(i+2, prices, -1));
        }
    }
public:
    int maxProfit(vector<int>& prices) {
        return rec(0, prices, -1);
    }
};

// Prefer this
// Same as above but more readable:
// O(2^n)
// O(n)

class Solution {
    int rec(int i, bool buying, vector<int>& prices) {
        if (i >= prices.size()) return 0;                  // Base case: beyond array bounds
        int cooldown = rec(i + 1, buying, prices);         // Option 1: Skip this day (cooldown) - common to both buy and sell
        if (buying) {                                      // When in buying state:
            int buy = rec(i + 1, false, prices) - prices[i]; // Option 2a: Buy stock => money spent => - prices[i]
            return max(buy, cooldown);                     // Choose max profit between buy or skip
        } else {                                           // When in selling state: => money earnt => + prices[i]
            int sell = rec(i + 2, true, prices) + prices[i]; // Option 2b: Sell and enforce cooldown
            return max(sell, cooldown);                    // Choose max profit between sell or skip
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        return rec(0, true, prices);                       // Start DFS at index 0 in buying state
    }
};

// [#IMP] - Prefer this method
// Recursion with memo using 2D DP table of size n * 2. Factor of 2 comes from the boolean variable buying
// If buying, store in dp[i][0] else if selling, store in dp[i][1]
// O(n*2) ~ O(n) | 0ms beats 100%
// O(n*2) ~ O(n)

class Solution {
    int rec(int i, bool buying, vector<int> &prices, vector<vector<int>> &dp) {
        if (i >= prices.size()) return 0;                      // Base case: reached end of timeline
        if(dp[i][buying]!=INT_MIN) return dp[i][buying];       // Return cached result if available
        int cooldown = rec(i + 1, buying, prices, dp);         // Option 1: Skip this day (cooldown)
        if (buying) {                                          // When in buying state:
            int buy = rec(i + 1, false, prices, dp) - prices[i]; // Option 2a: Buy stock today
            dp[i][buying] = max(buy, cooldown);                // Choose max profit between buying or skipping
        } else {                                               // When in selling state:
            int sell = rec(i + 2, true, prices, dp) + prices[i]; // Option 2b: Sell and enforce cooldown
            dp[i][buying] = max(sell, cooldown);               // Choose max profit between selling or skipping
        }
        return dp[i][buying];                                  // Return max profit for current state
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();                                 // Get number of days
        vector<vector<int>> dp(n, vector<int>(2, INT_MIN));    // Initialize DP table with sentinel values
        return rec(0, true, prices, dp);                       // Start recursion at day 0 in buying state
    }
};

// Ignore here onwards

// Recursion with memo using hashmap
// O(n^2) where n = prices.size() 
// O(n)
class Solution {
    int rec(int i, vector<int> &prices, int prevBuyPrice, map<pair<int, int>, int> &dp) {
        if(i>=prices.size()) return 0;                          // Base case: beyond array bounds
        if(dp.count({i, prevBuyPrice})) return dp[{i, prevBuyPrice}];  // Return memoized result if available
        if(prevBuyPrice==-1) {                                  // No stock currently held
            dp[{i, prevBuyPrice}] = max(rec(i+1, prices, -1, dp),      // Skip buying
                                     rec(i+1, prices, prices[i], dp));  // Buy stock at current price
        }
        else {                                                  // Already holding stock
            dp[{i, prevBuyPrice}] = max(rec(i+1, prices, prevBuyPrice, dp),            // Keep holding
                                     (prices[i] - prevBuyPrice) + rec(i+2, prices, -1, dp));  // Sell and cooldown
        }
        return dp[{i, prevBuyPrice}];                           // Return optimal profit
    }
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        map<pair<int, int>, int> dp;                            // Memoization using map
        return rec(0, prices, -1, dp);                          // Start recursion at index 0
    }
};

// Recusion with memo using hashmap
// O(n*k) where n = prices.size() and k = maxBuyPrice
// O(n)
// Same algorithm as above but uses 2D vector instead of map for memoization
// Note: 
// Init of DP 2D vector is n * k+2. As each row varies from 0 to k+1 where 0 stores -1, 1 -> 0 and so on
// This wastes a lot of space
class Solution {
    int rec(int i, vector<int> &prices, int prevBuyPrice, vector<vector<int>> &dp) {
        if(i>=prices.size()) return 0;                          // Base case: beyond array bounds
        if(dp[i][prevBuyPrice+1] != INT_MIN) return dp[i][prevBuyPrice+1];  // Use cached result if available
        if(prevBuyPrice==-1) {                                  // No stock currently held
            dp[i][prevBuyPrice+1] = max(rec(i+1, prices, -1, dp),           // Skip buying
                                     rec(i+1, prices, prices[i], dp));       // Buy stock
        }
        else {                                                  // Already holding stock
            dp[i][prevBuyPrice+1] = max(rec(i+1, prices, prevBuyPrice, dp),            // Keep holding
                                     (prices[i] - prevBuyPrice) + rec(i+2, prices, -1, dp));  // Sell with cooldown
        }
        return dp[i][prevBuyPrice+1];                           // Return optimal profit
    }
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int maxBuyPrice = INT_MIN;
        for(int i=0; i<n; i++) maxBuyPrice = max(maxBuyPrice, prices[i]);  // Find max stock price
        vector<vector<int>> dp(n, vector<int>(maxBuyPrice+2, INT_MIN));     // Initialize DP table
        return rec(0, prices, -1, dp);                                      // Start recursion
    }
};