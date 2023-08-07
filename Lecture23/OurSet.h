// OurSet.h
// Header file for our Set of ints Class

#pragma once

#include <ostream>
#include "treenode.h"
using namespace std;

class OurSet {
public:
    // constructor
    OurSet();

    // destructor
    ~OurSet();

    // put value into set
    void add(int value);

    // remove value from set
    void remove(int value);

    // check if set contains the value
    bool contains(int value);

    // removes all elements from the set
    void clear();

    // return the number of elements in the set
    int size();

    // true if zero elements
    bool isEmpty();

    // print elements of set in order
    void printSetContents();

private:
    /* FILL ME IN */
    TreeNode* root;
    int numItems;

    void freeTree(TreeNode* node);
    bool containsHelper(int value, TreeNode* node);
    void addHelper(int value, TreeNode*& node);


    void removeHelper(TreeNode*& node, int value);
    int removeLargestFrom(TreeNode*& node);
    void performDeletion(TreeNode*& toRemove);
};
