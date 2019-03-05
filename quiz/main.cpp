#include <iostream>
#include "bst.h"
#include "bintree.h"

using namespace std;

void testMystery() {
    BST<string> bst;
    bst.add("E");
    bst.add("B");
    bst.add("G");
    bst.add("A");
    bst.add("C");
    bst.add("D");
    bst.add("I");
    bst.add("H");
    int result = bst.mystery();
    cout << "Final: " << result << endl;
}

int main() {
    testMystery();

    BinTree<string> bin;
    bin.add("F");
    bin.add("C");
    bin.add("I");
    bin.add("B");
    bin.add("A");
    bin.add("E");
    bin.add("D");
    bin.add("G");
    bin.add("J");
    bin.add("H");
    bin.add("K");

    cout << bin.getHeight("H"); // 1
    cout << bin.getHeight("E"); // 2
    cout << bin.getHeight("C"); // 3
    cout << bin.getHeight("A"); // 1
    cout << bin.getHeight("Z"); // 0

    return 0;
}