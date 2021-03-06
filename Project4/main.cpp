#include <iostream>
#include <fstream>
#include "Node.hpp"
#include "Node.cpp"
#include "Lattice.cpp"
#include "Traverser.cpp"

using namespace std;

int main(int argc, char const *argv[]){

  int l = stoi(argv[1]);
  double temperature = stod(argv[2]);
  int n_cycles = stoi(argv[3]);
  string state = argv[4];
  Lattice grid(l,state,temperature);

  ofstream file("energy_magnetization.txt");
  ofstream meanFile("meanvalues.txt");

  for (int i = 0; i < n_cycles; i++){

    file << i << " " << grid.getEnergy() << " " << abs(grid.getMagnetization()) << " "<< grid.acceptence();
    file << " " << pow(grid.getEnergy(),2) << " " << pow(grid.getMagnetization(),2) << endl;
    grid.monteCarloCycle();
  }

  meanFile << grid.getAveE() << " " << grid.getChi() << " " << grid.getC() << " ";
  meanFile << grid.getAveMSQ() << " "<< grid.getAbsM() << endl;

  meanFile.close();
  file.close();




  vec probs = grid.getEnergyProbabilities();
  ofstream probFile("energy_probabilities.txt");
  int precalcPow = -pow(l,2);
  for (int i = 0; i < pow(l,2) + 1; i++){
    probFile << precalcPow + 4*i << " " << probs(i) << endl;
  }
  probFile.close();

  grid.writeCoords();

  return 1;
}
