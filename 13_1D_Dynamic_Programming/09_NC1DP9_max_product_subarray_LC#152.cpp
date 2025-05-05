/**
LC#152. NC1DP9. Maximum Product Subarray

Method 1. Naive or Brute Force Solution
Running time: O(n^2) where n = nums.size()
Auxiliary space: O(1) due to result or maxVal


Method 2. Using Kadane's Algorithm:
Approach:
We maintain both the minimum and maximum product values and update them when introducing a new element 
by considering three cases: 
a. starting a new subarray, 
b. multiplying with the previous max product, 
c. or multiplying with the previous min product. 
The max product is updated to the maximum of these three, while the min product is updated to the minimum. 
We also track a global max product for the result. This approach is known as Kadane's algorithm.

Running time: O(n) where n = nums.size()
Auxiliary space: O(3) ~ O(1) due to result, maxval, minval

Method 3: 

**/

// Method 2: Kadane's Algorithm:
// Steps:
// 1. Initialize three variables - ans, maxVal, and minVal with the first element of the array
// 2. Iterate through the array starting from the second element
// 3. For each element, calculate two products:
//    a. prod1 = maxVal * current element
//    b. prod2 = minVal * current element
// 4. Update maxVal to be the maximum of (prod1, prod2, current element)
// 5. Update minVal to be the minimum of (prod1, prod2, current element)
// 6. Update the answer 'ans' to be the maximum of previous ans and current maxVal
// 7. Return the final answer
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0];
        int maxVal = nums[0];
        int minVal = nums[0];
        for(int i=1; i<nums.size(); i++) {
            int prod1 = maxVal*nums[i];
            int prod2 = minVal*nums[i];
            maxVal = max(max(prod1, prod2), nums[i]);
            minVal = min(min(prod1, prod2), nums[i]);
            ans = max(ans, maxVal);
        }
        return ans;
    }
};


// Method 3: Two pointers
// Running time: O(n)
// Auxiliary space: O(1)

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size(), res = nums[0];
        int prefix = 1, suffix = 1; // [#IMP] both prefix and suffix initialized as 1

        for (int i = 0; i < n; i++) {
            // if nums[i] = 0 then it would make both prefix and suffix zero
            if(prefix == 0) prefix = 1; 
            if(suffix == 0) suffix = 1;
            prefix = nums[i] * prefix;
            suffix = nums[n - 1 - i] * suffix;
            res = max(res, max(prefix, suffix));
        }
        return res;
    }
};