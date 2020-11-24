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

  Lattice(int,string);
  Lattice(int,string,double);
  double getEnergy();
  double getMagnetization();
  double getAveE();
  double getAveESQ();
  double getAveM();
  double getAveMSQ();
  double getAbsM();
  int acceptence();
  vec getEnergyProbabilities();
  void monteCarloCycle();
  void writeCoords();

  void energyChange(Node*,int);

private:
  vec energyProb;
  int aveE = 0, aveM = 0, aveESQ = 0, aveMSQ = 0, absM = 0;
  int dim, nAccepted = 0;
  Node* fNode;       //first node

  double energy = 0, magnetization = 0;
  double jj,w1,w2;

  double energy = 0,magnetization = 0;
  double w1,w2,beta;

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
