/* LC#85. NCST7c. Maximal Rectangle 
It uses the largest rectangle in histogram approach (LC#84. Largest Area in Histogram) to find 
the largest rectangle in a binary matrix.

### Approach: Maximal Rectangle Using Histogram Technique
1. Treat each row of the matrix as the base of a histogram. The height of each column
in the histogram is determined by the number of consecutive '1's above it.
2. For each row:
   a. Update the heights array. If the cell is '1', increment the height. If the cell
is '0', reset the height to 0.
   b. Use the `largestRectangleInHistogram` function to calculate the largest rectangle
area for the current histogram.
   c. Update the maximum area encountered so far.
3. In the `largestRectangleInHistogram` function:
   a. Use a stack to calculate the left and right boundaries for each bar in the
histogram. The left boundary is the nearest bar to the left that is shorter, and the
right boundary is the nearest bar to the right that is shorter.
   b. For each bar, calculate the width of the rectangle as `rightMost[i] - leftMost[i]
+ 1` and the area as `width * height`.
   c. Track the maximum area encountered.
4. The algorithm ensures that each cell in the matrix is processed once, resulting in
a time complexity of O(n * m), where n is the number of rows and m is the number of
columns.
*/


// 1. Using the largest rectangle in histogram approach i.e. a stack and leftmost and rightmost boundaries
// Time Complexity: O(n * m)
// - For each row, we calculate the largest rectangle in a histogram, which takes O(m).
// - There are n rows, so the total complexity is O(n * m).

// Space Complexity: O(m)
// - Space is used for the `heights` vector and the stack in the histogram calculation.

class Solution {
    int largestRectangleInHistogram(vector<int> heights) {
        int maxArea = 0;                                // Initialize the maximum area
        int n = heights.size();                         // Number of columns in the histogram
        stack<int> st;                                  // Stack to store indices
        vector<int> leftMost(n, 0);                     // Stores the leftmost boundary for each bar
        vector<int> rightMost(n, n-1);                  // Stores the rightmost boundary for each bar
        for(int i=0; i<n; i++) {                        // Calculate left boundaries
            if(st.empty()) {                            // If stack is empty, left boundary is 0
                leftMost[i] = 0;
                st.push(i);                             // Push the current index onto the stack
            } else {
                if(heights[i] > heights[st.top()]) {    // If current height is greater than the top of the stack
                    leftMost[i] = st.top() + 1;         // Set left boundary to the next index of the top
                    st.push(i);                         // Push the current index onto the stack
                } else {
                    while(!st.empty() && heights[i] <= heights[st.top()]) st.pop(); // Pop until a smaller height is found
                    leftMost[i] = (st.empty()) ? 0 : st.top() + 1; // Set left boundary
                    st.push(i);                         // Push the current index onto the stack
                }
            }
        }
        while(!st.empty()) st.pop();                    // Clear the stack
        for(int i=n-1; i>=0; i--) {                     // Calculate right boundaries
            if(st.empty()) {                            // If stack is empty, right boundary is n-1
                rightMost[i] = n-1;
                st.push(i);                             // Push the current index onto the stack
            } else {
                if(heights[i] > heights[st.top()]) {    // If current height is greater than the top of the stack
                    rightMost[i] = st.top() - 1;        // Set right boundary to the previous index of the top
                    st.push(i);                         // Push the current index onto the stack
                } else {
                    while(!st.empty() && heights[i] <= heights[st.top()]) st.pop(); // Pop until a smaller height is found
                    rightMost[i] = (st.empty()) ? n-1 : st.top() - 1; // Set right boundary
                    st.push(i);                         // Push the current index onto the stack
                }
            }
        }
        // for(auto i: leftMost) cout<<i<<" "; cout<<endl;
        // for(auto i: rightMost) cout<<i<<" "; cout<<endl;
        for(int i=0; i<n; i++) {                        // Calculate the maximum area
            int width = rightMost[i] - leftMost[i] + 1; // Width of the rectangle
            int height = heights[i];                   // Height of the rectangle
            int area = width * height;                 // Area of the rectangle
            maxArea = max(maxArea, area);              // Update the maximum area
        }
        return maxArea;                                // Return the maximum area
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int maxArea = 0;                                // Initialize the maximum area
        int n = matrix.size();                          // Number of rows in the matrix
        int m = matrix[0].size();                       // Number of columns in the matrix
        vector<int> heights(m, 0);                      // Heights array for the histogram
        for(int i=0; i<n; i++) {                        // Iterate over each row
            for(int j=0; j<m; j++) {                    // Update the heights array
                if(matrix[i][j] == '1') heights[j]++;   // Increment height if the cell is '1'
                else heights[j] = 0;                    // Reset height if the cell is '0'
            }
            int area = largestRectangleInHistogram(heights); // Calculate the largest rectangle for the current row
            // for(auto h: heights) cout<<h<<" "; cout<<"area: "<<area<<endl;
            maxArea = max(maxArea, area);               // Update the maximum area
        }
        return maxArea;                                // Return the maximum area
    }
};

// or, same as above but compact
// Time Complexity: O(n * m)
// - For each row, we calculate the largest rectangle in a histogram, which takes O(m).
// - There are n rows, so the total complexity is O(n * m).

// Space Complexity: O(m)
// - Space is used for the `heights` vector and the stack in the histogram calculation.

class Solution {
    int largestRectangleInHistogram(vector<int> heights) {
        int maxArea = 0;                                // Initialize the maximum area
        int n = heights.size();                         // Number of columns in the histogram
        stack<int> st;                                  // Stack to store indices
        vector<int> leftMost(n, 0);                     // Stores the leftmost boundary for each bar
        vector<int> rightMost(n, n-1);                  // Stores the rightmost boundary for each bar
        for(int i=0; i<n; i++) {                        // Calculate left boundaries
            if(st.empty()) leftMost[i] = 0;             // If stack is empty, left boundary is 0
            else {                                      // Calculate left boundary | if(heights[i] > heights[st.top()]) leftMost[i] = st.top() + 1; is redundant here
                while(!st.empty() && heights[i] <= heights[st.top()]) st.pop(); // Pop until a smaller height is found
                leftMost[i] = (st.empty()) ? 0 : st.top() + 1; // Set left boundary
            }
            st.push(i);                                 // Push the current index onto the stack
        }
        while(!st.empty()) st.pop();                    // Clear the stack
        for(int i=n-1; i>=0; i--) {                     // Calculate right boundaries | // if(heights[i] > heights[st.top()]) rightMost[i] = st.top() - 1; is redundant here
            if(st.empty()) rightMost[i] = n-1;          // If stack is empty, right boundary is n-1
            else {                                      // Calculate right boundary
                while(!st.empty() && heights[i] <= heights[st.top()]) st.pop(); // Pop until a smaller height is found
                rightMost[i] = (st.empty()) ? n-1 : st.top() - 1; // Set right boundary
            }
            st.push(i);                                 // Push the current index onto the stack
        }
        for(int i=0; i<n; i++) {                        // Calculate the maximum area
            int width = rightMost[i] - leftMost[i] + 1; // Width of the rectangle
            int height = heights[i];                   // Height of the rectangle
            int area = width * height;                 // Area of the rectangle
            maxArea = max(maxArea, area);              // Update the maximum area
        }
        return maxArea;                                // Return the maximum area
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int maxArea = 0;                                // Initialize the maximum area
        int n = matrix.size();                          // Number of rows in the matrix
        int m = matrix[0].size();                       // Number of columns in the matrix
        vector<int> heights(m, 0);                      // Heights array for the histogram
        for(int i=0; i<n; i++) {                        // Iterate over each row
            for(int j=0; j<m; j++) {                    // Update the heights array
                if(matrix[i][j] == '1') heights[j]++;   // Increment height if the cell is '1'
                else heights[j] = 0;                    // Reset height if the cell is '0'
            }
            int area = largestRectangleInHistogram(heights); // Calculate the largest rectangle for the current row
            maxArea = max(maxArea, area);               // Update the maximum area
        }
        return maxArea;                                // Return the maximum area
    }
};