// LC#2013. NCMG8. Detect Squares

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */

 /*
### Appoach: Hash Map for Point Counting and Square Properties
1. Create a hash map to store the count of points at each coordinate.
2. Implement the `add` method to add a point to the hash map.
3. Implement the `count` method to count the number of squares formed with the given point.
    3.1. For each point in the hash map, check if it can form a square with the given point 
        i.e. abs(x1 - x2) == abs(y1 - y2) && x1 != x2 && y1 != y2.
    3.2. If a square can be formed, check if the other two points exist in the hash map which
        p3: {x1, y2} and p4: {x2, y1}.
    3.3. If they exist, multiply the counts of the point2, point3 and point4 to get the number of 
    squares formed.
    3.4. Return the total count of squares formed with the given point.
4. The time complexity of the `add` method is O(logn) not O(1) and the `count` method is O(n), 
    where n is the number of points in the hash map.
*/

// Time Complexity: add() - O(logn) for inserting a point into the map and count() - O(n) for counting squares.
// Space Complexity: O(n), for storing the points in the map.

class DetectSquares {
    map<pair<int, int>, int> points;                         // Map to store the frequency of each point.
public:
    DetectSquares() {}                                       // Constructor initializes the DetectSquares object.

    void add(vector<int> point) {                            // Adds a point to the map.
        points[{point[0], point[1]}]++;                      // Increment the count of the point in the map.
    }

    int count(vector<int> point) {                           // Counts the number of squares that can be formed.
        int ans = 0;                                         // Initialize the result to 0.
        int x1 = point[0];                                   // Extract the x-coordinate of the given point.
        int y1 = point[1];                                   // Extract the y-coordinate of the given point.
        for(auto p: points) {                                // Iterate through all points in the map.
            pair<int, int> point2 = p.first;                 // Extract the current point from the map.
            int x2 = point2.first;                           // Extract the x-coordinate of the current point.
            int y2 = point2.second;                          // Extract the y-coordinate of the current point.
            if(abs(x2 - x1) == abs(y2 - y1) && x1 != x2 && y1 != y2) { // Check if the points form a diagonal of a square.
                pair<int, int> point3 = {x1, y2};            // Calculate the third point of the square.
                pair<int, int> point4 = {x2, y1};            // Calculate the fourth point of the square.
                if(points.find(point3) != points.end()       // Check if the third point exists in the map.
                    && points.find(point4) != points.end()) {// Check if the fourth point exists in the map.
                    ans +=  points[point2] * points[point3] * points[point4]; // Multiply the counts of all points.
                }
            }
        }
        return ans;                                          // Return the total number of squares.
    }
};
