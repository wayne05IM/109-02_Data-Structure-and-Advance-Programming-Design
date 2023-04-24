#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int hamNum = 0, strdoor = 0, trials = 0;
    while (cin >> hamNum >> strdoor >> trials)
    {
        //input
        priority_queue<int> hamQueue;
        for(int i = 0; i < hamNum; i++)
        {
            int temp = 0;
            cin >> temp;
            hamQueue.push(temp);
        }
        //destroy
        int attackNum = -1;
        for(int j = 0; j < trials; j++)
        {
            int temp2 = hamQueue.top();
            strdoor -= temp2;
            hamQueue.push(temp2 / 2);
            hamQueue.pop();
            if(strdoor <= 0)
            {
                attackNum = j + 1;
                break;
            }
        }
        //output
        cout << attackNum << "\n";
    }
    return 0;
}