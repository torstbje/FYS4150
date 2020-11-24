#ifndef NODE_hpp
#define NODE_hpp

class Node{
public:
  Node(string);

  int getValue();
  void changeValue();
  int getDeltaEnergy();

  void setNorth(Node*);
  void setEast(Node*);
  void setWest(Node*);
  void setSouth(Node*);
  Node* northNode();
  Node* eastNode();
  Node* southNode();
  Node* westNode();

  int nNeighbors();

private:
  Node *north, *east, *south, *west;

  int value;
};

class Lattice{
public:
  Lattice(int,string);
  double getEnergy();
  void monteCarloCycle();
  void writeCoords();

private:
  int dim;
  Node* fNode;       //first node
  double energy = 0, magnetization = 0;
  double jj,w1,w2;
};

class Traverser{
public:
  Traverser(Node*);
  void goEast();
  void goSouth();
  Node* whatNode();

private:
  Node *currentNode;
};


#endif
