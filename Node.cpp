
#include "Node.h"


Node::Node(int row, int col, int distanceToS) {
   this->row = row;
   this->col = col;
   this->distanceToS = distanceToS;
}
    
Node::~Node(){
   // Intentionally empty
}

// Added as part of M4 implementation
Node::Node(Node* node) {
   this->row = node->row;
   this->col = node->col;
   this->distanceToS = node->distanceToS;
}

int Node::getRow() {
   return this->row;
}

int Node::getCol() {
   return this->col;
}

int Node::getDistanceToS() {
   return this->distanceToS;
}

void Node::setDistanceToS(int distanceToS){
   this->distanceToS = distanceToS;
}
