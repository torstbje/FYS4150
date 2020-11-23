#include <iostream>
#include "Node.hpp"
#include "Node.cpp"
#include "Lattice.cpp"
#include "Traverser.cpp"

using namespace std;

int main(int argc, char const *argv[]){
  (void) argc,argv;

  int l = 4;
  Lattice grid(l);
  grid.monteCarloCycle();

  return 1;
}
