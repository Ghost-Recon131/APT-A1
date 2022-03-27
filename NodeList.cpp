
#include "NodeList.h"
#include <iostream>


// Set all nodes in array to nullPtr then set length to 0
NodeList::NodeList(){

    for (auto & node : nodes){
        node = nullptr;
    }

    this->length = 0;
}


NodeList::~NodeList(){
    for (int i = 0; i < this->length; i++) {
        delete nodes[i];
    }
}

// Produces a DEEP COPY of the NodeList then change remaining nodes to nullPtr
NodeList::NodeList(NodeList& other){

    for (auto & node : nodes){
        node = nullptr;
    }

    length = other.length;

    for (int i = 0; i < length; ++i){
        nodes[i] = new Node(*other.nodes[i]);
    }
}


int NodeList::getLength(){
   return length;
}

// Get a pointer to the ith node in the node list, nullptr if none found
NodePtr NodeList::get(int i){
    Node* ithNodePtr = nullptr;
    if (i >= 0 && i < length){
        ithNodePtr = nodes[i];
    }
    return ithNodePtr;
}

void NodeList::addBack(NodePtr newNode){
   
}

bool NodeList::containsNode(NodePtr node){
   
}

void NodeList::clear(){
   
}