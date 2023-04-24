#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
using namespace std;

//Node
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

//QueueInterface
template <class ItemType>
class QueueInterface
{
public:
    virtual bool isEmpty() = 0;
    virtual bool enqueue(Node<ItemType> &newEntry) = 0;
    virtual bool dequeue() = 0;
    virtual Node<ItemType> *peekFront() = 0;
};

//Queue
template <class ItemType>
class Queue : public QueueInterface<ItemType>
{
private:
    Node<ItemType> *frontPtr;
    Node<ItemType> *backPtr;

public:
    Queue() : frontPtr(nullptr), backPtr(nullptr){};
    bool isEmpty();
    bool enqueue(Node<ItemType> &newEntry);
    bool dequeue();
    Node<ItemType> *peekFront();
};

template <class ItemType>
bool Queue<ItemType>::isEmpty()
{
    if ((frontPtr == nullptr) and (backPtr == nullptr))
        return true;
    return false;
}

template <class ItemType>
bool Queue<ItemType>::enqueue(Node<ItemType> &newEntry)
{
    Node<ItemType> *newNodePtr = new Node<ItemType>(newEntry);

    if (isEmpty()) //insertion into empty queue
        frontPtr = newNodePtr;
    else // insertion into nonempty queue
        backPtr->setNext(newNodePtr);

    backPtr = newNodePtr;
    return true;
}

template <class ItemType>
bool Queue<ItemType>::dequeue()
{
    bool result = false;
    if (!isEmpty())
    {
        Node<ItemType> *nodeToDeletePtr = frontPtr;
        if (frontPtr == backPtr)
        {
            frontPtr = nullptr;
            backPtr = nullptr;
        }
        else
            frontPtr = frontPtr->getNext();
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        result = true;
    }
    return result;
}

template <class ItemType>
Node<ItemType> *Queue<ItemType>::peekFront()
{
    return frontPtr;
}

//PriorityQueue
template <class ItemType>
class PriorityQueue : public QueueInterface<ItemType>
{
private:
    Node<ItemType> *frontPtr;
    Node<ItemType> *backPtr;

public:
    PriorityQueue() : frontPtr(nullptr), backPtr(nullptr){};
    bool enqueue(Node<ItemType> &newEntry);
    bool isEmpty();
    bool dequeue();
    Node<ItemType> *peekFront();
};

template <class ItemType>
bool PriorityQueue<ItemType>::isEmpty()
{
    if ((frontPtr == nullptr) and (backPtr == nullptr))
        return true;
    return false;
}

template <class ItemType>
bool PriorityQueue<ItemType>::dequeue()
{
    bool result = false;
    if (!isEmpty())
    {
        Node<ItemType> *nodeToDeletePtr = frontPtr;
        if (frontPtr == backPtr)
        {
            frontPtr = nullptr;
            backPtr = nullptr;
        }
        else
            frontPtr = frontPtr->getNext();
        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;
        result = true;
    }
    return result;
}

template <class ItemType>
Node<ItemType> *PriorityQueue<ItemType>::peekFront()
{
    return frontPtr;
}

template <class ItemType>
bool PriorityQueue<ItemType>::enqueue(Node<ItemType> &newEntry)
{
    Node<ItemType> *newNodePtr = new Node<ItemType>(newEntry);
    Node<ItemType> *currentPtr = frontPtr;

    if (isEmpty())
    {
        frontPtr = newNodePtr;
        backPtr = newNodePtr;
        return true;
    }
    else
    {
        if (currentPtr->getTime() > newNodePtr->getTime())
        {
            newNodePtr->setNext(currentPtr);
            frontPtr = newNodePtr;
        }
        else
        {
            while ((currentPtr->getNext() != nullptr) and ((currentPtr->getNext()->getTime()) <= (newNodePtr->getTime())))
            {
                currentPtr = currentPtr->getNext();
            }

            if (currentPtr->getNext() == nullptr)
            {
                currentPtr->setNext(newNodePtr);
                backPtr = newNodePtr;
            }
            else
            {
                newNodePtr->setNext(currentPtr->getNext());
                currentPtr->setNext(newNodePtr);
            }
        }
    }
    return true;
}

//simulation functions
bool tellerAvailable = true;
int currentTime = 0;

void ProcessArrival(Node<int> &newEvent, PriorityQueue<int> &eventListQueue, Queue<int> &bankQueue)
{
    eventListQueue.dequeue();

    currentTime = newEvent.getTime();
    cout << "Processing an arrival event at time: " << newEvent.getTime() << endl;
    if (bankQueue.isEmpty() && tellerAvailable == true)
    {
        currentTime += newEvent.getlenght();
        Node<int> departureEvent(currentTime, 0, 0);
        eventListQueue.enqueue(departureEvent);
        tellerAvailable = false;
    }
    else
        bankQueue.enqueue(newEvent);
}

float ProcessDeparture(Node<int> &newEvent, PriorityQueue<int> &eventListQueue, Queue<int> &bankQueue)
{
    eventListQueue.dequeue();

    float late = 0;
    cout << "Processing a departure event at time: " << newEvent.getTime() << endl;
    currentTime = newEvent.getTime();
    if (!bankQueue.isEmpty())
    {
        late = currentTime - bankQueue.peekFront()->getTime();
        currentTime += bankQueue.peekFront()->getlenght();
        Node<int> departureEvent(currentTime, 0, 0);
        bankQueue.dequeue();
        eventListQueue.enqueue(departureEvent);
    }
    else
    {
        tellerAvailable = true;
    }
    return late;
}

int main()
{
    //input
    PriorityQueue<int> eventListQueue;
    Queue<int> bankQueue;

    int peopleNum = 0;
    string aString = "";
    while (getline(cin, aString))
    {
        char *cstr = new char[aString.length() + 1];
        strcpy(cstr, aString.c_str());

        int tempTime = 0;
        int tempLen = 0;

        char *pch;
        pch = strtok(cstr, ", ");
        for (int i = 0; pch != nullptr; i++)
        {
            if (i == 0)
                tempTime = atoi(pch);
            else if (i == 1)
                tempLen = atoi(pch);

            pch = strtok(nullptr, ", ");
        }
        delete[] cstr;

        Node<int> a(tempTime, tempLen, 1);
        eventListQueue.enqueue(a);
        peopleNum++;
    }

    //Simulation
    float late = 0.0;
    cout << "Simulation Begins" << endl;
    while (eventListQueue.isEmpty() != true)
    {
        Node<int> newEvent = *eventListQueue.peekFront();

        if (newEvent.getType() == 1)
            ProcessArrival(newEvent, eventListQueue, bankQueue);
        else
            late += ProcessDeparture(newEvent, eventListQueue, bankQueue);
    }

    //final print
    cout << "Simulation Ends" << endl
         << endl;
    cout << "Final Statistics:" << endl
         << endl;
    cout << "Total number of people processed: " << peopleNum << endl;

    cout << setprecision(1) << fixed;
    cout << "Average amount of time spent waiting: " << (late / float(peopleNum)) << endl;
    return 0;
}