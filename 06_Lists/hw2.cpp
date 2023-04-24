#include <iostream>
#include <string>
#include <cstring>
using namespace std;

//ADT
template <class ItemType>
class LinkedListInterface
{
public:
    virtual void reverse() = 0;
    virtual void add(const ItemType &newName, const ItemType &newGift) = 0;
    virtual void print() const = 0;
};

//Node class
template <class ItemType>
class Node
{
private:
    ItemType Name;
    ItemType Gift;
    Node<ItemType> *next;

public:
    Node();
    Node(const ItemType &Name, const ItemType &Gift);
    Node(const ItemType &Name, const ItemType &Gift, Node<ItemType> *nextNodePtr);

    void setName(const ItemType &aName);
    void setGift(const ItemType &aGift);
    void setNext(Node<ItemType> *nextNodePtr);

    ItemType getName() const;
    ItemType getGift() const;
    Node<ItemType> *getNext() const;
};

//constructor
template <class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}
template <class ItemType>
Node<ItemType>::Node(const ItemType &Name, const ItemType &Gift) : Name(Name), Gift(Gift), next(nullptr)
{
}
template <class ItemType>
Node<ItemType>::Node(const ItemType &Name, const ItemType &Gift, Node<ItemType> *nextNodePtr) : Name(Name), Gift(Gift), next(nextNodePtr)
{
}

//setter
template <class ItemType>
void Node<ItemType>::setName(const ItemType &aName)
{
    Name = aName;
}
template <class ItemType>
void Node<ItemType>::setGift(const ItemType &aGift)
{
    Gift = aGift;
}
template <class ItemType>
void Node<ItemType>::setNext(Node<ItemType> *nextNodePtr)
{
    next = nextNodePtr;
}

//getter
template <class ItemType>
ItemType Node<ItemType>::getName() const
{
    return Name;
}
template <class ItemType>
ItemType Node<ItemType>::getGift() const
{
    return Gift;
}
template <class ItemType>
Node<ItemType> *Node<ItemType>::getNext() const
{
    return next;
}

//Nice
template <class ItemType>
class Nice : public LinkedListInterface<ItemType>
{
private:
    Node<ItemType> *headPtr;

public:
    Nice();
    void add(const ItemType &newName, const ItemType &newGift);
    void reverse();
    void print() const;
};

template <class ItemType>
Nice<ItemType>::Nice() : headPtr(nullptr)
{
}

template <class ItemType>
void Nice<ItemType>::add(const ItemType &newName, const ItemType &newGift)
{
    Node<ItemType> *newNodePtr = new Node<ItemType>();
    newNodePtr->setName(newName);
    newNodePtr->setGift(newGift);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
}

template <class ItemType>
void Nice<ItemType>::print() const
{
    Node<ItemType> *curPtr = headPtr;
    while ((curPtr->getNext()) != nullptr)
    {
        cout << curPtr->getName() << " " << curPtr->getGift() << ","
             << " ";
        curPtr = curPtr->getNext();
    }
    cout << curPtr->getName() << " " << curPtr->getGift() << endl;
}

template <class ItemType>
void Nice<ItemType>::reverse()
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

//Bad
template <class ItemType>
class Bad : public LinkedListInterface<ItemType>
{
private:
    Node<ItemType> *headPtr;

public:
    Bad();
    void add(const ItemType &newName, const ItemType &newGift);
    void reverse();
    void print() const;
};

template <class ItemType>
Bad<ItemType>::Bad() : headPtr(nullptr)
{
}

template <class ItemType>
void Bad<ItemType>::add(const ItemType &newName, const ItemType &newGift)
{
    Node<ItemType> *newNodePtr = new Node<ItemType>();
    newNodePtr->setName(newName);
    newNodePtr->setGift(newGift);
    newNodePtr->setNext(headPtr);
    headPtr = newNodePtr;
}

template <class ItemType>
void Bad<ItemType>::print() const
{
    Node<ItemType> *curPtr = headPtr;
    while ((curPtr->getNext()) != nullptr)
    {
        cout << curPtr->getName() << " ";
        curPtr = curPtr->getNext();
    }
    cout << curPtr->getName() << endl;
}

template <class ItemType>
void Bad<ItemType>::reverse()
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

//split string function
void create(string &aString, Nice<string> &nice, Bad<string> &bad)
{
    char *cstr = new char[aString.length() + 1];
    strcpy(cstr, aString.c_str());
    // cstr now contains a c-string copy of str
    
    char* p = strtok(cstr, " ");
    while (p != nullptr)
    {
        string tempName = p;
        p = strtok(nullptr, ",");
        string tempGift = p;
        p = strtok(nullptr," ");
        if(tempGift == "coal")
            bad.add(tempName, tempGift);
        else
            nice.add(tempName, tempGift);
    }

    delete[] cstr;
};

int main()
{
    string aString;
    while (getline(cin, aString))
    {
        Nice<string> niceString;
        Bad<string> badString;
        create(aString, niceString, badString);

        niceString.reverse();
        niceString.print();

        badString.reverse();
        badString.print();

        aString = "";
    }
    return 0;
}