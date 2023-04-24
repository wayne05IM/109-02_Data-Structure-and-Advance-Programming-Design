#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

typedef struct _Node
{
    int arr_time;
    int tran_time;
    int rest;
    struct _Node *next;

    _Node() : arr_time(0), tran_time(0), rest(0), next(nullptr) {}
    _Node(int a, int t) : arr_time(a), tran_time(t), rest(t), next(nullptr) {}
} Node;

typedef struct _PriorityQueue
{
    Node *head;
    _PriorityQueue() { head = nullptr; }

    void enQueue(Node *n)
    {
        if (head == nullptr)
        {
            head = n;
            return;
        }

        Node *curr = head;
        while (curr)
        {
            // sort by arrive time
            if (curr->arr_time > n->arr_time)
            {
                n->next = curr->next;
                curr->next = n;
                return;
            }
            else if (curr->next == nullptr)
            {
                curr->next = n;
                return;
            }
            curr = curr->next;
        }
    }

    Node *deQueue()
    {
        if (head == nullptr)
            return nullptr;

        Node *n = head;
        // clear next ptr
        head = head->next;
        n->next = nullptr;

        return n;
    }

    bool empty()
    {
        return head == nullptr;
    }
} PriorityQueue;

int total_num = 0;
float total = 0;

int main()
{

    int arr_time,
        tran_time;
    PriorityQueue arrive_q,
        waiting_q;

    // Get input and insert into queue
    string str_arr_time,
        str_tran_time;
    cout << "Simulation Begins\n";
    while (cin >> str_arr_time >> str_tran_time)
    {
        str_arr_time = str_arr_time.substr(0, str_arr_time.size() - 1); // remove ','
        tran_time = stoi(str_tran_time);
        arr_time = stoi(str_arr_time);
        arrive_q.enQueue(new Node(arr_time, tran_time));
        total_num++;
    }

    int curr_time = 0,
        delta;
    Node *curr_node = nullptr,
         *next_node = nullptr,
         *arr_node = nullptr;

    bool sametime;

    while (curr_time == 0 || !arrive_q.empty())
    {
        // handle the condition arrival and departure are happened at same time
        sametime = false;

        // get next node
        next_node = arrive_q.deQueue();
        arr_node = next_node;

        // calc the time from current one to next arrival
        delta = next_node->arr_time - curr_time;

        // if delta time can let nodes in waiting queue do transaction before next arrival
        // then we can pop those nodes and let them do transaction
        while (curr_node != nullptr && delta >= curr_node->rest)
        {
            delta -= curr_node->rest;
            curr_time += curr_node->rest;

            if (curr_time == next_node->arr_time)
            {
                sametime = true;
                cout << "Processing an arrival event at time: " << arr_node->arr_time << '\n';
                cout << "Processing a departure event at time: " << curr_time << '\n';
            }
            else
            {
                cout << "Processing a departure event at time: " << curr_time << '\n';
            }

            total += curr_time - curr_node->tran_time - curr_node->arr_time;
            delete (curr_node);
            curr_node = waiting_q.deQueue();
        }

        curr_time += delta;
        if (!sametime)
        {
            cout << "Processing an arrival event at time: " << arr_node->arr_time << '\n';
        }

        if (curr_node == nullptr)
        {
            curr_node = next_node;
        }
        else
        {
            curr_node->rest -= delta;
            delta = 0;
            waiting_q.enQueue(next_node);
        }
    }

    // last node
    cout << "Processing a departure event at time: " << curr_time + curr_node->rest << '\n';
    curr_time += curr_node->rest;
    total += curr_time - curr_node->tran_time - curr_node->arr_time;
    delete (curr_node);

    // if waiting queue is not empty
    while (!waiting_q.empty())
    {
        curr_node = waiting_q.deQueue();
        cout << "Processing a departure event at time: " << curr_time + curr_node->rest << '\n';
        curr_time += curr_node->rest;
        total += curr_time - curr_node->tran_time - curr_node->arr_time;
        delete (curr_node);
    }

    cout << "Simulation Ends\n\nFinal Statistics:\n\n";
    cout << "Total number of people processed: " << total_num << '\n';
    cout << "Average amount of time spent waiting: " << fixed << setprecision(1) << total / total_num << '\n';

    return 0;
}