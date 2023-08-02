#include "tree.h"
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include <iostream>
using namespace std;

TreeNode* buildExampleTree() {

    TreeNode* cream = new TreeNode("cream", nullptr, nullptr);
    TreeNode* milk = new TreeNode("milk", nullptr, nullptr);
    TreeNode* flour = new TreeNode("flour", nullptr, nullptr);
    TreeNode* creamCheese = new TreeNode("cream_cheese", cream, milk);
    TreeNode* grahamCracker = new TreeNode("graham_cracker", nullptr, flour);
    TreeNode* root = new TreeNode("cheesecake", creamCheese, grahamCracker);

    return root;
}

void preOrderTraversal(TreeNode* tree) {
    //base case
    if(tree == nullptr){
        return;
    }
    // 1. "Do something" with the current node
    // print the current node
    cout << tree->data << endl;
    // 2. Traverse the left subtree
    preOrderTraversal(tree->left);

    // 3. Traverse the right subtree
    preOrderTraversal(tree->right);

}


void inOrderTraversal(TreeNode* tree) {
    // base case
    if(tree == nullptr){
        return;
    }
    // 1. Traverse the left subtree
    inOrderTraversal(tree->left);
    // 2. "Do something" with the current node
    cout << tree->data << endl;
    // 3. Traverse the right subtree
    inOrderTraversal(tree->right);

}

void postOrderTraversal(TreeNode* tree) {
    if(tree == nullptr){
        return;
    }
    // 1. Traverse the left subtree
    postOrderTraversal(tree->left);

    // 2. Traverse the right subtree
    postOrderTraversal(tree->right);

    // 3. "Do something" with the current node
    cout << tree->data << endl;

}





// Level-order traversal
void levelOrder(TreeNode*tree) {
    Queue<TreeNode *>treeQueue;
    treeQueue.enqueue(tree);
    while (!treeQueue.isEmpty()) {
        TreeNode *node = treeQueue.dequeue();
        cout << node->data << " ";

        // enqueue both left and right, if they exist
        if (node->left != nullptr) {
            treeQueue.enqueue(node->left);
        }
        if (node->right != nullptr) {
            treeQueue.enqueue(node->right);
        }
    }
}

// All functions below this are to help with printing the tree
void printChars(int n, char c)
{
    for (int i = 0; i < n; i++) {
        cout << c;
    }
}

string padString(string s, int len) {
    // make the string len long
    int sLen = s.length();
    if ((len - sLen) % 2 == 1) {
        s += " ";
        sLen++;
    }
    for (int i = 0; i < (len - sLen) / 2; i++) {
        s = string(" ") + s + " ";
    }
    return s;
}

int treeHeight(TreeNode* tree) {
    if (tree == nullptr) {
        return 0;
    }
    int leftHeight = treeHeight(tree->left);
    int rightHeight = treeHeight(tree->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    } else {
        return rightHeight + 1;
    }
}

int longestData(TreeNode* tree) {
    if (tree == nullptr) return 0;
    int longest = max(longestData(tree->left),
                      longestData(tree->right));
    return (max((int)tree->data.length(), longest));
}

void prettyPrint(TreeNode* tree)
{
    // calculate levels
    int numLevels = treeHeight(tree);
    int maxLength = longestData(tree);

    // go through each level and mark locations of numbers
    Queue<TreeNode*> q;
    q.enqueue(tree);
    int level = 0;
    int numberCount = 1 << level;
    int nextNumberOfCount = 0;
    int spacesSoFar = 0;
    while (!q.isEmpty()) {
        TreeNode* curr = q.dequeue();
        //             xxx
        //     xxx             xxx
        // xxx     xxx     xxx     xxx
        int first = (1 << (numLevels - level - 1)) - 1;
        int elementMult = 1 << (numLevels - level);
        int nextPos = (first + (nextNumberOfCount * elementMult)) * maxLength;

        printChars(nextPos - spacesSoFar, ' ');
        spacesSoFar = nextPos;
        if (curr != nullptr) {
            cout << padString(curr->data, maxLength);
        } else {
            printChars(maxLength, '-');
        }
        spacesSoFar += maxLength;
        if (curr != nullptr) {
            q.enqueue(curr->left);
            q.enqueue(curr->right);
        } else {
            q.enqueue(nullptr);
            q.enqueue(nullptr);
        }
        nextNumberOfCount++;
        if (nextNumberOfCount == numberCount) {
            nextNumberOfCount = 0;
            level++;
            numberCount = 1 << level;
            spacesSoFar = 0;
            if (level == numLevels) break; // don't print last level, which will be empty
            cout << endl;
        }
    }
    cout << endl;
}
