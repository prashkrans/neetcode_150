/* LC#66. NCMG5. Plus One

Approaches:
1. Recursive
2. Iterative


### Approach 1: Recursive Handling of Carry
1. Check if the input vector contains a single digit `9`. If true, return `{1, 0}`,
as adding 1 to 9 results in 10.
2. If the last digit of the vector is less than 9:
   - Increment the last digit by 1.
   - Return the updated vector, as no carry is generated.
3. If the last digit is 9:
   - Set the last digit to 0, as adding 1 to 9 results in a carry.
   - Recursively call the function on the remaining digits (excluding the last digit).
   - Append the updated last digit (0) to the result of the recursive call.
4. Return the final result after processing all digits.
5. The recursion terminates when the base case is reached, ensuring that the carry
is handled correctly for all digits.
*/

// 1a. Recursion
// Time Complexity: O(n), where n is the number of digits in the input vector. Each recursive call processes one digit. | 0ms beats 100%
// Space Complexity: O(n), due to the recursion stack and the creation of new vectors during each recursive call.

class Solution {
public:
    vector<int> plusOne(vector<int> digits) {
        if(digits.size() == 1 && digits[0] == 9) {           // Base case: Single digit 9 becomes 10.
            return {1, 0};                                   // Return the result as {1, 0}.
        }
        if(digits.back() < 9) {                              // If the last digit is less than 9.
            digits.back()++;                                 // Increment the last digit.
            return digits;                                   // Return the updated vector.
        }
        else {                                               // If the last digit is 9.
            digits.back() = 0;                               // Set the last digit to 0.
            vector<int> res = plusOne({digits.begin(), digits.begin() + digits.size() - 1}); // Recursive call on the remaining digits.
            res.push_back(digits.back());                    // Append the updated last digit (0) to the result.
            return res;                                      // Return the final result.
        }
    }
};

// 1b. Recursion but slightly different
// Time Complexity: O(n), where n is the number of digits in the input vector. Each recursive call processes one digit.
// Space Complexity: O(n), due to the recursion stack and the creation of new vectors during each recursive call.

class Solution {
public:
    vector<int> rec(int i, vector<int> digits) {             // Recursive helper function to handle carry.
        if(i == -1) {                                        // Base case: If all digits are processed.
            digits.insert(digits.begin(), 1);                // Insert 1 at the beginning to handle carry.
            return digits;                                   // Return the updated vector.
        }       
        int n = digits.size();                               // Get the size of the digits vector.
        if(digits[i] < 9) {                                  // If the current digit is less than 9.
            digits[i]++;                                     // Increment the current digit.
            return digits;                                   // Return the updated vector.
        }
        else {                                               // If the current digit is 9.
            digits[i] = 0;                                   // Set the current digit to 0.
            vector<int> res = rec(i-1, digits);              // Recursive call on the previous digit.
            return res;                                      // Return the result of the recursive call.
        }
    }
    vector<int> plusOne(vector<int>& digits) {               // Main function to add one to the number.
        return rec(digits.size()-1, digits);                 // Start recursion from the last digit.
    }
};