/* LC#287. Find the Duplicate Number
Not a linked list problem, but a slow and fast pointer problem

[1, n] inclusive
There is only one repeated number in nums(twice or more times), return this repeated number.

You must solve the problem without modifying the array nums and using only constant extra space.


Approach: Negative Marking
1. Iterate through each element in the array
2. For each element, compute an index: idx = abs(num) - 1
3. Check if the value at nums[idx] is negative:
   - If yes, we've seen this number before, so return abs(num)
   - If no, mark it as visited by multiplying nums[idx] by -1
4. Return -1 if no duplicate found (though problem states there will always be one)

There are multiple other approaches in either O(1) or O(n) space like slow and fast pointers, using a hashmap, etc.

*/
//  1. Negative Marking
// Time & Space Complexity
// - Time Complexity: O(n) - We iterate through the array once
// - Space Complexity: O(1) - No extra space used beyond variables

// Constraints & Notes
// - Modifies the original array (destructive operation)
// - Works because input is guaranteed to contain numbers from 1 to n
// - Each number's value can be used as a pointer to an array index
// - Negative marking serves as our "hash map" to track seen values

class Solution {
  public:
      int findDuplicate(vector<int> nums) {
          for(int i = 0; i < nums.size(); i++) {          // Iterate through the array
              int idx = abs(nums[i]) - 1;                 // Compute the index corresponding to the current value
              if(nums[idx] < 0) return abs(nums[i]);      // If the value at nums[idx] is negative, the number is a duplicate
              nums[idx] *= -1;                            // Mark the index as visited by negating the value
          }
          return -1;                                      // Return -1 if no duplicate is found (shouldn't happen per constraints)
      }
  };

/*
Dry run of the code: 
Initial array: [1, 3, 4, 2, 2]

Loop steps:
- i = 0, nums[i] = 1
  idx = |1| - 1 = 0
  nums[0] is not negative, so nums[0] = -1
  Array becomes: [-1, 3, 4, 2, 2]
  i increments to 1

- i = 1, nums[i] = 3
  idx = |3| - 1 = 2
  nums[2] is not negative, so nums[2] = -4
  Array becomes: [-1, 3, -4, 2, 2]
  i increments to 2

- i = 2, nums[i] = -4
  idx = |-4| - 1 = 3
  nums[3] is not negative, so nums[3] = -2
  Array becomes: [-1, 3, -4, -2, 2]
  i increments to 3

- i = 3, nums[i] = -2
  idx = |-2| - 1 = 1
  nums[1] is not negative, so nums[1] = -3
  Array becomes: [-1, -3, -4, -2, 2]
  i increments to 4

- i = 4, nums[i] = 2
  idx = |2| - 1 = 1
  nums[1] is negative, so we return |2| = 2

Result: 2
*/
