#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_product(vector<int> &v);

typedef struct _PriorityQueue {
    vector<int> pq;
    void enQueue(int node) {
        pq.insert
        (
            lower_bound(pq.begin(), pq.end(), node, greater<int>()),
            node
        );
    }
    int deQueue() {
        int node = pq.back();
        pq.pop_back();

        return node;
    }
    void clear() {
        pq.clear();
    }
    bool empty() {
        return pq.empty();
    }
    int get_product() {
        return pq[0] * pq[1] * pq[2];
    }
} PriorityQueue;

int main()
{
    int n;

    while (cin >> n) {
        PriorityQueue v;
        int val;

        for (int i = 0; i < n; i++) {
            cin >> val;
            v.enQueue(val);

            if (i >= 2)
                cout << v.get_product() << '\n';
        }
    }
    
    return 0;
}