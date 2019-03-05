//
// Created by SooYunKim on 11/18/18.
//

template<class ItemType>
BinaryNode<ItemType>::BinaryNode() { }

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType &item) : item{item} {

}

template<class ItemType>
BinaryNode<ItemType>::~BinaryNode() { }

template<class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getLeftChildPtr() const {
    return leftPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(BinaryNode<ItemType> *childPtr) {
    leftPtr = childPtr;
}

template<class ItemType>
BinaryNode<ItemType> *BinaryNode<ItemType>::getRightChildPtr() const {
    return rightPtr;
}

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(BinaryNode<ItemType> *childPtr) {
    rightPtr = childPtr;
}

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const {
    return item;
}

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType &item) {
    this->item = item;
}
