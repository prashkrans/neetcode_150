// LC#994. NCG4. Is Oranges Rotting
// Note: This question is similar to walls and gates (LC#286)

// Method 1. First add all the rotten oranges in a queue and count the no. of fresh oranges 
// and use BFS along with for loop for current level size to keep a track of minutes. 

// So, one additional loop to count fresh oranges and push rotten oranges apart from BFS is used here
// Running time: O(n*m) not O(k*n*m) where k = no. of rotten oranges
// Auxiliary space: O(n*m) due to queue

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        queue<pair<int, int>> q;
        // vector<vector<int> time(grid); This 2D array is not required here as we need to return only min minutes spent but is useful in debugging

        int countFresh = 0;
        for (int i=0; i<n; i++) {
            for(int j=0; j<m; j++) {
                if(grid[i][j] == 1) countFresh++;
                else if(grid[i][j] == 2)
                    q.push({i, j});
            }
        }

        if (countFresh==0) return 0; // no fresh oranges found so time taken is zero
        
        int minutes = 0;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        while(!q.empty()) {
            int currLevelSize = q.size();                   // Get the current level queue size one line above the for loop
            for(int k=0; k<currLevelSize; k++) {            // Don't use for(int k=0; k<q.size(); k++) as q size would vary while in the for loop
                int ui = q.front().first;
                int uj = q.front().second;
                q.pop();
                for (auto dir: dirs) {
                    int vi = ui + dir[0];
                    int vj = uj + dir[1];
                    if(vi>=0 && vi<n && vj>=0 && vj<m && grid[vi][vj]==1) { // if isValid, traversable (if grid[vi][vj] == 0 or 2) and not visited (not -1)
                        q.push({vi, vj});
                        grid[vi][vj] = -1;  // marked as visited
                        // time[vi][vj] = minutes+1; // This is actually not required 
                        countFresh--;       // since a fresh orange has turned rotten reduce fresh oranges by 1
                    }
                }
            }
            minutes++; // It gets increment by one at the last loop
        }
        minutes--;
        return (countFresh == 0) ? minutes : -1; 
        // if fresh oranges > 0 => no path exists from a rotten orange to one or many fresh oranges then return -1
    }
};


// Method 2. Multisource BFS and dist[child] = dist[parent] + 1
// Incomplete - TODO: fix it later

class Solution {
    int bfs(int i, int j, int m, int n, vector<vector<int>> &dist) {
        int maxTime = INT_MIN;
        queue<pair<int, int>> q;
        vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        q.push({i, j});
        while(!q.empty()) {
            pair<int, int> u = q.front();
            int ui = u.first, uj = u.second;
            q.pop();
            for(int k=0; k<4; k++) {
                pair<int, int> v = {u.first + dirs[k][0], u.second + dirs[k][1]};
                int vi = v.first, vj = v.second;
                if(vi >= 0 && vi < m && vj >= 0 && vj < n && dist[vi][vj] != -1 && dist[vi][vj] >= 1 + dist[ui][uj]) {
                    // count--;
                    dist[vi][vj] = 1 + dist[ui][uj];
                    maxTime = max(maxTime, dist[vi][vj]);
                    q.push({vi, vj});
                }
            } 
        }
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) if(dist[i][j] == INT_MAX) return INT_MAX;
        }
        cout<<"maxTime: "<<maxTime<<endl;
        return (maxTime == INT_MIN) ? INT_MAX : maxTime + 1;
    }
    
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int ans = INT_MAX;
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        int countFreshOranges = 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 0 || grid[i][j] == 2) dist[i][j] = -1;
                else if(grid[i][j] == 1) countFreshOranges++;
            }
        }
        if(countFreshOranges == 0) return 0;
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == 2) {
                    ans = min(ans, bfs(i, j, m, n, dist));
                }
            }
        }
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                cout<<dist[i][j]<<" ";
                if(dist[i][j] == INT_MAX) return -1;
            }
            cout<<endl;
        }
        return ans;
    }
};