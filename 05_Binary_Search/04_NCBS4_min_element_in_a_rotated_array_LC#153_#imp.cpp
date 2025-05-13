/* LC#153. NCBS4. Find Minimum in Rotated Sorted Array
Constraints: Each element is unique, with the original array being sorted in ascending order which
is then rotated 1 to n times where n is the length of the array.

Note: 
Using nums[left] < nums[mid] only works in some specific cases and doesn't cover all possible rotated patterns.
Using nums[mid] > nums[right] is the correct and complete approach.

*/

// This is the best solution for this problem, so learn it well.
// 1. Iterative binary search to find the minimum element in a rotated sorted array.
// O(log n) due to binary search
// O(1) due to left, right and mid variables

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;                           // Start of search range
        int right = nums.size() - 1;            // End of search range

        if (nums[left] < nums[right]) return nums[left];  // [#IMP] Edge case: Array is not rotated, first element itself is minimum
        
        while (left < right) {
            int mid = left + (right - left) / 2;  // This is same as mid = (left + right) / 2. Used this way to prevent overflow.
            
            if (nums[mid] > nums[right]) {        // If mid > right, minimum is in right half
                left = mid + 1;
            }
            else {                                // If mid <= right, minimum is in left half (including mid)
                right = mid;
            }
        }
        
        return nums[left];                        // When left == right, we've found the minimum
    }
};

// or,
// Same as above but compact (O(logn) time and O(1) space)

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size()-1;
        if(nums[left] < nums[right]) return nums[left];
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] > nums[right]) left = mid + 1;
            else right = mid;
        }
        return nums[left];
    }
};


/**
 * Approach for finding minimum in rotated sorted array:
 * 
 * 1. Use binary search with pointers 'left' and 'right' to track the search range.
 * 
 * 2. First check if array is not rotated (nums[left] < nums[right]).
 *    - If true, return nums[left] as minimum.
 * 
 * 3. For the binary search:
 *    - Calculate mid = left + (right - left) / 2 to avoid integer overflow.
 *    - Compare nums[mid] with nums[right] to determine which half has the minimum:
 *      a) If nums[mid] > nums[right]: The array is not sorted in this range,
 *         so minimum must be in right half. Set left = mid + 1.
 *      b) If nums[mid] <= nums[right]: The array is sorted in this range,
 *         so minimum must be in left half (including mid). Set right = mid.
 * 
 * 4. Continue until left == right, which is the position of the minimum element.
 * 
 * 5. Return nums[left] as the minimum value.
 * 
 * Key Concepts:
 * 
 * 1. Binary Search: Dividing the search space in half at each step to achieve
 *    logarithmic time complexity O(log n).
 * 
 * 2. Modified Binary Search: Standard binary search finds a target value, but here
 *    we're modifying it to find the inflection point (minimum) in a rotated array.
 * 
 * 3. Rotated Sorted Array Property: In a rotated sorted array, at least one half
 *    (left or right) must be properly sorted at any given point.
 * 
 * 4. Inflection Point: The minimum element is the only element whose previous element
 *    is greater than it (the point where the array "wraps around").
 * 
 * 5. Invariant Maintenance: We maintain the invariant that the minimum element
 *    is always within our search range [left, right].
 * 
 * 6. Overflow Prevention: Using mid = left + (right - left) / 2 instead of
 *    mid = (left + right) / 2 to prevent integer overflow for large arrays.
 * 
 * Time Complexity: O(log n) - We're using binary search to halve the search space each time.
 * Space Complexity: O(1) - We're using constant extra space regardless of input size.
 */

