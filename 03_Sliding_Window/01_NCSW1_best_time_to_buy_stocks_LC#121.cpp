/* LC#121. NCSW1 Best Time to Buy and Sell Stock I

Total two ways:
1. Sliding window
2. MinVal till index i (with or without a stack)

1. Approach: Sliding Window with Two Pointers

1. We use a sliding window approach with two pointers to find the maximum
profit we can make by buying and selling stock once.

2. The left pointer (l) represents the buying day and the right pointer (r)
represents the selling day of the stock.

3. We initialize l=0 (first day) and r=1 (second day), and also initialize maxP=0
to track the maximum profit found so far.

4. We iterate through the prices array with the right pointer until we reach
the end of the array.

5. For each position, we check if buying at left and selling at right
would give us a profit (prices[l] < prices[r]).

6. If we can make a profit, we calculate the profit amount and update
the maximum profit if this profit is greater.

7. If we cannot make a profit (prices[l] >= prices[r]), we move the left [#IMP]
pointer to the current right position since we found a new lower price.

8. We always move the right pointer forward in each iteration to check
the next possible selling day.

9. This approach works because we only need to buy once and sell once,
so our goal is to find the lowest buying price and highest selling price.

10. The algorithm ensures we consider all possible buying and selling combinations while maintaining
linear time complexity by not repeating unnecessary comparisons.
*/

// 1. Two Pointers / Sliding Window Approach
// Time Complexity: O(n) - where n is the length of the prices array
// Space Complexity: O(1) - using only constant extra space

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int l = 0, r = 1;                                   // Initialize left pointer at 0 and right pointer at 1
        int maxP = 0;                                       // Initialize maximum profit to 0
        while (r < prices.size()) {                         // Iterate until right pointer reaches the end
            if (prices[l] < prices[r]) {                    // If we can make profit by buying at left and selling at right
                int profit = prices[r] - prices[l];         // Calculate current profit
                maxP = max(maxP, profit);                   // Update maximum profit if current profit is greater
            } else {                                        // If no profit can be made
                l = r;                                      // Move left pointer to right pointer (new potential buying point)
            }
            r++;                                            // Move right pointer forward to check next price
        }
        return maxP;                                        // Return the maximum profit found
    }
};

// or, same as above but compact code
// 1b. Two Pointers / Sliding Window Approach (My custom code)
// Time Complexity: O(n)
// - The algorithm iterates through the prices array once using two pointers.
// - n = length of the prices array.

// Space Complexity: O(1)
// - The algorithm uses only constant extra space for variables.

class Solution {
    public:
        int maxProfit(vector<int>& prices) {
            int maxProfit = 0;                                // Initialize the maximum profit
            int l = 0, r = 0;                                 // Initialize two pointers: l (buying day), r (selling day)
            while(r < prices.size()) {                        // Iterate until the right pointer reaches the end
                maxProfit = max(maxProfit, prices[r] - prices[l]); // Calculate profit and update maxProfit if greater
                if(prices[r] < prices[l]) l = r;              // Move the left pointer to r if a lower price is found
                r++;                                          // Move the right pointer to the next day
            }
            return maxProfit;                                 // Return the maximum profit found
        }
    };
    
    


/*
# 2. Stack-Based Minimum Tracking Approach

1. The problem requires finding the maximum profit by buying at a lower price and selling at a higher price later.
2. Key insight: We only need to track the minimum price seen so far to calculate the maximum profit.
3. Although a single variable could be used to track the minimum price, this solution uses a stack approach:
   - The stack stores potential buying prices
   - The top of the stack is always the minimum price seen so far
4. Logical flow:
   - Initialize maxProfit to 0 (if no profit is possible, return 0)
   - Iterate through each price in the array
   - If stack is empty, push the current price
   - If current price <= stack top, push it (representing a new minimum)
   - If current price > stack top, calculate profit (current price - stack top) and update maxProfit if higher
5. Mathematical concept: The profit is calculated as the difference between the current price and the minimum price seen 
before the current day (current_price - min_price_so_far).
6. Optimization potential: While this solution works correctly, the stack is actually only using its top element, so it 
could be simplified to use a single variable to track the minimum price instead of a stack.
*/


// 2. Stack-Based Minimum Tracking Approach (My custom code)
// Time Complexity: O(n) where n is the length of the prices array
// Space Complexity: O(n) in worst case for the stack

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;                   // Variable to track maximum profit
        int n = prices.size();               // Size of the prices array
        stack<int> st;                       // Stack to keep track of potential buying prices
        for(int i=0; i<n; i++) {             // Iterate through each price
            if(st.empty()) st.push(prices[i]); // If stack is empty, push current price
            else {
                if(prices[i] <= st.top()) st.push(prices[i]); // If current price is lower, push it (better buying opportunity)
                else maxProfit = max(maxProfit, prices[i] - st.top()); // Calculate profit with current price as selling price
            }
        }
        return maxProfit;                    // Return the maximum profit possible
    }
};

// or, same as above but keeping a minVal instead of using a stack (Prefer this method)

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;
        int minVal = INT_MAX;
        for(int i=0; i<prices.size(); i++) {
            minVal = min(minVal, prices[i]);
            maxProfit =  max(maxProfit, prices[i] - minVal);
        }
        return maxProfit;
    }
};