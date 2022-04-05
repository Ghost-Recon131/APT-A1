
#include "NodeList.h"
#include <iostream>

#define BLOCK_SIZE (16)

NodeList::NodeList() {

    this->count = 0;
    this->length = BLOCK_SIZE;
    this->nodes = new Node*[this->length];

}

NodeList::~NodeList() {
    this->clear();
}

NodeList::NodeList(NodeList& other) {

    this->nodes = new Node*[other.length];

    for (int index = 0; index < other.count; index++) {

        NodePtr original = other.nodes[index];
        NodePtr copy = new Node(
            original->getRow(),
            original->getCol(),
            original->getDistanceToS()
        );

        this->nodes[index] = copy;

    }

    this->count = other.count;
    this->length = other.length;
    
}


int NodeList::getLength() {
    return this->count;
}


NodePtr NodeList::get(int i) {

    // checks for outside of bounds
    Node* ithNodePtr = nullptr;
    if (i >= 0 && i < length){
        ithNodePtr = nodes[i];
    }
    return ithNodePtr;
}

void NodeList::addBack(NodePtr newNode) {

    // array is full, resize it
    if (this->length == this->count) {

        this->length += BLOCK_SIZE;

        Node** nodesOld = this->nodes;
        Node** nodesNew = new Node*[this->length];
        for (int index = 0; index < this->count; index++) {
            nodesNew[index] = nodesOld[index];
        }

        this->nodes = nodesNew;
        delete nodesOld;
    }

    this->nodes[this->count] = newNode;
    this->count++;
}

bool NodeList::containsNode(NodePtr nodeA) {
    bool containsNode = false;

    for (int index = 0; index < this->count; index++) {

        NodePtr nodeB = this->nodes[index];

        bool testA = nodeA->getRow() == nodeB->getRow();
        bool testB = nodeA->getCol() == nodeB->getCol();

        if (testA && testB) {
            containsNode = true;
        }
    }
    return containsNode;

}

void NodeList::clear() {
    for (int index = 0; index < this->count; index++) {
        delete this->nodes[index];

    }
    this->length = 0;
}

NodePtr NodeList::find(int row, int col) {
    int limit = this->getLength();

    // Return nullptr if node is not found
    NodePtr foundnode = nullptr;
    for (int index = 0; index < limit; index++) {
        NodePtr node = this->nodes[index];
        if (node->getRow() == row && node->getCol() == col) {
            foundnode = node;
        }
    }
    return foundnode;
}


NodePtr NodeList::remove(int index) {
    NodePtr removed;

    if (index >= this->count) {
        removed = nullptr;
    }else{
        removed = this->nodes[index];
    }

    this->count--;
    this->nodes[index] = this->nodes[this->count];

    return removed;
}

void NodeList::reverse() {
    int indexA = 0;
    int indexB = this->count;

    while (indexA < indexB) {
        indexB--;

        NodePtr nodeA, nodeB;
        nodeA = this->nodes[indexA];
        nodeB = this->nodes[indexB];
        this->nodes[indexA] = nodeB;
        this->nodes[indexB] = nodeA;
        indexA++;
    }

}

void NodeList::release() {
    this->count = 0;
}

