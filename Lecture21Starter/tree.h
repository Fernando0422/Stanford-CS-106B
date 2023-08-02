#pragma once
#include <string>

struct TreeNode {
    std::string data;
    TreeNode* left;
    TreeNode* right;

    //default constructor
    TreeNode() {}

    //3-arg constructor sets fields from arguments
    TreeNode(std::string data, TreeNode* left, TreeNode* right) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

//function prototype declarations
TreeNode* buildExampleTree();
void preOrderTraversal(TreeNode* tree);
void inOrderTraversal(TreeNode* tree);
void postOrderTraversal(TreeNode* tree);
void levelOrder(TreeNode*tree);

//functions to help with printing the tree
int treeHeight(TreeNode* tree);
void prettyPrint(TreeNode* tree);
void printChars(int n, char c);
int longestData(TreeNode* tree);
std::string padString(std::string s, int len);
