/*
 * File: trees.cpp
 * -------------
 * Free a tree using tree traversal.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "trees.h"
#include "SimpleTest.h"

using namespace std;

void freeTree(TreeNode* node) {
    // base
    if (node == nullptr){
        return;
    }


    // recursive - post order
    freeTree(node->left);
    freeTree(node->right);
    delete node;

}

PROVIDED_TEST("Free empty tree") {
    freeTree(nullptr);
}

PROVIDED_TEST("Free tree with one node") {
    TreeNode* tree = new TreeNode("test", nullptr, nullptr);
    freeTree(tree);
}

PROVIDED_TEST("Free sample tree") {
    /*
     *          pineapple
     *          /       \
     *       coconut   strawberry
     *      /      \        \
     *   banana   durian    taro
     */
    TreeNode* banana = new TreeNode("banana", nullptr, nullptr);
    TreeNode* durian = new TreeNode("durian", nullptr, nullptr);
    TreeNode* taro = new TreeNode("taro", nullptr, nullptr);

    TreeNode* coconut = new TreeNode("coconut", banana, durian);
    TreeNode* strawberry = new TreeNode("strawberry", nullptr, taro);

    TreeNode* root = new TreeNode("pineapple", coconut, strawberry);
    freeTree(root);
}

