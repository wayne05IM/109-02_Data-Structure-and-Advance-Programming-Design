//a.) doubly-linked chain node define
template <typename ItemType>
class Node
{
private:
    ItemType item;
    Node<ItemType> *next;
    Node<ItemType> *previous;

public:
    Node();
    Node(const ItemType &anItem, Node<ItemType> *previousNodePtr);
    Node(const ItemType &anItem, Node<ItemType> *nextNodePtr);
    Node(const ItemType &anItem, Node<ItemType> *previousNodePtr, Node<ItemType> *nextNodePtr);
    void setItem(const ItemType &anItem);
    void setPrevious(Node<ItemType> *previousNodePtr);
    void setNext(Node<ItemType> *nextNodePtr);
    ItemType getItem() const;
    Node<ItemType> *getPrevious() const;
    Node<ItemType> *getNext() const;
};

//constructors
//default constructor
template <class ItemType>
Node<ItemType>::Node() : previous(nullptr), next(nullptr)
{
};
//initial Item and previous pointer constructor
template <class ItemType>
Node<ItemType>::Node(const ItemType &anItem, Node<ItemType> *previousNodePtr) : item(anItem), previous(previousNodePtr), next(nullptr)
{
};
//initial Item and next pointer constructor
template <class ItemType>
Node<ItemType>::Node(const ItemType &anItem, Node<ItemType> *nextNodePtr) : item(anItem), previous(nullptr), next(nextNodePtr)
{
};
//initial Item, previous pointer and next pointer constructor
template <class ItemType>
Node<ItemType>::Node(const ItemType &anItem, Node<ItemType> *previousNodePtr, Node<ItemType> *nextNodePtr) : item(anItem), previous(previousNodePtr), next(nextNodePtr)
{
};

//setter
//setItem
template <class ItemType>
void Node<ItemType>::setItem(const ItemType &anItem)
{
    item = anItem;
}
//setPrevious
template <class ItemType>
void Node<ItemType>::setPrevious(Node<ItemType> *previousNodePtr)
{
    previous = previousNodePtr;
}
//setNext
template <class ItemType>
void Node<ItemType>::setNext(Node<ItemType> *nextNodePtr)
{
    next = nextNodePtr;
}

//getter
//getItem
template <class ItemType>
ItemType Node<ItemType>::getItem() const
{
    return item;
}
//getPrevious
template <class ItemType>
Node<ItemType> *Node<ItemType>::getPrevious() const
{
    return previous;
}
//getNext
template <class ItemType>
Node<ItemType> *Node<ItemType>::getNext() const
{
    return next;
}