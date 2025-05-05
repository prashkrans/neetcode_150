/* LC#238. NCAH7. Product of Array Except Self

### Approach 1: Single-Pass Product Calculation with Zero Handling
Note: There could be three cases:
a. No zeroes in the array: product of all elements except self
b. One zero in the array: if(nums[i] == 0) nums[i] = product of all non-zero elements
                          else if (nums[i] != 0) nums[i] = 0
c. More than one zero in the array: if(nums[i] == 0 || nums[i] != 0) nums[i] = 0

1. Calculate the product of all elements in the array and separately track the product
of all non-zero elements.
2. Count the number of zeroes in the array to handle special cases correctly.
3. If there are multiple zeroes (more than 1), set the non-zero product to zero
since any product except self will contain at least one zero.
4. For each non-zero element, divide the total product by the element itself to
get the product of all elements except that one.
5. For zero elements, use the product of all non-zero elements as the result,
which represents the product of all other elements.
6. This approach efficiently handles edge cases like arrays containing zeroes without requiring
additional memory beyond the input array.
7. The solution has linear time complexity O(n) with constant space complexity O(1)
by reusing the input array for the output.
*/

// 1a. Single-Pass Product Calculation with Zero Handling (my custom code)
// Time Complexity: O(n) where n is the size of nums array | 0ms beats 100%
// Space Complexity: O(1) as we're modifying the input array in-place
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) { // no need to check nums.size() == 0 or 1 as its always greater than 1
        int n = nums.size();                           // Store the size of input array
        int prod = 1;                                  // Variable to store product of all elements
        int prodWithoutZero = 1;                       // Variable to store product of all non-zero elements
        int countZeroes = 0;                           // Counter to keep track of number of zeroes
        for(int i=0; i<n; i++) {                       // Iterate through the array
            prod *= nums[i];                           // Calculate product of all elements
            if(nums[i] != 0) prodWithoutZero *= nums[i]; // Calculate product excluding zeroes
            if(nums[i] == 0) countZeroes++;            // Count number of zeroes in the array
        }
        if(countZeroes > 1) prodWithoutZero = 0;       // If more than one zero exists, all products will be zero
        for(int i=0; i<n; i++) {                       // Second pass to populate result
            if(nums[i] != 0) nums[i] = prod / nums[i]; // For non-zero elements, divide total product by the element
            else nums[i] = prodWithoutZero;            // For zero elements, use product of all non-zero elements
        }
        return nums;                                   // Return the modified array as result
    }
};

/*
### Approach: Single-Pass Product Calculation with Zero Handling
1. Calculate the product of all non-zero elements in the array and count the number of zeroes.
2. Handle three cases:
   a. If there are no zeroes, the result for each element is the total product divided by the element itself.
   b. If there is exactly one zero, the result for the zero element is the product of all non-zero elements, and all other elements are 0.
   c. If there are more than one zero, the result for all elements is 0.
3. Iterate through the array twice:
   a. First pass: Calculate the product of non-zero elements and count zeroes.
   b. Second pass: Compute the result for each element based on the number of zeroes.
4. This approach avoids division by zero and handles edge cases efficiently.
5. The solution has linear time complexity O(n) and constant space complexity O(1) by modifying the input array in-place.
*/

// 1b. Single-Pass Product Calculation with Zero Handling (My custom code) (Prefer this over 1a)
// Time Complexity: O(2n) ~ O(n) where n is the size of nums array | 0ms beats 100%
// - The first loop iterates through the array to calculate the product of non-zero elements and count zeroes.
// - The second loop iterates through the array to compute the result for each element.
// - Overall complexity is O(n), where n is the size of the input array.

// Space Complexity: O(1)
// - The solution modifies the input array in-place and uses only a few extra variables.

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();                                // Size of the input array
        int prodWithoutZeroes = 1;                          // Product of all non-zero elements
        int countZeroes = 0;                                // Count of zeroes in the array
        for(int i=0; i<n; i++) {                            // First pass: Calculate product and count zeroes
            if(nums[i] != 0) prodWithoutZeroes *= nums[i];  // Multiply non-zero elements
            else countZeroes++;                             // Increment zero count
        }
        for(int i=0; i<n; i++) {                            // Second pass: Compute result for each element
            if(nums[i] != 0) {                              // If the element is non-zero
                if(countZeroes == 0) 
                    nums[i] = prodWithoutZeroes / nums[i];  // Divide product by the element
                else nums[i] = 0;                           // If there is a zero, result is 0 for non-zero elements
            } else {  // if(nums[i] == 0)                   // If the element is zero
                if(countZeroes == 1) 
                    nums[i] = prodWithoutZeroes;            // If only one zero, result is the product of non-zero elements
                else nums[i] = 0;                           // If more than one zero, result is 0
            }
        }
        return nums;                                        // Return the modified array
    }
};



/*
### Approach 2: Prefix and Suffix Products
1. Create three vectors: the result vector and two auxiliary vectors for storing
prefix and suffix products.
2. Initialize prefix and suffix arrays with 1s as the base multiplier since
multiplying by 1 doesn't change values.
3. Calculate prefix products where each element at index i contains the product
of all elements from index 0 to i-1.
4. Calculate suffix products where each element at index i contains the product
of all elements from index i+1 to n-1.
5. For each position i, the product of all numbers except nums[i] is simply
prefixProd[i] * suffixProd[i].
6. This approach avoids division operations completely, which is helpful when dealing
with arrays that might contain zeroes.
7. The solution has linear time complexity O(n) with linear space complexity
O(n) for the auxiliary arrays.
8. This prefix-suffix approach efficiently handles the problem without requiring special
edge case handling for zeroes.
*/
// 2. Prefix and Suffix Products
// Time Complexity: O(3n) ~ O(n) where n is the size of nums array | 0ms beats 100%
// Space Complexity: O(3n) ~ O(n) for storing prefix, suffix, and answer arrays

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();                                    // Store the size of input array
        vector<int> ans, prefixProd(n, 1), suffixProd(n, 1);    // Initialize result and product arrays with 1s
        
        for(int i=1; i<n; i++)                                  // Calculate prefix products starting from index 1
            prefixProd[i] = nums[i-1] * prefixProd[i-1];        // Each element stores product of all elements to its left
        
        for(int i=n-2; i>=0; i--)                               // Calculate suffix products starting from second-last element
            suffixProd[i] = nums[i+1] * suffixProd[i+1];        // Each element stores product of all elements to its right

        // for(auto i: prefixProd) cout<<i<<" "; cout<<endl;    // Debug print for prefix products
        // for(auto j: suffixProd) cout<<j<<" "; cout<<endl;    // Debug print for suffix products

        for(int i=0; i<n; i++) ans.push_back(prefixProd[i] * suffixProd[i]); // Combine prefix and suffix products
        return ans;                                             // Return the result array
    }
};