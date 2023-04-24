#include <iostream>
using namespace std;


//main
int main()
{
    //input
    int num = 0;
    while(cin >> num)
    {
        int* numArray = new int[num + 1];
        for(int i = 1; i <= num; i++)
            cin >> numArray[i];
    }
    //process

    return 0;
}