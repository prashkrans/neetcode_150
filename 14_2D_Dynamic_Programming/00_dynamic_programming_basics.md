# Some DP learnings:

### How to Solve Dynamic Programming Problems:
To solve a DP question effectively, always follow these steps:

1. **Understand the problem carefully**
   - Identify the input, output, and constraints
   - Clarify any ambiguous parts of the problem statement

2. **Draw the recursion tree or decision tree diagram**
   - Work with a smaller test case to visualize the problem
   - Identify overlapping subproblems

3. **Formulate the recurrence relation along with proper base cases**
   - Define the state clearly
   - Establish the recurrence relation based on your recursion tree
   - Identify all the necessary base cases

4. **1. Recursion without memoization: Implement the recursive solution:**
   - Translate the recurrence relation and base cases into code without memoization
   - Verify correctness with test cases

5. **2. Recursion with memoization: Apply memoization to the recursive solution**
   - Add a DP array (1D or 2D) to cache results
   - Reuse previously calculated results to avoid redundant computation

6. **3. Bottom up DP: Convert to bottom-up approach**
   - Initialize the DP array with base cases
   - Carefully define the iteration order
   - Pay special attention to boundary conditions in 2D DP problems
   - Ensure proper handling of start and end states
   - E.g. 
        - if going from bottom right to top left return DP[0][0]
        - if going from bottom left to top right return DP[0][m] (unbounded knapsack).


### uint vs int:
If the below is mentioned in Leetcode Q description then use vector<vector<uint>> dp(n+1, vector<uint>(m+1, 0));
i.e. use unsigned int `uint` instead of signed int `int`.

`The test cases are generated so that the answer fits on a 32-bit signed integer.`




