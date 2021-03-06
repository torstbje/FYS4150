#include "Node.hpp"
#include <tgmath.h>

using namespace std;
using namespace arma;
Lattice::Lattice(int L,string initState,double temp){


  srand(2);                             //seed
  dim = L;
  energyProb = vec(pow(dim,2)+1);
  if (initState == "alligned"){
    energy = pow(dim,2)*2;
    magnetization = pow(dim,2);
  }

  beta = 1.0/temp;
  w1 = exp(-4*beta);
  w2 = exp(-8*beta);

  Node* nodes[dim][dim];


  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      nodes[i][j] = new Node(initState);
    }
  }

  for (int i = 0; i < dim; i++){
    /*Connects the boundary nodes*/

    /*Connects top row with bottom row*/
    (*nodes[0][i]).setNorth(nodes[dim-1][i]);
    (*nodes[dim-1][i]).setSouth(nodes[0][i]);

    /*Connects left column with right column*/
    (*nodes[i][0]).setWest(nodes[i][dim-1]);
    (*nodes[i][dim-1]).setEast(nodes[i][0]);

  }

  for (int i = 0; i < dim - 1; i++){

    for (int j = 0; j < dim -1; j++){
      /*Connects all the other nodes*/
      (*nodes[i][j]).setEast(nodes[i][j+1]);
      (*nodes[i][j+1]).setWest(nodes[i][j]);


      (*nodes[i][j]).setSouth(nodes[i+1][j]);
      (*nodes[i+1][j]).setNorth(nodes[i][j]);


      /*Collects the initial energy*/

    }
    /*connects right column with itself, and bottow row with itself*/
    (*nodes[i][dim-1]).setSouth(nodes[i+1][dim-1]);
    (*nodes[i+1][dim-1]).setNorth(nodes[i][dim-1]);

    (*nodes[dim-1][i]).setEast(nodes[dim-1][i+1]);
    (*nodes[dim-1][i+1]).setWest(nodes[dim-1][i]);

  }
  energy *= -1;
  fNode = nodes[0][0];

}
void Lattice::writeCoords(){
  Traverser pos(fNode);
  ofstream file;
  file.open("ValueGrid.txt");
  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      Node*thisNode = pos.whatNode();
      file << (*thisNode).getValue() << " ";
      pos.goEast();
    }
    file << endl;
    pos.goSouth();
  }
  file.close();
}

void Lattice::monteCarloCycle(){
  int deltaE;
  nAccepted = 0;
  aveE = 0; aveM = 0; aveESQ = 0; aveMSQ = 0; absM = 0;
  Traverser pos(fNode);

  for (int i = 0; i < dim; i++){
    /*Loops over all rows*/
    for (int j= 0; j < dim; j++){
      /*Potentially changes energy for all spins in a row*/
      Node* thisNode = pos.whatNode();
      deltaE = (*thisNode).getDeltaEnergy();        //units of J
      if (deltaE <= 0){
        energyChange(thisNode,deltaE);
      }
      else if (deltaE == 4){
        double r = (double)rand()/RAND_MAX;
        if (r < w1){
          energyChange(thisNode,deltaE);
        }
      }
      else if (deltaE == 8){
        double r = (double)rand()/RAND_MAX;
        if (r < w2){
          energyChange(thisNode,deltaE);
        }
      }

      /*Updates average values*/

      aveE += energy/((double)pow(dim,2));
      aveESQ += pow(energy,2)/((double)pow(dim,2));
      aveM += magnetization/((double)pow(dim,2));
      aveMSQ += pow(magnetization,2)/((double)pow(dim,2));
      absM += abs(magnetization)/((double)pow(dim,2));
      aveChi += (pow(magnetization,2) - pow(abs(magnetization),2))/(pow(dim,2))*beta;
      aveC += (pow(energy,2) - pow(abs(energy),2))/(pow(dim,2))*pow(beta,2);

      pos.goEast();
    }
    pos.goSouth();
  }

  //double norm = dim*dim;

}
void Lattice::energyChange(Node* aNode, int dE){
  /*Is called whenever a spin is flipped*/
  (*aNode).changeValue();
  energy += dE;
  magnetization += 2*(*aNode).getValue();
  nAccepted++;
  energyProb((energy+2*pow(dim,2))/4)++;

}
double Lattice::getAveE(){
  return aveE;
}
double Lattice::getAveESQ(){
  return aveESQ;
}
double Lattice::getAveM(){
  return aveM;
}
double Lattice::getAveMSQ(){
  return aveMSQ;
}
double Lattice::getAbsM(){
  return absM;
}
double Lattice::getChi(){
  return aveChi;
}
double Lattice:: getC(){
  return aveC;
}

vec Lattice::getEnergyProbabilities(){
  return energyProb;
}

double Lattice::getEnergy(){
  return energy;
}
double Lattice::getMagnetization(){
  return magnetization;
}
int Lattice::acceptence(){
  return nAccepted;
}
