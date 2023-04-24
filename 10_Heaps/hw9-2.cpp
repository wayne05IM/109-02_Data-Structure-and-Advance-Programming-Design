#include <iostream>
using namespace std;

template<class ItemType>
class HeapInterface
{
public:
   /** Sees whether this heap is empty.
    @return True if the heap is empty, or false if not. */
   virtual bool isEmpty() const = 0;
   
   /** Gets the number of nodes in this heap.
    @return The number of nodes in the heap. */
   virtual int getNumberOfNodes() const = 0;
   
   /** Gets the height of this heap.
    @return The height of the heap. */
   virtual int getHeight() const = 0;
   
   /** Gets the data that is in the root (top) of this heap.
    For a maxheap, the data is the largest value in the heap;
    for a minheap, the data is the smallest value in the heap.
    @pre The heap is not empty.
    @post The root’s data has been returned, and the heap is unchanged.
    @return The data in the root of the heap. */
   virtual ItemType peekTop() const = 0;
   
   /** Adds a new node containing the given data to this heap.
    @param newData The data for the new node.
    @post The heap contains a new node.
    @return True if the addition is successful, or false if not. */
   virtual bool add(const ItemType& newData) = 0;
   
   /** Removes the root node from this heap.
    @return True if the removal is successful, or false if not. */
   virtual bool remove() = 0;
   
   /** Removes all nodes from this heap. */
   virtual void clear() = 0;
}; // end HeapInterface

template<class ItemType>
class ArrayMaxHeap : public HeapInterface<ItemType>
{
private:
   static const int ROOT_INDEX = 0;        // Helps with readability
   static const int DEFAULT_CAPACITY = 21; // Small capacity to test for a full heap
   ItemType* items;                        // Array of heap items
   int itemCount;                          // Current count of heap items
   int maxItems;                           // Maximum capacity of the heap
   
   // ---------------------------------------------------------------------
   // Most of the private utility methods use an array index as a parameter
   // and in calculations. This should be safe, even though the array is an
   // implementation detail, since the methods are private.
   // ---------------------------------------------------------------------
   
   // Returns the array index of the left child (if it exists).
   int getLeftChildIndex(const int nodeIndex) const;
   
   // Returns the array index of the right child (if it exists).
   int getRightChildIndex(int nodeIndex) const;
   
   // Returns the array index of the parent node.
   int getParentIndex(int nodeIndex) const;
   
   // Tests whether this node is a leaf.
   bool isLeaf(int nodeIndex) const;
   
   // Converts a semiheap to a heap.
   void heapRebuild(int subTreeRootIndex);
   
   // Creates a heap from an unordered array.
   void heapCreate();
   
public:
   ArrayMaxHeap();
   ArrayMaxHeap(const ItemType someArray[], const int arraySize);
   virtual ~ArrayMaxHeap();
   
   // HeapInterface Public Methods:
   bool isEmpty() const;
   int getNumberOfNodes() const;
   int getHeight() const;
   ItemType peekTop() const throw(PrecondViolatedExcep);
   bool add(const ItemType& newData);
   bool remove();
   void clear();
}; // end ArrayMaxHeap

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
   return (2 * nodeIndex) + 1;
}  // end getLeftChildIndex

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate() 
{
   for (int index = itemCount / 2; index >= 0; index--)
   {
      heapRebuild(index);  
   }  // end for
}  // end heapCreate

template<class ItemType>
ArrayMaxHeap<ItemType>::
ArrayMaxHeap(const ItemType someArray[], const int arraySize):
             itemCount(arraySize), maxItems(2 * arraySize)
{
   // Allocate the array
   items = new ItemType[2 * arraySize];
   
   // Copy given values into the array
   for (int i = 0; i < itemCount; i++)
      items[i] = someArray[i];
   
   // Reorganize the array into a heap
   heapCreate();
} // end constructor

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcep)
{
   if (isEmpty())
      throw PrecondViolatedExcep("Attempted peek into an empty heap.");
   
   return items[0];
} // end peekTop

//main

int main()
{
    int itemArray[10000] = {0};
    int itemNum = 0;
    while (cin >> itemArray[itemNum])
    {
        itemNum++; 
    }

    // original tree
    minHeap<int> tree;
    for(int i = 0; i <= itemNum; i++)
    {
        tree.add(itemArray[i]);
    }
    tree.preorderTraverse();
    tree.inorderTraverse();
    tree.postorderTraverse();
    tree.getNumberOfNodes();
    tree.getNumberofLeaf();
    tree.getHeight();

    cout << "** after removing %d nodes **" , round(itemNum / 2) << endl;

    // remove tree
    for(int i = 0; i <= round(itemNum/2) - 1; i++)
    {
        tree.remove(itemArray[i]);
    }
    tree.preorderTraverse();
    tree.inorderTraverse();
    tree.postorderTraverse();
    tree.getNumberOfNodes();
    tree.getNumberofLeaf();
    tree.getHeight();

    return 0;
}