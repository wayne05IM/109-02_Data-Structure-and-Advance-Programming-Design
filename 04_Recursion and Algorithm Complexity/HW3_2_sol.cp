#include <iostream>

using namespace std;

bool checkPalindrome(string s, int start, int end) {
    if (start >= end) {
        return true;
    }
    return s[start] == s[end] && checkPalindrome(s, start+1, end-1);
}

int main()
{
    string s;

    while (cin >> s)
    {
        if (checkPalindrome(s, 0, s.length()-1)) {
            cout << "The entered word is a palindrome.\n";
        } else {
            cout << "The entered word is not a palindrome.\n";
        }
    }
}