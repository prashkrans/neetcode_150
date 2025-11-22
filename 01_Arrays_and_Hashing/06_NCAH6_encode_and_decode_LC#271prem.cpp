/* LC#217Premium NCAH6. Encode and Decode Strings 

1. A naive solution would be to use a non-ascii character as a delimiter. Can you think of a better way?

2. We can use an encoding approach where we start with a number representing the length of the string, 
followed by a separator character (let's use # for simplicity), and then the string itself. 
To decode, we read the number until we reach a #, then use that number to read the specified number of 
characters as the string.

*/

// Method 2. Using curr string size + '#' + curr string. E.g. {"new", "places"} => encode as => "3#new6#places"
// O(n*m) where n = size of vector strings and m = length of the longest string in strings
// O(n*m + c*n) where c is a constant (size + '#')

class Solution {
public:
    string encode(vector<string>& strs) {
        string encodedString;
        for(int i=0; i<strs.size(); i++) {
            int size = strs[i].size();
            encodedString += to_string(size) + '#' + strs[i];
        }
        // cout<<"encodedString: "<<encodedString<<endl;
        return encodedString;
    }

    vector<string> decode(string s) {
        vector<string> decodedStrings;
        int i = 0;
        string str;
        while(i < s.size()) {
            str += s[i];
            if(s[i] == '#'){
                int sizeLength = str.size()-1;
                int size = stoi(str.substr(0, sizeLength));
                string curr = s.substr(i+1, size);
                // cout<<sizeLength<<" "<<size<<" "<<curr<<endl;
                decodedStrings.push_back(curr);
                str = "";
                i = i + size;
            }
            i++;
        }
        // for(auto i: decodedStrings) cout<<i<<endl;
        return decodedStrings;
    }
};
