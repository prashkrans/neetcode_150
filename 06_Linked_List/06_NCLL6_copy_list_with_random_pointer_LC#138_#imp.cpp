/* LC#138. NCLL6. Copy List with Random Pointer

Note: Whenever we have to deep copy, whether a graph, a tree or a linked list, we need to create a mapping 
of the original nodes to the new nodes. After creating the new nodes, we can set the next and random pointers

### Approach: Hash Map for Node Mapping
1. Use an unordered_map to store a mapping of original nodes to their corresponding new nodes.
2. First pass:
   - Traverse the original list and create a new node for each original node.
   - Store the mapping of the original node to the new node in the unordered_map.
3. Second pass:
   - Traverse the original list again and set the `next` and `random` pointers for each new node using the map.
   - The `next` pointer of the new node is set to the new node corresponding to the `next` pointer of the original node.
   - The `random` pointer of the new node is set to the new node corresponding to the `random` pointer of the original node.
4. Return the head of the new list, which is the mapped node corresponding to the head of the original list.
5. This approach ensures that the `next` and `random` pointers are correctly set in O(n) time.
*/

// 1. Hash Map for Node Mapping (Prefer this approach) (My custom code)

// Time Complexity: O(n)
// - The first loop iterates through the original list to create a mapping of original nodes to new nodes.
// - The second loop iterates through the original list to set the `next` and `random` pointers for the new nodes.
// - Overall complexity is O(n), where n is the number of nodes in the list.

// Space Complexity: O(n)
// - The unordered_map stores a mapping of original nodes to new nodes, which requires O(n) space.

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp;                  // Map to store the mapping of original nodes to new nodes
        Node* curr = head;                               // Pointer to traverse the original list
        while(curr) {                                    // First pass: Create new nodes and map them
            Node* newNode = new Node(curr->val);         // Create a new node with the same value as the current node
            mp[curr] = newNode;                          // Map the original node to the new node
            curr = curr->next;                           // Move to the next node in the original list
        }
        curr = head;                                     // Reset pointer to the head of the original list
        while(curr) {                                    // Second pass: Set the `next` and `random` pointers
            mp[curr]->next = mp[curr->next];             // Set the `next` pointer for the new node
            mp[curr]->random = mp[curr->random];         // Set the `random` pointer for the new node
            curr = curr->next;                           // Move to the next node in the original list
        }
        return mp[head];                                 // Return the head of the copied list
    }
};


// 2. Create a copy linked list without random pointer, simultaneously map original nodes to copy nodes 
// s.t. mp[random] = copied_random
// O(2n) i.e. two passes ~ O(n)
// O(n) due to the recursion stack and the map of size n

class Solution {
    Node* createListAndMap(Node* head, unordered_map<Node*, Node*> &mp) {
        if(head == nullptr) return nullptr;                     // Base case: empty list
        Node* newHead = new Node(head->val);                    // Create new node with same value
        newHead->next = createListAndMap(head->next, mp);       // Recursively build the rest of the list
        mp[head] = newHead;                                     // One to one mapping from original nodes to copy nodes
        return newHead;                                         // Return head of the copied list
    }

public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> mp;                         // Map to track node mapping
        Node* newHead = createListAndMap(head, mp);             // First pass: create list with next pointers
        Node* curr1 = head;                                     // Pointer to original list
        Node* curr2 = newHead;                                  // Pointer to copied list
        while(curr1) {
            if(curr1->random) curr2->random = mp[curr1->random]; // Set random pointer using map
            else curr2->random = nullptr;                        // If no random, set to null
            curr1 = curr1->next;                                 // Move to next node in original
            curr2 = curr2->next;                                 // Move to next node in copy
        }
        return newHead;                                          // Return head of fully copied list
    }   
};