/* LC#355. NCPQ7. Design Twitter
TODO - improve the solution

This is a design problem. The goal is to implement a Twitter-like system with the following functionalities:
1. postTweet(userId, tweetId): User posts a new tweet with the given tweetId.
2. getNewsFeed(userId): Retrieve the 10 most recent tweetIds in the user's news feed. Each item in the news feed must be posted by users that the user followed or by the user themselves. Tweets must be ordered from most recent to least recent.
3. follow(followerId, followeeId): User with followerId follows the user with followeeId.
4. unfollow(followerId, followeeId): User with followerId unfollows the user with followeeId.

Note: feedMap is actually not required to be stored in the class. It can be generated on the 
fly when getNewsFeed is called. However, for the sake of this implementation, we are storing it 
to avoid recalculating the feed every time.

Space and Time Complexity Analysis:

Data Structures:
- followMap: O(u + f) space
- tweetMap: O(u + t) space
- feedMap: O(u * k) space

Time Complexities:
1. postTweet(userId, tweetId):
   - Time: O(1) for adding a tweet to the vector
   - No feed updates are triggered, so it's very efficient

2. follow(followerId, followeeId):
   - Time: O(log f) for the set insertion operation
   - No feed updates are triggered

3. unfollow(followerId, followeeId):
   - Time: O(log f) for finding and erasing from set
   - No feed updates are triggered

4. getNewsFeed(userId):
   - Calls updateFeedMap which does:
     - O(f) to get and process set of followed users
     - O(t' * log k) where t' is total tweets from followed users (for min heap operations)
     - O(k * log k) for min to max heap transfer
   - Converting queue to vector: O(k)
   - Overall: O(f + t' * log k)

If k = 10 (as in this implementation): 
   - The log k factor becomes essentially constant
   - getNewsFeed complexity is approximately O(f + t')

If k is variable:
   - The complexity remains O(f + t' * log k)

Total Space Complexity: O(u + f + t + u*k)

Where:
u = number of users
f = number of follow relationships
t = total number of tweets
t' = total tweets from followed users
k = max tweets per feed (k = 10 in this implementation)

*/

// Note: this could be further optimized but it passes all the test cases for now.
// E.g. use vector for tweetMap since we don't want lookup and unordered_set doesn't work with pair<int, int>
// But use set<int> for followup as we need O(1) lookup

class Twitter {
    int timestamp;                                   // Global counter for ordering tweets chronologically
    map<int, set<int>> followMap;                    // Maps users to the set of users they follow
    map<int, vector<pair<int, int>>> tweetMap;       // Maps users to their tweets (timestamp, tweetId)
    map<int, priority_queue<pair<int, int>>> feedMap; // Maps users to their cached news feeds
    
    void print(map<int, vector<pair<int, int>>> &mp) {  // Debug helper to print tweet maps
        for(auto i: mp) {
            cout<<i.first<<" -> ";
            for(auto j: i.second) cout<<"{time: "<<j.first<<", tweetId: "<<j.second<<"} ";
            cout<<endl;
        }
    }

    void print(map<int, set<int>> &mp) {             // Debug helper to print follow relationships
        for(auto i: mp) {
            cout<<i.first<<" -> ";
            for(auto j: i.second) cout<<j<<" ";
            cout<<endl;
        }
    }

    void print(set<int> &st) {                       // Debug helper to print sets
        for(auto i: st) cout<<i<<" "; cout<<endl;
    }
    
    void updateFeedMap(int userId) {                 // Regenerates news feed for a user
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // Min heap for selecting top 10
        set<int> usersInFeed = followMap[userId];    // Get all users being followed
        usersInFeed.insert(userId);                  // Include user's own tweets
        // cout<<"User: "<<userId<<" has news feed containing the following users:"<<endl;
        // print(usersInFeed);
        for(auto user: usersInFeed) {                // Collect tweets from all relevant users
            vector<pair<int, int>> tweetsByUser = tweetMap[user];
            for(auto tweet: tweetsByUser) {
                minHeap.push(tweet);                 // Add tweet to min heap
                if(minHeap.size()>10) minHeap.pop(); // Keep only 10 most recent tweets (removes oldest)
            }
        }
        priority_queue<pair<int, int>> maxHeap;      // Max heap to reverse order (newest first)
        while(!minHeap.empty()) {                    // Transfer from min heap to max heap
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
        feedMap[userId] = maxHeap;                   // Store the prepared feed
    }

public:
    Twitter() {                                      // Constructor initializes all data structures
        timestamp = 0;
        followMap = map<int, set<int>>();
        tweetMap = map<int, vector<pair<int, int>>>();
        feedMap = map<int, priority_queue<pair<int, int>>>();
    }
    
    void postTweet(int userId, int tweetId) {        // Add a new tweet for a user
        tweetMap[userId].push_back({timestamp++, tweetId}); // Associate with current timestamp and increment
        // cout<<"User: "<<userId<<" posted a tweet with id: "<<tweetId<<" at time: "<<timestamp<<"\n";
        // print(tweetMap);
    }
    
    vector<int> getNewsFeed(int userId) {            // Get 10 most recent tweets from followed users and self
        updateFeedMap(userId);                       // Ensure feed is current
        vector<int> newsFeed;                        // Will hold tweet IDs to return
        priority_queue<pair<int, int>> userIdFeed = feedMap[userId];
        while(!userIdFeed.empty()) {                 // Convert queue to vector
            newsFeed.push_back(userIdFeed.top().second); // Extract tweet ID only
            userIdFeed.pop();
        }
        return newsFeed;                             // Return the news feed
    }
    
    void follow(int followerId, int followeeId) {    // Add a follow relationship
        followMap[followerId].insert(followeeId);    // User starts following another user
        // cout<<"Follow: "; print(followMap);
    }
    
    void unfollow(int followerId, int followeeId) {  // Remove a follow relationship
        if(followMap[followerId].find(followeeId) != followMap[followerId].end()) 
            followMap[followerId].erase(followeeId); // Remove followee if exists
        // cout<<"Unfollow: "; print(followMap);
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */