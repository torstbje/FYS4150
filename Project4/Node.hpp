#ifndef NODE_hpp
#define NODE_hpp

class Node{
public:
  Node();

  int getValue();
  void changeValue();
  int getDeltaEnergy();

  void setNorth(Node);
  void setEast(Node);
  void setWest(Node);
  void setSouth(Node);
  Node northNode();
  Node eastNode();
  Node southNode();
  Node westNode();

  int nNeighbors();

private:
  Node *north,*east,*south,*west;

  int value;
};

class Lattice{
public:
  Lattice(int);
  double getEnergy();

private:
  int dim;
  Node firstNode;
  void setupLattice();

};


#endif
