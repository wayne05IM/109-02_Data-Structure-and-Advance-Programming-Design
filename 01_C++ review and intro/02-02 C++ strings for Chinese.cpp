#include <iostream>
#include <string>
using namespace std;

int main()
{
  string s = "�j�a�n";
  int n = s.length(); // 6
  string t = s;
  for(int i = 0; i < n - 1; i = i + 2)
  {
    t[n - i - 2] = s[i];
    t[n - i - 1] = s[i + 1];
  } // good
  cout << t << endl; // �n�a�j
  return 0;
}

