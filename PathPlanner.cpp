
#include "PathPlanner.h"
#include "milestone4.h"

#include <iostream>


PathPlanner::PathPlanner(Env env, int lengthY, int lengthX) {

    this->env = make_env(lengthY, lengthX);

    this->lengthX = lengthX;
    this->lengthY = lengthY;

    for (int x = 0; x < lengthX; x++) {
        for (int y = 0; y < lengthY; y++) {
            this->env[y][x] = env[y][x];
            if (env[y][x] == SYMBOL_START) {
                this->initialPosition(y, x);
            }
        }
    }

}

PathPlanner::~PathPlanner() {
    delete_env(this->env, this->lengthY, this->lengthX);
}

void PathPlanner::initialPosition(int startY, int startX) {
    this->startX = startX;
    this->startY = startY;
}

NodeList* PathPlanner::getReachableNodes() {

    // list reachableNodes (O in pseudocode) of nodes that the robot can reach
    NodeList* reachableNodes = new NodeList();

    // list closedList (C in pseudocode) of nodes
    NodeList* closedList = new NodeList();

    // Make variable startNode and point to start node
    NodePtr startNode = new Node(this->startY, this->startX, 0);
    reachableNodes->addBack(startNode);

    // repeat
    bool repeatLoop = true;
    while (repeatLoop) {

        int x = startNode->getCol();
        int y = startNode->getRow();

        // when picking nodeQ, use this order relative to startNode: up, right, down, left
        const int offsets[4][2] = {
            {  0, -1 },
            { +1,  0 },
            {  0, +1 },
            { -1,  0 }
        };

        // for each node q that the robot can reach from startNode
        for (int index = 0; index < 4; index++) {
            int offsetX = offsets[index][0];
            int offsetY = offsets[index][1];
            int qX = x + offsetX;
            int qY = y + offsetY;

            bool testA = qX >= 0 && qY >= 0;
            bool testB = qX < this->lengthX && qY < this->lengthY;

            // only consider points inside boundaries
            if (testA && testB) {
                char character = this->env[qY][qX];

                // only consider empty spaces and the goal
                if (character == SYMBOL_EMPTY || character == SYMBOL_GOAL) {

                    // sets the distanceToS of nodeQ to be one more that of startNode
                    NodePtr nodeQ = new Node(qY, qX, startNode->getDistanceToS() + 1);

                    // add nodeQ to reachableNodes if and only if it's not contained
                    if (!reachableNodes->containsNode(nodeQ)) {
                        reachableNodes->addBack(nodeQ);
                    } else {
                        delete nodeQ;
                    }
                }
            }

        }

        // add "startNode" to list "closedList".
        closedList->addBack(startNode);

        bool nextFound = false;
        int limit = reachableNodes->getLength();

        // select a node "startNode" from the list "reachableNodes" that is NOT in the list "closedList"
        for (int index = 0; index < limit && !nextFound; index++) {

            startNode = reachableNodes->get(index);

            if (!closedList->containsNode(startNode)) {
                nextFound = true;
            }
        }

        // until no such position "startNode" can be found
        repeatLoop = nextFound;
    }

    closedList->release();
    delete closedList;
    return reachableNodes;

}

NodeList* PathPlanner::getPath() {
    int goalX = (-1);
    int goalY = (-1);

    for (int x = 0; x < this->lengthX; x++) {
        for (int y = 0; y < this->lengthY; y++) {
            if (this->env[y][x] == SYMBOL_GOAL) {
                goalX = x;
                goalY = y;
                x = this->lengthX;
                y = this->lengthY;
            }
        }
    }

    NodeList* reachables = this->getReachableNodes();
    NodeList* solution = new NodeList();

    NodePtr node = reachables->find(goalY, goalX);
    solution->addBack(new Node(node));

    // backtrack from the goal back to the start
    bool repeatLoop = true;
    while (repeatLoop) {

        int x = node->getCol();
        int y = node->getRow();

        const int offsets[4][2] = {
            {  0, -1 }, // up
            { +1,  0 }, // right
            {  0, +1 }, // down
            { -1,  0 }  // left
        };

        NodePtr next = node;

        for (int index = 0; index < 4; index++) {
            int offsetX = offsets[index][0];
            int offsetY = offsets[index][1];
            int otherX = x + offsetX;
            int otherY = y + offsetY;

            NodePtr other = reachables->find(otherY, otherX);
            if (other != nullptr) {
                int distanceNext = next->getDistanceToS();
                int distanceOther = other->getDistanceToS();
                if (distanceOther < distanceNext) {
                    next = other;
                }
            }
        }
        node = next;
        next = new Node(next);
        solution->addBack(next);

        // no more places to go
        repeatLoop = next->getDistanceToS() != 0;
    }

    // reverses the list, so that it walks from the start to the goal
    solution->reverse();

    delete reachables;
    return solution;
}

