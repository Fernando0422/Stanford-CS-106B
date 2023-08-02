/*
 * File: treeTraversal.cpp
 * -------------
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "tree.h"
using namespace std;

int main() {
    TreeNode* tree = buildExampleTree();
    prettyPrint(tree);
    cout << endl;

    cout << "1) Pre-order" << endl;
    cout << "2) In-order" << endl;
    cout << "3) Post-order" << endl;
    cout << "4) Level-order" << endl << endl;
    int choice = -1;
    while (choice != 0) {
        choice = getInteger("Please choose 1-4 (0 to quit): ");
        switch (choice) {
            case 1: preOrderTraversal(tree); break;
            case 2: inOrderTraversal(tree); break;
            case 3: postOrderTraversal(tree); break;
            case 4: levelOrder(tree); break;
        }
        cout << endl << endl;
    }
    cout << "Goodbye!" << endl;
    return 0;
}
