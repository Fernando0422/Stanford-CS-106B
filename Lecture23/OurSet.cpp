#include "error.h"
#include "strlib.h"
#include "OurSet.h"
#include "SimpleTest.h"

/*
 * Constructor for OurSet class. Intializes instance variables to
 * correct values
 */
OurSet::OurSet() {
    root = nullptr;
    numItems = 0;

}

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
/*
 * Destructor for OurSet class. Frees all the memory associated with
 * the internal binary search tree.
 */
OurSet::~OurSet(){
    freeTree(root);
}

/*
 * Remove all elements from the set.
 */
void OurSet::clear() {
    freeTree(root);
}

/*
 * Return the number of elements in the set
 */
int OurSet::size() {
    return numItems;
}

/*
 * Returns true if the set is empty, false otherwise.
 */
bool OurSet::isEmpty() {
    return numItems = 0;
}

/*
 * Prints contents of set in ascending order.
 */
void OurSet::printSetContents() {
    /* FILL ME IN */
}

bool OurSet::containsHelper(int value, TreeNode* node) {
    // base case
    if (node == nullptr) return false;
    if(node->data == value) return true;
    // recursive case
    if(value > node->data){
        return containsHelper(value, node->left);
    } else{
        return containsHelper(value, node->right);
    }
}


/*
 * Checks if the specified value is in the set. Returns
 * true if the element is in the set, and false otherwise.
 */
bool OurSet::contains(int value) {
    return containsHelper(value, root);
}
void OurSet::addHelper(int value, TreeNode*& node) {
    // base case
    if (node == nullptr) {
        // add node
        // create new node
        // node = new node
        // numItems++


        TreeNode* toAdd = new TreeNode(value, nullptr, nullptr);
        node = toAdd;
        numItems++;
        return;
    }

    if(node->data == value) return;

    // recursive case
    if(value > node->data){
        containsHelper(value, node->left);
    } else{
        containsHelper(value, node->right);
    }
}
/*
 * Adds the specified value to the set by inserting it into the correct
 * location in the internal binary search tree.
 */
void OurSet::add(int value) {
    return addHelper(value, root);
}

// --- BELOW: NODE REMOVAL CODE IS COMPLETE ---

/* Removes the specified value from the set by deleting the element
 * containing that value from the internal binary search tree, making sure
 * to preserve the sturcture of the BST.
 */
void OurSet::remove(int value){
    removeHelper(root, value);
}

/*
 * Recursive helper function to help with removing a specified value from the
 * tree whose root is represented by the provided node.
 */
void OurSet::removeHelper(TreeNode*& node, int value) {
    /* If the tree is empty, there’s nothing to remove! */
    if (node == nullptr) {
        return;
    }
    /* If the node to delete is to the left, remove it from there. */
    else if (value < node->data) {
        removeHelper(node->left, value);
    }
    /* If the node to delete is to the right, remove from there. */
    else if (value > node->data) {
        removeHelper(node->right, value);
    }
    /* Otherwise, we’ve found the node to remove – so go remove it! */
    else {
        performDeletion(node);
        numItems--;
    }
}

/* Actually does the deletion necessary to remove a node from the tree. */
void OurSet::performDeletion(TreeNode*& toRemove) {
    /* Case 1: The node is a leaf. Then we just delete it. */
    if (toRemove->left == nullptr && toRemove->right == nullptr) {
        delete toRemove;
        /* Inform whoever was pointing at us that we no longer exist. */
        toRemove = nullptr;
    }
    /* Case 2a: Only have a left child. */
    else if (toRemove->right == nullptr) {
        TreeNode* replacement = toRemove->left;
        delete toRemove;
        toRemove = replacement;
    }
    /* Case 2b: Only have a right child. */
    else if (toRemove->left == nullptr) {
        TreeNode* replacement = toRemove->right;
        delete toRemove;
        toRemove = replacement;
    }
    /* Case 3: Replace this node with the largest node in its left subtree. */
    else {
        toRemove->data = removeLargestFrom(toRemove->left);
    }
}

/* Deletes the largest value from the specified tree, returning that value. */
int OurSet::removeLargestFrom(TreeNode*& node) {
    if (node->right == nullptr) {
        int result = node->data;
        performDeletion(node);
        return result;
    }
    return removeLargestFrom(node->right);
}


PROVIDED_TEST("Test OurSet constructor and destructor."){
    OurSet ss;
    EXPECT(ss.isEmpty());
    EXPECT_EQUAL(ss.size(), 0);
}

PROVIDED_TEST("Test add and contains functions."){
    OurSet ss;

    /* Test add function to add some elements to the set. */
    ss.add(8);
    EXPECT(!ss.isEmpty());
    EXPECT_EQUAL(ss.size(), 1);

    ss.add(3);
    EXPECT_EQUAL(ss.size(), 2);

    Vector<int> nums = {4, 2, 13, 10, 5, 7, 15, 21};
    for (int num: nums) {
        ss.add(num);
    }
    EXPECT_EQUAL(ss.size(), 10);

    /* Display current state of the set. */
    cout << endl << "Full set: ";
    ss.printSetContents();

    /* Test contains function to see if add operations were successful. */
    EXPECT(ss.contains(4));
    EXPECT(ss.contains(10));
    EXPECT(ss.contains(7));
    EXPECT(ss.contains(21));

    EXPECT(!ss.contains(9));
    EXPECT(!ss.contains(1));
}

PROVIDED_TEST("Test remove function"){
    OurSet ss;
    Vector<int> nums = {4, 2, 13, 10, 5, 7, 15, 21};
    for (int num: nums) {
        ss.add(num);
    }
    EXPECT_EQUAL(ss.size(), 8);

    /* Display current state of the set. */
    cout << endl << "Full set: ";
    ss.printSetContents();

    ss.remove(5);
    EXPECT(!ss.contains(5));
    EXPECT_EQUAL(ss.size(), 7);

    cout << "New set contents: ";
    ss.printSetContents();

    ss.remove(4);
    EXPECT(!ss.contains(4));
    EXPECT_EQUAL(ss.size(), 6);

    cout << "New set contents: ";
    ss.printSetContents();

    ss.remove(15);
    EXPECT(!ss.contains(15));
    EXPECT_EQUAL(ss.size(), 5);

    cout << "New set contents: ";
    ss.printSetContents();
}
