#include "Solar.hpp"
#include "CelBody.cpp"
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;


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

  CelBody earth("Earth", rE, vE, massEarth);
  CelBody sun("Sun", rS, vS, massSun, false);

  return 0;
}
