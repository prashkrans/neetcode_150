/* LC#146. NCLL9. LRU Cache

We can use a doubly linked list (head and tail) where key-value pairs are stored as nodes, with the least recently used (LRU) 
node at the head and the most recently used (MRU) node at the tail. Whenever a key is accessed using get() or put(), 
we remove the corresponding node and reinsert it at the tail. When the cache reaches its capacity, we remove 
the LRU node from the head of the list. Additionally, we use a hash map to store each key and the corresponding address 
of its node, enabling efficient operations in O(1) time.

*/

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

 /**
* LRU Cache Analysis Summary:
* 
* Time Complexity:
* - Constructor: O(1)
* - get(): O(1) - Hash map lookup + constant-time pointer operations
* - put(): O(1) - Hash map operations + constant-time list manipulations
* 
* Space Complexity:
* - Overall: O(capacity) - Stores up to 'capacity' nodes and hash map entries
* 
* Key Optimizations:
* - Dummy head/tail nodes eliminate edge cases
* - Hash map enables O(1) lookups
* - Pure pointer operations (no data copying)
* - Efficient LRU tracking (recent near tail, old near head)
*/

// 1. Using a doubly linked list
// put(): O(1) | get(): O(1)
// O(capacity) 

struct Node { // Struct for a doubly linked list
    int key;        // Key to identify the node
    int val;        // Value stored in the node
    Node *prev;     // Pointer to previous node
    Node* next;     // Pointer to next node
    Node(): key(-1), val(-1), prev(nullptr), next(nullptr) {}  // Default constructor
    Node(int _key, int _val): key(_key), val(_val), prev(NULL), next(NULL) {}  // Parameterized constructor
};


class LRUCache {
    int capacity;   // Maximum number of elements the cache can hold
    Node* head;     // Dummy head node for easier list operations
    Node* tail;     // Dummy tail node for easier list operations
    unordered_map<int, Node*> cache;  // Hash map to store key-node pairs for O(1) lookup

    void remove(Node* node) {  // Remove a node from the linked list
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;    // Update previous node's next pointer
        nextNode->prev = prevNode;    // Update next node's prev pointer
        // don't use delete node yet   // Node is only unlinked, not freed
    }

    void insertBeforeTail(Node* node) {  // Insert a node before tail (most recently used position)
        Node* beforeTail = tail->prev;
        beforeTail->next = node;      // Update previous node's next
        node->next = tail;            // Set node's next to tail
        node->prev = beforeTail;      // Set node's prev to previous node
        tail->prev = node;            // Update tail's prev to node
    }

public:
    LRUCache(int capacity) {  // Constructor
        this->capacity = capacity;
        
        // Adding dummy head and tail nodes makes are our life much easier. Connect them after initializing them.
        head = new Node(0, 0);        // Dummy head node
        tail = new Node(0, 0);        // Dummy tail node
        head->next = tail;            // Connect head to tail initially
        tail->prev = head;            // Connect tail to head initially

        cache = unordered_map<int, Node*>();  // Initialize empty hash map
    }
    
    int get(int key) {  // Get value by key
        if(cache.find(key) == cache.end()) return -1;  // Return -1 if key not found
        Node* node = cache[key];      // Get node from cache
        remove(node);                 // Remove node from current position
        insertBeforeTail(node);       // Move node to most recently used position
        return node->val;             // Return the value
    }
    
    void put(int key, int value) {  // Insert or update key-value pair
        if(cache.find(key) != cache.end()) {  // If key exists, update value
            Node* node = cache[key];
            node->val = value;        // Update value
            remove(node);             // Remove from current position
            insertBeforeTail(node);   // Move to most recently used position
        }
        else {  // If the key doesn't exist and cache is full
            if(cache.size() == capacity) {  // If cache is full, remove least recently used
                Node* lru = head->next;     // LRU node is right after head
                remove(lru);                // Remove LRU node from list
                cache.erase(lru->key);      // Remove LRU entry from hash map
                delete lru;                 // Free memory
            }
            // If the key doesn't exist and the cache is not full
            Node* newNode = new Node(key, value);  // Create new node
            insertBeforeTail(newNode);      // Insert at most recently used position
            cache[key] = newNode;           // Add to hash map
        }   
    }
};

// 2. Better than Method 3. since O(log n) for put and get due to min-heap using a set

// Time Complexity:
// - Constructor: O(1)
// - get(key): O(log n) - Due to set operations in updateTime()
// - put(key, value): O(log n) - Due to set operations in updateTime() and eviction
// - updateTime(): O(log n) - Finding, erasing, and inserting in ordered set

// Space Complexity:
// - O(capacity) - Storing elements in cache, time mapping, and ordered set

class LRUCache {
    int capacity;                       // Maximum number of key-value pairs the cache can hold
    int timestamp;                      // Global counter to track recency of access
    unordered_map<int, int> cache;      // Stores key-value pairs
    unordered_map<int, int> time;       // Maps keys to their timestamps
    set<pair<int, int>> minHeap;        // Ordered set that acts as a min heap {timestamp, key}

    void updateTime(int key) {
        int prevTimestamp = time[key];                            // Get previous timestamp for the key
        int newTimestamp = timestamp++;                           // Generate new timestamp and increment counter
        if(minHeap.find({prevTimestamp, key}) != minHeap.end())   // Find and remove old timestamp entry
            minHeap.erase({prevTimestamp, key});
        minHeap.insert({newTimestamp, key});                      // Insert new timestamp entry
        time[key] = newTimestamp;                                 // Update timestamp map
    }
public:
    LRUCache(int capacity) {
        this->capacity = capacity;                // Set cache capacity
        timestamp = 0;                            // Initialize timestamp counter
        cache = unordered_map<int, int>();        // Initialize key-value cache
        time = unordered_map<int, int>();         // Initialize timestamp tracking
        minHeap = set<pair<int, int>>();          // Initialize ordered set for LRU tracking
    }
    
    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;   // Return -1 if key not found
        updateTime(key);                                // Update access time for this key
        return cache[key];                              // Return the value for this key
    }
    
    void put(int key, int value) {
        if(cache.find(key) != cache.end()) cache[key] = value;   // If key exists, update value
        else {
            if(cache.size() < capacity) cache[key] = value;      // If cache not full, add new key-value
            else {
                auto it = minHeap.begin();                       // Get least recently used item
                int LRUkey = it->second;                         // Extract the key to evict
                minHeap.erase(it);                               // Remove from ordered set
                time.erase(LRUkey);                              // Remove from timestamp map
                cache.erase(LRUkey);                             // Remove from cache
                cache[key] = value;                              // Insert new key-value pair
            }
        }
       updateTime(key);                                          // Update access time for this key
    }   
};

// 3. My custom code: Using two unordered maps cache and time
// Running time: O(n) for put and O(1) for get.
// Auxiliary space: O(capacity) - Stores at most 'capacity' elements in two hash maps
// Passes all testcases but takes 303 ms time beats 5% in leetcode

class LRUCache {
    int capacity;              // Maximum number of key-value pairs the cache can hold
    int timestamp;             // Global counter to track recency of access
    unordered_map<int, int> cache;  // Stores key-value pairs
    unordered_map<int, int> time;   // Tracks when each key was last accessed
public:
    LRUCache(int capacity) {
        this->capacity = capacity;  // Initialize with given capacity
        this->timestamp = 0;        // Start timestamp at 0
        cache = unordered_map<int, int>();  // Initialize empty cache
        time = unordered_map<int, int>();   // Initialize empty timestamp tracker
    }
    
    // Time: O(1) - Hash map lookup and update
    int get(int key) {
        if(cache.find(key) == cache.end()) return -1;  // Key not found
        time[key] = timestamp++;  // Update access time for this key
        return cache[key];        // Return the value
    }
    
    // Time: O(n) where n is the capacity (due to linear search for LRU item)
    // Could be optimized to O(1) using a min-heap or ordered data structure
    void put(int key, int value) {
        if(cache.find(key) != cache.end()) cache[key] = value;  // Update existing key
        else {
            if(cache.size() < capacity) cache[key] = value;  // Cache not full, just add
            else {
                int lowTime = INT_MAX;  // Find least recently used item
                int lowKey = -1;
                for(auto i: time) {  // Linear search through all timestamps
                    int k = i.first;
                    int t = i.second;
                    if(lowTime > t) {
                        lowTime = t;
                        lowKey = k;
                    }
                }
                time.erase(lowKey);    // Remove LRU item from time tracker
                cache.erase(lowKey);   // Remove LRU item from cache
                cache[key] = value;    // Add new item to cache
            }
        }
        time[key] = timestamp++;  // Update access time for this key
    }   
};


