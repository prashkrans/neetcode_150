/**
LC#213. NC1DP4. House Robber II

Approach:
We can create two arrays from the given array. The first will include houses from the first house to the 
second-to-last house, and the second will include houses from the second house to the last house. 
We can run the recursive or bottom up approach function on both arrays independently and 
return the maximum result between the two. 
Advanced techniques such as bottom-up dynamic programming can further optimize the solution.

E.g. nums: {2, 9, 8, 3, 6} -> array 1: {2, 9, 8, 3} and array 2: {9, 8, 3, 6}


**/

// Method 1b. Bottom up approach using two variables n1 and n2 i.e. space optimized
// Running time = O(2*n) ~ O(n) due to 0 to n-2 traversal of nums array
// Auxiliary space = O(1) due to the variables n1 and n2

class Solution {
    int houseRobber(vector<int> &nums) {
        int n = nums.size();
        int n1 = nums[n-1];
        int n2 = 0;
        for(int i=n-2; i>=0; i--) {
            int temp = max(n1, nums[i] + n2);
            n2 = n1;
            n1 = temp; 
        }
        return n1;
    }
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if(n==0) return 0;
        else if(n==1) return nums[0];
        vector<int> nums1 = {nums.begin(), nums.begin()+n-1};
        vector<int> nums2 = {nums.begin()+1, nums.end()};
        return max(houseRobber(nums1), houseRobber(nums2));
    }
};
