// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.
// Remove starter comments and add your own
// comments on each function and on complex code sections.
#include <iostream>
#include <fstream>
#include "error.h"
#include "filelib.h"
#include "grid.h"
#include "maze.h"
#include "mazegraphics.h"
#include "queue.h"
#include "set.h"
#include "stack.h"
#include "vector.h"
#include "SimpleTest.h" // IWYU pragma: keep (needed to quiet spurious warning)
using namespace std;


// This function generates a set of valid neighboring grid locations given a maze and a current location.

Set<GridLocation> generateValidMoves(Grid<bool>& maze, GridLocation cur) {
    Set<GridLocation> neighbors;
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (const auto& direction : directions) {
        int newRow = cur.row + direction.first;
        int newCol = cur.col + direction.second;

        if (maze.inBounds(newRow, newCol)) {
            if (maze[newRow][newCol]) {
                GridLocation neighbor = {newRow, newCol};
                neighbors.add(neighbor);
            }
        }
    }

    return neighbors;
}


// The validatePath function checks if a given path in a maze is valid, ensuring it starts at the entry point, ends at the exit point, does not contain walls, out-of-bounds locations, or loops.

void validatePath(Grid<bool>& maze, Vector<GridLocation>& path) {
    if (path.isEmpty()) {
        error("Path is empty!");
    }
    /* TODO: Fill in the remainder of this function. */
    if (path[0] != GridLocation{0, 0}) {
        error("Path does not start at the entry point!");
    }


    GridLocation exit = {maze.numRows() -1, maze.numCols() - 1};
    if (path[path.size() -1] != exit){
        error("Path does not end at the exit point");
    }

    set<GridLocation> visited;
    for (int i = 0; i < path.size(); i++){
        GridLocation location = path[i];

        if(!maze.inBounds(location.row, location.col)){
            error("Path contains out of bounds locations");
        }
        if (!maze[location.row][location.col]){
            error("path contains walls");
        }
        if (visited.count(location) > 0) {
            error("Path contains a loop!");
        }

        visited.insert(location);
    }

    /* If you find a problem with the path, call error() to report it.
     * If the path is a valid solution, then this function should run to completion
     * without raising any errors.
     */
}

// This function uses Breadth-First Search (BFS) to solve a maze represented by a grid of boolean values, finding a path from the top-left corner to the bottom-right corner.

Vector<GridLocation> solveMazeBFS(Grid<bool>& maze) {
    Vector<GridLocation> path;
    Queue<Vector<GridLocation>> allPaths;
    Set<GridLocation> visited;

    Vector<int> drows = {-1, 1, 0, 0};
    Vector<int> dcols = {0, 0, -1, 1};

    GridLocation start(0, 0);
    Vector<GridLocation> initialPath = {start};
    allPaths.enqueue(initialPath);

    while (!allPaths.isEmpty()) {
        Vector<GridLocation> currentPath = allPaths.dequeue();
        GridLocation currentLocation = currentPath[currentPath.size() - 1];

        if (currentLocation.row == maze.numRows() - 1 && currentLocation.col == maze.numCols() - 1) {
            path = currentPath;
            break;
        }

        Set<GridLocation> neighbors = generateValidMoves(maze, currentLocation);
        for (const auto& neighbor : neighbors) {
            if (!visited.contains(neighbor)) {
                Vector<GridLocation> newPath = currentPath;
                newPath.add(neighbor);
                allPaths.enqueue(newPath);
                visited.add(neighbor);
            }
        }
        drawMaze(maze);
        highlightPath(currentPath, "blue", 10);
    }

    drawMaze(maze);
    highlightPath(path, "green", 1000);


    return path;
}


// This function uses Depth-First Search (DFS) to solve a maze represented by a grid of boolean values, finding a path from the top-left corner to the bottom-right corner.
Vector<GridLocation> solveMazeDFS(Grid<bool>& maze) {
    Vector<GridLocation> path;
    Stack<Vector<GridLocation>> allPaths;
    Set<GridLocation> visited;

    Vector<int> drows = {-1, 1, 0, 0};
    Vector<int> dcols = {0, 0, -1, 1};

    GridLocation start(0, 0);
    Vector<GridLocation> initialPath = {start};
    allPaths.push(initialPath);

    while (!allPaths.isEmpty()) {
        Vector<GridLocation> currentPath = allPaths.pop();
        GridLocation currentLocation = currentPath[currentPath.size() - 1];

        if (currentLocation.row == maze.numRows() - 1 && currentLocation.col == maze.numCols() - 1) {
            path = currentPath;
            break;
        }

        Set<GridLocation> neighbors = generateValidMoves(maze, currentLocation);
        for (const auto& neighbor : neighbors) {
            if (!visited.contains(neighbor)) {
                Vector<GridLocation> newPath = currentPath;
                newPath.add(neighbor);
                allPaths.push(newPath);
                visited.add(neighbor);
            }
        }
    }

    drawMaze(maze);
    return path;
}

/*
 * The given readMazeFile function correctly reads a well-formed
 * maze from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readMazeFile(string filename, Grid<bool>& maze) {
    /* The following code reads data from the file into a Vector
     * of strings representing the lines of the file.
     */
    ifstream in;

    if (!openFile(in, filename))
        error("Cannot open file named " + filename);

    Vector<string> lines;
    readEntireFile(in, lines);

    /* Now that the file data has been read into the Vector, populate
     * the maze grid.
     */
    int numRows = lines.size();        // rows is count of lines
    int numCols = lines[0].length();   // cols is length of line
    maze.resize(numRows, numCols);     // resize grid dimensions

    for (int r = 0; r < numRows; r++) {
        if (lines[r].length() != numCols) {
            error("Maze row has inconsistent number of columns");
        }
        for (int c = 0; c < numCols; c++) {
            char ch = lines[r][c];
            if (ch == '@') {        // wall
                maze[r][c] = false;
            } else if (ch == '-') { // corridor
                maze[r][c] = true;
            } else {
                error("Maze location has invalid character: '" + charToString(ch) + "'");
            }
        }
    }
}

/* The given readSolutionFile correctly reads a path from a file.
 *
 * This provided function is fully correct. You do not need to change
 * any of the code in this function.
 */
void readSolutionFile(string filename, Vector<GridLocation>& soln) {
    ifstream in;

    if (!openFile(in, filename)) {
        error("Cannot open file named " + filename);
    }

    if (!(in >> soln)) {// if not successfully read
        error("Maze solution did not have the correct format.");
    }
}


/* * * * * * Test Cases * * * * * */

PROVIDED_TEST("generateValidMoves on location in the center of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

PROVIDED_TEST("generateValidMoves on location on the side of 3x3 grid with no walls") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation side = {0, 1};
    Set<GridLocation> expected = {{0, 0}, {0, 2}, {1, 1}};

    EXPECT_EQUAL(generateValidMoves(maze, side), expected);
}

PROVIDED_TEST("generateValidMoves on corner of 2x2 grid with walls") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

PROVIDED_TEST("validatePath on correct solution, hand-constructed maze") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Vector<GridLocation> soln = { {0 ,0}, {1, 0}, {1, 1} };

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on correct solution read from file, medium maze") {
    Grid<bool> maze;
    Vector<GridLocation> soln;
    readMazeFile("res/5x7.maze", maze);
    readSolutionFile("res/5x7.soln", soln);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("validatePath on invalid path should raise error") {
    Grid<bool> maze = {{true, false},
                       {true, true},
                       {true, true}};
    Vector<GridLocation> notBeginAtEntry = { {1, 1}, {2, 1} };
    Vector<GridLocation> notEndAtExit = { {0, 0}, {1, 0}, {2, 0} };
    Vector<GridLocation> moveThroughWall = { {0 ,0}, {0, 1}, {1, 1}, {2, 1} };

    EXPECT_ERROR(validatePath(maze, notBeginAtEntry));
    EXPECT_ERROR(validatePath(maze, notEndAtExit));
    EXPECT_ERROR(validatePath(maze, moveThroughWall));
}

PROVIDED_TEST("solveMazeBFS on file 5x7") {
    Grid<bool> maze;
    readMazeFile("res/5x7.maze", maze);
    Vector<GridLocation> soln = solveMazeBFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

PROVIDED_TEST("solveMazeDFS on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

// STUDENT TEST CASES
STUDENT_TEST("generateValidMoves on corner of 3x3 grid with walls") {
    Grid<bool> maze = {{false, true, true},
                       {true, true, true},
                       {true, true, true}};
    GridLocation corner = {0, 0};
    Set<GridLocation> expected = {{0, 1}, {1, 0}};

    EXPECT_EQUAL(generateValidMoves(maze, corner), expected);
}

STUDENT_TEST("generateValidMoves on location surrounded by walls") {
    Grid<bool> maze = {{false, false, false},
                       {false, true, false},
                       {false, false, false}};
    GridLocation center = {1, 1};
    Set<GridLocation> expected;

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

STUDENT_TEST("generateValidMoves on location in the middle of grid with no walls") {
    Grid<bool> maze = {{true, true, true, true},
                       {true, true, true, true},
                       {true, true, true, true},
                       {true, true, true, true}};
    GridLocation center = {2, 2};
    Set<GridLocation> expected = {{1, 2}, {2, 1}, {2, 3}, {3, 2}};

    EXPECT_EQUAL(generateValidMoves(maze, center), expected);
}

STUDENT_TEST("validatePath on invalid path starting at the wrong location") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Vector<GridLocation> path = { {1, 0}, {1, 1} };

    EXPECT_ERROR(validatePath(maze, path));
}

STUDENT_TEST("validatePath on invalid path ending at the wrong location") {
    Grid<bool> maze = {{true, false},
                       {true, true}};
    Vector<GridLocation> path = { {0 ,0}, {1, 0}, {1, 1}, {1, 0} };

    EXPECT_ERROR(validatePath(maze, path));
}

STUDENT_TEST("validatePath on invalid path containing a loop") {
    Grid<bool> maze = {{true, true, true},
                       {true, true, true},
                       {true, true, true}};
    Vector<GridLocation> path = { {0 ,0}, {0, 1}, {1, 1}, {1, 0}, {0, 0} };

    EXPECT_ERROR(validatePath(maze, path));
}



STUDENT_TEST("solveMazeBFS on file 13x39") {
    Grid<bool> maze;
    readMazeFile("res/13x39.maze", maze);
    Vector<GridLocation> soln = solveMazeBFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("solveMazeBFS on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Vector<GridLocation> soln = solveMazeBFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("solveMazeBFS on file 33x41") {
    Grid<bool> maze;
    readMazeFile("res/33x41.maze", maze);
    Vector<GridLocation> soln = solveMazeBFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}




STUDENT_TEST("solveMazeDFS on file 21x23") {
    Grid<bool> maze;
    readMazeFile("res/21x23.maze", maze);
    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}

STUDENT_TEST("solveMazeDFS on file 2x2") {
    Grid<bool> maze;
    readMazeFile("res/2x2.maze", maze);
    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}
STUDENT_TEST("solveMazeDFS on file 25x15") {
    Grid<bool> maze;
    readMazeFile("res/25x15.maze", maze);
    Vector<GridLocation> soln = solveMazeDFS(maze);

    EXPECT_NO_ERROR(validatePath(maze, soln));
}









