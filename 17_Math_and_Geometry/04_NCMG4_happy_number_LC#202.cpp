// LC#202. NCMG4. Happy Number

//  1. Using an unordered_set
// Time Complexity: O(log n), where n is the input number. 
// Each iteration reduces the number of digits, and the sum of squares converges to a cycle or 1 in a small number of steps.
// Space Complexity: O(log n), for the unordered_set used to store previously seen numbers.

class Solution {
    int sumOfSquareOfDigits(int n) {                         // Helper function to calculate the sum of squares of digits.
        int ans = 0;                                         // Initialize the result to 0.
        while(n) {                                           // Loop until all digits are processed.
            int rem = n % 10;                                // Extract the last digit.
            ans += rem * rem;                                // Add the square of the digit to the result.
            n /= 10;                                         // Remove the last digit from the number.
        }
        return ans;                                          // Return the sum of squares of digits.
    }
public:
    bool isHappy(int n) {                                    // Function to determine if a number is a happy number.
        unordered_set<int> st;                               // Set to store previously seen numbers to detect cycles.
        st.insert(n);                                        // Insert the initial number into the set.
        while(n != 1) {                                      // Loop until the number becomes 1.
            n = sumOfSquareOfDigits(n);                      // Calculate the sum of squares of digits.
            if(st.find(n) != st.end()) return false;         // If the number is already in the set, a cycle is detected.
            st.insert(n);                                    // Insert the new number into the set.
        }
        return true;                                         // If the loop exits, the number is happy.
    }
};
