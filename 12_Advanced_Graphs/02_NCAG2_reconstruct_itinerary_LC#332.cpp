/**
LC#332. NCAG2. Reconstruct Itinerary

Euler path: The path which visits all the edges once while a node could be visited more than once.

Method 1. Post order DFS
Method 2. Hierholzer's algorithm, a modified DFS approach | verify once

Summary:
Time Complexity: O(E * L * log E) (where E is #tickets, L is max airport code length). 
Or O(E log E) if L is constant. The sorting step is the primary driver.

Space Complexity: O(E * L) (driven by graph storage, result vector, ticket counts, and recursion stack). 
Or O(E) if L is constant.

**/

// Method 1. Using post order DFS + a map for the edges 
// Note: Using a set doesn't cover the edge case as below:
// Tickets: [["EZE","AXA"],["TIA","ANU"],["ANU","JFK"],["JFK","ANU"],["ANU","EZE"],
// ["TIA","ANU"],["AXA","TIA"],["TIA","JFK"],["ANU","TIA"],["JFK","TIA"]]
// Here, ["TIA", "ANU"] is given two times so TIA -> ANU, ANU, JFK (not ANU, JFK) 
// Thus, used a map instead of a set and also the adjL should be a map of vector not a map of set

// Running time: O(n*(nlogn)) which is O(ElogE) due to sorting where E: no. of edges/tickets
// Auxiliary space: O(E) due to the edges map

class Solution {
    // void dfs(string u, map<string, set<string>> &adjL, vector<string> &ans, set<pair<string, string>> &st) {
    void dfs(string u, map<string, vector<string>> &adjL, vector<string> &ans, map<pair<string, string>, int> &mp) {
        for(auto v: adjL[u]) {
            // if(st.find({u, v})!=st.end()) {
            //     st.erase({u, v});
            //     dfs(v, adjL, ans, st);
            // }
            if(mp[{u,v}]>0) { // Don't use mp.count({u, v}) > 0 as mp[{u, v}] == 0 is still mp.count({u, v}) > 0
                mp[{u, v}]--;
                dfs(v, adjL, ans, mp);
            }
        }
        ans.push_back(u);
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> ans;
        // map<string, set<string>> adjL;
        map<string, vector<string>> adjL;
        // set<pair<string, string>> st;
        map<pair<string, string>, int> mp;
        // for(auto i: tickets) st.insert({i[0], i[1]});
        for(auto i: tickets) mp[{i[0], i[1]}]++;
        for(int i=0; i<tickets.size(); i++) {
            string u = tickets[i][0];
            string v = tickets[i][1];
            // adjL[u].insert(v); // directed edge
            adjL[u].push_back(v); // directed edge
            // if(adjL.count(v)==0) adjL[v] = set<string>();
            if(adjL.count(v)==0) adjL[v] = vector<string>();
        }
        for(auto i: adjL) {
            string u = i.first;
            // cout<<u<<" -> ";
            sort(adjL[u].begin(), adjL[u].end());
            // for(auto v: adjL[u]) cout<<v<<" ";
            // cout<<endl;
        }
        // dfs("JFK", adjL, ans, st);
        dfs("JFK", adjL, ans, mp);
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
