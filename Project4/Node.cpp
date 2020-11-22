#include "Node.hpp"
using namespace std;

Node::Node(){
  value = (rand() % 2)*2 - 1;       //randomly chooses either -1, or 1
  north = east = west = south = nullptr;
}

int Node::nNeighbors(){
  int s = 0;
  if (north){
    s++;
  }
  if (east){
    s++;
  }
  if (south){
    s++;
  }
  if (west){
    s++;
  }
  return s;
}


int Node::getValue(){
  return value;
}
void Node::changeValue(){
  value *= -1;                      //switches the sign
}
void Node::setNorth(Node aNode){
  north = &aNode;

}
void Node::setEast(Node aNode){
  east = &aNode;

}
void Node::setSouth(Node aNode){
  south = &aNode;
}
void Node::setWest(Node aNode){
  west = &aNode;
}

Node Node::northNode(){
  return *north;
}
Node Node::eastNode(){
  if (east){

    return *east;
  }
  cout << "error\n";
  return *this;
}
Node Node::southNode(){
  return *south;
}
Node Node::westNode(){
  return *west;
}


int Node::getDeltaEnergy(){
  int delta = 2*value*(north -> getValue() + east->getValue() + south->getValue() + west->getValue());  //units of J
}
