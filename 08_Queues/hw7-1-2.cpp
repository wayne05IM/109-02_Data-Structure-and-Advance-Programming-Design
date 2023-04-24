#include <iostream>
#include <string>
#include <queue> 
using namespace std;

template <class ItemType>
class Node
{
private:
    ItemType type;
    ItemType time;
    ItemType length;
    Node<ItemType> *next;

public:
    Node() : next(nullptr){};
    Node(const ItemType &aTime, const ItemType &aLength, const ItemType &type) : time(aTime), length(aLength), type(type), next(nullptr){};
    Node(const ItemType &aTime, const ItemType &aLength, const ItemType &type, Node<ItemType> *nextNodePtr) : time(aTime), length(aLength), type(type), next(nextNodePtr){};

    void setType(const ItemType &aType) { type = aType; };
    void setTime(const ItemType &aTime) { time = aTime; };
    void setLength(const ItemType &aLen) { length = aLen; };
    void setNext(Node<ItemType> *nextNodePtr) { next = nextNodePtr; };

    ItemType getType() const { return type; };
    ItemType getTime() const { return time; };
    ItemType getlenght() const { return length; };
    Node<ItemType> *getNext() const { return next; };

};

template <class ItemType>
bool operator<(const Node<ItemType> &p1, const Node<ItemType> &p2)
{
    return p1.getTime() < p2.getTime();
}

//simulation functions

bool tellerAvailable = true;

void create(string &aString, priority_queue<int> &eventListQueue)
{
    size_t pos = aString.find(",");
    string tempStr = aString.substr(0, pos);
    int tempTime = stoi(tempStr);
    tempStr = aString.substr(pos + 2);
    int tempLen = stoi(tempStr);
    Node<int> temp(tempTime, tempLen, 1);
    eventListQueue.push(temp);
    //cout << eventListQueue.peekFront()->getlenght();
};

void ProcessArrival(Node<int> &newEvent, PriorityQueue<int> &eventListQueue, Queue<int> &bankQueue, int currentTime)
{
    cout << "A" << endl;
    eventListQueue.dequeue();

    if (bankQueue.isEmpty() && tellerAvailable == false)
    {
        cout << "Processing an arrival event at time: " << currentTime << endl;
        Node<int> departureEvent(currentTime + newEvent.getlenght(), 0, 0);
        eventListQueue.enqueue(departureEvent);
        tellerAvailable = false;
    }
    else
        bankQueue.enqueue(newEvent);
}

float ProcessDeparture(Node<int> &newEvent, PriorityQueue<int> &eventListQueue, Queue<int> &bankQueue, int currentTime)
{
    cout << "D" << endl;
    eventListQueue.dequeue();

    float late = 0;
    if (!bankQueue.isEmpty())
    {
        late = currentTime - bankQueue.peekFront()->getTime();
        bankQueue.dequeue();
        Node<int> departureEvent(currentTime + newEvent.getlenght(), 0, 0);
        eventListQueue.enqueue(departureEvent);
    }
    else
    {
        cout << "Processing a departure event at time: " << newEvent.getTime() << endl;
        tellerAvailable = true;
    }
    return late;
}

int main()
{
    //input
    priority_queue< Node<int> > eventListQueue;
    queue< Node<int> > bankQueue;

    int peopleNum = 0;
    string aString = "";
    while (getline(cin, aString) && aString != "")
    {
        create(aString, eventListQueue);
        peopleNum++;
        aString = "";
    }

    cout << eventListQueue.peekFront()->getTime() << eventListQueue.peekFront()->getlenght() << endl;
    //eventListQueue.printQ();
    
    //Simulation
    float late = 0;
    cout << "Simulation Begins" << endl;
    while (eventListQueue.isEmpty() != true)
    {
        cout << "abc";
        Node<int> newEvent = *eventListQueue.peekFront();
        int currentTime = newEvent.getTime();

        if (newEvent.getType() == 1)
            ProcessArrival(newEvent, eventListQueue, bankQueue, currentTime);
        else
            late += ProcessDeparture(newEvent, eventListQueue, bankQueue, currentTime);
    }

    //final print
    cout << "Stimulaion Ends" << endl
         << endl;
    cout << "Final Statistics:" << endl
         << endl;
    cout << "Total number of people processed: " << peopleNum << endl;
    cout << "Average amount of time spent waiting: " << round(late / float(peopleNum)) << endl;

    return 0;
}