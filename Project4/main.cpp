#include <iostream>
#include <fstream>
#include "Node.hpp"
#include "Node.cpp"
#include "Lattice.cpp"
#include "Traverser.cpp"

using namespace std;

int main(int argc, char const *argv[]){
  (void) argc,argv;

  int l = 8;
  Lattice grid(l);
  grid.monteCarloCycle();
  grid.writeCoords();

  return 1;
}
