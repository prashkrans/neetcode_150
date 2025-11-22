/* LC#939. NCMG8b. Minimum Area Rectangle
TODO: LC#963. Minimum Area Rectangle II (Requires a different approach)

## Condition for rectangles parallel to x and y axes.
If point1 = (x1, y1) then point2 = (x2, y2) s.t. abs(x2 - x1) > 0 && abs(y2 - y1) > 0
If there exists a point2 then point3 = (x1, y2) and point4 = (x2, y1)
If point2 and point3 exists then current area = abs(x2 - x1) * abs(y2 - y1)

## Condition for squares parallel to x and y axes.
If point1 = (x1, y1) then point2 = (x2, y2) s.t. 
    (abs(x2 - x1) == abs(y2 - y1) && abs(x2 - x1) > 0)
    or,
    (abs(x2 - x1) == abs(y2 - y1) && x1 != x2 && y1 != y2)

### Approach: Using a Set to Check for Rectangle Diagonals
1. Store all points in an unordered_set as unique keys. Each key is created by combining
the x and y coordinates of a point into a single 64-bit integer. This allows O(1)
lookups for any point.
2. Iterate over all pairs of points in the input array. For each pair of points, treat
them as diagonally opposite corners of a potential rectangle.
3. For each pair of points:
   a. Check if the x-coordinates and y-coordinates differ. If they do not, the points
cannot form a diagonal of a rectangle.
   b. Calculate the keys for the other two points that would complete the rectangle.
   These points must have the same x and y coordinates as the original points but
swapped.
   c. Use the unordered_set to check if these two points exist in the input. If they
do, calculate the area of the rectangle formed by the four points.
4. Track the minimum area encountered during the iteration. If no rectangle is found,
return 0.
5. The algorithm ensures that each pair of points is processed once, resulting in a
time complexity of O(n^2), where n is the number of points.
*/

// 1. Using a set that first converts a pair<int, int> to a long key then stores it for O(1) lookup
// Time Complexity: O(n^2)
// - Outer loop iterates over all points: O(n)
// - Inner loop iterates over remaining points: O(n) thus, O(n^2)
// - Checking for points in the set: O(1) (amortized)
// - Overall: O(n^2)

// Space Complexity: O(n)
// - Space used by the unordered_set to store all points.

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int minArea = INT_MAX;                          // Initialize minimum area to a large value
        unordered_set<long long> st;                   // Set to store points as unique keys
        for(int i=0; i<points.size(); i++) {           // Iterate over all points
            long long key = (long long) points[i][0] << 32 | points[i][1]; // Create a unique key for each point
            st.insert(key);                            // Insert the point into the set
        }
        for(int i=0; i<points.size(); i++) {           // Iterate over all points again
            int x1 = points[i][0];                     // Extract x-coordinate of the first point
            int y1 = points[i][1];                     // Extract y-coordinate of the first point
            for(int j = i+1; j<points.size(); j++) {   // Iterate over remaining points
                int x2 = points[j][0];                 // Extract x-coordinate of the second point
                int y2 = points[j][1];                 // Extract y-coordinate of the second point
                if(abs(x1 - x2) > 0 && abs(y1 - y2) > 0) { // Check if points form a diagonal of a rectangle
                    long long point3 = (long long) x1 << 32 | y2; // Create key for the third point
                    long long point4 = (long long) x2 << 32 | y1; // Create key for the fourth point
                    if(st.find(point3) != st.end() && st.find(point4) != st.end()) { // Check if both points exist
                        minArea = min(minArea, abs(x1-x2) * abs(y1-y2)); // Update minimum area if rectangle is valid
                    }
                }
            }
        }
        return (minArea == INT_MAX) ? 0 : minArea;      // Return 0 if no rectangle is found, else return min area
    }
};

// 2. Using an ordered set that stores a pair<int, int> for points for O(logn) lookup
// Time Complexity: O(n^2)
// - Outer loop iterates over all points: O(n)
// - Inner loop iterates over remaining points: O(n), resulting in O(n^2)
// - Checking for points in the set: O(log n) for each lookup
// - Overall: O(n^2 * log n)

// Space Complexity: O(n)
// - Space used by the set to store all points.

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        int minArea = INT_MAX;                              // Initialize minimum area to a large value
        set<pair<int, int>> st;                             // Set to store points as unique pairs
        for(int i=0; i<points.size(); i++)                  // Iterate over all points
            st.insert({points[i][0], points[i][1]});        // Insert each point into the set
        for(int i=0; i<points.size(); i++) {                // Iterate over all points again
            int x1 = points[i][0];                          // Extract x-coordinate of the first point
            int y1 = points[i][1];                          // Extract y-coordinate of the first point
            for(int j = i+1; j<points.size(); j++) {        // Iterate over remaining points
                int x2 = points[j][0];                      // Extract x-coordinate of the second point
                int y2 = points[j][1];                      // Extract y-coordinate of the second point
                if(abs(x1 - x2) > 0 && abs(y1 - y2) > 0) {  // Check if points form a diagonal of a rectangle
                    pair<int, int> point3 = {x1, y2};       // Create coordinates for the third point
                    pair<int, int> point4 = {x2, y1};       // Create coordinates for the fourth point
                    if(st.find(point3) != st.end() && st.find(point4) != st.end()) { // Check if both points exist
                        minArea = min(minArea, abs(x1 - x2) * abs(y1 - y2)); // Update minimum area if rectangle is valid
                    }
                }
            }
        }
        return (minArea == INT_MAX) ? 0 : minArea;          // Return 0 if no rectangle is found, else return min area
    }
};