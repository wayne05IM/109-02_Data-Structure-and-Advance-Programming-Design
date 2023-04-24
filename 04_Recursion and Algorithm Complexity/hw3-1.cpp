#include <iostream>
using namespace std;

// print out all the even numbers
void Even(int &maxNum, int num)
{
    if (num <= maxNum)
    {
        if (num % 2 == 0)
        {
            cout << num << " ";
            Even(maxNum, num + 2);
        }
        else
            Even(maxNum, num + 1);
    }
}

//print out all the odd numbers
void Odd(int &maxNum, int num)
{
    if (num <= maxNum)
    {
        if (num % 2 == 1)
        {
            cout << num << " ";
            Odd(maxNum, num + 2);
        }
        else
            Odd(maxNum, num + 1);
    }
}

int main()
{
    int maxNum = 0;
    while (cin >> maxNum)
    {
        Even(maxNum, 1);
        cout << endl;
        Odd(maxNum, 1);
        cout << endl;
    }
    return 0;
}