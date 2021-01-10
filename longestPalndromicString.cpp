#include <iostream>
#include <string.h>

using namespace std;

class Solution {
public:
    string longest(string strings[], int total) {
        int l = 0;
        string ans = "";
        for(int i = 0; i < total; ++i) {
            if(strings[i].length() > l) {
                ans = strings[i];
                l = strings[i].length();
            }
        }
        return ans;
    }
    
    string palindrome(string s, int i) {
        //check for odd palindromes
        string odd = "";
        int j = i - 1;
        int k = i + 1;
        while(j >= 0 && k <= (s.length() - 1)) {
            if(s[j] != s[k])
                break;
            --j;
            ++k;
        }
        odd = s.substr(j + 1, (k - 1) - (j + 1) + 1);
        
        //check for even palindromes on left side
        int evenCountLeft = 0;
        string evenLeft;
        j = 0;
        k = i;
        while(j <= k) {
            if(s[j] == s[k])
                ++evenCountLeft;
            else
                evenCountLeft = 0;
            ++j;
            --k;
        }
        evenLeft = s.substr(j - evenCountLeft, (k + evenCountLeft) - (j - evenCountLeft) + 1);
        
        //check for even palindromes on right side
        int evenCountRight = 0;
        string evenRight;
        j = i;
        k = s.length() - 1;
        while(j <= k) {
            if(s[j] == s[k])
                ++evenCountRight;
            else
                evenCountRight = 0;
            ++j;
            --k;
        }
        evenRight = s.substr(j - evenCountRight, (k + evenCountRight) - (j - evenCountRight) + 1);
        string strings[3] = {odd, evenLeft, evenRight};
        return longest(strings, 3);
    }
    
    string longestPalindrome(string s) {
        string strings[s.length()];
        for(int i = 0; i < s.length(); ++i)
            strings[i] = palindrome(s, i);
        return longest(strings, s.length());
    }
};

int main() {

    Solution solution;
    cout << solution.longestPalindrome("ooijdosvsdoirasdsasasaade") << "\n";

    return 0;
}