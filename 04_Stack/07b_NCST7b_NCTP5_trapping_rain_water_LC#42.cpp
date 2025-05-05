/* LC#42. NCTP5. & NCST8. Trapping Rain Water
This is an easier variant of the problem LC#84 Largest Rectangle in Histogram

From the image, we can see that to calculate the amount of water trapped at a position, 
the greater element to the left l and the greater element to the right r of the current position 
are crucial. 
[#IMP] The formula for the trapped water at index i is given by: min(height[l], height[r]) - height[i].

I. Approach: Preprocessing Left and Right Maximum Bounds Using Stack
1. The goal is to compute how much water can be trapped between the bars after
   raining, where water trapped at each index depends on the minimum of the
   maximum heights to its left and right.
2. We first build a leftBound array using a stack. For each bar, we compute the
   maximum height seen to the left. We compare the previous bar’s height and the
   current max from stack to update the left bound.
3. Similarly, we build the rightBound array by iterating from the right. For each
   bar, we compute the max height seen to its right using the next bar and the
   top of the stack.
4. At the end of each of these loops, we debug print the left and right bounds
   to verify the preprocessing.
5. After having both bounds, we loop through each index and compute the water
   trapped at that index as max(0, min(leftBound, rightBound) - height[i]).
6. This ensures no negative water values are added, and we only accumulate where
   a container can actually hold water.
7. The final result is returned after summing the trapped water at all indices.
8. Overall complexity is linear due to double-pass preprocessing and one more
   pass for summation, making the approach efficient.
*/


// 1. Preprocessing Left and Right Maximum Bounds Using Stack
// Time Complexity: O(3n) ~ O(n), where n = number of bars in the height array | 0ms beats 100%
// Space Complexity: O(n), for storing leftBound, rightBound, and the stack

class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size();                                      // total number of bars
        vector<int> leftBound(n, 0), rightBound(n, 0);              // arrays to store left and right max heights
        stack<int> st;                                              // stack to maintain maximums
        for(int i=0; i<n; i++){                                     // build leftBound array
            if(i==0) {
                st.push(0);                                         // initialize with 0 for first index
                leftBound[i] = 0;                                   // left of first bar has no boundary
            }
            else {
                if(height[i] < height[i-1]) {
                    leftBound[i] = max(height[i-1], st.top());      // use max of previous height and top of stack
                    st.push(leftBound[i]);                          // push updated max to stack
                }
                else leftBound[i] = st.top();                       // assign top as left bound
            }
        }
        // for(auto i: leftBound) cout<<i<<" "; cout<<endl;            // debug print for left bounds

        while(!st.empty()) st.pop();                                // clear stack for reuse

        for(int i=n-1; i>=0; i--){                                   // build rightBound array
            if(i==n-1) {
                st.push(0);                                         // initialize with 0 for last index
                rightBound[i] = 0;                                  // right of last bar has no boundary
            }
            else {
                if(height[i] < height[i+1]) {
                    rightBound[i] = max(height[i+1], st.top());     // use max of next height and top of stack
                    st.push(rightBound[i]);                         // push updated max to stack
                }
                else rightBound[i] = st.top();                      // assign top as right bound
            }
        }
        // for(auto i: rightBound) cout<<i<<" "; cout<<endl;           // debug print for right bounds

        int sum = 0;                                                // variable to accumulate trapped water
        for(int i=0; i<n; i++) {
            int curr = max(0, (min(leftBound[i], rightBound[i]) - height[i])); // water trapped at i = min(L,R) - height
            sum += curr;                                            // add current water to total
        }
        return sum;                                                 // return total trapped water
    }
};
    

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
