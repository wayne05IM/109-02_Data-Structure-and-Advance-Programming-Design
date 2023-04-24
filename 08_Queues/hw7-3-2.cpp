#include <iostream>
#include <queue>
using namespace std;


//main
int main()
{
    //input
    int num = 0;
    while(cin >> num)
    {
        priority_queue<int> numQueue;
        for(int i = 0; i < num; i++)
        {
            int temp = 0;
            cin >> temp;
            numQueue.push(temp);
            if(i >= 2)
            {
                int num1 = numQueue.top();
                numQueue.pop();
                int num2 = numQueue.top();
                numQueue.pop();
                int num3 = numQueue.top();
                numQueue.pop();
                numQueue.push(num1);
                numQueue.push(num2);
                numQueue.push(num3);
                cout << num1 * num2 * num3 << "\n";
            }
        }
    }
    //process

    return 0;
}