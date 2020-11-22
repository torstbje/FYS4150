#include "Node.hpp"

using namespace std;

Lattice::Lattice(int L){
  //srand(1);                             //seed
  dim = L;
  setupLattice();
}

void Lattice::setupLattice(){

  Node eastNode;

  firstNode = Node();

  Node& thisNode = firstNode;

  for (int i = 0; i < dim - 1; i++){
    /*
    Sets up the first row of nodes
    */
    eastNode = Node();

    eastNode.setWest(thisNode);
    thisNode.setEast(eastNode);
    Node& thisNode = eastNode;            //One step eastward in the lattice
  }


  firstNode.setWest(eastNode);         //Closes the loop by connecting the edges

  thisNode.setEast(firstNode);

  Node& northNode = firstNode;

  thisNode = Node();
  for (int j = 0;j < dim-1;j++){
    /*Loops over all rows, this part is not written yet*/
    for (int i = 0; i < dim - 1; i++){
      /*Loops over a new row, and pairs it up with the row north of it*/
      eastNode = Node();
      northNode.setSouth(thisNode);
      eastNode.setWest(thisNode);
      thisNode.setNorth(northNode);
      thisNode.setEast(eastNode);

      Node tempNode = northNode.eastNode();
      Node& northNode = tempNode;
      Node& thisNode = eastNode;
    }
  }
}
