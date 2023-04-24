findItem(23Tree : TwoThreeTree, target : ItemType) : ItemType
{
    if (target is in 23Tree’s root node r)
    {
        // The item has been found
        treeItem = the data portion of r 
        return treeItem // Success
    }
    else if (r is a leaf)       //r is not rarget
        throw NotFoundException // Failure
    
    // Else search the appropriate subtree
    else if (r has two data items) //3-node
    {
        if (target < smaller item in r)
            return findItem(r’s left subtree, target)
        else if (target < larger item in r)
            return findItem(r’s middle subtree, target)
        else
            return findItem(r’s right subtree, target)
    }
    else
    { // r has one data item, 2-node
        if (target < r’s data item)
            return findItem(r’s left subtree, target)
        else
            return findItem(r’s right subtree, target)
    }
}

// method 1 : restrict the item range and do the inorderTraversal
rangeQuery(23Tree : TwoThreeTree, lowerBound : ItemType, upperBound : ItemType) : void
{
    if (23Tree’s root node r is a leaf)
    {
        if(lowerBound < data item < upperBound)
            Visit the data item(s)
    }
    else if (r has two data items)
    { //3-nodes
        inorder(left subtree of 23Tree’s root)
        if(lowerBound < first data item < upperBound)
            Visit the first data item
        inorder(middle subtree of 23Tree’s root)
        if(lowerBound < second data item < upperBound)
            Visit the second data item
        inorder(right subtree of 23Tree’s root)
    }
    else //r has one data item, 2-nodes
    {
        inorder(left subtree of 23Tree’s root)
        if(lowerBound < data item < upperBound)
            Visit the data item
        inorder(right subtree of 23Tree’s root)
    }
}

// method 2 : find the place of the lowerBound and the upperBound and do inorderTaversal between them
rangeQuery(23Tree : TwoThreeTree, lowerBound : ItemType, upperBound : ItemType) : void
{
    do inorderTraversal from findItem(TwoThreeTree, lowerBound) to findItem(TwoThreeTree, upperBound)
}