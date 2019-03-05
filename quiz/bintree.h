//
// Created by SooYunKim on 11/18/18.
//

#ifndef QUIZ_BINTREE_H
#define QUIZ_BINTREE_H

#include "binarynode.h"
#include <iostream>

using namespace std;

template<class ItemType>
class BinTree {
public:
    // constructor, empty tree
    BinTree<ItemType>();
    // destructor
    virtual ~BinTree<ItemType>();
    // add a new item
    // return true if successful
    // false if item already in tree or some other reason to fail
    bool add(const ItemType &item);
    // true if no nodes
    //bool isEmpty() const;
    // 0 if empty, 1 if only root, otherwise
    // max height of subtrees + 1
    int getHeight(string label);
private:
    // root of the tree
    BinaryNode<ItemType> *rootPtr{nullptr};
    // add a new node, helper function for add
    BinaryNode<ItemType> *placeNode(BinaryNode<ItemType> *node, string label);
    // helper function for getHeight to return height of tree
    int getHeightHelper(BinaryNode<ItemType> *root, string label, int height);
    /* Compute the "maxDepth" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
    int maxDepth(BinaryNode<ItemType> *node, int height);
};

#include "bintree.cpp"

#endif //QUIZ_BINTREE_H
