/* LC#45. NCAG3. Jump Game II


1. Greedy O(n) - best approach (TODO)
2. Rec without memo O(2^n)
3. Rec with memo O(n^2)

*/


// 1. Rec without memo
// O(2^n)
// O(n) due to rec stack

class Solution {
    int rec(int i, vector<int> &nums) {
        if(i >= nums.size()-1) return 0; // Note: we have to reach n-1 or above
        if(nums[i] == 0) return INT_MAX;
        int maxJump = nums[i];
        int ans = INT_MAX;
        while(maxJump>0) {      // Don't use while(maxJump--) because we need to use the value of maxJump from maxJump to 1
            int res = rec(i+maxJump, nums);
            if(res != INT_MAX) ans = min(ans, 1 + res);
            maxJump--;
        }
        return ans;
    }
public:
    int jump(vector<int>& nums) {
        return rec(0, nums);
    }
};

// 2. Rec with memo
// O(n^2)
// O(n) due to the dp array

class Solution {
    int rec(int i, vector<int> &nums, vector<int> &dp) {
        if(i >= nums.size()-1) return 0; // Note: we have to reach n-1 or above
        if(dp[i] != -1) return dp[i];
        if(nums[i] == 0) return dp[i] = INT_MAX;
        int maxJump = nums[i];
        dp[i] = INT_MAX;
        while(maxJump>0) {      // Don't use while(maxJump--) because we need to use the value of maxJump from maxJump to 1
            int res = rec(i + maxJump, nums, dp);
            if(res != INT_MAX) dp[i] = min(dp[i], 1 + res);
            maxJump--;
        }
        return dp[i];
    }
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);  // i varies from 0 to n-1 only so size is n not n+1
        return rec(0, nums, dp);
    }
};