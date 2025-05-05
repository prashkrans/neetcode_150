/**
LC#300. NC1DP11. Longest Increasing Subsequence

*/



// Method 1: Recursion without memoization
// Running time: O(2^n)
// Auxiliary space: O(n) due to the recursion stack

class Solution {
    int rec(int i, vector<int> &nums, int prevIndex) {
        if(i==nums.size()) return 0;
        // Note: skip is just rec while take is 1 + rec when conditions are met else take is 0
        int skip = rec(i+1, nums, prevIndex); 
        int take = 0;
        if(prevIndex==-1 || nums[prevIndex] < nums[i]) take = 1 + rec(i+1, nums, i);
        return max(skip, take);        
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        return rec(0, nums, -1);
    }
};


// Method 2: Recursion with memoization (2D)
// Running time: O(n^2) 
// Auxiliary space: O(n^2) due to the dp table

class Solution {
    int rec(int i, vector<int> &nums, int prevIndex, vector<vector<int>> &dp) {
        if(i==nums.size()) return 0;
        else {
            if(dp[i][prevIndex+1] != -1) return dp[i][prevIndex+1];
            else {
                int skip = rec(i+1, nums, prevIndex, dp);
                int take = 0;
                if(prevIndex==-1 || nums[prevIndex] < nums[i]) take = 1 + rec(i+1, nums, i, dp);
                return dp[i][prevIndex+1] = max(skip, take);  
            }    
        }
    }
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1)); // n or n+1 and n+1
        return rec(0, nums, -1, dp);
    }
};


// Method 3: Bottom Up DP I (2D array)
// Running time: O(n^2) 
// Auxiliary space: O(n^2) due to the dp table



// Method 4: Bottom Up DP I (1D array)
// Running time: O(n^2) 
// Auxiliary space: O(n) due to the dp table

class Solution {
    public:
        int lengthOfLIS(vector<int>& nums) {
            int n=nums.size();
            vector<int>dp(n,1);
            int maxi=1;
            for(int i=0;i<n;i++){
                for(int j=i-1;j>=0;j--){
                    if(nums[i]>nums[j])
                    dp[i]=max(dp[i],1+dp[j]);
                }
                maxi=max(maxi,dp[i]);
            }
            return maxi;
            
        }
    };









//###################################################################

// This is an incorrect code:
// This code only works for longest non strictly increasing subsequence
// Running time: O(n)
// Auxiliary space: O(n) due to the dp array
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1, 0);
        dp[n] = 0;
        for(int i=n-1; i>=0; i--) {
            int j=i+1;
            while(j<n) {
                if(nums[j]<=nums[i]) j++;
                else break;
            }
            dp[i] = max(dp[i+1], 1 + dp[j]);
        }
        return dp[0];
    }
};
    