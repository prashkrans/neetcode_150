#include<iostream>
#include<climits>
using namespace std;


int stringToInt(string s) {
    if(s == "#") return INT_MAX;
    int n = s.size();
    int i = (s[0] == '-') ? 1 : 0;
    int ans = 0;
    while(i<n) ans = ans*10 + (s[i++] - '0');
    return (s[0] == '-') ? -1*ans : ans;
}


int main() {
    string s;
    cin>>s;
    cout<<s<<" == "<<stringToInt(s)<<endl;
    return 0;
}