/* LC#128. NCAH9. NCTP6. Longest Consecutive Sequence

### Approach 1: 
We can consider a number num as the start of a sequence if and only if num - 1 does not exist in the given array. 
We iterate through the array and only start building the sequence if it is the start of a sequence. 
This avoids repeated work. We can use a hash set for O(1) lookups by converting the array to a hash set.

Optimized Hash Set with Linear Sequence Building:
1. We use an unordered_set to efficiently store and check for elements in
constant time, eliminating duplicates naturally.
2. First, we insert all elements from the input array into the hash
set for O(1) lookups.
3. We then iterate through each element in the set and only process
elements that could be the start of a sequence.
4. An element is considered a sequence start if its predecessor (element-1) doesn't
exist in the set.
5. For each potential sequence start, we use a while loop to efficiently
check consecutive integers until we find a gap.
6. The while loop increments the current number and checks if the next
number exists in the set.
7. This optimization ensures we only do necessary lookups rather than iterating
through the entire set repeatedly.
8. We track the maximum sequence length encountered and return it as the
final answer.
9. This approach has an optimal time complexity of O(n) despite having nested
loops, as each number is only checked once.
10. The space complexity is O(n) for storing the unique elements in
the hash set.
*/

// 1. Using an unordered hash set with linear sequence building (Prefer this as its faster)
// Time Complexity: O(n) where n is the size of nums array
// Space Complexity: O(n) for storing unique elements in the hash set

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int ans = 0;                                             // Initialize answer to track max sequence length
        unordered_set<int> st;                                   // Hash set to store unique elements
        for(int i=0; i<nums.size(); i++) st.insert(nums[i]);     // Insert all elements into the set
        for(auto i: st) {                                        // Iterate through each unique element
            if(st.find(i-1) == st.end()) {                       // [#IMP] Check if this is the start of a sequence
                int currNum = i;                                 // Current number in sequence
                int currLen = 1;                                 // Initialize current sequence length
                while(st.find(currNum + 1) != st.end()) {        // Check for consecutive numbers
                    currNum++;                                   // Move to next consecutive number
                    currLen++;                                   // Increment sequence length
                }
                ans = max(ans, currLen);                         // Update answer with longest sequence found
            }
        }
        return ans;                                              // Return the length of longest consecutive sequence
    }
};

/*
### Approach 2: Two pointer method: Sort and Scan with Deduplication and then use two pointers to check for the longest sequence. 
1. This approach first sorts the array to bring consecutive elements next to
each other, making it easier to identify sequences.
2. We handle the empty array edge case by immediately returning 0 when
the input array has no elements.
3. After sorting, we create a new array that removes duplicates from the
original sorted array to simplify processing.
4. We preserve only unique elements in the newNums array by comparing adjacent
elements and adding an element only if different from the next.
5. We manually add the last element of the original array to ensure
it's included in our deduplicated array.
6. Using two pointers (l and r), we scan through the deduplicated array
to identify consecutive sequences.
7. A sequence breaks when the difference between adjacent elements is not exactly
1, at which point we update our answer.
8. We also handle the case where the last sequence extends to the
end of the array.
9. The time complexity is dominated by the sorting operation, making it
O(n log n) overall.
10. The space complexity is O(n) in the worst case when all
elements are unique.
*/

// 2. Two pointer method: Sort and Scan with Deduplication and then use two pointers to check for the longest sequence. 
// Time Complexity: O(n + nlogn + n) ~ O(nlogn) due to sorting where n is the size of nums array 
// Space Complexity: O(n) for storing the deduplicated array newNums

class Solution {
public:
   int longestConsecutive(vector<int>& nums) {
       if(nums.empty()) return 0;                             // Handle empty array edge case
       sort(nums.begin(), nums.end());                        // Sort the array in ascending order
       vector<int> newNums;                                   // Vector to store sorted and only unique elements
       for(int i=0; i<nums.size()-1; i++) {                   // Iterate through all elements except the last one
           if(nums[i] != nums[i+1])
               newNums.push_back(nums[i]);                    // Add unique elements to newNums array
       }
       newNums.push_back(nums.back());                        // Add the last element of original array
       // for(auto i: newNums) cout<<i<<" "; cout<<endl;      // Debug print of deduplicated array
       int ans = 1;                                           // Initialize answer to minimum possible sequence length
       int l = 0, r = 0;                                      // Left and right pointers to track sequences
       while(r < newNums.size()) {                            // Iterate through deduplicated array
           if(r<newNums.size()-1 && newNums[r] + 1 != newNums[r + 1]) { // If next element breaks the sequence
               ans = max(ans, r - l + 1);                     // Update answer with current sequence length
               l = r + 1;                                      // Move left pointer to start of next potential sequence
           }
           else if(r == newNums.size()-1) ans = max(ans, r - l + 1); // Handle the last sequence
           r++;                                                // Move right pointer forward
       }
       return ans;                                            // Return the longest consecutive sequence length
   }
};

