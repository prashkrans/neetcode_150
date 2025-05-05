/**
LC#53. NC1DP9b. Maximum Subarray

Kadane's Algorithm (Dynamic Programming)
Approach:
1. Initialize two variables: 
   - 'ans' to track the maximum subarray sum (initialized to minimum possible value)
   - 'sum' to track the current running sum (initialized to 0)
2. Iterate through the array once
3. At each position, if the current running sum becomes negative, reset it to 0
   (This is because carrying a negative sum will only decrease future sums)
4. Add the current element to the running sum
5. Update the max subarray sum if the current running sum is larger
6. Return the maximum subarray sum found

Running time: O(n) - we only traverse the array once
Auxiliary space: O(1) - we only use two variables regardless of input size
This is simpler than Max Product Subarray (LC#152) because we can reset negative sums,
while with products, negative values might become positive when multiplied by another negative
**/

// Method 1. Naive Solution
// Running time: O(n^2) where n = nums.size()
// Auxiliary space: O(1) due to the variables n and ans

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int ans = INT_MIN;
        for(int i=0; i<n; i++) {
            int currSum = 0;
            for(int j=i; j<n; j++) {
                currSum += nums[j];
                ans = max(ans, currSum);
            }
        }
        return ans;
    }
};

// Method 2a. Kadane's Algo (Dynamic Programming) - easier than Max Product Subarray
// Running time: O(n)
// Auxiliary space: O(2) ~ O(1) due to sum and ans
// Refer LC#152 - Max Product Subarray

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int sum = 0;
        for(int i=0; i<nums.size(); i++) {
            if(sum<0) sum = 0;              // reset if sum becomes negative
            sum += nums[i];
            ans = max(ans, sum);
        }
        return ans;
    }
}; 

// or, same as above (2a) 

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int sum = 0;
        for(int i=0; i<nums.size(); i++) {
            sum = max(sum + nums[i], nums[i]);  // this line is equivalent to sum = max(sum, 0); sum += nums[i];
            ans = max(ans, sum);
        }
        return ans;
    }
};

// Method 3. Dynamic Programming (Bottom Up)
// Running time: O(n)
// Auxiliary space: O(n) due to the dp array
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n); // dp[i] = max subarray sum ending at index i
        dp[0] = nums[0];
        int ans = nums[0];
        for (int i = 1; i < n; i++) {
            dp[i] = max(nums[i], dp[i-1] + nums[i]);
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

// Method 2b. Kadane's Algo (Dynamic Programming) - similar to Max Product Subarray
// Running time: O(n)
// Auxiliary space: O(3) ~ O(1) due to maxVal, minVal and ans

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = nums[0];
        int maxVal = nums[0];
        int minVal = nums[0];
        for(int i=1; i<nums.size(); i++) { // Note here i varies from 0 to n-1
            // cout<<i<<" "<<nums[i]<<" "<<maxVal<<" "<<minVal<<endl;
            int sum1 = nums[i] + maxVal;
            int sum2 = nums[i] + minVal;
            maxVal = max(nums[i], max(sum1, sum2));
            minVal = min(nums[i], min(sum1, sum2));
            ans = max(ans, maxVal);
        }
        return ans;
    }
};

// or 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = INT_MIN;
        int maxVal = INT_MIN;
        int minVal = INT_MAX;
        for(int i=0; i<nums.size(); i++) {
            // cout<<i<<" "<<nums[i]<<" "<<maxVal<<" "<<minVal<<endl;
            if(i==0) {
                maxVal = nums[i];
                minVal = nums[i];
                ans = max(ans, nums[i]);
            } else {
                int sum1 = nums[i] + maxVal;
                int sum2 = nums[i] + minVal;
                maxVal = max(nums[i], max(sum1, sum2));
                minVal = min(nums[i], min(sum1, sum2));
                ans = max(ans, maxVal);
            }   
        }
        return ans;
    }
};