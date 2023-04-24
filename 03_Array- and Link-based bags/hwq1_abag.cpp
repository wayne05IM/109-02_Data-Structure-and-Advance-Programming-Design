#include <iostream>
using namespace std;

/*
template <class ItemType>
class BagInterface
{
public:
    virtual int getCurrentSize() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool add(const ItemType &newEntry) = 0;
    virtual bool remove(const ItemType &anEntry) = 0;
    virtual void clear() = 0;
    virtual int getFrequencyOf(const ItemType &anEntry) const = 0;
    virtual bool contains(const ItemType &anEntry) const = 0;
};
*/

//=======================================================================

// aBag is given as a bag of integers so template is no needed in this case
// applying Array-based Implementation
class aBag : public BagInterface
{
private:
    static const int DEFAULT_CAPACITY = 6;
    int items[DEFAULT_CAPACITY];
    int itemCount;
    int maxItems;

    // member function for question b
    int getIndexOf(const int &beReplaced) const;

public:
    // is already defined in class
    ArrayBag();
    int getCurrentSize() const;
    bool isEmpty() const;
    bool add(const int &newEntry);
    bool remove(const int &anEntry);
    void clear();
    bool contains(const int &anEntry) const;
    int getFrequencyOf(const int &anEntry) const;

    //Answers for question 1
        // question a
    int sum() const;
        // question b
    bool replace(const int &toReplace, const int &beReplaced);   
};

// question a
int aBag::sum() const
{
    int sum = 0;
    for(int i = 0; i < itemCount; i++)
        sum += items[i];
    return sum;
};

// question b
int aBag::getIndexOf(const int &beReplaced) const
{
    bool found = false;
    int result = -1;
    for(int index = 0; index < itemCount; index++)
    {
        if(items[index] == beReplaced)
        {
            result = index;
            break;
        }
    }
    return result;
};

bool aBag::replace(const int &toReplace, const int &beReplaced)
{
    int index = getIndexOf(beReplaced);
    bool canBeReplaced = (index != -1);
    if(canBeReplaced)
    {
        items[index] = toReplace;
    }
    return canBeReplaced;
};