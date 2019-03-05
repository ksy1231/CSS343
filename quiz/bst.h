//
// Created by SooYunKim on 11/18/18.
//

#ifndef QUIZ_BST_H
#define QUIZ_BST_H

#include "binarynode.h"
#include <iostream>

using namespace std;

template<class ItemType>
class BST {
public:
    // constructor, empty tree
    BST<ItemType>();
    // destructor
    virtual ~BST<ItemType>();
    // add a new item
    // return true if successful
    // false if item already in tree or some other reason to fail
    bool add(const ItemType &item);
    int mystery() const;
private:
    // root of the tree
    BinaryNode<ItemType> *rootPtr{nullptr};
    // add a new node, helper function for add
    BinaryNode<ItemType> *placeNode(BinaryNode<ItemType> *subTreePtr, BinaryNode<ItemType> *newNodePtr);
    // n passed by reference
    int helper(BinaryNode<ItemType> *current, int &n) const;
    int ​​helper(BinaryNode<ItemType> *current, int &n) const;
};

#include "bst.cpp"

#endif //QUIZ_BST_H
