#include "Solar.hpp"
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;

void f1(Planet, Planet[],int);
void f2(Planet, Planet[],int);
int main(int argc, char const *argv[]){

  vec rE(2), vE(2), rS(2), vS(2);

  rE(0) = 1;
  rE(1) = 0;

  double massEarth = 6e24;
  double massSun = 2e30;
  double g = 6.674e-11;
  vE(0) = 0;
  vE(1) = sqrt(g*massSun);
  rS(0) = 0; rS(1) = 0; vS(0) = 0; vS(1) = 0;

  Planet earth("Earth", rE, vE, massEarth, f2);
  Planet sun("Sun", rS, vS, massSun, f1);
}

void f1(Planet thisPlanet, Planet celestialBodies[], int nPlanets){
  return;
}

void f2(Planet thisPlanet, Planet* celestialBodies, int nBodies, vec& acc){
  for (int i = 0; i < acc.n_rows; i++){
    acc(i) = 0;
  }
  string thisName = thisPlanet.getName();
  vec r = thisPlanet.getPos();
  double mass;
  vec pos;
  string name;
  for (int i = 0; i < nBodies; i++){
    name = celestialBodies[i].getName();
    if (name != thisName){
      mass = celestialBodies[i].getMass();
      pos = celestialBodies[i].getPos();
      acc += (pos-r)*mass/pow(abs(pos-r),3);
    }
  }
}
