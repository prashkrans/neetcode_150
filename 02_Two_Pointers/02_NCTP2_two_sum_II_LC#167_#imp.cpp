/* LC#167. NCTP2. Two Sum II - Input Array Is Sorted
This could be solved similar to LC#1. Two Sum using a hashmap, but the input array is sorted and 
we have to solve it in O(1) space complexity.

Approach: Two Pointer Technique

1. We use a two-pointer approach since the input array is already sorted.
2. We initialize two pointers: l at the beginning (index 0) and r at the end of the array (index n-1).
3. We iteratively adjust these pointers based on the sum of elements they point to.
4. In each iteration, we calculate the sum of nums[l] and nums[r] and compare it with the target.
5. If the sum is greater than the target, we decrease the right pointer to reduce the sum.
6. If the sum is less than the target, we increase the left pointer to increase the sum.
7. If the sum equals the target, we've found our answer and return the indices (adding 1 to convert to 1-indexed).
8. This approach works because the array is sorted, allowing us to systematically narrow down the search space.
9. Note that the problem requires 1-indexed output, so we add 1 to both indices before returning them.
*/

// 1. Two Pointer Technique
// Time Complexity: O(n) - where n is the size of the input array | 0ms beats 100%
// Space Complexity: O(1) - using only constant extra space

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;                                    // Initialize answer vector
        int n = nums.size();                                // Get the size of input array
        int l = 0, r = n - 1;                               // Initialize left and right pointers
        while(l < r) {                                      // Continue until pointers meet
            if(nums[l] + nums[r] > target) r--;             // If sum is too large, decrease right pointer
            else if(nums[l] + nums[r] < target) l++;        // If sum is too small, increase left pointer
            else {                                          // If sum equals target
                ans = {l+1, r+1};                           // Store 1-indexed positions (as per problem requirement)
                break;                                      // Exit the loop once solution is found
            }
        }
        return ans;                                         // Return the answer vector
    }
};

// or, using a more compact version of the above code
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0;
        int r = numbers.size() - 1;
        while(l < r) {
            if(numbers[l] + numbers[r] == target) return {l+1, r+1};
            else if(numbers[l] + numbers[r] > target) r--;
            else l++;
        }
        return {};  // This line will never be reached since the problem guarantees a solution
    }
};
    