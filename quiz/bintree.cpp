//
// Created by SooYunKim on 11/18/18.
//

template<class ItemType>
BinTree<ItemType>::BinTree() { }

template<class ItemType>
BinTree<ItemType>::~BinTree() { }

template<class ItemType>
bool BinTree<ItemType>::add(const ItemType &item) {
    BinaryNode<ItemType>* newNode = new BinaryNode<ItemType>(item);

    if (rootPtr == NULL) {
        rootPtr = newNode;
        return true;
    } else if (rootPtr->getItem() == item) {
        return false;
    } else if (rootPtr->getItem() != item){
        placeNode(rootPtr, item);
        return true;
    }

    return false;
}

template<class ItemType>
BinaryNode<ItemType> *BinTree<ItemType>::placeNode(BinaryNode<ItemType> *node, string label) {
    /* If the tree is empty, return a new node */
    if (node == nullptr) {
        BinaryNode<ItemType> *temp = new BinaryNode<ItemType>(label);
        return temp;
    }

    /* Otherwise, recur down the tree */
    if (label < node->getItem())
        node->setLeftChildPtr(placeNode(node->getLeftChildPtr(), label));
    else if (label > node->getItem())
        node->setRightChildPtr(placeNode(node->getRightChildPtr(), label));

    return node;
}

template<class ItemType>
int BinTree<ItemType>::getHeight(string label) {
    int height = maxDepth(rootPtr, 0);
    return getHeightHelper(rootPtr, label, height);
}

template<class ItemType>
int BinTree<ItemType>::getHeightHelper(BinaryNode<ItemType> *root, string label, int height) {
    if (root == nullptr) {
        return 0;
    }
    if (root->getItem() == label)
        return height;
    return getHeightHelper(root->getRightChildPtr(), label, height - 1) + getHeightHelper(root->getLeftChildPtr(), label, height - 1);
}

template<class ItemType>
int BinTree<ItemType>::maxDepth(BinaryNode<ItemType> *node, int height) {
    if (node == nullptr)
        return height;
    return std::max(maxDepth(node->getLeftChildPtr(), height + 1), maxDepth(node->getRightChildPtr(), height + 1));
}
