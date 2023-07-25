/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "recursion.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)

using namespace std;

/*
This function extracts and returns only the bracketing characters from the input string.
 */
string operatorsFrom(string str) {
    if (str.empty()) {
        return "";
    }

    char firstChar = str[0];
    string rest = operatorsFrom(str.substr(1)); // Recursive call

    // Check if the first character is a bracketing character
    if (firstChar == '(' || firstChar == ')' || firstChar == '[' || firstChar == ']' || firstChar == '{' || firstChar == '}') {
        return firstChar + rest;
    } else {
        return rest;
    }
}

/*
This function checks if a string of operators is properly matched and balanced, returning true if they are and false otherwise.
 */
bool operatorsAreMatched(string ops) {
    // Base case: empty string is balanced
    if (ops.empty()) {
        return true;
    }

    // Check for "()", "[]", or "{}" in the string
    size_t pos;
    if ((pos = ops.find("()")) != string::npos || (pos = ops.find("[]")) != string::npos || (pos = ops.find("{}")) != string::npos) {
        // Remove the found substring and make a recursive call
        string rest = ops.substr(0, pos) + ops.substr(pos + 2);
        return operatorsAreMatched(rest);
    }

    // No balanced substring found or the recursive call returned false
    return false;
}

/*
 * The isBalanced function assumes correct implementation of
 * the above two functions operatorsFrom and operatorsMatch.
 * It uses operatorsFrom to extract the operator characters
 * from the input string and then confirms that those
 * operators are balanced by using operatorsMatch.
 * You should not modify the provided code in the isBalanced
 * function.  If the previous two functions have been implemented
 * correctly, the provided isBalanced will correctly report whether
 * the input string has balanced bracketing operators.
 */
bool isBalanced(string str) {
    string ops = operatorsFrom(str);
    return operatorsAreMatched(ops);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("operatorsFrom on simple example") {
    EXPECT_EQUAL(operatorsFrom("vec[3]"), "[]");
}

PROVIDED_TEST("operatorsAreMatched on simple example") {
    EXPECT(operatorsAreMatched("{}"));
}

PROVIDED_TEST("isBalanced on example from writeup") {
    string example ="int main() { int x = 2 * (vec[2] + 3); x = (1 + random()); }";
    EXPECT(isBalanced(example));
}

PROVIDED_TEST("isBalanced on non-balanced examples from writeup") {
    EXPECT(!isBalanced("( ( [ a ] )"));
    EXPECT(!isBalanced("3 ) ("));
    EXPECT(!isBalanced("{ ( x } y )"));
}

STUDENT_TEST("operatorsFrom on empty string") {
    EXPECT_EQUAL(operatorsFrom(""), "");
}
STUDENT_TEST("operatorsFrom on string without any bracketing characters") {
    EXPECT_EQUAL(operatorsFrom("Hello, World!"), "");
}
STUDENT_TEST("operatorsFrom on string with nested bracketing characters") {
    EXPECT_EQUAL(operatorsFrom("{{[(Hello)]}}"), "{}[]");
}

STUDENT_TEST("operatorsAreMatched on empty string") {
    EXPECT(operatorsAreMatched(""));
}
STUDENT_TEST("operatorsAreMatched on string without balanced operators") {
    EXPECT(!operatorsAreMatched("abc"));
}
STUDENT_TEST("operatorsAreMatched on string with nested balanced operators") {
    EXPECT(operatorsAreMatched("[({})]"));
}

STUDENT_TEST("isBalanced on empty string") {
    EXPECT(isBalanced(""));
}
STUDENT_TEST("isBalanced on string without any balanced operators") {
    EXPECT(isBalanced("Hello, World!"));
}
STUDENT_TEST("isBalanced on string with nested balanced operators") {
    EXPECT(isBalanced("[({})]"));
}
