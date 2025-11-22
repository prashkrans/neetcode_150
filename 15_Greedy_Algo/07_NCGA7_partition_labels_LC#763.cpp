/* LC#763. NCGA7. Partition Labels (Its an easy problem but tricky to understand)
   Problem: Given a string s, partition it into as many parts as possible so that each letter appears in at 
   most one part.
   Return a list of integers representing the size of these parts.
   Example: Input: s = "ababcbacadefegdehijhklij"
            Output: [9,7,8]
            Explanation: The partitions are "ababcbaca", "def

Note: It is different from LC#3. Longest Substring Without Repeating Characters which uses sliding window approach.


### Approach: Greedy Partitioning Based on Last Occurrence
1. Create a frequency map (unordered_map) to store the last occurrence of each
character in the input string. This allows O(1) lookups.
2. Iterate through the string while maintaining two variables: `size` to track
the size of the current partition and `end` to track the farthest index that
the current partition can extend to.
3. For each character, update the `end` index to the maximum of its current
value and the last occurrence of the current character. This ensures that
all characters in the current partition are included.
4. If the current index matches the `end` index, it means the current partition
is complete. Add the partition size to the result and reset the size for the
next partition.
5. Continue this process until the entire string is processed. The result will
contain the sizes of all partitions.
6. This approach ensures that each character appears in only one partition,
and the partitions are as large as possible while satisfying the constraints.
*/
// 1. Greedy Partitioning Based on Last Occurrence
// Time Complexity: O(2n) ~ O(n) for traversing the string twice (once to build the map and once to partition)
// Space Complexity: O(1) (not O(n)) for the frequency map (fixed size of 26 for lowercase letters)

class Solution {
public:
    vector<int> partitionLabels(string s) {
        vector<int> ans;                                     // Stores the sizes of partitions
        unordered_map<char, int> lastIndex;                  // Maps each character to its last occurrence

        for(int i = 0; i < s.size(); i++) 
            lastIndex[s[i]] = i;                             // Record the last index of each character

        int size = 0, end = 0;                               // Initialize partition size and end index
        for(int i = 0; i < s.size(); i++) {                  // Iterate through the string
            size++;                                          // Increment the current partition size
            end = max(end, lastIndex[s[i]]);                 // Update the end index of the current partition
            if(i == end) {                                   // If the current index matches the end index
                ans.push_back(size);                         // Add the partition size to the result
                size = 0;                                    // Reset the partition size for the next segment
            }
        }
        return ans;                                          // Return the list of partition sizes
    }
};
    
// Dryrun:
// i = 0 1 2 3 4 5 6 7 8 9 10 11 12
// s = x y x x y z b z b b i  s  l

// Step 1: Build lastIndex map
// lastIndex = {x: 3, y: 4, z: 7, b: 9, i: 10, s: 11, l: 12}

// Step 2: Partitioning process
// i = 0, size = 1, end = max(0, 3) = 3
// i = 1, size = 2, end = max(3, 4) = 4
// i = 2, size = 3, end = max(4, 3) = 4
// i = 3, size = 4, end = max(4, 3) = 4
// i = 4, size = 5, end = max(4, 4) = 4 i == end -> Partition complete, ans = [5]

// i = 5, size = 1, end = max(5, 7) = 7
// i = 6, size = 2, end = max(7, 9) = 9
// i = 7, size = 3, end = max(9, 7) = 9
// i = 8, size = 4, end = max(9, 9) = 9
// i = 9, size = 5, end = max(9, 9) = 9 i == end -> Partition complete, ans = [5, 5]

// i = 10, size = 1, end = max(10, 10) = 10 i == end -> Partition complete, ans = [5, 5, 1]
// i = 11, size = 1, end = max(11, 11) = 11 i == end -> Partition complete, ans = [5, 5, 1, 1]
// i = 12, size = 1, end = max(12, 12) = 12 i == end -> Partition complete, ans = [5, 5, 1, 1, 1]

// Final result: [5, 5, 1, 1, 1]