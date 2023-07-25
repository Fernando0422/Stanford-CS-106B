// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "map.h"
#include "search.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;


// The cleanToken function takes a string as input and removes punctuation marks,
// converts uppercase letters to lowercase, and excludes specific characters ('$','@','.'). It returns the cleaned string as the output.


string cleanToken(string s) {
    string cleanedString;
    int length = s.length();

    for (int i = 0; i < length; i++) {
        char c = s[i];
        if (isupper(c)) {
            c = tolower(c);
        }
        if (!(ispunct(c) || c == '$' || c == '@' || c == '.')) {
            cleanedString += c;
        }
    }

    return cleanedString;
}

// The fixedToken function cleans a token by removing non-alphabetic characters and converting it to lowercase.
//The gatherTokens function extracts and cleans tokens from a given string, returning a set of unique cleaned tokens.


string fixedToken(string token) {
    string cleanedToken;
    for (char ch : token) {
        if (isalpha(ch))
            cleanedToken += tolower(ch);
    }
    return cleanedToken;
}


Set<string> gatherTokens(string bodytext) {
    Set<string> tokens;
    string cleanedToken;
    Vector<string> splitTokens = stringSplit(bodytext, " ");

    for (const string& token : splitTokens) {
        cleanedToken = fixedToken(token);
        tokens.add(cleanedToken);
    }

    return tokens;
}



//In this code, the cleanToken function is defined before the gatherTokens function. This ensures that the function is properly declared before it is used within gatherTokens.

//Please try running the updated code, and it should resolve the redefinition error.

// TThe buildIndex function creates an index by mapping tokens to the lines they
//  appear in, and it returns the count of unique web pages seen.

int buildIndex(Vector<string>& lines, Map<string, Set<string>>& index) {
    Set<string> uniquePages; // Set to store unique web pages

    for (string line : lines) {
        Vector<string> tokens = stringSplit(line, " "); // Split the line into tokens

        for (string token : tokens) {
            index[token].add(line);
        }

        // Add the current line to the set of unique pages
        uniquePages.add(line);
    }

    return uniquePages.size();
}



// The findQueryMatches function searches for web page URLs that match a given query using an index of words and returns a set of matching URLs.
// The searchEngine function builds the index, prompts the user for queries, calls findQueryMatches, and displays the matching web page URLs.

Set<string> findQueryMatches(Map<string, Set<string>>& index, string query) {
    Set<string> result;

    Vector<string> searchTerms = stringSplit(query, " ");
    bool firstTerm = true;

    for (string term : searchTerms) {
        string cleanedTerm = cleanToken(term);

        if (cleanedTerm.empty())
            continue;

        bool negate = false;
        bool intersect = false;

        if (cleanedTerm[0] == '-') {
            negate = true;
            cleanedTerm = cleanedTerm.substr(1); // Remove the leading -
        } else if (cleanedTerm[0] == '+') {
            intersect = true;
            cleanedTerm = cleanedTerm.substr(1); // Remove the leading +
        }

        cleanedTerm = fixedToken(cleanedTerm);

        Set<string> matches = index[cleanedTerm];

        if (firstTerm) {
            result = matches;
            firstTerm = false;
        } else {
            if (negate)
                result = result.difference(matches);
            else if (intersect)
                result = result.intersect(matches);
            else
                result = result.unionWith(matches);
        }
    }

    return result;
}





// implements a basic search engine by building an index of distinct words found in web page contents and allows the user to enter search queries to find matching web pages based on the indexed words.
void searchEngine(Vector<string>& lines) {
    Map<string, Set<string>> index;
    int numPages = buildIndex(lines, index);
    cout << "Web pages processed: " << numPages << endl;
    cout << "Distinct words found: " << index.size() << endl;

    while (true) {
        string query = getLine("Enter a query (or enter an empty string to quit): ");
        if (query.empty()) break;

        Set<string> matches = findQueryMatches(index, query);
        cout << "Matching pages:" << endl;
        for (const string& page : matches) {
            cout << page << endl;
        }
    }
}

/*
 * The given readDatabaseFile function correctly reads a well-formed
 * website database from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readDatabaseFile(string filename, Vector<string>& lines) {
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    readEntireFile(in, lines);
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("cleanToken on strings of letters and digits") {
    EXPECT_EQUAL(cleanToken("hello"), "hello");
    EXPECT_EQUAL(cleanToken("WORLD"), "world");
    EXPECT_EQUAL(cleanToken("CS106B"), "cs106b");
}

PROVIDED_TEST("cleanToken on strings containing punctuation") {
    EXPECT_EQUAL(cleanToken("/hello/"), "hello");
    EXPECT_EQUAL(cleanToken("~woRLD!"), "world");
    EXPECT_EQUAL(cleanToken("they're"), "theyre");
}

PROVIDED_TEST("cleanToken on string of only punctuation") {
    EXPECT_EQUAL(cleanToken("#$^@@.;"), "");
}

PROVIDED_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}

PROVIDED_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}

PROVIDED_TEST("gatherTokens from seuss, 6 unique tokens, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 6);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

PROVIDED_TEST("buildIndex from tiny.txt, 4 pages, 12 unique tokens") {
    Vector<string> lines;
    Map<string, Set<string>> index;
    readDatabaseFile("res/tiny.txt", lines);
    int nPages = buildIndex(lines, index);
    EXPECT_EQUAL(nPages, 4);
    EXPECT_EQUAL(index.size(), 12);
    EXPECT(index.containsKey("fish"));
}

PROVIDED_TEST("findQueryMatches from tiny.txt, single word query") {
    Vector<string> lines;
    Map<string, Set<string>> index;
    readDatabaseFile("res/tiny.txt", lines);
    buildIndex(lines, index);
    Set<string> matchesRed = findQueryMatches(index, "red");
    EXPECT_EQUAL(matchesRed.size(), 2);
    EXPECT(matchesRed.contains("www.dr.seuss.net"));
    Set<string> matchesHippo = findQueryMatches(index, "hippo");
    EXPECT(matchesHippo.isEmpty());
}

PROVIDED_TEST("findQueryMatches from tiny.txt, compound queries") {
    Vector<string> lines;
    Map<string, Set<string>> index;
    readDatabaseFile("res/tiny.txt", lines);
    buildIndex(lines, index);
    Set<string> matchesRedOrFish = findQueryMatches(index, "red fish");
    EXPECT_EQUAL(matchesRedOrFish.size(), 4);
    Set<string> matchesRedAndFish = findQueryMatches(index, "red +fish");
    EXPECT_EQUAL(matchesRedAndFish.size(), 1);
    Set<string> matchesRedWithoutFish = findQueryMatches(index, "red -fish");
    EXPECT_EQUAL(matchesRedWithoutFish.size(), 1);
}


// TODO: add your test cases here

STUDENT_TEST("cleanToken on strings of upper and lowercase letters") {
    EXPECT_EQUAL(cleanToken("KaSpER"), "kasper");
}
STUDENT_TEST("cleanToken on strings of letters, nums, and random letters") {
    EXPECT_EQUAL(cleanToken("Br1teN&"), "br1ten");
}
STUDENT_TEST("cleanToken on strings of letters upper and lowercase and punctuation") {
    EXPECT_EQUAL(cleanToken("What's Up"), "whats up");
}
STUDENT_TEST("gatherTokens from simple string") {
    Set<string> expected = {"go", "gophers"};
    EXPECT_EQUAL(gatherTokens("go go go gophers"), expected);
}
STUDENT_TEST("gatherTokens correctly cleans tokens") {
    Set<string> expected = {"i", "love", "cs106b"};
    EXPECT_EQUAL(gatherTokens("I _love_ CS*106B!"), expected);
}
STUDENT_TEST("gatherTokens from Seuss, 6 unique tokens, mixed case, punctuation") {
    Set<string> tokens = gatherTokens("One Fish Two Fish *Red* fish Blue fish ** 10 RED Fish?");
    EXPECT_EQUAL(tokens.size(), 6);
    EXPECT(tokens.contains("fish"));
    EXPECT(!tokens.contains("Fish"));
}

