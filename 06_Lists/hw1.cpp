#include <iostream>
#include <string>
using namespace std;

//ADT
template <class ItemType>
class LinkedListInterface
{
public:
    virtual int search(const ItemType &item) const = 0;
    virtual void reverse() = 0;
    virtual void add(const ItemType &newEntry) = 0;
    virtual void print() const = 0;
};

//Node class
template <class ItemType>
class Node
{
private:
    ItemType item;
    Node<ItemType> *next;

public:
    Node();
    Node(const ItemType &anItem);
    Node(const ItemType &anItem, Node<ItemType> *nextNodePtr);

    void setItem(const ItemType &anItem);
    void setNext(Node<ItemType> *nextNodePtr);

    ItemType getItem() const;
    Node<ItemType> *getNext() const;
};

//constructor
template <class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}
template <class ItemType>
Node<ItemType>::Node(const ItemType &anItem) : item(anItem), next(nullptr)
{
}
template <class ItemType>
Node<ItemType>::Node(const ItemType &anItem, Node<ItemType> *nextNodePtr) : item(anItem), next(nextNodePtr)
{
}

//setter
template <class ItemType>
void Node<ItemType>::setItem(const ItemType &anItem)
{
    item = anItem;
}
template <class ItemType>
void Node<ItemType>::setNext(Node<ItemType> *nextNodePtr)
{
    next = nextNodePtr;
}

//getter
template <class ItemType>
ItemType Node<ItemType>::getItem() const
{
    return item;
}
template <class ItemType>
Node<ItemType> *Node<ItemType>::getNext() const
{
    return next;
}

//LinkedList
template <class ItemType>
class LinkedList : public LinkedListInterface<ItemType>
{
private:
    Node<ItemType> *headPtr;

public:
    LinkedList();
    void add(const ItemType &newEntry);
    int search(const ItemType &item) const;
    void reverse();
    void print() const;
};

template <class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr)
{
}

template <class ItemType>
void LinkedList<ItemType>::add(const ItemType &newEntry)
{
    Node<ItemType> *newNodePtr = new Node<ItemType>();
    newNodePtr->setItem(newEntry);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
}

template <class ItemType>
int LinkedList<ItemType>::search(const ItemType &item) const
{
    Node<ItemType> *curPtr = headPtr;
    int count = 0;
    while (curPtr != nullptr)
    {
        count++;
        if (item == (curPtr->getItem()))
            return count;
        else
            curPtr = (curPtr->getNext());
    }
    return -1;
}

template <class ItemType>
void LinkedList<ItemType>::print() const
{
    Node<ItemType> *curPtr = headPtr;
    while ((curPtr->getNext()) != nullptr)
    {
        cout << curPtr->getItem() << " ";
        curPtr = curPtr->getNext();
    }
    cout << curPtr->getItem();
}

template <class ItemType>
void LinkedList<ItemType>::reverse()
{
    if (headPtr == nullptr || headPtr->getNext() == nullptr)
        return;

    Node<ItemType> *previous = nullptr, *current = headPtr, *preceding = headPtr->getNext();

    while (preceding != nullptr)
    {
        current->setNext(previous);
        previous = current;
        current = preceding;
        preceding = preceding->getNext();
    }

    current->setNext(previous);
    headPtr = current;
}

//main
int main()
{
    string items, target;
    while ((getline(cin, items)) and (getline(cin, target)))
    {
        LinkedList<string> aString;

        //split string
        string del = " ";
        int start = 0;
        int end = items.find(del);
        while (end != -1)
        {
            string subString = items.substr(start, end - start);
            aString.add(subString);
            start = end + del.size();
            end = items.find(del, start);
        }
        aString.add(items.substr(start, end - start));

        //print list
        aString.reverse();
        aString.print();
        cout << endl;

        //print count
        cout << (aString.search(target)) << endl;

        //print reverse
        aString.reverse();
        aString.print();
        cout << endl;

        items = "";
        target = "";
    }

    return 0;
}