/*
 * This file contains supporting code that we used to help
 * us with working with trees.
 */

#pragma once
#include "testing/MemoryDiagnostics.h"


struct TreeNode {
    std::string data;
    TreeNode* left;
    TreeNode* right;

    // default constructor does not initialize
    TreeNode() {}

    // 3-arg constructor sets fields from arguments
    TreeNode(std::string d, TreeNode* l, TreeNode* r) {
        data = d;
        left = l;
        right = r;
    }

    TRACK_ALLOCATIONS_OF(TreeNode); //  SimpleTest allocationg tracking
};

// function prototype declarations
void freeTree(TreeNode* tree);
