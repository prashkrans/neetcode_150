/* LC#50. NCMG6. Pow(x, n)

### Approach: Recursive Exponentiation by Squaring
1. Use recursion to calculate `x^n` efficiently by dividing the problem size by 2 at each step.
2. Base cases:
   - If `x == 0`, return 0 (0 raised to any power is 0).
   - If `n == 0`, return 1 (any number raised to the power 0 is 1).
3. Recursive step:
   - Calculate `x^(n/2)` recursively.
   - If `n` is even, the result is `(x^(n/2))^2`.
   - If `n` is odd, the result is `(x^(n/2))^2 * x`.
4. Handle negative exponents:
   - Convert `n` to a positive value using `abs((long long)n)` to avoid overflow for `INT_MIN`.
   - If `n` is negative, return the reciprocal of the result.

### Notes:
- This approach is efficient and avoids overflow issues by using `long long` for `n`.
- It handles edge cases like `x = 0`, `n = 0`, and `n = INT_MIN` correctly.
*/

// 1. Naive approach using a loop
// Time Complexity: O(n)
// Space Complexity: O(1)


// 2. Using recursion to calculate power
// Time Complexity: O(log n)
// - The recursion divides the problem size by 2 at each step, resulting in a logarithmic number 
// of recursive calls.

// Space Complexity: O(log n)
// - The recursion stack can go as deep as log n due to the division by 2 at each step.

class Solution {
    double powRec(double x, long long n) {
        if(x == 0) return 0;                        // Base case: 0^n = 0
        if(n == 0) return 1;                        // Base case: x^0 = 1 i.e. any number raised to 0 is 1
        double res = powRec(x, n / 2);              // Recursively calculate x^(n/2)
        if(n % 2 == 0) res = res * res;             // If n is even, result is res^2
        else res = res * res * x;                   // If n is odd, multiply by x once more
        return res;
    }
public:
    double myPow(double x, int n) {
        // negation of -2147483648 i.e. INT_MIN cannot be represented in type 'int' hence use long long
        double res = powRec(x, abs((long long)n));  // Calculate power for the absolute value of n
        return (n < 0) ? 1 / res : res;             // If n is negative, return the reciprocal
    }
};

/*
Dry run for myPow(2, 7):

1. Call powRec(2, 7)
  - n=7 is not 0, x=2 is not 0
  - Call powRec(2, 7/2) = powRec(2, 3)
    
    2. Call powRec(2, 3)
       - n=3 is not 0, x=2 is not 0
       - Call powRec(2, 3/2) = powRec(2, 1)
       
       3. Call powRec(2, 1)
          - n=1 is not 0, x=2 is not 0
          - Call powRec(2, 1/2) = powRec(2, 0)
          
          4. Call powRec(2, 0)
             - n=0, so return 1
          
          - res = 1
          - n=1 is odd, so res = 1 * 1 * 2 = 2
          - Return res = 2
       
       - res = 2
       - n=3 is odd, so res = 2 * 2 * 2 = 8
       - Return res = 8
    
    - res = 8
    - n=7 is odd, so res = 8 * 8 * 2 = 128
    - Return res = 128

2. n=7 is positive, so return res = 128

Time Complexity: O(log n) - We divide n by 2 in each recursive call
Space Complexity: O(log n) - Maximum depth of recursion is log n
*/