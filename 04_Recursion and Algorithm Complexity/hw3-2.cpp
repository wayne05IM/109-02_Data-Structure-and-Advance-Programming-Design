#include <iostream>
using namespace std;

bool palindromeOrNot(int start, int end, string &s)
{
    if (start >= end)
    {
        return true;
    }
    else
    {
        if (s[start] == s[end])
            return palindromeOrNot(start + 1, end - 1, s);
        else
            return false;
    }
}

int main()
{
    string word;
    while (cin >> word)
    {
        int len = word.length();
        if ((palindromeOrNot(0, len - 1, word) == true) or (len == 0))
            cout << "The entered word is a palindrome." << endl;
        else
            cout << "The entered word is not a palindrome." << endl;
    }
    return 0;
}