/* LC#11. NCTP3. Container With Most Water

Approach: Two Pointer Technique for Container With Most Water
We can use the two pointer algorithm. One pointer is at the start and the other at the end. At each step, 
we calculate the amount of water using the formula (j - i) * min(heights[i], heights[j]). Then, we move 
the pointer that has the smaller height value.
In the formula, the amount of water depends only on the minimum height. Therefore, it is appropriate to 
replace the smaller height value.

1. Naive Solution: A brute force solution would be to try all pairs of bars in the array, compute the water 
for each pair, and return the maximum water among all pairs. This would be an O(n^2) solution. 
*/

// 2a. Two Pointer Technique for Container With Most Water
// Time Complexity: O(n), where n = number of elements in the heights vector
// Space Complexity: O(1), as no extra space is used apart from a few variables

class Solution {
public:
    int maxArea(vector<int>& heights) {
        int n = heights.size();                                 // total number of height lines
        int l = 0, r = n - 1;                                   // two pointers at both ends of the array
        int maxArea = 0;                                        // variable to keep track of maximum area
        while(l < r) {                                          // iterate until pointers cross each other
            int area = (r - l) * min(heights[l], heights[r]);   // calculate area between lines
            maxArea = max(maxArea, area);                       // update max area if current is greater
            if(heights[l] <= heights[r]) l++;                   // move left pointer if left height is smaller
            else r--;                                           // move right pointer otherwise
        }
        return maxArea;                                         // return the maximum area found
    }
};

// or, same as above but more expalanatory
// 2b. Two Pointer Technique for Container With Most Water
// Time Complexity: O(n), where n = number of elements in the heights vector | 0ms beats 100%
// Space Complexity: O(1), as no extra space is used apart from a few variables

class Solution {
public:
    int maxArea(vector<int>& heights) {
        int maxArea = 0;                                        // Initialize the maximum area
        int left = 0, right = heights.size() - 1;               // Two pointers at both ends of the array
        while(left < right) {                                   // Iterate until the pointers meet
            int width = right - left;  // not l - r + 1         // Calculate the width between the two pointers
            int height = min(heights[left], heights[right]);    // Determine the height (minimum of the two lines)
            int area = width * height;                          // Calculate the area
            maxArea = max(maxArea, area);                       // Update the maximum area if the current area is larger
            if(heights[left] < heights[right]) left++;          // Move the left pointer if the left height is smaller
            else right--;                                       // Otherwise, move the right pointer
        }
        return maxArea;                                         // Return the maximum area found
    }
};

    
// ###############################
// TODO: Fix the code below, if its possible

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxArea = 0;
        int n = height.size();
        int leftBoundIndex = 0, rightBoundIndex = n-1;
        vector<int> leftMost(n, 0);
        vector<int> rightMost(n, n-1);
        for(int i=0; i<n; i++) {
            if(i==0) leftBoundIndex = 0;
            else if(height[i] > height[leftBoundIndex]) {
                leftBoundIndex = i;
            }
            leftMost[i] = leftBoundIndex;
        }
        for(int i=n-1; i>=0; i--) {
            if(i==n-1) rightBoundIndex = n-1;
            else if(height[i] > height[rightBoundIndex]) {
                rightBoundIndex = i;
            }
            rightMost[i] = rightBoundIndex;
        } 
        for(auto i: leftMost) cout<<i<<" "; cout<<endl;
        for(auto i: rightMost) cout<<i<<" "; cout<<endl;
        cout<<leftBoundIndex<<"->"<<rightBoundIndex<<endl;
        int maxWidth = rightBoundIndex - leftBoundIndex;
        int maxHeight = min(height[leftBoundIndex], height[rightBoundIndex]);
        return maxWidth * maxHeight;
    }
};