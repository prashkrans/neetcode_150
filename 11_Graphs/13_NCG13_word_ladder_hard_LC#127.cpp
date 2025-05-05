/** LC#127. NCG11. Word Ladder [Hard]

Approach:
Hint 1:
Consider the given problem in terms of a graph, treating strings as nodes. Think of a way to build edges where two strings 
have an edge if they differ by a single character. A naive approach would be to consider each pair of strings and check 
whether an edge can be formed. Can you think of an efficient way? For example, consider a string hot and think about the 
strings that can be formed from it by changing a single letter.

Hint 2:
To efficiently build edges, consider transforming each word into intermediate states by replacing one character with a 
wildcard, like *. For example, the word hot can be transformed into *ot, h*t, and ho*. These intermediate states act as 
"parents" that connect words differing by one character. For instance, *ot can connect to words like cot. For each word 
in the list, generate all possible patterns by replacing each character with * and store the word as a child of these 
patterns. We can run a BFS starting from the beginWord, visiting other words while avoiding revisiting by using a hash set.

Hint 3:
Refer Noteful Notes (DSA Revision 2025)
Add beginWord to parentMap

Running time: O((m*(m-1)/2)*n) where m = length of each word and n = total number of words in the wordList
            => O(m^2*n) ~ O(m^3) since m = n+1 

Auxiliary space: O(m^2*n) due to parentMap 

**/

// Method 1a. Using iterators instead of auto and a dist array
class Solution {
    public:
        void mapStrings(string s, unordered_map<string, vector<string>> &parentMap) {
            for(int i=0; i<s.size(); i++) {
                string parentS = s;
                parentS[i] = '*';
                parentMap[parentS].push_back(s);
            }
        }
    
        int bfsDistance(string src, string dest, unordered_map<string, vector<string>> &adjList) {
            unordered_map<string, int> visited;
            unordered_map<string, int> dist;
            queue<string> q;
            q.push(src);
            visited[src] = 1;
            dist[src] = 1;  // This is generally zero but here we need dist + 1;
            while(!q.empty()) {
                string u = q.front();
                q.pop();
                for(vector<string>::iterator it = adjList[u].begin(); it!=adjList[u].end(); ++it) {
                    string v = *it;
                    if(visited.count(v)==0) {
                        q.push(v);
                        visited[v] = 1;
                        dist[v] = dist[u] + 1;
                        if(v==dest) return dist[dest];
                    }
                }
            }
            return 0;        
        }
    
        int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
            unordered_map<string, vector<string>> parentMap;
            bool isEndWordPresent = false;
            mapStrings(beginWord, parentMap);
            for(auto s: wordList) {
                mapStrings(s, parentMap);
                if(s == endWord) isEndWordPresent = true;
            }
            if(!isEndWordPresent) return 0;
            
            // for(auto i: parentMap) {
            //     cout<<i.first<<" -> ";
            //     for(auto node: i.second) {
            //         cout<<node<<", ";
            //     }
            //     cout<<endl;
            // }
    
            unordered_map<string, vector<string>> adjList;
            for(unordered_map<string, vector<string>>::iterator it = parentMap.begin(); it!=parentMap.end(); ++it) {
                vector<string> stringList = it->second;
                int size = stringList.size();
                if(size > 1) {
                    for(int i=0; i<size; i++) {
                        for(int j=i+1; j<size; j++) {
                            string u = stringList[i];
                            string v = stringList[j];
                            adjList[u].push_back(v);
                            adjList[v].push_back(u);
                        }
                    }
                }
            }
    
            // for(auto i: adjList) {
            //     cout<<i.first<<" -> ";
            //     for(auto j: i.second) cout<<j<<", ";
            //     cout<<endl;
            // }
    
            return bfsDistance(beginWord, endWord, adjList);
        }
    };

// Method 1b. UIsing dist variable instead of dist array and auto keywords

class Solution {
    public:
        void mapStrings(string s, unordered_map<string, vector<string>> &parentMap) {
            for(int i=0; i<s.size(); i++) {
                string parentS = s;
                parentS[i] = '*';
                parentMap[parentS].push_back(s);
            }
        }
    
        int bfsDistance(string src, string dest, unordered_map<string, vector<string>> &adjList) {
            unordered_map<string, int> visited;
            // unordered_map<string, int> dist;
            queue<string> q;
            q.push(src);
            visited[src] = 1;
            int dist = 1;   // This is generally zero but here we need dist + 1;
            // dist[src] = 1;  // This is generally zero but here we need dist + 1;
            while(!q.empty()) {
                int qSize = q.size(); 
                for(int i=0; i<qSize; i++) {
                    string u = q.front();
                    q.pop();
                    for(auto v: adjList[u]) {
                        if(visited.count(v)==0) {
                            q.push(v);
                            visited[v] = 1;
                            // dist[v] = dist[u] + 1;
                            if(v==dest) return dist+1;
                            // if(v==dest) return dist[dest];
                        }
                    }
                }
                dist++;
            }
            return 0;        
        }
    
        int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
            unordered_map<string, vector<string>> parentMap;
            bool isEndWordPresent = false;
            mapStrings(beginWord, parentMap);
            for(auto s: wordList) {
                mapStrings(s, parentMap);
                if(s == endWord) isEndWordPresent = true;
            }
            if(!isEndWordPresent) return 0;
    
            unordered_map<string, vector<string>> adjList;
            for(auto x: parentMap) {
                vector<string> stringList = x.second;
                int size = stringList.size();
                if(size > 1) {
                    for(int i=0; i<size; i++) {
                        for(int j=i+1; j<size; j++) {
                            string u = stringList[i];
                            string v = stringList[j];
                            adjList[u].push_back(v);
                            adjList[v].push_back(u);
                        }
                    }
                }
            }
    
            return bfsDistance(beginWord, endWord, adjList);
        }
    };