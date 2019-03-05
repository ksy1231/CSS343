//
// Created by SooYunKim on 11/18/18.
//

template<class ItemType>
BST<ItemType>::BST() { }

template<class ItemType>
BST<ItemType>::~BST() { }

template<class ItemType>
bool BST<ItemType>::add(const ItemType &item) {
    BinaryNode<ItemType>* newNode = new BinaryNode<ItemType>(item);
    if (rootPtr == NULL) {
        rootPtr = newNode;
        return true;
    }
    else if (rootPtr->getItem() == item) {
        return false;
    }
    else if (rootPtr->getItem() != item){
        placeNode(rootPtr, newNode);
        return true;
    }
    return false;
}

template<class ItemType>
BinaryNode<ItemType> *BST<ItemType>::placeNode(BinaryNode<ItemType> *subTreePtr,
                                                            BinaryNode<ItemType> *newNodePtr) {
    if (subTreePtr == NULL) {
        return subTreePtr;
    }
    if (newNodePtr->getItem() < subTreePtr->getItem()) {
        if (subTreePtr->getLeftChildPtr() == NULL) {
            subTreePtr->setLeftChildPtr(newNodePtr);
        }
        else {
            placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        }
    }

    if (newNodePtr->getItem() > subTreePtr->getItem()) {
        if (subTreePtr->getRightChildPtr() == NULL) {
            subTreePtr->setRightChildPtr(newNodePtr);
        }
        else {
            placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
        }
    }

    return subTreePtr;
}

template<class ItemType>
int BST<ItemType>::mystery() const {
    int n = 0;
    return helper(rootPtr, n);
}

// n passed by reference
template<class ItemType>
int BST<ItemType>::helper(BinaryNode<ItemType> *current, int &n) const {
    cout << "M: " << n << " ";
    if (current == nullptr)
        cout << "NULL" << endl;
    else
        cout << current->getItem() << endl;
    n++;
    if (current == nullptr)
        return n;
    if (current->getRightChildPtr() == nullptr)
        return 1;
    return helper(current->getLeftChildPtr(), n) + helper(current->getRightChildPtr(), n);
}

