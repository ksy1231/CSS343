//
// Created by SooYunKim on 10/17/18.
//

// stub file
// provided so that the BinarySearchTree can be compiled
// none of the functions are implemented



template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() {
}

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {
    clear();
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType &rootItem) {
    BinaryNode<ItemType>* newNode = new BinaryNode<ItemType>;
    newNode->setItem(rootItem);
    rootPtr = newNode;
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType> &bst) {
    rootPtr = copyTree(bst.rootPtr);
} // end copy constructor

template<class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::copyTree(const BinaryNode<ItemType> *treePtr) const {
    BinaryNode<ItemType>* newTreePtr = nullptr;

    // Copy tree nodes during a inorder traversal
    if (treePtr != nullptr) {
        // Copy node
        newTreePtr = new BinaryNode<ItemType>(treePtr->getItem());
        newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
    } // end if
    // Else tree is empty (newTreePtr is nullptr)

    return newTreePtr;
} // end copyTree

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
    return rootPtr == NULL;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const {
    return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeightHelper(BinaryNode<ItemType> *currNode) const {
    if (currNode == NULL) {
        return 0;
    }

    int left = 1 + getHeightHelper(currNode->getLeftChildPtr());
    int right = 1 + getHeightHelper(currNode->getRightChildPtr());

    return left > right ? left : right;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {
    return countNode(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::countNode(BinaryNode<ItemType> *currNode) const {
    int c =  1;             //Node itself should be counted
    if (currNode ==NULL)
        return 0;
    else
    {
        c += countNode(currNode->getLeftChildPtr());
        c += countNode(currNode->getRightChildPtr());
        return c;
    }
    /*
    if (currNode == NULL) {
        return 0;
    }
    return 1 + countNode(currNode->getLeftChildPtr()) + countNode(currNode->getRightChildPtr());
     */
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType &item) {
    BinaryNode<ItemType>* newNode = new BinaryNode<ItemType>;
    newNode->setItem(item);
    if (rootPtr == NULL) {
        rootPtr = newNode;
        return true;
    }
    else if (rootPtr->getItem() == item) {
        return false;
    }
    else if (rootPtr->getItem() != item){
        //BinaryNode<ItemType> *nNode = new BinaryNode<ItemType>;
        //nNode->setItem(item);
        placeNode(rootPtr, newNode);
        return true;
    }
    delete newNode;
    return false;
}

template<class ItemType>
BinaryNode<ItemType> *BinarySearchTree<ItemType>::placeNode(BinaryNode<ItemType> *subTreePtr,
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
}  // end placeNode

template<class ItemType>
void BinarySearchTree<ItemType>::clear() {
    clearHelper(rootPtr);
    rootPtr = NULL;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clearHelper(BinaryNode<ItemType> *currNode) {
    if (currNode == NULL) {
        return;
    }
    if (currNode->getLeftChildPtr() != nullptr) {
        clearHelper(currNode->getLeftChildPtr());
        //delete currNode->getLeftChildPtr();
    }
    if (currNode->getRightChildPtr() != nullptr) {
        clearHelper(currNode->getRightChildPtr());
        //delete currNode->getRightChildPtr();
    }

    delete currNode;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &item) const {
    return findNode(rootPtr, item);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType> *subTreePtr,
                                                           const ItemType &target) const {
    BinaryNode<ItemType>* temp = subTreePtr;
    while (temp != NULL) {
        if (temp->getItem() == target) {
            return true;
        }
        else {
            if (target < temp->getItem()) {
                temp = temp->getLeftChildPtr();
            }
            else {
                temp = temp->getRightChildPtr();
            }
        }
    }
    return false;
}  // end findNode

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType &)) const {
    if (rootPtr == nullptr) {
        return;
    }
    inorderHelper(rootPtr, visit);
}  // end inorder

template<class ItemType>
void BinarySearchTree<ItemType>::inorderHelper(void visit(ItemType &), BinaryNode<ItemType>* treePtr) const {
    if (treePtr != nullptr) {
        inorderHelper(visit, treePtr->getLeftChildPtr());
        ItemType theItem = treePtr->getItem();
        visit(treePtr->getItem());
        inorderHelper(visit, treePtr->getRightChildPtr());
    }
}

// 동적 배열을 만들고 모든 항목을 배열에 복사 한 다음 배열을 읽어 트리를 다시 만듭니다.
// rebalance and readTree -- they are closely related to each other. To rebalance a tree,
// write all the values into an array in the correct order,
// delete the tree and then recreate the tree from scratch using the array.
// If you have already implemented `readTree` then `rebalance` should be easy.
template<class ItemType>
void BinarySearchTree<ItemType>::rebalance() {
    if (rootPtr == NULL) {
        return;
    }
    else {
        BinaryNode<ItemType>* arr = new BinaryNode<ItemType>[this->getNumberOfNodes()];
        arr[0].setItem(rootPtr->getItem());
        if (rootPtr->getLeftChildPtr() != NULL) {
            int index = 1;
            rebalanceHelper(&arr, rootPtr, index);
        }
        for (int i = 0; i < (int)sizeof(arr); i++) {
            add(arr[i].getItem());
        }
        delete[] arr;
    }
}

template<class ItemType>
void BinarySearchTree<ItemType>::rebalanceHelper(BinaryNode<ItemType>* arr[], BinaryNode<ItemType> *currNode, int &index) {
    if (currNode == NULL) {
        return;
    }
    if (currNode->getLeftChildPtr() != NULL) {
        rebalanceHelper(arr, currNode->getLeftChildPtr(), index);
    }
    //BinaryNode<ItemType>* temp;
    //temp->setItem(currNode->getItem());
    //ItemType item = currNode->getItem();
    arr[index]->setItem(currNode->getItem());
    index++;

    if (currNode->getRightChildPtr() != NULL) {
        rebalanceHelper(arr, currNode->getRightChildPtr(), index);
    }
}

// 트리를 지운 다음 길이 n의 지정된 배열을 사용하여 최소 높이를 가진 배열의 항목으로이 트리를 만듭니다.
template<class ItemType>
bool BinarySearchTree<ItemType>::readTree(ItemType arr[], int n) {
    return readTreeHelper(rootPtr, &arr, 0, n);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::readTreeHelper(BinaryNode<ItemType>* currNode, ItemType* arr[], int low, int high) {
    if (low > high) {
        currNode = NULL;
    }
    else {
        if (currNode != NULL) {
            int mid = (low + high) / 2;
            add(*arr[mid]);
            arr[mid] = NULL;
            readTreeHelper(currNode, arr, low, mid - 1);
            readTreeHelper(currNode, arr, mid + 1, high);
        }
    }
    return true;
}


template<class ItemType>
void BinarySearchTree<ItemType>::displaySideways() const {
    sideways(rootPtr, 0);
}

template<class ItemType>
void BinarySearchTree<ItemType>::sideways(BinaryNode<ItemType> *current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->getRightChildPtr(), level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << current->getItem() << endl;        // display information of object
        sideways(current->getLeftChildPtr(), level);
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::operator==(const BinarySearchTree<ItemType> &other) const {
    return isEqual(rootPtr, other.rootPtr);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEqual(BinaryNode<ItemType> *leftNode, BinaryNode<ItemType> *rightNode) const {
    if (leftNode == NULL && rightNode == NULL) {
        return true;
    }
    else if (leftNode == NULL || rightNode == NULL) {
        return false;
    }
    else if (leftNode->getItem() == rightNode->getItem()) {
        return true;
    }
    return (leftNode->getItem() == rightNode->getItem()
            && isEqual(leftNode->getLeftChildPtr(), rightNode->getLeftChildPtr())
            && isEqual(leftNode->getRightChildPtr(), rightNode->getRightChildPtr()));
}

template<class ItemType>
bool BinarySearchTree<ItemType>::operator!=(const BinarySearchTree<ItemType> &other) const {
    return !(*this == other);
}

