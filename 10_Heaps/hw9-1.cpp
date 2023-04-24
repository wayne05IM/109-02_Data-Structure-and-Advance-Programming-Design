#include <iostream>
using namespace std;

//node
template <class ItemType>
class BinaryNode
{
private:
    ItemType item;                       // Data portion
    BinaryNode<ItemType> *leftChildPtr;  // Pointer to left child
    BinaryNode<ItemType> *rightChildPtr; // Pointer to right child

public:
    BinaryNode();
    BinaryNode(const ItemType &anItem);
    BinaryNode(const ItemType &anItem,
               BinaryNode<ItemType> *leftPtr,
               BinaryNode<ItemType> *rightPtr);

    void setItem(const ItemType &anItem) { item = anItem; };
    ItemType getItem() const { return item; };

    bool isLeaf() const
    {
        if ((leftChildPtr == nullptr) and (rightChildPtr == nullptr))
            return true;
        return false;
    };

    BinaryNode<ItemType> *getLeftChildPtr() const { return leftChildPtr; };
    BinaryNode<ItemType> *getRightChildPtr() const { return rightChildPtr; };

    void setLeftChildPtr(BinaryNode<ItemType> *leftPtr){leftChildPtr = leftPtr; };
    void setRightChildPtr(BinaryNode<ItemType> *rightPtr){rightChildPtr = rightPtr; };
};

//binary tree interface
template <class ItemType>
class BinaryTreeInterface
{
public:
    virtual bool isEmpty() const = 0;

    virtual int getHeight() const = 0;
    virtual int getNumberOfNodes() const = 0;

    virtual ItemType getRootData() const = 0;
    virtual void setRootData(const ItemType &newData) = 0;

    virtual bool add(const ItemType &newData) = 0;
    virtual bool remove(const ItemType &data) = 0;
    virtual void clear() = 0;

    virtual ItemType getEntry(const ItemType &anEntry) const;
    //virtual bool contains(const ItemType &anEntry) const = 0;

    virtual void preorderTraverse(void visit(ItemType &)) const = 0;
    virtual void inorderTraverse(void visit(ItemType &)) const = 0;
    virtual void postorderTraverse(void visit(ItemType &)) const = 0;
};

//binary tree
template <class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
    BinaryNode<ItemType> *rootPtr;

protected:
    int getHeightHelper(BinaryNode<ItemType> *subTreePtr) const; //
    int getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const;//

    void destroyTree(BinaryNode<ItemType> *subTreePtr); //
    BinaryNode<ItemType> *copyTree(const BinaryNode<ItemType>* treePtr) const; //

    BinaryNode<ItemType> *balancedAdd(BinaryNode<ItemType> *subTreePtr,
                                      BinaryNode<ItemType> *newNodePtr); //

    //virtual BinaryNode<ItemType> *removeValue(BinaryNode<ItemType> *subTreePtr,
                                      //const ItemType target, bool &success) = 0;
    //virtual BinaryNode<ItemType> *moveValuesUpTree(BinaryNode<ItemType> *subTreePtr) = 0;
    //virtual BinaryNode<ItemType> *findNode(BinaryNode<ItemType> *treePtr,
                                   //const ItemType &target,
                                   //bool &success) const = 0;

    void postorderTraverse(const BinaryNode<ItemType>* treePtr) const; //
    void inorderTraverse(const BinaryNode<ItemType>* treePtr) const; //
    void preorderTraverse(const BinaryNode<ItemType>* treePtr) const; //

public:
    BinaryNodeTree(); //
    BinaryNodeTree(const ItemType &rootItem); //
    BinaryNodeTree(const ItemType &rootItem, //
                   const BinaryNodeTree<ItemType> *leftTreePtr, //
                   const BinaryNodeTree<ItemType> *rightTreePtr); //
    BinaryNodeTree(const BinaryNodeTree<ItemType> &tree); //
    virtual ~BinaryNodeTree(); //

    bool isEmpty() const //
    {
        if(rootPtr == nullptr)
            return true;
        return false;
    };
    int getHeight() const {return getHeightHelper(rootPtr);};//
    int getNumberOfNodes() const {return getNumberOfNodesHelper(rootPtr);};//

    ItemType getRootData() const {return rootPtr->getItem();}; //
    void setRootData(const ItemType &newData) {rootPtr = newData;}; //

    virtual bool add(const ItemType &newData) = 0; // Adds a node //
    bool remove(const ItemType &data); // Removes a node
    void clear() {destroyTree(rootPtr);}; //

    void printpreorderTraverse() const; //
    void printinorderTraverse() const; //
    void printpostorderTraverse() const; //
};

    //protected
//helper function
template <class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType> *subTreePtr) const
{
    if (subTreePtr == nullptr)
        return 0;
    else
        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()->getItem()),
                       getHeightHelper(subTreePtr->getRightChildPtr()->getItem()));
}

template <class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType> *subTreePtr) const
{
    if(subTreePtr != nullptr)
        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) + getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
    else
        return 0;
}

//destroy and copy
template <class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType> *subTreePtr)
{
    if (subTreePtr != nullptr)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
    }
}

template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType> *treePtr) const
{
    BinaryNode<ItemType> *newTreePtr = nullptr;

    if (treePtr != nullptr)
    {
        newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    }

    return newTreePtr;
}

//add and remove
template <class ItemType>
BinaryNode<ItemType> *BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType> *subTreePtr,
                                                            BinaryNode<ItemType> *newNodePtr)
{
    if (subTreePtr == nullptr)
        return newNodePtr;
    else
    {
        BinaryNode<ItemType> *leftPtr = subTreePtr->getLeftChildPtr();
        BinaryNode<ItemType> *rightPtr = subTreePtr->getRightChildPtr();

        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
        {
            rightPtr = balancedAdd(rightPtr, newNodePtr);
            subTreePtr->setRightChildPtr(rightPtr);
        }
        else
        {
            leftPtr = balancedAdd(leftPtr, newNodePtr);
            subTreePtr->setLeftChildPtr(leftPtr);
        }

        return subTreePtr;
    }
}

//traversal
template <class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(const BinaryNode<ItemType>* treePtr) const
{
    if (rootPtr == nullptr)
        return;
 
    postorderTraverse(treePtr->leftChildPtr());
    postorderTraverse(treePtr->rightChildPtr());
    cout << treePtr->getItem() << " ";
}

template <class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(const BinaryNode<ItemType>* treePtr) const
{
    if (treePtr == nullptr)
        return;
 
    inorderTraverse(treePtr->leftChildPtr());
    cout << treePtr->getItem() << " ";
    inorderTraverse(treePtr->rightChildPtr());
}

template <class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(const BinaryNode<ItemType>* treePtr) const
{
    if (treePtr == nullptr)
        return;
    
    cout << treePtr->getItem() << " ";
    preorderTraverse(treePtr->leftChildPtr());
    preorderTraverse(treePtr->rightChildPtr());
}

    //pubic
//constructors and destructors 
template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType &rootItem,
                                         const BinaryNodeTree<ItemType> *leftTreePtr,
                                         const BinaryNodeTree<ItemType> *rightTreePtr)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr),
                                       copyTree(rightTreePtr->rootPtr));
}

template <class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType> &treePtr)
{
    rootPtr = copyTree(treePtr.rootPtr);
}

template <class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
    destroyTree(rootPtr);
}

// traversal print
template <class ItemType>
void BinaryNodeTree<ItemType>::printpostorderTraverse() const
{
    postorderTraverse(rootPtr);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::printinorderTraverse() const
{
    inorderTraverse(rootPtr);
}

template <class ItemType>
void BinaryNodeTree<ItemType>::printpreorderTraverse() const
{
    preorderTraverse(rootPtr);
}

//Binary Search Tree
template <class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
    BinaryNode<ItemType> *rootPtr;

protected:
    void insertInorder(BinaryNode<ItemType> *subTreePtr,
                       BinaryNode<ItemType> *newNode);
    void removeNode(BinaryNode<ItemType> *subTreePtr,
                     const ItemType target);
    //BinaryNode<ItemType> *removeLeftmostNode(BinaryNode<ItemType> *subTreePtr,
                                             //ItemType &inorderSuccessor);
    BinaryNode<ItemType> *findNode(BinaryNode<ItemType> *treePtr,
                                   const ItemType &target) const;

public:
    BinarySearchTree() : rootPtr(nullptr) {};
    BinarySearchTree(const ItemType &rootItem)
    {rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);};
    BinarySearchTree(const BinarySearchTree<ItemType> &tree) {rootPtr = copyTree(tree.rootPtr);};
    virtual ~BinarySearchTree() {destroyTree(rootPtr);};

    bool add(const ItemType &newEntry);
    bool remove(const ItemType &anEntry);
};

    //protected
template <class ItemType>
void BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType> *subTreePtr,
                                               BinaryNode<ItemType> *newNode)
{
    if(subTreePtr == nullptr)
    {
        subTreePtr = newNode;
        return;
    }
    else
    {
        if(newNode->getItem() <= subTreePtr->getItem())
            insertInorder(subTreePtr->getLeftChildPtr(), newNode);
        else
            insertInorder(subTreePtr->getRightChildPtr(), newNode);
    }
}

template <class ItemType>
void BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType> *subTreePtr,
                                             const ItemType target)
{
    BinaryNode<ItemType> *curRoot = findNode(subTreePtr, target);
    while(curRoot->getRightChildPtr() != nullptr)
    {
        curRoot->setItem() = curRoot->getRightChildPtr()->getItem();
        curRoot = curRoot->getRightChildPtr();
    }
    delete curRoot;
}

template <class ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType> *treePtr,
                                                            const ItemType &target) const
{
    if(treePtr->getItem() == target)
        return treePtr;
    else
    {
        if(target <= treePtr->getItem())
            findNode(treePtr->getLeftChildPtr(), target);
        else
            findNode(treePtr->getRightChildPtr(), target);
    }
}

    //public
template <class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &newEntry)
{
    BinaryNode<ItemType> *newNode = new BinaryNode<ItemType>(newEntry, nullptr, nullptr);
    insertInorder(rootPtr, newNode);
}

template <class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &newEntry)
{
    removeNode(rootPtr, newEntry);
}

// main function
int main()
{
    int itemArray[10000] = {0};
    int itemNum = 0;
    while (cin >> itemArray[itemNum])
    {
        itemNum++; 
    }

    // original tree
    BinarySearchTree<int> tree;
    for(int i = 0; i <= itemNum; i++)
    {
        tree.add(itemArray[i]);
    }
    tree.printpreorderTraverse();
    tree.printinorderTraverse();
    tree.printpostorderTraverse();
    tree.getNumberOfNodes();
    tree.getNumberOfLeaf();
    tree.getHeight();

    cout << "** after removing" << round(itemNum / 2) << "nodes **" << endl;

    // remove tree
    for(int i = 0; i <= round(itemNum / 2) - 1; i++)
    {
        tree.remove(itemArray[i]);
    }
    tree.printpreorderTraverse();
    tree.printinorderTraverse();
    tree.printpostorderTraverse();
    tree.getNumberOfNodes();
    tree.getNumberOfLeaf();
    tree.getHeight();

    return 0;
}