/* LC#1128. Number of Equivalent Domino Pairs 

### Approach: Frequency Counting with Hash Map
1. **Key Representation**:
   - Represent each domino pair as a unique key using the smaller and larger values of the pair.
   - Use bit manipulation (`minVal << 16 | maxVal`) to create a unique key for each pair.

2. **Frequency Map**:
   - Use an unordered map to count the frequency of each unique domino pair.
   - For each domino, calculate its key and update its frequency in the map.

3. **Count Equivalent Pairs**:
   - For each unique domino pair with frequency `n`, the number of equivalent pairs is given by the combination formula `nC2 = (n * (n - 1)) / 2`.

4. **Return the Result**:
   - Sum up the equivalent pairs for all unique domino pairs and return the result.

5. **Time Complexity**:
   - Iterating through the `dominoes` array takes O(n).
   - Calculating the equivalent pairs from the frequency map takes O(k), where k is the number of unique keys.
   - Since k is bounded by the number of dominoes, the overall complexity is O(n).

6. **Space Complexity**:
   - The `freqMap` stores at most k unique keys, where k is the number of unique domino pairs.
   - The space complexity is O(k).
*/

// Time Complexity: O(n)
// - Iterating through the `dominoes` array takes O(n).
// - Calculating the equivalent domino pairs from the frequency map takes O(k), where k is the number of unique keys.
// - Since k is bounded by the number of dominoes, the overall complexity is O(n).

// Space Complexity: O(k)
// - The `freqMap` stores at most k unique keys, where k is the number of unique domino pairs.

class Solution {
    public:
        int numEquivDominoPairs(vector<vector<int>>& dominoes) {
            int ans = 0;                                  // Initialize the count of equivalent pairs
            unordered_map<int, int> freqMap;              // Map to store the frequency of each domino pair
            for(int i = 0; i < dominoes.size(); i++) {    // Iterate through all dominoes
                int a = dominoes[i][0];                   // First number of the domino
                int b = dominoes[i][1];                   // Second number of the domino
                int minVal = min(a, b);                   // Smaller value of the pair
                int maxVal = max(a, b);                   // Larger value of the pair
                int key = minVal << 16 | maxVal;          // Create a unique key by combining the two values
                if(freqMap.count(key)) freqMap[key]++;    // Increment the frequency if the key exists
                else freqMap[key] = 1;                    // Otherwise, initialize the frequency to 1
            }
            for(auto i: freqMap) {                        // Iterate through the frequency map
                int n = i.second;                         // Frequency of the current domino pair
                if(n > 1) ans += (n * (n - 1)) / 2;       // Add the number of equivalent pairs (nC2)
            }
            return ans;                                   // Return the total count of equivalent pairs
        }
    };