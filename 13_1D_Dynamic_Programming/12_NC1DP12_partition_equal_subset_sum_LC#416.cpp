/**
LC#416. NC1DP12. Partition Equal Subset Sum

Two approaches:
return true iff
a. sum of subset 1 == sum of subset 2
or 
b. if the sum or any subset is equal to half of the sum of nums (halfSum)

Note: 
- Recursion with memo needs 2D array or map<pair<int, int>, bool> where i and sum1 or halfSum
- Bottom Up DP can solve this question using 1D array using halfSum as key [Tricky]


**/

// Method 1: Recursion without memoization
// Running time: O(2^n)
// Auxiliary space: O(n) due to the recursion stack


class Solution {
    bool rec(int i, vector<int> &nums, int sum1, int sum2) {
        if(sum1 == sum2) return true;
        else if(i==nums.size()) return false;
        else return(rec(i+1, nums, sum1, sum2) || rec(i+1, nums, sum1-nums[i], sum2+nums[i])); 
        // This is compact but doesn't return true ASAP, but goes through all the branches then returns true
    }
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        return rec(0, nums, sum, 0);
    }
};

// or slightly better as it returns true as soon as it finds it.
class Solution {
    bool rec(int i, vector<int> &nums, int sum1, int sum2) {
        if(sum1 == sum2) return true;
        else if(i==nums.size()) return false;
        else {
            bool left = rec(i+1, nums, sum1, sum2);
            if(left) return true;
            bool right = rec(i+1, nums, sum1-nums[i], sum2+nums[i]);
            if(right) return true;
            return false;
        }// Running time:
// Auxiliary space:
    }
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        return rec(0, nums, sum, 0);
    }
};

// 2. Recursion with memoization: 2D array (i index, halfSum) <= {0 to n-1, 0 to halfSum} where n = nums.size()
// Running time: O(n*halfSum)
// Auxiliary space: O(n*halfSum) due to the 2D DP array

class Solution {
public:
    bool rec(int i, vector<int> &nums, int halfSum, vector<vector<int>> &dp) {
        if(halfSum == 0) return true;
        if(halfSum < 0 || i == nums.size()) return false;

        if(dp[i][halfSum] != -1) return dp[i][halfSum];
        
        bool skip = rec(i+1, nums, halfSum, dp);            // Skip current element
        bool take = rec(i+1, nums, halfSum-nums[i], dp);    // Take current element
        
        return dp[i][halfSum] = (skip || take);             // But doesn't return true ASAP
    }

    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(int i=0; i<nums.size(); i++) sum += nums[i];
        if(sum % 2 == 1) return false;
        int halfSum = sum/2;
        vector<vector<int>> dp(nums.size(), vector<int>(halfSum+1, -1)); // [index][remaining sum]
        return rec(0, nums, halfSum, dp);
    }
};


// 3. Bottom up 1D array i.e. space optimized bottom up DP
// Running time: O(n*halfSum)
// Auxiliary space: O(halfSum)

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0;
        for(auto num: nums) sum+=num;
        if(sum%2==1) return false;
        int halfSum = sum/2;
        vector<bool> dp(halfSum + 1, false);
        dp[0] = true;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = halfSum; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[halfSum];
    }
};