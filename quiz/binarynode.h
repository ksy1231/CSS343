//
// Created by SooYunKim on 11/18/18.
//

#ifndef QUIZ_BINARYNODE_H
#define QUIZ_BINARYNODE_H

#include <iostream>

using namespace std;

template<class ItemType>
class BinaryNode {

public:
    // default constructor
    BinaryNode<ItemType>();
    // constructor setting the data to be stored
    explicit BinaryNode<ItemType>(const ItemType &item);
    // destructor to cleanup
    virtual ~BinaryNode<ItemType>();
    // get left child, possibly nullptr
    BinaryNode<ItemType> *getLeftChildPtr() const;
    // set the left child ptr
    void setLeftChildPtr(BinaryNode<ItemType> *childPtr);
    // get right child, possibly nullptr
    BinaryNode<ItemType> *getRightChildPtr() const;
    // set the right child ptr
    void setRightChildPtr(BinaryNode<ItemType> *childPtr);
    // return the item stored
    ItemType getItem() const;
    // set the item stored to a new value
    void setItem(const ItemType &item);
private:
    // the data that will be stored
    ItemType item;
    // left child
    BinaryNode<ItemType> *leftPtr{nullptr};
    // right child
    BinaryNode<ItemType> *rightPtr{nullptr};
};

#include "binarynode.cpp"

#endif //QUIZ_BINARYNODE_H
