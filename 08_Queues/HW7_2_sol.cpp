#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct _PriorityQueue
{
    vector<int> pq;
    void enQueue(int node)
    {
        pq.insert(
            upper_bound(pq.begin(), pq.end(), node),
            node);
    }
    int deQueue()
    {
        int node = pq.back();
        pq.pop_back();

        return node;
    }
    void clear()
    {
        pq.clear();
    }
    bool empty()
    {
        return pq.empty();
    }
} PriorityQueue;

int main()
{
    PriorityQueue hammers;
    int n, k, door;
    int hammer;

    while (cin >> n >> door >> k)
    {
        hammers.clear();

        for (int i = 0; i < n; i++)
        {
            cin >> hammer;
            hammers.enQueue(hammer);
        }

        int trial = 0;
        while (!hammers.empty() && trial < k)
        {
            hammer = hammers.deQueue();

            door -= hammer;
            hammer /= 2;
            trial++;

            if (hammer)
                hammers.enQueue(hammer);

            if (door <= 0)
                break;
        }

        if (door <= 0)
            cout << trial << '\n';
        else
            cout << -1 << '\n';
    }

    return 0;
}