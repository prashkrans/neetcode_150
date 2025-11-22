// LC#312. NC2DP10. Burst Balloons

//==============================//
//        POINTWISE DIFFERENCE //
//==============================//

// 1. Recursive Strategy
//--------------------------
/* First Code: Burst i LAST in [l, r] */
for (int i = l; i <= r; i++) {
    int coins = nums[l-1] * nums[i] * nums[r+1];
    int left = rec(l, i-1, nums);
    int right = rec(i+1, r, nums);
}

/* Second Code: Burst i NOW from current list */
for (int i = 1; i < nums.size() - 1; i++) {
    int coins = nums[i-1] * nums[i] * nums[i+1];
    vector<int> newNums(nums);
    newNums.erase(newNums.begin() + i);
    int rest = rec(newNums);
}

// 2. Data Modification
//--------------------------
/* First Code: nums is constant, passed as reference */
/* Second Code: nums is copied and modified each time */

// 3. Space Efficiency
//--------------------------
/* First Code: Efficient - No vector copies */
/* Second Code: Inefficient - Copies vector in each call */

// 4. Neighbor Logic
//--------------------------
/* First Code: neighbors are nums[l-1] and nums[r+1]
   (assuming i is the last to be burst) */

/* Second Code: neighbors are nums[i-1] and nums[i+1]
   (since we burst i immediately) */

// 5. Performance
//--------------------------
/* First Code: Suitable for memoization/DP (O(n^3) with memo) */
/* Second Code: Naive recursion with O(n!) complexity */

// 6. Padding of Array
//--------------------------
/* Both versions use:
   vector<int> newNums(n+2, 1);
   for (int i = 0; i < n; i++) newNums[i+1] = nums[i];
   // Adds 1 to front and back to simplify edge cases
*/

// First code (Prefer this method for memoization)
// O(n*2^n)
// O(n*2^n)
class Solution {
    int rec(int l, int r, vector<int> &nums) {
        if(l>r) return 0;
        int res = 0;
        for(int i=l; i<=r; i++) {
            int coins = nums[l-1] * nums[i] * nums[r+1]; // l-1 and r+1 not i-1 and i+1
            int left = rec(l, i-1, nums);
            int right = rec(i+1, r, nums);
            res = max(res, coins + left + right);
        }
        return res;
    }
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> newNums(n+2, 1);
        for(int i=0; i<n; i++) newNums[i+1] = nums[i];
        return rec(1, n, newNums);
    }// Approach: Top-Down Dynamic Programming with Memoization (Burst Last Strategy)

// 1. We are given a list of balloons with numbers. Bursting a balloon gives coins equal to the
//    product of its value and its adjacent (still unburst) balloons.

// 2. To simplify edge cases, we pad the input array with 1 at the beginning and the end.
//    This way, even if we burst the first or last real balloon, we still have valid neighbors.

// 3. The main idea is to choose one balloon to burst last in a given subrange [l, r].
//    By bursting it last, we know that its immediate neighbors (l-1 and r+1) are still intact,
//    so we can safely calculate the coins from that operation.

// 4. For each subrange [l, r], we try every possible position i (from l to r) to burst last.
//    For each i:
//    - We calculate coins from bursting balloon i last (nums[l-1] * nums[i] * nums[r+1])
//    - Recursively calculate the max coins from left side [l, i-1]
//    - Recursively calculate the max coins from right side [i+1, r]
//    - Take the sum of these three values and update the max result for this range

// 5. We store the results of subproblems in a 2D dp table to avoid recomputation (memoization).

// 6. The initial call starts with the full range of original balloons: [1, n]
//    (since index 0 and n+1 are the virtual 1s we added).

// 7. This approach ensures that all overlapping subproblems are solved only once,
//    and gives an efficient solution with time complexity O(n^3).

class Solution {
    int rec(vector<int> &nums) {
        if(nums.size() == 2) return 0;
        int res = 0;
        for(int i=1; i<nums.size()-1; i++) {
            int coins = nums[i-1] * nums[i] * nums[i+1];
            vector<int> newNums(nums);  // this wastes space
            newNums.erase(newNums.begin() + i);
            res = max(res, coins + rec(newNums));
        }
        return res;
    }
public:
    int maxCoins(vector<int>& nums) {
        // nums.insert(nums.begin(), 1);                // modern way of inserting 1 at 0 and n+1
        // nums.push_back(1);
        // return rec(nums);
        int n = nums.size();
        vector<int> newNums(n+2, 1);
        for(int i=0; i<n; i++) newNums[i+1] = nums[i]; // padding by 1 at 0 and n+1 positions
        return rec(newNums);
    }
};


// First code with memoization (Prefer this code):
// Approach: Top-Down Dynamic Programming with Memoization (Burst Last Strategy)

// 1. We are given a list of balloons with numbers. Bursting a balloon gives coins equal to the
//    product of its value and its adjacent (still unburst) balloons.

// 2. To simplify edge cases, we pad the input array with 1 at the beginning and the end.
//    This way, even if we burst the first or last real balloon, we still have valid neighbors.

// 3. The main idea is to choose one balloon to burst last in a given subrange [l, r].
//    By bursting it last, we know that its immediate neighbors (l-1 and r+1) are still intact,
//    so we can safely calculate the coins from that operation.

// 4. For each subrange [l, r], we try every possible position i (from l to r) to burst last.
//    For each i:
//    - We calculate coins from bursting balloon i last (nums[l-1] * nums[i] * nums[r+1])
//    - Recursively calculate the max coins from left side [l, i-1]
//    - Recursively calculate the max coins from right side [i+1, r]
//    - Take the sum of these three values and update the max result for this range

// 5. We store the results of subproblems in a 2D dp table to avoid recomputation (memoization).

// 6. The initial call starts with the full range of original balloons: [1, n]
//    (since index 0 and n+1 are the virtual 1s we added).

// 7. This approach ensures that all overlapping subproblems are solved only once,
//    and gives an efficient solution with time complexity O(n^3).

// Time complexity: O(n^3) due to rec inside the for loop
// Space complexity: O(n^2) due to the DP 2D array
class Solution {
    int rec(int l, int r, vector<int> &nums, vector<vector<int>> &dp) {
        if (l > r) return 0; // base case: no balloons to burst
        if (dp[l][r] != -1) return dp[l][r]; // return memoized result

        int res = 0;
        for (int i = l; i <= r; i++) {
            // burst balloon i last in [l, r]
            int coins = nums[l-1] * nums[i] * nums[r+1]; // neighbors: l-1 and r+1 not i-1 and r+1
            int left = rec(l, i-1, nums, dp); // max coins from left subarray
            int right = rec(i+1, r, nums, dp); // max coins from right subarray
            res = max(res, coins + left + right); // update max result
        }
        return dp[l][r] = res; // memoize and return
    }

public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> newNums(n + 2, 1); // pad with 1 at start and end
        for (int i = 0; i < n; i++) newNums[i + 1] = nums[i]; // copy original nums into middle
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1)); // dp[l][r] stores max coins in range [l, r]
        return rec(1, n, newNums, dp); // compute max coins from 1 to n
    }
};

// ✅ Time Complexity: O(n³)
// The key operation is the recursive call rec(l, r, nums, dp) which loops over all i in [l, r]. Let's break it down:

// - There are O(n²) possible subproblems since l and r can each range from 1 to n.
// - For each subproblem, we loop over i = l to r, which is O(n) in the worst case.
// - So, total time = O(n² subproblems) × O(n work per subproblem) = O(n³).
