
#include "Node.hpp"
#include <tgmath.h>

using namespace std;

Lattice::Lattice(int L){
  srand(3);                             //seed
  jj = 1.0;
  dim = L;

  double beta = 1.0/8;
  w1 = exp(-4*jj*beta);
  w2 = exp(-8*jj*beta);

  Node* nodes[dim][dim];



  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      nodes[i][j] = new Node();
    }
  }

  for (int i = 0; i < dim; i++){
    /*Connects the boundary nodes*/

    /*Connects top row with bottom row*/
    (*nodes[0][i]).setNorth(nodes[dim-1][i]);
    (*nodes[dim-1][i]).setSouth(nodes[0][i]);
    energy += (*nodes[0][i]).getValue()*(*nodes[dim-1][i]).getValue();

    /*Connects left column with right column*/
    (*nodes[i][0]).setWest(nodes[i][dim-1]);
    (*nodes[i][dim-1]).setEast(nodes[i][0]);
    energy += (*nodes[i][0]).getValue()*(*nodes[i][dim-1]).getValue();

  }

  for (int i = 0; i < dim - 1; i++){

    for (int j = 0; j < dim -1; j++){
      /*Connects all the other nodes*/
      (*nodes[i][j]).setEast(nodes[i][j+1]);
      (*nodes[i][j+1]).setWest(nodes[i][j]);
      energy += (*nodes[i][j]).getValue()*(*nodes[i][j+1]).getValue();

      (*nodes[i][j]).setSouth(nodes[i+1][j]);
      (*nodes[i+1][j]).setNorth(nodes[i][j]);
      energy += (*nodes[i][j]).getValue()*(*nodes[i+1][j]).getValue();

      /*Collects the initial energy*/

    }
    /*connects right column with itself, and bottow row with itself*/
    (*nodes[i][dim-1]).setSouth(nodes[i+1][dim-1]);
    (*nodes[i+1][dim-1]).setNorth(nodes[i][dim-1]);
    energy += (*nodes[i][dim-1]).getValue()*(*nodes[i+1][dim-1]).getValue();

    (*nodes[dim-1][i]).setEast(nodes[dim-1][i+1]);
    (*nodes[dim-1][i+1]).setWest(nodes[dim-1][i]);
    energy += (*nodes[dim-1][i]).getValue()*(*nodes[dim-1][i+1]).getValue();

  }
  energy *= -jj;
  fNode = nodes[0][0];

}
void Lattice::writeCoords(){
  Traverser pos(fNode);
  ofstream file;
  file.open("ValueGrid.txt");
  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      Node*thisNode = pos.whatNode();
      cout << (*thisNode).getValue() << endl;
      file << i << " " << j << " " << (*thisNode).getValue() << endl;
      pos.goEast();
    }
    pos.goSouth();
  }
  file.close();
}

void Lattice::monteCarloCycle(){
  int deltaE;

  Traverser pos(fNode);

  for (int i = 0; i < dim; i++){
    /*Loops over all rows*/
    for (int j= 0; j < dim; j++){
      /*Potentially changes energy for all spins in a row*/
      Node* thisNode = pos.whatNode();
      deltaE = (*thisNode).getDeltaEnergy();        //units of J
      if (deltaE <= 0){
        (*thisNode).changeValue();
        energy += deltaE*jj;
      }
      else if (deltaE == 4){
        double r = (double)rand()/RAND_MAX;
        if (r < w1){
          (*thisNode).changeValue();
          energy += deltaE*jj;
        }
      }
      else if (deltaE == 8){
        double r = (double)rand()/RAND_MAX;
        if (r < w2){
          (*thisNode).changeValue();
          energy += deltaE*jj;
        }
      }
      pos.goEast();
    }
    pos.goSouth();
    cout << "test\n";
  }

}

double Lattice::getEnergy(){
  return energy;
}
