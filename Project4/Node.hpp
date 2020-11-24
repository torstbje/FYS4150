#ifndef NODE_hpp
#define NODE_hpp
#include <armadillo>

using namespace std;
using namespace arma;

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
<<<<<<< HEAD
  Lattice(int,string);
=======
  Lattice(int,string,double);
>>>>>>> b393b70c695f8e791c4f7f560daec4f7f45a7ad0
  double getEnergy();
  double getMagnetization();
  int acceptence();
  vec getEnergyProbabilities();
  void monteCarloCycle();
  void writeCoords();

  void energyChange(Node*,int);

private:
  vec energyProb;
  int dim, nAccepted = 0;
  Node* fNode;       //first node
<<<<<<< HEAD
  double energy = 0, magnetization = 0;
  double jj,w1,w2;
=======
  double energy = 0,magnetization = 0;
  double jj,w1,w2,beta;

>>>>>>> b393b70c695f8e791c4f7f560daec4f7f45a7ad0
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
