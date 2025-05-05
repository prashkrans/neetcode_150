// LC#43. NCMG7. Multiply Strings

/* 
1. Reverse the second number
2. Multiply each digit of the second number with the entire first number
2. Reverse the result and add trailing zeros based on the place value of the digit in the second number
3. Sum up all the intermediate results
*/

// 1. Using multiply and add (not Karatsuba algorithm)


// Time Complexity: O(n * m), where n is the length of num1 and m is the length of num2. Each digit of num2 is multiplied with num1, and the results are added.
// Space Complexity: O(n + m), for storing the intermediate results and the final result.

class Solution {
    string multiplySingleDigit(string num1, char digit, string zeroes) { // Multiplies num1 with a single digit and appends trailing zeroes.
        string s;                                                       // Result string for the multiplication.
        int carry = 0;                                                  // Carry for handling overflow during multiplication.
        for(int i=num1.size()-1; i>=0; i--) {                           // Iterate through num1 from the least significant digit.
            int a = num1[i] - '0';                                      // Convert the current character to an integer.
            int b = digit - '0';                                        // Convert the single digit to an integer.
            int c = a * b + carry;                                      // Multiply and add the carry.
            int rem = c % 10;                                           // Extract the remainder (current digit).
            s += rem + '0';                                             // Append the digit to the result string.
            carry = c / 10;                                             // Update the carry.
        }
        if(carry > 0) s += (carry % 10 + '0');                          // Append the remaining carry if any.
        reverse(s.begin(), s.end());                                    // Reverse the result string to correct the order.
        s += zeroes;                                                    // Append trailing zeroes for place value.
        return s;                                                       // Return the result.
    }

    string addResult(string res, string ans) {  // res is always >= ans // Adds two strings representing numbers.
        if(ans.empty()) return res;                                     // If ans is empty, return res directly.
        string s;                                                       // Result string for the addition.
        int n = res.size(), m = ans.size();                             // Get the sizes of the two strings.
        int i = n-1, j = m-1;                                           // Start from the least significant digits.
        int carry = 0;                                                  // Carry for handling overflow during addition.
        while(j >= 0) {                                                 // Iterate through ans.
            int a = res[i--] - '0';                                     // Get the current digit from res.
            int b = ans[j--] - '0';                                     // Get the current digit from ans.
            int c = a + b + carry;                                      // Add the digits and the carry.
            int rem = c % 10;                                           // Extract the remainder (current digit).
            carry = c / 10;                                             // Update the carry.
            s += rem + '0';                                             // Append the digit to the result string.
        }
        while(i >= 0) {                                                 // Process remaining digits in res.
            int a = res[i--] - '0';                                     // Get the current digit from res.
            int c = a + carry;                                          // Add the carry.
            int rem = c % 10;                                           // Extract the remainder (current digit).
            carry = c / 10;                                             // Update the carry.
            s += rem + '0';                                             // Append the digit to the result string.
        }
        if(carry > 0) s += carry + '0';                                 // Append the remaining carry if any.
        reverse(s.begin(), s.end());                                    // Reverse the result string to correct the order.
        return s;                                                       // Return the result.
    }
public:
    string multiply(string num1, string num2) {                         // Multiplies two strings representing numbers.
        string ans;                                                     // Final result string.
        reverse(num2.begin(), num2.end());                              // Reverse num2 for easier processing.
        string zeroes = "";                                             // Trailing zeroes for place value.
        for(int i=0; i<num2.size(); i++) {                              // Iterate through each digit of num2.
            string res = multiplySingleDigit(num1, num2[i], zeroes);    // Multiply num1 with the current digit of num2.
            ans = addResult(res, ans);                                  // Add the result to the final answer.
            zeroes += '0';                                              // Append a trailing zero for the next place value.
        }
        return (ans[0] == '0') ? "0" : ans;                             // Handle leading zeroes and return the result.
    }
};