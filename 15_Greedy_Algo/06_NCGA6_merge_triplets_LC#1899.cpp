/* LC#1899. NCAG6. Merge Triplets to Form Target Triplet

Note: triplet values are > 1 so we can use 0 to mark invalid triplets

Approach:
Specifically, if a triplet t has any element greater than the corresponding value in target 
(i.e., t[0] > target[0], t[1] > target[1], or t[2] > target[2]), we can discard it. This is 
because using such a triplet in operations would exceed the target values, making it invalid.

Now, from the remaining valid triplets, we only need to check whether the target triplet values 
exist. Since all values in the valid triplets are less than or equal to the corresponding values 
in the target triplet, finding the target triplet among them guarantees that we can achieve it.

### Approach 1: Filtering and Validation (Greedy Approach)
1. Iterate through the input triplets and filter out any triplet where any value
exceeds the corresponding value in the target array. This ensures that only
valid triplets are considered for merging.
2. Replace invalid triplets with {0, 0, 0} to mark them as unusable for further
processing.
3. Create a boolean vector of size 3 to track whether each target value has been
matched by at least one triplet.
4. Iterate through the filtered triplets and check if each target value is matched
by comparing the triplet values with the target values.
5. If all three target values are matched (i.e., all elements in the boolean vector
are true), return true. Otherwise, return false.
6. This approach ensures that the solution is efficient, with a linear time complexity
and constant space usage for tracking matches.
*/

// 1. Filtering and Validation (Greedy Approach)
// Time Complexity: O(2n) ~ O(n), where n is the number of triplets in the input array
// Space Complexity: O(1), as only a fixed-size vector is used for tracking

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        for(auto &triplet: triplets) {                    // Iterate through each triplet in the input array
            if(triplet[0] > target[0] ||                  // If any value in the triplet exceeds the target
                triplet[1] > target[1] ||                  // for the corresponding index, invalidate the triplet
                triplet[2] > target[2]) {
                triplet = {0, 0, 0};                      // Set the triplet to {0, 0, 0} to mark it as invalid
            }
        }
        // for(auto triplet: triplets) cout<<triplet[0]<<" "<<triplet[1]<<" "<<triplet[2]<<endl;
        vector<bool> found(3, false);                    // Create a vector to track if all target values are found
        for(auto triplet: triplets) {                    // Iterate through the (possibly modified) triplets
            if(target[0] == triplet[0]) found[0] = true; // Check if the first target value is matched
            if(target[1] == triplet[1]) found[1] = true; // Check if the second target value is matched
            if(target[2] == triplet[2]) found[2] = true; // Check if the third target value is matched
        }
        return found[0] && found[1] && found[2];         // Return true if all target values are matched
    }
};

// or 

class Solution {
public:
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        int n = triplets.size();
        for(int i=0; i<n; i++) {
            if(triplets[i][0] > target[0] 
                || triplets[i][1] > target[1] 
                || triplets[i][2] > target[2]) {
                triplets[i] = {0, 0, 0};
            }
        }
        vector<bool> found(3, false);
        for(int i=0; i<n; i++) {
            if(target[0] == triplets[i][0]) found[0] = true;
            if(target[1] == triplets[i][1]) found[1] = true;
            if(target[2] == triplets[i][2]) found[2] = true;
        }
        return found[0] && found[1] && found[2];
    }
};
    