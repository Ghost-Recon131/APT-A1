#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"
#include "milestone4.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env& env, int& rows, int& cols);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution, int rows, int cols);


int main(int argc, char** argv) {
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    int rows = (-1);
    int cols = (-1);

    // Load Environment 
    Env env;
    readEnvStdin(env, rows, cols);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, rows, cols);
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution, rows, cols);

    delete pathplanner;
    delete reachablePositions;
    delete solution;
    delete_env(env, rows, cols);

}

void readEnvStdin(Env& env, int& rows, int& cols) {

    const char symbols[] = {
        SYMBOL_WALL,
        SYMBOL_EMPTY,
        SYMBOL_GOAL,
        SYMBOL_START
    };


    size_t countBuffer = 0;
    size_t lengthBuffer = 256;
    char* arrayBuffer = new char[lengthBuffer];

    int indexA = 0;
    int indexB = 0;

    char character;
    while (std::cin.get(character)) {

        // resize buffer if full
        if (countBuffer == lengthBuffer) {
            lengthBuffer += 256;
            char* oldBuffer = arrayBuffer;
            char* newBuffer = new char[lengthBuffer];
            for (size_t index = 0; index < countBuffer; index++) {
                newBuffer[index] = oldBuffer[index];
            }
            delete oldBuffer;
            arrayBuffer = newBuffer;
        }

        bool test1, test2, test3, test4;
        test1 = character == symbols[0];
        test2 = character == symbols[1];
        test3 = character == symbols[2];
        test4 = character == symbols[3];

        // proper character found
        if (test1 || test2 || test3 || test4) {
            arrayBuffer[indexA] = character;
            countBuffer++;
            indexA++;
        }

        if (character == '\n') {
            cols = indexA - indexB;
            indexB = indexA;
        }
    }

    rows = indexA / cols;
    env = make_env(rows, cols);

    int limit = rows * cols;
    for (int index = 0; index < limit; index++) {
        int x = index % cols;
        int y = index / cols;
        env[y][x] = arrayBuffer[index];
    }
    delete[] arrayBuffer;
}

void printPath(Env env, NodeList* solution, int rows, int cols) {

    int x, y;
    int index, limit;

    limit = solution->getLength();
    for (index = 1; index < limit; index++) {
        NodePtr nodeA, nodeB;
        nodeA = solution->get(index - 1);
        nodeB = solution->get(index - 0);

        int distanceX, distanceY;
        distanceX = nodeA->getCol() - nodeB->getCol();
        distanceY = nodeA->getRow() - nodeB->getRow();

        x = nodeA->getCol();
        y = nodeA->getRow();

        // Y-axis
        if (distanceX == 0) {
            if (distanceY > 0) {
                env[y][x] = '^';
            }
            if (distanceY < 0) {
                env[y][x] = 'v';
            }
        }

        // X-axis
        if (distanceY == 0) {
            if (distanceX < 0) {
                env[y][x] = '>';
            }
            if (distanceX > 0) {
                env[y][x] = '<';
            }
        }

    }

    NodePtr nodeS = solution->get(0);
    x = nodeS->getCol();
    y = nodeS->getRow();
    env[y][x] = SYMBOL_START;

    index = 0;
    limit = rows * cols;

    bool repeatLoop = true;
    while (repeatLoop) {

        x = index % cols;
        y = index / cols;

        // outputs single character
        char character = env[y][x];
        std::cout << character;

        index++;

        // end of row found
        if (index % cols == 0) {
            std::cout << std::endl;
        }
        // all characters reached output
        repeatLoop = index < limit;
    }
    
}

void printReachablePositions(Env env, NodeList* reachablePositions){
    //TODO
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "NodeList:" << std::endl;

    int limit = nodeList->getLength();
    for (int index = 0; index < limit; index++) {

        Node* node = nodeList->get(index);
        std::cout << node->getRow() << ",";
        std::cout << node->getCol() << ",";
        std::cout << node->getDistanceToS() << std::endl;
    }

}