/*
 * TODO: remove and replace this file header comment
 * You will edit and turn in this file.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include <iostream>    // for cout, endl
#include "queue.h"
#include "SimpleTest.h"
using namespace std;

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> binaryMerge(Queue<int> a, Queue<int> b) {
    // Validate if the input queues are sorted
    int prev = a.peek(); // Access the front element without dequeuing
    while (!a.isEmpty()) {
        int current = a.peek(); // Access the front element without dequeuing
        if (current < prev) {
            error("Input queue 'a' is not sorted.");
        }
        prev = current;
        a.dequeue();
    }

    prev = b.peek(); // Access the front element without dequeuing
    while (!b.isEmpty()) {
        int current = b.peek(); // Access the front element without dequeuing
        if (current < prev) {
            error("Input queue 'b' is not sorted.");
        }
        prev = current;
        b.dequeue();
    }

    Queue<int> result;
    // Merge the two queues in ascending order
    while (!a.isEmpty() && !b.isEmpty()) {
        if (a.peek() <= b.peek()) { // Access the front element without dequeuing
            result.enqueue(a.dequeue());
        } else {
            result.enqueue(b.dequeue());
        }
    }

    // Add any remaining elements from 'a' or 'b'
    while (!a.isEmpty()) {
        result.enqueue(a.dequeue());
    }

    while (!b.isEmpty()) {
        result.enqueue(b.dequeue());
    }

    return result;
}

/*
 * This function assumes correct functionality of the previously
 * defined binaryMerge function and makes use of this function to
 * iteratively merge a collection of sequences, starting off with
 * an empty sequence and progressively merging in one sequence at
 * a time. This function is provided for you fully implemented –
 * it does not need to modified at all.
 */
Queue<int> naiveMultiMerge(Vector<Queue<int>>& all) {
    Queue<int> result;

    for (Queue<int>& q : all) {
        result = binaryMerge(q, result);
    }
    return result;
}

/*
 * TODO: Replace this comment with a descriptive function
 * header comment.
 */
Queue<int> recMultiMerge(Vector<Queue<int>>& all) {
    if (all.isEmpty()){
        return {};
    }

    Queue<int> result = all[0];
    for(int i = 1; i <all.size(); i++){
        result = binaryMerge(result, all[i]);
    }

    return result;
}


/* * * * * * Test Cases * * * * * */

Queue<int> createSequence(int size);
void distribute(Queue<int> input, Vector<Queue<int>>& all);

PROVIDED_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {2, 4, 5};
    Queue<int> b = {1, 3, 3};
    Queue<int> expected = {1, 2, 3, 3, 4, 5};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

PROVIDED_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{3, 6, 9, 9, 100},
                             {1, 5, 9, 9, 12},
                             {5},
                             {},
                             {-5, -5},
                             {3402}
                            };
    Queue<int> expected = {-5, -5, 1, 3, 5, 5, 6, 9, 9, 9, 9, 12, 100, 3402};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

PROVIDED_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 20;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

PROVIDED_TEST("Time binaryMerge operation") {
    int n = 1000000;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

PROVIDED_TEST("Time naiveMultiMerge operation") {
    int n = 11000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}
PROVIDED_TEST("Time recMultiMerge operation") {
    int n = 90000;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


/* Test helper to fill queue with sorted sequence */
Queue<int> createSequence(int size) {
    Queue<int> q;
    for (int i = 0; i < size; i++) {
        q.enqueue(i);
    }
    return q;
}

/* Test helper to distribute elements of sorted sequence across k sequences,
   k is size of Vector */
void distribute(Queue<int> input, Vector<Queue<int>>& all) {
    while (!input.isEmpty()) {
        all[randomInteger(0, all.size()-1)].enqueue(input.dequeue());
    }
}

// student

STUDENT_TEST("binaryMerge, two short sequences") {
    Queue<int> a = {5, 4, 7};
    Queue<int> b = {1, 2, 9};
    Queue<int> expected = {1, 2, 4, 5, 7, 9};
    EXPECT_EQUAL(binaryMerge(a, b), expected);
    EXPECT_EQUAL(binaryMerge(b, a), expected);
}

STUDENT_TEST("naiveMultiMerge, small collection of short sequences") {
    Vector<Queue<int>> all = {{2, 5, 8, 8, 99},
        {1, 2, 5, 7, 14},
        {6},
        {},
        {-6, -6},
        {3401}
    };
    Queue<int> expected = {-6, -6, 1, 2, 2, 5, 5, 6, 7, 8, 8, 14, 99, 3401};
    EXPECT_EQUAL(naiveMultiMerge(all), expected);
}

STUDENT_TEST("recMultiMerge, compare to naiveMultiMerge") {
    int n = 14;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(n);
    distribute(input, all);
    EXPECT_EQUAL(recMultiMerge(all), naiveMultiMerge(all));
}

STUDENT_TEST("Time binaryMerge operation") {
    int n = 10013400;
    Queue<int> a = createSequence(n);
    Queue<int> b = createSequence(n);
    TIME_OPERATION(a.size() + b.size(), binaryMerge(a, b));
}

STUDENT_TEST("Time naiveMultiMerge operation") {
    int n = 100400400;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), naiveMultiMerge(all));
}

STUDENT_TEST("Time recMultiMerge operation") {
    int n = 50500;
    int k = n/10;
    Queue<int> input = createSequence(n);
    Vector<Queue<int>> all(k);
    distribute(input, all);
    TIME_OPERATION(input.size(), recMultiMerge(all));
}


