/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>
#include "prototypes.h"
#include "lexicon.h"
#include "set.h"
#include "SimpleTest.h"
#include "strlib.h"
using namespace std;

// keypad is a program-wide constant that stores the Map from integer to
// its associated set of possible letters
static const Map<int,Set<char>> keypad = {
    {2, {'a','b','c'} }, {3, {'d','e','f'} }, {4, {'g','h','i'} },
    {5, {'j','k','l'} }, {6, {'m','n','o'} }, {7, {'p','q','r','s'} },
    {8, {'t','u','v'} }, {9, {'w','x','y','z'} } };

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
void findWordsRecursive(string& digits, Set<string>& suggestions, Lexicon& lex, string currentWord, int index) {
    // Base case: if the currentWord forms a word in the lexicon, add it to suggestions
    if (index == digits.length()) {
        if (lex.contains(currentWord)) {
            suggestions.add(currentWord);
        }
        return;
    }

    // Get the digit from the digit sequence
    int digit = digits[index] - '0';

    // Get the set of possible letters associated with the digit
    Set<char> letters = keypad[digit];

    // Explore all possible combinations of letters
    for (char letter : letters) {
        // Append the current letter to the currentWord
        string newWord = currentWord + letter;
        // Continue exploring the next digit in the sequence
        findWordsRecursive(digits, suggestions, lex, newWord, index + 1);
    }
}




void predict(string digits, Set<string>& suggestions, Lexicon& lex)
{
    findWordsRecursive(digits, suggestions, lex, "", 0);

}


/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Predict intended words for digit sequence 6263, example from writeup") {
    string digits = "6263";
    Set<string> expected = {"name", "mane", "oboe"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}

// STUDENT TESTS

STUDENT_TEST("Predict intended words for digit sequence 23") {
    string digits = "23";
    Set<string> expected = {"ad", "ae", "be"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}

STUDENT_TEST("Predict intended words for digit sequence 743") {
    string digits = "743";
    Set<string> expected = {"pie", "rid", "rif", "she"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}



// Test with an empty digit sequence
STUDENT_TEST("Predict intended words for empty digit sequence") {
    string digits = "";
    Set<string> expected = {};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}

// Test with a digit sequence that doesn't form any words
STUDENT_TEST("Predict intended words for digit sequence 9999") {
    string digits = "9999";
    Set<string> expected = {};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}
