//
// Created by SooYunKim on 10/17/18.
//

// Edit 20 Jan 2018. Added <ItemType> for all cases
// since it was complaining under some compilers but not g++

// BinarySearchTree class
// Creates a BST to store values
// Uses BinaryNode which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately

#ifndef ASS2_BINARYSEARCHTREE_H
#define ASS2_BINARYSEARCHTREE_H

#include "binarynode.h"

using namespace std;

template<class ItemType>
class BinarySearchTree {
public:
    // constructor, empty tree
    BinarySearchTree<ItemType>();
    // constructor, tree with root
    explicit BinarySearchTree<ItemType>(const ItemType &rootItem);
    // copy constructor
    BinarySearchTree<ItemType>(const BinarySearchTree<ItemType> &bst);
    // destructor
    virtual ~BinarySearchTree<ItemType>();
    // true if no nodes
    bool isEmpty() const;
    // 0 if empty, 1 if only root, otherwise
    // max height of subtrees + 1
    int getHeight() const;
    // number of nodes and data in tree
    int getNumberOfNodes() const;
    // add a new item
    // return true if successful
    // false if item already in tree or some other reason to fail
    bool add(const ItemType &item);
    // true if item is in tree
    bool contains(const ItemType &item) const;
    // display a sideways ascii representation of tree
    void displaySideways() const;
    // inorder traversal: left-root-right
    // takes a function that takes a single parameter of ItemType
    // the function can modify the data in tree, but the
    // tree structure is not changed
    void inorderTraverse(void visit(ItemType &)) const;
    // create dynamic array, copy all the items to the array
    // and then read the array to re-create this tree
    void rebalance();
    // delete all nodes in tree and set root to nullptr
    void clear();
    // clear the tree and then use the given array of length n
    // to create this tree with item from the array
    // with the minimum height
    bool readTree(ItemType arr[], int n);
    // trees are equal if they have the same structure
    // AND the same item values at all the nodes
    bool operator==(const BinarySearchTree<ItemType> &) const;
    // not == to each other
    bool operator!=(const BinarySearchTree<ItemType> &) const;
private:
    // root of the tree
    BinaryNode<ItemType> *rootPtr{nullptr};
    // helper function for copy constructor
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;
    // add a new node, helper function for add
    BinaryNode<ItemType> *placeNode(BinaryNode<ItemType> *subTreePtr, BinaryNode<ItemType> *newNodePtr);
    // find the node with given vale, helper function for contains
    //BinaryNode<ItemType> *findNode(BinaryNode<ItemType> *subTreePtr, const ItemType &target) const;
    bool findNode(BinaryNode<ItemType> *subTreePtr, const ItemType &target) const;
    // helper function for displaySideways to work recursively
    void sideways(BinaryNode<ItemType> *current, int level) const;
    // helper function for clear to delete all nodes and set nullptr
    void clearHelper(BinaryNode<ItemType>* currNode);
    // helper function for operator== to compare whether same tree or not
    bool isEqual(BinaryNode<ItemType>* leftNode, BinaryNode<ItemType>* rightNode) const;
    // helper function for getHeight to return height of tree
    int getHeightHelper(BinaryNode<ItemType>* currNode) const;
    // helper function for getNumberOfNodes to return the number of nodes in tree
    int countNode(BinaryNode<ItemType>* currNode) const;
    // helper function for inorderTraverse to traverses a binary search tree in sorted order
    void inorderHelper(void visit(ItemType &), BinaryNode<ItemType>* treePtr) const;
    // helper function for rebalance to build a dynamic array from tree
    void rebalanceHelper(BinaryNode<ItemType>* arr[], BinaryNode<ItemType>* currNode, int &index);
    // helper function for readTree to build tree from array and set array to NULL
    bool readTreeHelper(BinaryNode<ItemType>* currNode, ItemType* arr[], int low, int high);
};

#include "binarysearchtree.cpp"

#endif //ASS2_BINARYSEARCHTREE_H
