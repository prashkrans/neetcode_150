/* LC#1296. NCGA5b. Divide Array in Sets of K Consecutive Numbers 
   (Same problem as LC#846. Hand of Straights)
   Problem: Given an array of integers, determine if it is possible to divide the array
   into sets of k consecutive numbers. Each set must consist of exactly k numbers,
   and all numbers in a set must be consecutive.

   Example: Input: arr = [1,2,3,4,5], k = 2  
            Output: true (can form sets [1,2] and [3,4])


/*
### Approach 1: Frequency Counting with Consecutive Validation
1. Create a frequency map (unordered_map) to count how many times each number appears
in the input array. This allows O(1) lookups.
2. Sort the input array in ascending order to ensure numbers are processed in sequential
order, which is necessary for forming groups.
3. Iterate through the sorted array. For each number, check if it is still available
in the frequency map. If not, skip to the next number.
4. If the number is available, attempt to form a group of size k starting from the
current number. Decrement the frequency of each number in the group.
5. If any number required to complete the group is missing (frequency is zero),
return false immediately as forming groups is impossible.
6. Continue this process until all numbers are processed. If all groups are successfully
formed, return true.
7. The sorting step ensures that groups are formed in ascending order, and the
frequency map ensures efficient tracking of number availability.
*/



// 1a. Frequency Counting with Consecutive Validation (Greedy Approach) | Using only auto in loops
// Time Complexity: O(n log n) for sorting + O(n * k) for the nested loops
// Space Complexity: O(n) for the frequency map

class Solution {
    public:
        bool isPossibleDivide(vector<int>& nums, int k) {
            int n = nums.size();                                  // Get the size of the input array
            if(n % k != 0) return false;                          // If total numbers can't form groups, return false
            unordered_map<int, int> freq;                         // Create a frequency map to count occurrences
            sort(nums.begin(), nums.end());                       // Sort the array to process numbers in order
            for(auto num: nums) freq[num]++;                      // Populate the frequency map with counts
            for(auto num: nums) {                                 // Iterate through the sorted array
                if(freq[num] > 0) {                               // If the current number is still available
                    for(int size = 1; size <= k; size++) {        // Attempt to form a group of size k
                        if(freq[num] == 0) return false;          // If the next number is missing, return false
                        freq[num]--;                              // Decrement the frequency of the current number
                        num++;                                    // Move to the next number in the sequence
                    }
                }
            }
            return true;                                          // Return true if all groups are successfully formed
        }
    };