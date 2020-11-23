#include "Node.hpp"
using namespace std;

Traverser::Traverser(Node* aNode){
  currentNode = aNode;
}
void Traverser::goEast(){
  currentNode = (*currentNode).eastNode();
}
void Traverser::goSouth(){
  currentNode = (*currentNode).southNode();
}
Node* Traverser::whatNode(){
  return currentNode;
}
