/* LC#5. NCAG2. Jump Game I
1. Greedy O(n) - best approach
2. Rec without memo O(2^n)
3. Rec with memo O(n^2)


### Approach: Greedy Reachability Check
1. Initialize a variable to track the maximum reachable index starting from the
beginning of the array.
2. Iterate through each index of the array using a for-loop. At every step,
compare the current index with the maximum index reachable so far.
3. If the current index is greater than the maximum reachable index, it means
we are stuck and cannot proceed further, so return false.
4. Otherwise, update the maximum reachable index by taking the maximum of the
existing reach and the sum of the current index and the jump length at that index.
5. If we successfully complete the loop without returning false, it means we can
reach or surpass the last index, so return true.
*/


// 1. Greedy Reachability Check
// Time Complexity: O(n), where n is the length of nums, as we iterate through the array once. | 0ms beats 100%
// Space Complexity: O(1), constant space used.

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;                                       // Tracks the farthest index we can reach so far
        for(int i = 0 ; i < nums.size(); i++) {                 // Traverse each index from 0 to n-1
            if(maxReach < i) return false;                      // If current index is beyond max reachable, return false
            maxReach = max(maxReach, i + nums[i]);              // Update max reachable index from current position
        }
        return true;                                            // If loop completes, we can reach the end
    }
};



// 2. Rec without memo
// Time Complexity: O(n^n)
// - In worst case, each index tries all possible jumps (n) recursively
// - This leads to exponential branching where each recursive call can make n more calls
// - The recursion forms a tree with potentially n^n nodes in worst case
// - Example: [3,2,1,0,4] would generate a large number of recursive calls

// Space Complexity: O(n)
// - The maximum depth of the recursion stack is n in worst case
// - This happens when we make sequential jumps through all array elements
// - No additional data structures are used beyond the call stack

class Solution {
    bool rec(int i, vector<int> &nums) {
        if(i >= nums.size()-1) return true;                         // Base case: reached or surpassed the last index
        if(nums[i] == 0) return false;                              // No forward move possible from a zero jump

        int maxJump = nums[i];                                      // Maximum possible jump from the current index
        while(maxJump > 0) {                                        // Try jumps from maxJump down to 1
            if(rec(i + maxJump, nums)) return true;                 // If recursive call from new index returns true, path exists
            maxJump--;                                              // Decrease jump length and retry
        }

        return false;                                               // No valid path found, return false
    }

public:
    bool canJump(vector<int>& nums) {
        return rec(0, nums);                                        // Start checking from index 0
    }
};

// 3. Rec with memo
// Time Complexity: O(n²)
// - With memoization, each index is processed at most once
// - For each index i, we try at most n different jumps (from 1 to nums[i])
// - This gives us O(n) work per index, with n indices total
// - Overall complexity is O(n²) instead of exponential

// Space Complexity: O(n)
// - We use a dp array of size n to store results for each index
// - The recursion stack also takes O(n) space in worst case
// - Total space complexity remains O(n)

class Solution {
    bool rec(int i, vector<int> &nums, vector<int> &dp) {
        if(i >= nums.size()-1) return true;                         // Base case: if at or beyond last index (n-1), return true
        if(dp[i] != -1) return dp[i];                               // Return memoized result if already computed
        if(nums[i] == 0) return dp[i] = false;                      // Cannot move forward if jump is 0

        int maxJump = nums[i];                                      // Get max jump length from current index
        while(maxJump > 0) {                                        // Try every jump from maxJump down to 1
            dp[i] = rec(i + maxJump, nums, dp);                     // Recursive call from next index after jump
            if(dp[i]) return dp[i];                                 // If a path is found from there, return true
            maxJump--;                                              // Otherwise, reduce jump length and try again
        }

        return dp[i] = false;                                       // No valid path found, mark false
    }

public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();                                        // DP has size of n not n+1 since i varies from 0 to n-1 only
        vector<int> dp(n, -1);                                      // Initialize DP array with -1 (uncomputed)
        dp[n-1] = true;                                             // Last index is always reachable from itself
        return rec(0, nums, dp);                                    // Start recursion from index 0
    }
};

