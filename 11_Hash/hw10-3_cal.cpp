#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    float m = 1000;
    float A = (sqrt(5) - 1) / 2;
    float a = 0;
    cin >> a;
    cout << floor(m * fmod(a * A, 1));
    return 0;
}