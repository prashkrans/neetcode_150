// LC#494. NC2DP5. Target Sum 

// 1. Rec without memo
// O(2^n) since two choices add or subtract
// O(n) due to the recursion stack

class Solution {
    int rec(int i, vector<int> &nums, int target) {
        if(i==nums.size()) return (target == 0) ? 1 : 0;
        int add = rec(i+1, nums, target - nums[i]);
        int sub = rec(i+1, nums, target + nums[i]);
        return add + sub;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return rec(0, nums, target);
    }
};

// 2. Rec with memo
// Time Complexity: O(n * sum) where sum is the sum of all elements in the array
// Space Complexity: O(n * sum) for the memoization table + O(n) for the recursion stack, 
// which simplifies to O(n * sum)

class Solution {
    int rec(int i, vector<int> &nums, int target, map<pair<int, int>, int> &dp) {
        if(i==nums.size()) return dp[{i, target}] = (target == 0) ? 1 : 0;
        if(dp.find({i, target})!=dp.end()) return dp[{i, target}];
        int add = rec(i+1, nums, target - nums[i], dp);
        int sub = rec(i+1, nums, target + nums[i], dp);
        return dp[{i, target}] = add + sub;
    }
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        map<pair<int, int>, int> dp;
        return rec(0, nums, target, dp);
    }
};


// Incorrect code: Don't use a 2D DP Array here
// class Solution {
//     int rec(int i, vector<int> &nums, int target, vector<vector<int>> &dp) {
//         if(i==nums.size()) return dp[nums.size()][target] = (target == 0) ? 1 : 0;
//         int add = rec(i+1, nums, target - nums[i], dp);
//         int sub = rec(i+1, nums, target + nums[i], dp);
//         return dp[i][target] = add + sub;
//     }
// public:
//     int findTargetSumWays(vector<int>& nums, int target) {
//         vector<vector<int>> dp(nums.size()+1, vector<int>(target+1, INT_MIN));
//         return rec(0, nums, target, dp);
//     }
// };
