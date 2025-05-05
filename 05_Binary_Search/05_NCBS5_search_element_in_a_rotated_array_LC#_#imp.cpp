/* LC#33. NCBS5. Search in Rotated Sorted Array
Slightly different from LC#153. NCBS4. Find Minimum in Rotated Sorted Array

/*
### Approach: Binary Search in Rotated Sorted Array
1. Initialize two pointers, `l` (left) and `r` (right), to the start and end of the
array, respectively.
2. Perform binary search while `l <= r`:
   a. Calculate the middle index `mid` as `(l + r) / 2` or `l + (r - l)/2`.
   b. If the target is equal to `nums[mid]`, return `mid` as the index of the target.
   c. Check if the left half of the array (`nums[l]` to `nums[mid]`) is sorted:
      i. If the target is outside the range of the left half (`target > nums[mid]` or
      `target < nums[l]`), move to the right half by setting `l = mid + 1`.
      ii. Otherwise, move to the left half by setting `r = mid - 1`.
   d. If the left half is not sorted, the right half must be sorted:
      i. If the target is outside the range of the right half (`target < nums[mid]` or
      `target > nums[r]`), move to the left half by setting `r = mid - 1`.
      ii. Otherwise, move to the right half by setting `l = mid + 1`.
3. If the target is not found after the loop, return -1.
4. The algorithm ensures logarithmic time complexity by halving the search space at
each step.
*/

// Time Complexity: O(log n) | 0ms beats 100%
// - The binary search algorithm divides the search space in half at each step.
// - n = size of the input array.

// Space Complexity: O(1)
// - The algorithm uses constant space for variables.

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;                 // Initialize left and right pointers

        while (l <= r) {                                // Perform binary search
            int mid = l + (r - l) / 2;                      // Calculate the middle index
            if (target == nums[mid]) {                  // Check if the target is at mid
                return mid;                             // Return the index if found
            }

            if (nums[l] <= nums[mid]) {                 // Check if the left half is sorted
                if (target > nums[mid] || target < nums[l]) { // Check if target is outside the left half
                    l = mid + 1;                        // Move to the right half
                } else {                                // Target is within the left half
                    r = mid - 1;                        // Move to the left half
                }
            } else {                                    // Right half is sorted
                if (target < nums[mid] || target > nums[r]) { // Check if target is outside the right half
                    r = mid - 1;                        // Move to the left half
                } else {                                // Target is within the right half
                    l = mid + 1;                        // Move to the right half
                }
            }
        }
        return -1;                                      // Return -1 if target is not found
    }
};

// or, same as above but compact

class Solution {
    public:
        int search(vector<int>& nums, int target) {
            int left = 0, right = nums.size() - 1;
            while(left <= right) { // Note: <= not <
                int mid = left + (right - left) / 2;
                if(nums[mid] == target) return mid;
                else if(nums[left] <= nums[mid]) {  // Note: <= not <
                    if(target > nums[mid] || target < nums[left]) left = mid + 1;
                    else right = mid - 1;
                }
                else {
                    if(target < nums[mid] || target > nums[right]) right = mid - 1;
                    else left = mid + 1;
                }
            }
            return -1;
        }
    };