/* LC#42. NCTP5. & NCST8. Trapping Rain Water
This is an easier variant of the problem LC#84 Largest Area in Histogram
[#IMP] This is slightly different from LC#84 as we add water at each index instead of a range i.e. right - left

From the image, we can see that to calculate the amount of water trapped at a position, 
the greater element to the left l and the greater element to the right r of the current position 
are crucial. 
[#IMP] The formula for the trapped water at index i is given by: max(0, min(height[l], height[r]) - height[i])

### Approach 1: Precomputing Left and Right Maximum Bounds using a max height variable
1. The problem is to calculate how much water can be trapped after rain given an array where each element represents the height of a bar.
2. Water above a bar is limited by the shorter of the tallest bars to its left and right.
3. Precompute the maximum height to the left of each bar (`leftMost`) and the maximum height to the right of each bar (`rightMost`).
4. For each bar, calculate the trapped water as `min(leftMost[i], rightMost[i]) - height[i]`.
5. Accumulate the trapped water for all bars to get the total trapped water.
6. This approach uses three passes:
   a. First pass: Compute the `leftMost` array.
   b. Second pass: Compute the `rightMost` array.
   c. Third pass: Calculate the trapped water for each bar.
7. The solution has O(n) time complexity and O(n) space complexity due to the use of the `leftMost` and `rightMost` arrays.
*/

// 1. Preprocessing Left and Right Maximum Bounds using a max height variable
// Time Complexity: O(3n) ~ O(n), where n = number of bars in the height array | 0ms beats 100%
// Space Complexity: O(n), for storing leftBound, rightBound

// Time Complexity: O(n)
// - The first loop calculates the leftMost array in O(n).
// - The second loop calculates the rightMost array in O(n).
// - The third loop calculates the trapped water for each bar in O(n).
// - Overall complexity is O(3n) ≈ O(n), where n is the number of bars in the height array.

// Space Complexity: O(n)
// - Space is used for the `leftMost` and `rightMost` arrays, each of size n.

class Solution {
public:
    int trap(vector<int>& height) {
        int areaSum = 0;                                // Initialize the total trapped water
        int n = height.size();                          // Number of bars in the height array
        vector<int> leftMost(n, 0);                     // Array to store the maximum height to the left of each bar
        vector<int> rightMost(n, 0);                    // Array to store the maximum height to the right of each bar
        int maxHeight = 0;                              // Variable to track the maximum height from the left
        for(int i=0; i<n; i++) {                        // Calculate leftMost array
            leftMost[i] = maxHeight;                    // Store the maximum height to the left of the current bar
            maxHeight = max(maxHeight, height[i]);      // Update the maximum height
        }
        maxHeight = 0;                                  // Reset maxHeight to calculate rightMost array
        for(int i=n-1; i>=0; i--) {                     // Calculate rightMost array
            rightMost[i] = maxHeight;                   // Store the maximum height to the right of the current bar
            maxHeight = max(maxHeight, height[i]);      // Update the maximum height
        }
        for(int i=0; i<n; i++) {                        // Calculate the trapped water for each bar
            int currTrap = min(leftMost[i], rightMost[i]) - height[i]; // Water trapped above the current bar
            areaSum += max(0, currTrap);                // Add the trapped water to the total (ensure non-negative)
        }
        return areaSum;                                 // Return the total trapped water
    }
};
    
/*
index:      [0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11]
height:     [0,  1,  0,  2,  1,  0,  1,  3,  2,  1,  2,  1]
leftMost:   [0,  0,  1,  1,  2,  2,  2,  2,  3,  3,  3,  3]
rightMost:  [3,  3,  3,  3,  3,  3,  3,  2,  2,  2,  1,  0]
min(l,r):   [0,  0,  1,  1,  2,  2,  2,  2,  2,  2,  1,  0]
water:      [0,  0,  1,  0,  1,  2,  1,  0,  0,  1,  0,  0]
*/

// 2. Two pointers method with constant space
// Time Complexity: O(n), where n = number of bars in the height array | 0ms beats 100%
// Space Complexity: O(1), uses only constant extra space for pointers and variables

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) {                           // if no bars, no water can be trapped
            return 0;                                   // return 0
        }

        int l = 0, r = height.size() - 1;               // two pointers at both ends
        int leftMax = height[l], rightMax = height[r];  // track max height from both ends
        int ans = 0;                                    // to accumulate total trapped water
        while (l < r) {                                 // loop until pointers meet
            if (leftMax < rightMax) {                   // decide direction based on smaller max
                l++;                                    // move left pointer inward
                leftMax = max(leftMax, height[l]);      // update left max height
                ans += leftMax - height[l];             // add trapped water at current index
            } else {
                r--;                                    // move right pointer inward
                rightMax = max(rightMax, height[r]);    // update right max height
                ans += rightMax - height[r];            // add trapped water at current index
            }
        }
        return ans;                                     // return total trapped water
    }
};

/* Approach: Two Pointer Optimization with Constant Space
1. The problem is to calculate how much water can be trapped after rain given an array where each element represents the height of a bar.
2. Water above a bar is limited by the shorter of the tallest bars to its left and right. Instead of precomputing bounds, we optimize using two pointers.
3. Initialize two pointers: one at the beginning (l) and one at the end (r) of the height array. Also initialize leftMax and rightMax to the heights at those positions.
4. At each step, compare leftMax and rightMax. Move the pointer pointing to the side with the smaller maximum height inward, as this side limits water.
5. If moving left pointer, update leftMax and calculate water at the new left position as leftMax - height[l]. Accumulate to total.
6. Similarly, if moving right pointer, update rightMax and calculate water at the new right position as rightMax - height[r].
7. Continue until the two pointers meet. This ensures all bars are processed in linear time without needing extra space for bounds.
8. This is the most space-efficient approach while maintaining O(n) time,  making it optimal for the given problem.
*/
