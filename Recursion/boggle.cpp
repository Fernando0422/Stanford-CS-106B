/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "gridlocation.h"
#include "grid.h"
#include "set.h"
#include "lexicon.h"
#include "SimpleTest.h"
using namespace std;

/*
 * Provided helper function to score a single word.
 */
int points(string str) {
    return max((int)str.length() - 3, 0);
}
int totalScore = 0;
void explorePath(Grid<char>& board, Lexicon& lex, Set<string>& foundWords, string currentWord, GridLocation currentLocation, Set<GridLocation>& visited) {
    int row = currentLocation.row;
    int col = currentLocation.col;

    // first i need to check if the currentWord is valid, and if it is add it to the foundWords set and update the total score.
    if (currentWord.length() >= 4 && lex.contains(currentWord)) {
        if (!foundWords.contains(currentWord)) {
            foundWords.add(currentWord);
            int wordPoints = points(currentWord);
            totalScore += wordPoints;
        }
    }

    // i need to explore all the neighbors of the current location
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            int newRow = row + dRow;
            int newCol = col + dCol;
            GridLocation neighbor(newRow, newCol);
            Set<GridLocation> visited;

            if (board.inBounds(newRow, newCol) && !visited.contains(neighbor)) {
                visited.add(neighbor);
                explorePath(board, lex, foundWords, currentWord + board[newRow][newCol], neighbor, visited);
                visited.remove(neighbor); // i need to backtrack and remove the visited neighbor to explore more
            }
        }
    }


}



/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */

int scoreBoard(Grid<char>& board, Lexicon& lex) {

    //first initialize variables to keep track of words and their scores
    Set<string> foundWords;
    int totalScore = 0;

    for (int row = 0; row < board.numRows(); row++){
        for (int col = 0; col < board.numCols(); col++){
            GridLocation startLocation(row, col);
            Set<GridLocation> visited;
            visited.add(startLocation);
            explorePath(board, lex, foundWords, string("") + board[row][col], startLocation, visited);
            visited.remove(startLocation);
        }
    }
    return totalScore;
}

/* * * * * * Test Cases * * * * * */

/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Load shared Lexicon, confirm number of words") {
    Lexicon lex = sharedLexicon();
    EXPECT_EQUAL(lex.size(), 127145);
}

PROVIDED_TEST("Test scoreBoard, board contains no words, score of zero") {
    Grid<char> board = {{'B','C','D','F'}, //no vowels, no words
                        {'G','H','J','K'},
                        {'L','M','N','P'},
                        {'Q','R','S','T'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 0);
}

PROVIDED_TEST("Test scoreBoard, board contains one word, score of 1") {
    Grid<char> board = {{'C','_','_','_'},
                        {'Z','_','_','_'},
                        {'_','A','_','_'},
                        {'_','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, alternate paths for same word, still score of 1") {
    Grid<char> board = {{'C','C','_','_'},
                        {'C','Z','C','_'},
                        {'_','A','_','_'},
                        {'R','_','R','_'}};
    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 1);
}

PROVIDED_TEST("Test scoreBoard, small number of words in corner of board") {
    Grid<char> board = {{'L','I','_','_'},
                        {'M','E','_','_'},
                        {'_','S','_','_'},
                        {'_','_','_','_'}};
    Set<string> words = {"SMILE", "LIMES", "MILES", "MILE", "MIES", "LIME", "LIES", "ELMS", "SEMI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()),  2 + 2 + 2 + 1 + 1 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, small number of words") {
    Grid<char> board = {{'E','Z','R','R'},
                        {'O','H','I','O'},
                        {'N','J','I','H'},
                        {'Y','A','H','O'}};
    Set<string> words = { "HORIZON", "OHIA", "ORZO", "JOHN", "HAJI"};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 4 + 1 + 1 + 1 + 1);
}

PROVIDED_TEST("Test scoreBoard, full board, medium number of words") {
    Grid<char> board = {{'O','T','H','X'},
                        {'T','H','T','P'},
                        {'S','S','F','E'},
                        {'N','A','L','T'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 76);
}

PROVIDED_TEST("Test scoreBoard, full board, large number of words") {
    Grid<char> board = {{'E','A','A','R'},
                        {'L','V','T','S'},
                        {'R','A','A','N'},
                        {'O','I','S','E'}};

    EXPECT_EQUAL(scoreBoard(board, sharedLexicon()), 234);
}
