#include <iostream>
#include <fstream>
#include "Node.hpp"
#include "Node.cpp"
#include "Lattice.cpp"
#include "Traverser.cpp"

using namespace std;

int main(int argc, char const *argv[]){
  //(void) argc,argv;

  int l = 300;
  int n_cycles = 10000;
  Lattice grid(l);
  for (int i = 0; i<n_cycles; i++){
    grid.monteCarloCycle();
  }

  grid.writeCoords();

  return 1;
}
