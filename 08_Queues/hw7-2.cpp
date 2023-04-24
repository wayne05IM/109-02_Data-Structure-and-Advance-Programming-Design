#include <iostream>
using namespace std;

//QueueInterface
template <class ItemType>
class QueueInterface
{
public:
    virtual bool isEmpty() = 0;
    virtual bool enqueue(const ItemType &newEntry) = 0;
    virtual bool dequeue() = 0;
    virtual ItemType peekFront() = 0;
};

//ArrayQueue
const int MAX_QUEUE = 50;
template <class ItemType>
class ArrayQueue : public QueueInterface<ItemType>
{
private:
    ItemType items[MAX_QUEUE];
    int front;
    int back;
    int count;
public:
    ArrayQueue() : front(0), back(MAX_QUEUE - 1), count(0) {};
    bool isEmpty() const {return count == 0;};
    bool enqueue(const ItemType& newEntry);
    bool dequeue();
    void insertionSort();
    ItemType peekFront() const;
};

template<class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType& newEntry)
{
   bool result = false;
   if (count < MAX_QUEUE)
   {
      // Queue has room for another item
      back = (back + 1) % MAX_QUEUE;
      items[back] = newEntry;
      count++;
      result = true;
   } // end if
   
   return result;
}

template<class ItemType>
bool ArrayQueue<ItemType>::dequeue()
{
   bool result = false;
   if (!isEmpty())
   {
      front = (front + 1) % MAX_QUEUE;
      count--;
      result = true;
   } // end if
   
   return result;
}

template<class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const
{
   // Queue is not empty; return front
   return items[front];
}

template<class ItemType>
void ArrayQueue<ItemType>::insertionSort()
{
    
}

int main()
{
    int hamNum = 0, strdoor = 0, trials = 0;
    while (cin >> hamNum >> strdoor >> trials)
    {
        //input
        int *hamArray = new int[hamNum + 1];
        for (int i = 0; i < hamNum; i++)
            cin >> hamArray[i];
    }
    return 0;
}