/* LC#739. NCST5. Daily Temperatures

# Daily Temperatures - Approach & Dry Run

## Approach:
1. Use a monotonic decreasing stack to track indices of temperatures that haven't found a warmer day yet
2. For each temperature in the array:
  a. While current temperature is warmer than the temperature at stack top:
     - Calculate days between current index and stack top index
     - Pop from stack
  b. Push current index onto stack
3. Return array with calculated waiting days
*/

// 1a. Using a stack to store difference of indices
// Time Complexity: O(n) - Each element is pushed and popped at most once
// Space Complexity: O(n) - For the stack and result array
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ans(n, 0);                // Initialize result array with zeros
        stack<int> st;                        // Stack to store indices of temperatures not the temp. itself
        
        for(int i=0; i<n; i++) {
            int currTemp = temperatures[i];   // Current temperature being processed
            while(!st.empty() && currTemp > temperatures[st.top()]) {  // Found warmer day for elements in stack
                ans[st.top()] = i - st.top(); // Calculate days until warmer temperature
                st.pop();                     // Remove processed temperature
            }
            st.push(i);                       // Push current index not currTemp to stack
        }
        return ans;                           // Return array with days to wait
    }
};



/*
## Dry Run:
Input: temperatures = [73, 74, 69, 72]

Initialize:
- ans = [0, 0, 0, 0]
- stack = []

i=0, temp=73:
 - stack is empty, push 0
 - stack = [0]
 - ans = [0, 0, 0, 0]

i=1, temp=74:
 - 74 > 73, we found next warmer day for index 0
 - ans[0] = 1-0 = 1
 - pop 0 from stack
 - push 1 to stack
 - stack = [1]
 - ans = [1, 0, 0, 0]

i=2, temp=69:
 - 69 < 74, so just push 2
 - stack = [1, 2]
 - ans = [1, 0, 0, 0]

i=3, temp=72:
 - 72 > 69, so ans[2] = 3-2 = 1, pop 2
 - 72 < 74, so push 3
 - stack = [1, 3]
 - ans = [1, 0, 1, 0]

Final answer: [1, 0, 1, 0]

*/

/*
### Approach: Monotonic Decreasing Stack
1. Use a stack to store indices of temperatures in a monotonic decreasing order.
2. Traverse the array from right to left:
   - For each temperature, check if it is less than the temperature at the top of the stack.
   - If it is, calculate the difference in indices to determine the number of days to wait for a warmer temperature.
   - If it is not, pop elements from the stack until a warmer temperature is found or the stack becomes empty.
3. Push the current index onto the stack.
4. If the stack is empty after processing, it means there is no warmer temperature, so the result for that index is 0.
5. The algorithm ensures that each element is processed at most twice (once when pushed and once when popped), resulting in O(n) time complexity.
6. The space complexity is O(n) due to the stack.
*/

// 1b. Using a stack to store difference of indices (same as above but in reverse order)
// (Prefer this code as this is my custom code)

// Time Complexity: O(n)
// - Each element is pushed and popped from the stack at most once.
// - The total number of operations is proportional to the size of the input array.

// Space Complexity: O(n)
// - The stack stores indices of temperatures, which can be at most n elements in the worst case.

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();                        // Size of the input array
        vector<int> ans(n, 0);                              // Initialize result array with zeros
        stack<int> st;                                      // Stack to store indices of temperatures
        
        for(int i=n-1; i>=0; i--) {                         // Traverse the array from right to left
            while(!st.empty() && temperatures[i] >= temperatures[st.top()]) { // [#IMP >= not >]
                st.pop();                                   // Remove indices of temperatures that are not warmer
            }
            ans[i] = (st.empty()) ? 0 : st.top() - i;       // Calculate days to wait for a warmer temperature
            st.push(i);                                     // Push the current index onto the stack
        }
        return ans;                                         // Return the result array
    }
};

// Important Case: temperatures = [89,62,70,58,47,47,46,76,100,70]