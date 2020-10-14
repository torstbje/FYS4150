#include "Solar.hpp"
#include "CelBody.cpp"
#include "MultiBodySystem.cpp"
#include <fstream>
#include <armadillo>


using namespace std;
using namespace arma;


int main(int argc, char const *argv[]){

  string version = "earthStatSun";

  if (version == "earthStatSun"){
    ifstream inFile("initial_conditions");
    string line, name;
    double mass, x, y, z, vx, vy, vz;
    int n_bodies = 2;
    CelBody earth, sun;

    getline(inFile,line);
    while(getline(inFile,line)){
      istringstream iss(line);
      iss >> name;

      if (name == "earth"){
        iss >> mass >> x >> y >> z >> vx >> vy >> vz;
        vec r {x,y,z};
        vec v {vx,vy,vz};
        earth = CelBody(name,r,v,mass);
      }
      if (name == "sun"){
        iss >> mass;
        vec r{0,0,0};
        vec v{0,0,0};
        sun = CelBody(name,r,v,mass,false);   //Stationary sun
      }
    }
    inFile.close();
    CelBody bodies[2];
    bodies[0] = earth;
    bodies[1] = sun;
    MultiBodySystem solarSystem(n_bodies,bodies);
  }


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
