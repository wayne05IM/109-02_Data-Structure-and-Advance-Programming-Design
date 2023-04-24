#include <iostream>

using namespace std;

void oddOrEven(int n) {
    if (n <= 0)
        return;
    oddOrEven(n-2);
    cout << n << ' ';
}

int main()
{
    int range;
    // [*] Input must larger than 1
    while (cin >> range)
    {
        if (range <= 1 && !cin.good()) {
            break;
        }
        if (range & 1) {
            oddOrEven(range-1);
            cout << '\n';
            oddOrEven(range);
            cout << '\n';
        } else {
            oddOrEven(range);
            cout << '\n';
            oddOrEven(range-1);
            cout << '\n';
        }
    }
    return 0;
}