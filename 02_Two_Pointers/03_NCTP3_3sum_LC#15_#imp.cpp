/* LC#15. NCTP3. 3Sum
This is a variation of the two sum II problem (LC#167)

Approach: Sorting and Two Pointers

1. We sort the input array first to handle duplicates easily and to use the two-pointer technique.
2. We iterate through each element as a potential first element of our triplet.
3. For each first element, we use two pointers (left and right) to find pairs that complete the triplet.
4. We start with the first element nums[i], then set left pointer at i+1 and right pointer at the end.
5. We have several optimizations to improve performance:
   a. If the current element is positive, we break since no three positive numbers can sum to zero
   b. We skip duplicate values for the first element to avoid duplicate triplets
6. For each combination, we calculate the sum of the three elements.
7. If sum > 0, we decrease the right pointer to reduce the sum.
8. If sum < 0, we increase the left pointer to increase the sum.
9. If sum == 0, we found a valid triplet which we add to our result.
10. After adding a triplet, we move both pointers and skip any duplicates for the second element.
11. This approach works because by fixing one element and using two pointers for the remaining two,
    we reduce the problem to a variation of the two-sum problem.
12. The solution has O(n²) time complexity because we have a loop O(n) and for each element,
    we perform a two-pointer search O(n).
*/

// 1. Naive Solution: Three nested for loops: O(n^3) and O(1)
// TODO

// 2a. Sorting and Two Pointers
// Time Complexity: O(n²) - where n is the size of the input array
// Space Complexity: O(1) - excluding the output array

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;                                // Initialize result array to store triplets
        sort(nums.begin(), nums.end());                         // Sort the array to handle duplicates and use two pointers
        int n = nums.size();                                    // Get the array size
        for(int i=0; i<n; i++) {                                // Iterate through each element as potential first element
            if(nums[i] > 0) break;                              // If current element is positive, no triplet can sum to zero
            if(i>0 && nums[i] == nums[i-1]) continue;           // Skip duplicates for first element
            int l = i + 1, r = n - 1;                           // Initialize two pointers for remaining elements
            while(l < r) {                                      // Use two pointer technique to find pairs
                int sum = nums[i] + nums[l] + nums[r];          // Calculate current sum
                if(sum > 0) r--;                                // If sum is too large, decrease right pointer
                else if(sum < 0) l++;                           // If sum is too small, increase left pointer
                else {                                          // If sum equals zero
                    ans.push_back({nums[i], nums[l], nums[r]}); // Add triplet to result
                    l++;                                        // Move left pointer right
                    r--;                                        // Move right pointer left
                    while(l < r && nums[l] == nums[l-1]) l++;   // Skip duplicates for second element
                }
            }
        }
        return ans;                                             // Return all unique triplets
    }
};

// 2b. Sorting and Two Pointers but directly using twoSumSorted function
// Time Complexity: O(n²) - where n is the size of the input array
// - Sorting the array takes O(n log n).
// - The outer loop runs O(n) times.
// - For each iteration of the outer loop, the two-pointer search runs in O(n).
// - Overall complexity is O(n log n + n²) ≈ O(n²).

// Space Complexity: O(1) (excluding the output array)
// - The solution uses constant extra space for variables and modifies the input array in-place.

class Solution {
    vector<vector<int>> twoSumSorted(int l, int r, vector<int> &nums, int target) {
        vector<vector<int>> res;                          // Vector to store pairs that sum to the target
        while(l < r) {                                    // Two-pointer approach
            int twoSum = nums[l] + nums[r];               // Calculate the sum of the two pointers
            if(twoSum == target) {                        // If the sum matches the target
                res.push_back({nums[l], nums[r]});        // Add the pair to the result
                l++;                                      // Move the left pointer
                r--;                                      // Move the right pointer
                while(l < r && nums[l] == nums[l-1]) l++; // [#IMP] Skip duplicates for the left pointer
            }
            else if(twoSum > target) r--;                 // If the sum is too large, move the right pointer
            else l++;                                     // If the sum is too small, move the left pointer
        }
        return res;                                       // Return all pairs that sum to the target
    }
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;                          // Vector to store triplets
        sort(nums.begin(), nums.end());                   // Sort the array to handle duplicates and use two pointers
        int n = nums.size();                              // Get the size of the array
        for(int i=0; i<n-2; i++) {                        // Iterate through each element as the first element of the triplet
            if(i>0 && nums[i] == nums[i-1]) continue;     // [#IMP] Skip duplicates for the first element
            int target = -1 * nums[i];                    // Target for the two-sum problem
            int l = i+1, r = n-1;                         // Initialize two pointers
            vector<vector<int>> res = twoSumSorted(l, r, nums, target); // Find pairs that sum to the target
            if(!res.empty()) {                            // If pairs are found
                for(int j=0; j<res.size(); j++) {         // Iterate through the pairs
                    res[j].push_back(nums[i]);            // Add the first element to each pair to form a triplet
                    ans.push_back(res[j]);                // Add the triplet to the result
                }
            }
        }
        return ans;                                       // Return all unique triplets
    }
};

// {-4, -1, -1, 0, 1, 2} - Only sort nums and don't remove the duplicates
