/* LC#84. Largest Rectangle in Histogram
Note: LC#85. Maximal Rectangle uses this approach directly as a subroutine.

Approach:
1. For each bar, determine how far to the left it can extend without encountering a smaller bar:
   - Use a stack to keep track of indices with increasing height.
   - For every bar, pop elements from stack while they are greater than or equal to current height.
   - Left boundary is 0 if nothing smaller exists to the left, otherwise it's `top of stack + 1`.

2. Repeat the same in reverse to determine the right extent of each bar:
   - Again use a stack to keep indices of increasing heights from right to left.
   - Right boundary is `n - 1` if no smaller bar exists on the right, else it's `top of stack - 1`.

3. For each bar:
   - Compute width as `rightMost[i] - leftMost[i] + 1`.
   - Area = `width * height[i]`.
   - Keep track of the maximum area found.

4. Key Concepts:
   - Stack-based approach for nearest smaller element to left/right in O(n) time.
   - Area of largest rectangle in histogram = max of all individual bar-based rectangles using calculated bounds.

*/

// 1. Using a stack and doing left pass and right pass to get the leftMost and RightMost boundaries for each bar.
// Time Complexity: O(3n) ~  - Each element is pushed and popped at most once from each stack
// Space Complexity: O(n) - For the stack and result arrays

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> leftMost(n, 0), rightMost(n, 0);  // Arrays to store boundaries for each height
        stack<int> st;                                // Stack to find next smaller element

        for(int i=0; i<n; i++) {                      // Find left boundaries (leftmost index for each height)
            if(st.empty()) {
                leftMost[i] = 0;                      // If stack empty, left boundary is start of array
                st.push(i); 
            }
            else {
                while(!st.empty() && heights[st.top()]>=heights[i]) st.pop();  // Pop higher heights
                if(st.empty()) leftMost[i] = 0;       // If no smaller height found, use left edge
                else leftMost[i] = st.top()+1;        // Otherwise, use next position after smaller height
                st.push(i);                           // Push current index to stack
            }
        }

        while(!st.empty()) st.pop();                  // st.clear() X so, clear the stack to reuse for right boundaries

        for(int i=n-1; i>=0; i--) {                   // Find right boundaries (rightmost index for each height)
            if(st.empty()) {
                rightMost[i] = n-1;                   // If stack empty, right boundary is end of array
                st.push(i); 
            }
            else {
                while(!st.empty() && heights[st.top()]>=heights[i]) st.pop();  // Pop higher heights
                if(st.empty()) rightMost[i] = n-1;    // If no smaller height found, use right edge
                else rightMost[i] = st.top()-1;       // Otherwise, use position before smaller height
                st.push(i);                           // Push current index to stack
            }
        }

        // cout<<"Left = "; for(auto i : leftMost) cout<<i<<" "; cout<<"\n";  // Debug print
        // cout<<"Right = "; for(auto i: rightMost) cout<<i<<" "; cout<<"\n"; // Debug print
        
        int height, width, currArea, maxArea = 0;
        for(int i=0; i<n; i++) {                      // Calculate max area
            width = rightMost[i] - leftMost[i] + 1;   // Calculate width of rectangle
            height = heights[i];                      // Use current height
            int currArea = width*height;              // Calculate area
            maxArea = max(maxArea, currArea);         // Update max area if needed
        }
        return maxArea;                               // Return the maximum area found
    }
};