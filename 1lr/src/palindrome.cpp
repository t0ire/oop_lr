#include "palindrome.h"

int palindrome(std::string s) {
    for(size_t i = 0; i < s.length(); ++i) {
        if(s[i] == ' ') {
            s.replace(i, 1, "");
        }
        if(int(s[i]) > 64 && int(s[i]) < 91) {
            s[i] += 32;
        }
    }
    int l = 0;
    int r = s.length() - 1;
    while (l < r) {
        if (s[l] == s[r]) {
            l++;
            r--;
        } 
        else {
            return 0;
        }
    }
    return 1;
}